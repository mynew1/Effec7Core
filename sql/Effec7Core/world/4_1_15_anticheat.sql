REPLACE INTO `command` VALUES 
('anticheat global', '1000', 'Syntax: .anticheat global returns the total amount reports and the average. (top three players)'), 
('anticheat player', '1001', 'Syntax: .anticheat player $name returns the players''s total amount of warnings, the average and the 
amount of each cheat type.'), 
('anticheat handle', '1002', 'Syntax: .anticheat handle [on|off] Turn on/off the AntiCheat-Detection .'),
('anticheat delete', '1003´', 'Syntax: .anticheat delete [deleteall|$name] Deletes the report records of all the players or deletes all the reports of player $name.'),
('anticheat jail', '1004', 'Syntax: .anticheat jail'),
('anticheat warn', '1005', 'Syntax: .anticheat warn'),
('anticheat targetmarker', '1006', 'Syntax: .anticheat targetmarker');
