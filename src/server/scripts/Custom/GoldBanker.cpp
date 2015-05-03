/*######################-> [[GOLD BANKER ]] <-#########################
**************************! DEV: ak47sigh !****************************
#######################################################################*/
#include "ScriptPCH.h"
#include <cstring>
#include "Chat.h"

// -- [[ Configs:
uint32 maxPlayerDeposits = 3;\
uint32 minDepositNameLenght = 5;
uint32 createDepositCost = 100000;		// default 10 gold per deposit
uint32 createDepositPlus = 50000;		// increase the cost by X gold for each new repository
uint32 maxDepositAmount = 2000000000;	// recommended not to pass this value 2 000 000 000

// -- [[ DO NOT EDIT BELLOW // --
#define MENIU(a, b, c, d)						PlayerTalkClass->GetGossipMenu().AddMenuItem(-1, a, b, c, d, "", 0)
#define MENIU_EXTENDED(a, b, c, d, e, f, g)		PlayerTalkClass->GetGossipMenu().AddMenuItem(-1, a, b, c, d, e, f, g)
#define TRIMITE_MENIU(a, b)						PlayerTalkClass->SendGossipMenu(a, b)

struct DepositInfo
{
    uint64 editselectedid;
	uint64 depid;
	std::string depname;
};
static std::map<uint32, DepositInfo> editselectedid;

