-- ---------------------------------------------
-- 19424 - [Bleeding Hollow Tormentor]
-- 16925 - [Bonechewer Raider]
-- 8551 - [Dark Summoner <Cult of the Damned>]
-- ---------------------------------------------
-- SQL CODE (Fix - Crash Server [Mind control])
-- ---------------------------------------------
 
UPDATE `creature_template` SET `mechanic_immune_mask` = 1 WHERE `entry` IN (19424,16925,8551);