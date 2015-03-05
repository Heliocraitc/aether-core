#include "ScriptPCH.h"
#include "DatabaseFunctions.h"

/*characters table*/
uint8 DatabaseFunctions::GetDB_character_deaths(uint32 playerGUID)
{
    QueryResult result = CharacterDatabase.PQuery("SELECT deaths FROM characters WHERE guid = %u;", playerGUID);
    Field * field = result->Fetch();
    uint8 playerdeaths = field[0].GetUInt8();

    return playerdeaths;
}

void DatabaseFunctions::SetDB_character_deaths(uint32 playerGUID, uint8 deathsCount)
{
    CharacterDatabase.PExecute("UPDATE characters SET deaths = (deaths + %u) WHERE guid = %u;", deathsCount, playerGUID);
}

/*guild table*/
uint8 DatabaseFunctions::GetDB_guild_guildlevel(uint32 guildid)
{
    QueryResult result = CharacterDatabase.PQuery("SELECT guild_level FROM guild WHERE guildid = %u;", guildid);
    Field * field = result->Fetch();
    uint8 guildlevel = field[0].GetUInt8();

    return guildlevel;
}
uint8 DatabaseFunctions::GetDB_guild_guildfaction(uint32 guildid)
{
    QueryResult result = CharacterDatabase.PQuery("SELECT guild_faction FROM guild WHERE guildid = %u;", guildid);
    Field * field = result->Fetch();
    uint8 guildfaction = field[0].GetUInt8();

    return guildfaction;
}
void DatabaseFunctions::SetDB_guild_guildlevel(uint32 guildid, uint8 guildlevel)
{
    CharacterDatabase.PExecute("UPDATE guild SET guildlevel = %u WHERE guildid = %u;", guildlevel, guildid);
}
void DatabaseFunctions::SetDB_guild_guildfaction(uint32 guildid, uint8 guildfaction)
{
    CharacterDatabase.PExecute("UPDATE guild SET guildfaction = %u WHERE guildid = %u;", guildfaction, guildid);
}

/*creature table*/

uint8 DatabaseFunctions::GetDB_creature_deaths(uint32 creatureGUID)
{
    QueryResult result = WorldDatabase.PQuery("SELECT deaths FROM creature WHERE guid = %u;", creatureGUID);
    Field* field = result->Fetch();
    uint8 deaths = field[0].GetUInt8();

    return deaths;
}

uint8 DatabaseFunctions::GetDB_creature_faction(uint32 creatureGUID)
{
    QueryResult result = WorldDatabase.PQuery("SELECT faction FROM creature WHERE guid = %u;", creatureGUID);
    Field* field = result->Fetch();
    uint8 faction = field[0].GetUInt8();

    return faction;
}

uint32 DatabaseFunctions::GetDB_creature_guildid(uint32 creatureGUID)
{
    QueryResult result = WorldDatabase.PQuery("SELECT guild_id FROM creature WHERE guid = %u;", creatureGUID); //Reads the number of deaths.
    Field * field = result->Fetch(); //Reads the above query's result.
    uint32 guildid = field[0].GetUInt32();

    return guildid;
}

uint32 DatabaseFunctions::GetDB_creature_playerguid(uint32 creatureGUID)
{
    QueryResult result = WorldDatabase.PQuery("SELECT player_guid FROM creature WHERE guid = %u;", creatureGUID); //Reads the number of deaths.
    Field * field = result->Fetch();
    uint32 playerGUID = field[0].GetUInt32();

    return playerGUID;
}

void DatabaseFunctions::SetDB_creature_deaths(uint32 creatureGUID, uint8 deathsCount)
{
    WorldDatabase.PExecute("UPDATE creature SET deaths = (deaths + %u) WHERE guid = %u;", deathsCount, creatureGUID);
}

void DatabaseFunctions::SetDB_creature_faction(uint32 creatureGUID, uint8 faction)
{
    WorldDatabase.PExecute("UPDATE creature SET faction = %u WHERE guid = %u;", faction, creatureGUID);
}

void DatabaseFunctions::SetDB_creature_guildid(uint32 creatureGUID, uint32 guildid)
{
    WorldDatabase.PExecute("UPDATE creature SET guild_id = %u WHERE guid = %u;", guildid, creatureGUID);
}

void DatabaseFunctions::SetDB_creature_playerguid(uint32 creatureGUID, uint32 playerGUID)
{
    WorldDatabase.PExecute("UPDATE creature SET player_guid = %u WHERE guid = %u;", playerGUID, creatureGUID);
}

/*gameobject table*/

uint32 DatabaseFunctions::GetDB_gameobject_guildid(uint32 gameobjectGUID)
{
    QueryResult result = WorldDatabase.PQuery("SELECT guild_id FROM gameobject WHERE guid = %u;", gameobjectGUID);
    Field * field = result->Fetch();
    uint32 guildid = field[0].GetUInt32();

    return guildid;
}

uint32 DatabaseFunctions::GetDB_gameobject_playerguid(uint32 gameobjectGUID)
{
    QueryResult result = WorldDatabase.PQuery("SELECT player_guid FROM gameobject WHERE guid = %u;", gameobjectGUID);
    Field * field = result->Fetch();
    uint32 playerGUID = field[0].GetUInt32();

    return playerGUID;
}

void DatabaseFunctions::SetDB_gameobject_guildid(uint32 gameobjectGUID, uint32 guildGuid)
 {
     WorldDatabase.PExecute("UPDATE gameobject SET guild_guid = %u WHERE guid = %u;", guildGuid, gameobjectGUID);
 }

void DatabaseFunctions::SetDB_gameobject_playerguid(uint32 gameobjectGUID, uint32 playerGUID)
 {
     WorldDatabase.PExecute("UPDATE gameobject SET player_guid = %u WHERE guid = %u;", playerGUID, gameobjectGUID);
 }