class gold_banker : public CreatureScript
{
public:
    gold_banker() : CreatureScript("Gold_Banker") { }
	// Deposit gold in the last selected deposit
	bool DepositGold(Player* player, Creature* creature, uint32 amount, uint32 deposit_id)
	{
		QueryResult depInfo = WorldDatabase.PQuery("SELECT * FROM `gold_bank_data` WHERE `depositGUID`='%u'", deposit_id);

		if(!depInfo)
		{
			ChatHandler(player->GetSession()).PSendSysMessage("ERR: You are trying to deposit into a non existing one!");
			ListPlayerDeposits(player, creature);
			return false;
		}

		Field * pField = depInfo->Fetch();

		if(amount + pField[2].GetUInt32() > maxDepositAmount)
		{
			ChatHandler(player->GetSession()).PSendSysMessage("ERR: Amount is to higher enough to pass '%u' of gold.", maxDepositAmount);
			ListPlayerDeposits(player, creature);
			return false;
		}

		if(amount > player->GetMoney()/10000)
		{
			ChatHandler(player->GetSession()).PSendSysMessage("ERR: You dont have the amount inserted.");
			ListPlayerDeposits(player, creature);
			return false;
		}

		if(amount <= 0)
		{
			ChatHandler(player->GetSession()).PSendSysMessage("ERR: Invalid amount to deposit.");
			ListPlayerDeposits(player, creature);
			return false;
		}

		WorldDatabase.PExecute("UPDATE `gold_bank_data` SET `depGold`=`depGold`+'%u' WHERE `depositGUID`='%u'", amount, deposit_id);
		player->ModifyMoney(-amount*10000, false);
		ChatHandler(player->GetSession()).PSendSysMessage("Deposit [\'%u\'][%s] loaded with a plus of \'%u\' gold.", deposit_id, editselectedid[player->GetGUID()].depname.c_str(), amount);
		player->PlayerTalkClass->SendCloseGossip();

		return true;
	}
	// Withdraw gold from the last deposit selected
	bool WithdrawGold(Player* player, Creature* creature, uint32 amount, uint32 deposit_id)
	{
		QueryResult depInfo = WorldDatabase.PQuery("SELECT * FROM `gold_bank_data` WHERE `depositGUID`='%u'", deposit_id);

		if(!depInfo)
		{
			ChatHandler(player->GetSession()).PSendSysMessage("ERR: You are trying to withdraw from a non existing deposit!");
			ListPlayerDeposits(player, creature);
			return false;
		}

		Field * pField = depInfo->Fetch();

		if(amount > pField[2].GetUInt32())
		{
			ChatHandler(player->GetSession()).PSendSysMessage("ERR: You can't withdraw more than you don't have!", maxDepositAmount);
			ListPlayerDeposits(player, creature);
			return false;
		}

		if(amount <= 0)
		{
			ChatHandler(player->GetSession()).PSendSysMessage("ERR: Invalid amount to withdraw.");
			ListPlayerDeposits(player, creature);
			return false;
		}

		WorldDatabase.PExecute("UPDATE `gold_bank_data` SET `depGold`=`depGold`-'%u' WHERE `depositGUID`='%u'", amount, deposit_id);
		player->ModifyMoney(amount*10000, false);

		if(amount == pField[2].GetUInt32())
			ChatHandler(player->GetSession()).PSendSysMessage("Deposit [\'%u\'][%s] drawn all \'%u\' gold.", deposit_id, editselectedid[player->GetGUID()].depname.c_str(), amount);
		else
			ChatHandler(player->GetSession()).PSendSysMessage("Deposit [\'%u\'][%s] drawn an amount of \'%u\' gold.", deposit_id, editselectedid[player->GetGUID()].depname.c_str(), amount);

		player->PlayerTalkClass->SendCloseGossip();

		return true;
	}
	// Rename the last selected deposit
	bool RenameDeposit(Player* player, Creature* creature, const char* deposit_name)
	{
		QueryResult depInfo = WorldDatabase.PQuery("SELECT * FROM `gold_bank_data` WHERE `depositGUID`='%u'", editselectedid[player->GetGUID()].depid);

		if(!depInfo)
		{
			ChatHandler(player->GetSession()).PSendSysMessage("ERR: You are trying to rename a non existing deposit!");
			ListPlayerDeposits(player, creature);
			return false;
		}

		std::string depnamepreview = deposit_name;

		if(depnamepreview.length() < minDepositNameLenght)
		{
			ChatHandler(player->GetSession()).PSendSysMessage("ERR: Invalid string length, minimum %u characters required.", minDepositNameLenght);
			ListPlayerDeposits(player, creature);
			return false;
		}

		WorldDatabase.PExecute("UPDATE `gold_bank_data` SET `depName`='%s' WHERE `depositGUID`='%u'", deposit_name, editselectedid[player->GetGUID()].depid);
		ChatHandler(player->GetSession()).PSendSysMessage("Deposit renamed to \'%s\'.", deposit_name);
		player->PlayerTalkClass->SendCloseGossip();

		return true;
	}
	//Disband deposit
	bool DisbandDeposit(Player* player, Creature* creature, uint32 deposit_id)
	{
		QueryResult depInfo = WorldDatabase.PQuery("SELECT * FROM `gold_bank_data` WHERE `depositGUID`='%u'", deposit_id);

		if(!depInfo)
		{
			ChatHandler(player->GetSession()).PSendSysMessage("ERR: You are trying to disband a non existing deposit!");
			ListPlayerDeposits(player, creature);
			return false;
		}

		Field * pField = depInfo->Fetch();
		WorldDatabase.PExecute("DELETE FROM `gold_bank_data` WHERE `depositGUID`='%u'", deposit_id);
		ChatHandler(player->GetSession()).PSendSysMessage("Deposit disbanded.");
		player->PlayerTalkClass->SendCloseGossip();

		return true;
	}
	// Creates a deposit
	bool CreateDeposit(Player* player, Creature* creature)
	{
		QueryResult depResult = WorldDatabase.PQuery("SELECT * FROM `gold_bank_data` WHERE plrGUID = %u", player->GetGUID());

		uint32 deposits = 0;
		uint32 cost = createDepositCost;

		if(depResult)
		{
			deposits = depResult->GetRowCount();

			if(deposits > maxPlayerDeposits)
			{
				ChatHandler(player->GetSession()).PSendSysMessage("You already have the max deposits allowed.");
				return false;
			}
			Field * pField = depResult->Fetch();
		}

		if(deposits == 0)
		{
			cost = createDepositCost;
		}
		else
		{
			cost = createDepositCost + (deposits * createDepositPlus);
		}
	
		player->ModifyMoney(-cost, false);
		WorldDatabase.PExecute("INSERT INTO `gold_bank_data` (`plrGUID`, `depName`) VALUES (%u, 'Change my name')", player->GetGUID());
		ChatHandler(player->GetSession()).PSendSysMessage("Deposit created and ready to use, you can change it's name at anytime.");
		player->PlayerTalkClass->SendCloseGossip();

		return true;
	}
	// Opens a menu to edit the selected deposit
	void EditSelectedDeposit(Player* player, Creature* creature, uint32 uiAction)
	{
		player->PlayerTalkClass->ClearMenus();
		editselectedid[player->GetGUID()].depid = uiAction;
		QueryResult depInfo = WorldDatabase.PQuery("SELECT * FROM `gold_bank_data` WHERE `depositGUID`='%u'", editselectedid[player->GetGUID()].depid);

		player->MENIU(7, "|cff5C5C5C[Return]|r", GOSSIP_SENDER_MAIN, 1);
		if(depInfo)
		{
			Field * pField = depInfo->Fetch();
			editselectedid[player->GetGUID()].depname = pField[1].GetString().c_str();

			player->MENIU_EXTENDED(6, "Withdraw some gold", GOSSIP_SENDER_MAIN, 888, "How much gold would you like to|cffFF0000 withdraw|r?\n Press \"Accept\" button to insert", 0/*copper*/, true);
			player->MENIU_EXTENDED(6, "Deposit some gold", GOSSIP_SENDER_MAIN, 777, "How much gold would you like to|cFF00FF00 deposit|r?\n Press \"Accept\" button to insert", 0/*copper*/, true);
			player->MENIU_EXTENDED(8, "|cff9E00FFRename deposit|r", GOSSIP_SENDER_MAIN, 555, "|cffEBFF00Press \'Accept\' button to insert a name|r", 0/*copper*/, true);
			player->MENIU_EXTENDED(4, "|cffFF0000Disband deposit|r", GOSSIP_SENDER_MAIN, 888, "|cffEBFF00Are you sure about disbanding this deposit?\n |cFFFF0000Once disbanded cannot be recovered!|r", 0/*copper*/, false);
		}
		else // deposit no longer exists
		{
			player->MENIU(0, "|cffFF0000Deposit no longer exists or connection could not be established! Please contact a Game Master as soon as it's possible. Thank you|r", GOSSIP_SENDER_MAIN, 1);
		}
		player->PlayerTalkClass->SendGossipMenu(7777778, creature->GetGUID());
	}
	// Opens a list with the player's available deposits
	void ListPlayerDeposits(Player* pPlayer, Creature* pCreature, unsigned int start = 0)
	{ 
		pPlayer->PlayerTalkClass->ClearMenus();
		pPlayer->MENIU(0, "|cff5C5C5C[Return]|r", GOSSIP_SENDER_MAIN, 999);
		QueryResult depResult = WorldDatabase.PQuery("SELECT * FROM gold_bank_data WHERE plrGUID = %u", pPlayer->GetGUID());

		uint32 deposits = 0;

		if(depResult)
		{
			deposits = depResult->GetRowCount();
			int offset = 0;
			Field * pField = depResult->Fetch();
			bool ranOnce = false;
			for(unsigned int i = start; i < deposits; i++)
			{
				if(start != 0 && ranOnce == false)
				{
					for(int x = 0; x < start; x++)
					{
						depResult->NextRow();
					}
					ranOnce = true;
				}

				if(offset != maxPlayerDeposits) // max returns
				{
					std::ostringstream cString1, cString2;
					cString1 << pField[3].GetUInt32();
					cString2 << pField[2].GetUInt32();
					pPlayer->MENIU(GOSSIP_ICON_MONEY_BAG, "[Deposit |cffFFFFFF" + cString1.str() + "|r] \"|cff0055FF" + pField[1].GetString() + "|r\"\n |cff00ff00available|r " + cString2.str() + "|cffFF0000 gold|r", GOSSIP_SENDER_MAIN, pField[3].GetUInt32());
					offset++;
					depResult->NextRow();
				}
			}
			if(deposits < maxPlayerDeposits)
			{
				uint32 cost = createDepositCost;

				if(deposits == 0)
				{
					cost = createDepositCost;
				}
				else
				{
					cost = createDepositCost + (deposits * createDepositPlus);
					}
			
				pPlayer->MENIU_EXTENDED(GOSSIP_ICON_INTERACT_2, "[+] Create a new Deposit", GOSSIP_SENDER_MAIN, 0, "Would you like to create a new deposit?", cost, false);
			}
		}
		if(deposits == 0)
		{
			uint32 cost = createDepositCost;
			
			pPlayer->MENIU_EXTENDED(GOSSIP_ICON_INTERACT_2, "[+] Create a new Deposit", GOSSIP_SENDER_MAIN, 0, "Would you like to create a new deposit?", cost, false);
		}
		pPlayer->PlayerTalkClass->SendGossipMenu(7777778, pCreature->GetGUID());
	}
	// Main Gold Banker menu
    bool OnGossipHello(Player * player, Creature * creature)
    {
		player->PlayerTalkClass->ClearMenus();
		editselectedid[player->GetGUID()].depid = 0; // reset
		player->MENIU(8, "I want to check deposits", GOSSIP_SENDER_MAIN, 1);
		player->MENIU(2, "Maybe'..later", GOSSIP_SENDER_MAIN, 2);
		player->TRIMITE_MENIU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		return true;
    }
	// ..
    bool OnGossipSelect(Player * player, Creature * creature, uint32 sender, uint32 uiAction) 
    {
		switch(uiAction)
		{
			case 0:
				CreateDeposit(player, creature);
				break;
			case 1:
				ListPlayerDeposits(player, creature);
				break;
			case 2:
				player->PlayerTalkClass->SendCloseGossip();
				break;
			case 888:
				DisbandDeposit(player, creature, editselectedid[player->GetGUID()].depid);
				break;
			case 999:
				OnGossipHello(player, creature);
				break;
			default:
				if(uiAction != 999 || uiAction != 888 || uiAction != 1 || uiAction != 0 || uiAction != 2)
					EditSelectedDeposit(player, creature, uiAction);
				break;
		}
        return true;
    }
	// ..
    bool OnGossipSelectCode(Player* player, Creature* creature, uint32 sender, uint32 uiAction, const char* code)
    {
        uint32 codexx = uint32(atol(code)); 

		switch(uiAction)
		{
		case 555:
			RenameDeposit(player, creature, code);
			break;
		case 777:
			DepositGold(player, creature, codexx, editselectedid[player->GetGUID()].depid);
			break;
		case 888:
			WithdrawGold(player, creature, codexx, editselectedid[player->GetGUID()].depid);
			break;
		}
		return true;
    }
};
 
void AddSC_Gold_Banker()
{
    new gold_banker();
}