# Copyright (C) 2008-2015 TrinityCore <http://www.trinitycore.org/>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

file(GLOB_RECURSE sources_Custom Custom/*.cpp Custom/*.h)

set(scripts_STAT_SRCS
  ${scripts_STAT_SRCS}
#  ${sources_Custom}
Custom/dynamic_teleporter.cpp
Custom/Transmog/Transmogrification.cpp
Custom/Transmog/Transmogrification.h
Custom/Transmog/Transmogrifier.cpp
Custom/duel_reset.cpp
Custom/1v1_arena.cpp
Custom/boss_cooldown_reset.cpp
Custom/ArenaWatcher.cpp
Custom/GoldBanker.cpp
)

message("  -> Prepared: Custom")
