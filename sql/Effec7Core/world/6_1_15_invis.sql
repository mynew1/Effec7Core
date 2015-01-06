-- HACK-Fix mage ability Invisibility / Unsichtbarkeit (spells 66, 35009, 32612) causing
-- mage to enter combat for a short moment with every hostile NPC nearby
-- Add SPELL_ATTR3_NO_INITIAL_AGGRO to the spell
UPDATE `spell_dbc` SET `AttributesEx3` = `AttributesEx3` | 131072 WHERE `id` = 35009;