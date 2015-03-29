#include "Group.h"

enum SPELL_DEBUFF
{
    DEBUFF_SATED     = 57724,
    DEBUG_EXHAUSTION = 57723,
};

void remove_debuff_and_cooldown(Player* player)
{
    uint32 remove_debuff_spell[3] =
    {
        DEBUFF_SATED,
        DEBUG_EXHAUSTION
    };

    for (uint32 i = 0; i < sizeof(remove_debuff_spell) / sizeof(uint32); i++)
        if (player->HasAura(remove_debuff_spell[i]))
            player->RemoveAura(remove_debuff_spell[i]);

    player->RemoveAllSpellCooldown();
}

void PlayerIsInGroup(Player* player)
{
    Group * group = player->GetGroup();

    Group::MemberSlotList const &members = group->GetMemberSlots();
    for (Group::MemberSlotList::const_iterator itr = members.begin(); itr != members.end(); ++itr)
    {
        Group::MemberSlot const &slot = *itr;
        Player* player = ObjectAccessor::FindPlayer((*itr).guid);
        if (player && player->GetSession())
            remove_debuff_and_cooldown(player);
    }
}

bool IsInDungeonOrRaid(Player* player)
{
    if (sMapStore.LookupEntry(player->GetMap()->Instanceable()))
        return true;
    return false;
}

class CD : public PlayerScript
{
    public:
        CD() : PlayerScript("CD") {}

        void OnCreatureKill(Player* player, Creature* boss)
        {
            if ((IsInDungeonOrRaid(player)) && (boss->isWorldBoss() || boss->IsDungeonBoss()))
            {
                if (player->GetGroup())
                    PlayerIsInGroup(player);
                else
                    remove_debuff_and_cooldown(player);
            }
        }
};

void AddSC_CD()
{
    new CD();
}