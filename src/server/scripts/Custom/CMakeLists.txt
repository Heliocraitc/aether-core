# Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

# file(GLOB_RECURSE sources_Custom Custom/*.cpp Custom/*.h)

set(scripts_STAT_SRCS
  ${scripts_STAT_SRCS}
#  ${sources_Custom}
    Custom/Transmogrification.h
    Custom/DatabaseFunctions.h
    Custom/MiscFunctions.h
    Custom/Transmogrification.cpp
    Custom/Transmogrifier.cpp
    Custom/Reforging.cpp
    Custom/GOMove.cpp
    Custom/deathsystem.cpp
    Custom/objectsystem.cpp
    Custom/scaler.cpp
    Custom/aetherlogin.cpp
    Custom/groupsystem.cpp
    Custom/guildsystem.cpp
    Custom/itemrequest.cpp
    Custom/aethercommands.cpp
    Custom/miscnpc.cpp
    Custom/miscobjects.cpp
    Custom/DatabaseFunctions.cpp
    Custom/menustone.cpp
    Custom/MiscFunctions.cpp
)

message("  -> Prepared: Custom")
