#ifndef DATABASE_FUNCTIONS_H
#define DATABASE_FUNCTIONS_H

class DatabaseFunctions
{
    public:
    /*Characters*/
    static uint8 GetDB_character_deaths(uint32 playerGUID);
    static void SetDB_character_deaths(uint32 playerGUID, uint8 deathsCount = 1);

    /*guild table*/
    static uint8 GetDB_guild_guildlevel(uint32 guildid);
    static uint8 GetDB_guild_guildfaction(uint32 guildid);
    static void SetDB_guild_guildlevel(uint32 guildid, uint8 guildlevel);
    static void SetDB_guild_guildfaction(uint32 guildid, uint8 guildfaction);

    /*creature table*/
    static uint8 GetDB_creature_deaths(uint32 creatureGUID);
    static uint8 GetDB_creature_faction(uint32 creatureGUID);
    static uint32 GetDB_creature_guildid(uint32 creatureGUID);
    static uint32 GetDB_creature_playerguid(uint32 creatureGUID);
    static void SetDB_creature_deaths(uint32 creatureGUID, uint8 deathCount = 1);
    static void SetDB_creature_faction(uint32 creatureGUID, uint8 faction);
    static void SetDB_creature_guildid(uint32 creatureGUID, uint32 guildid);
    static void SetDB_creature_playerguid(uint32 creatureGUID, uint32 playerGUID);

    /*gameobject table*/
    static uint32 GetDB_gameobject_guildid(uint32 gameobjectGUID);
    static uint32 GetDB_gameobject_playerguid(uint32 gameobjectGUID);
    static void SetDB_gameobject_guildid(uint32 gameobjectGUID, uint32 guildid);
    static void SetDB_gameobject_playerguid(uint32 gameobjectGUID, uint32 playerGUID);
};

#endif
