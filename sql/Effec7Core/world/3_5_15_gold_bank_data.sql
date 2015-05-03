-- Create gold banker NPC
SET @NPC_ID = 1000000; -- change it at any time
DELETE FROM `creature_template` WHERE `entry`=@NPC_ID;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES
(1000000, 0, 0, 0, 0, 0, 30417, 0, 0, 0, 'Moon Shader', 'Gold Banker', 'Pickup', 0, 80, 80, 2, 35, 35, 1, 1, 1.14286, 1, 3, 10, 10, 0, 0, 1, 1000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 10000, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 'Gold_Banker', 1);

-- Create gold bank data table
DROP TABLE IF EXISTS `gold_bank_data`;
CREATE TABLE IF NOT EXISTS `gold_bank_data` (
  `plrGUID` bigint(10) NOT NULL,
  `depName` varchar(25) NOT NULL,
  `depGold` int(10) NOT NULL,
  `depositGUID` bigint(20) NOT NULL AUTO_INCREMENT,
  UNIQUE KEY `depositGUID` (`depositGUID`)
) ENGINE=InnoDB AUTO_INCREMENT=0 DEFAULT CHARSET=latin1;

-- Insert UNUSED deposits, these should not be edited or modified!
INSERT INTO `gold_bank_data` (`plrGUID`, `depName`, `depGold`, `depositGUID`) VALUES
	(0, 'do_not_use_this_deposit', 0, 1),
	(0, 'do_not_use_this_deposit', 0, 2),
	(0, 'do_not_use_this_deposit', 0, 3),
	(0, 'do_not_use_this_deposit', 0, 555),
	(0, 'do_not_use_this_deposit', 0, 777),
	(0, 'do_not_use_this_deposit', 0, 888),
	(0, 'do_not_use_this_deposit', 0, 999);
