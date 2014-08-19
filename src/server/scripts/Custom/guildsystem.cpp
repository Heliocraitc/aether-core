#include "ScriptPCH.h"
#include "Guild.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "Player.h"
#include <cstring>
#include "Common.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "World.h"
#include "ObjectMgr.h"
#include "GuildMgr.h"
#include "Log.h"
#include "Opcodes.h"
#include "GossipDef.h"
#include "SocialMgr.h"

class cs_keypointitem : public ItemScript
{

public:
    cs_keypointitem() : ItemScript("cs_keypointitem") {}


    bool OnUse(Player* player, Item* item, SpellCastTargets const& targets)
    {
        uint32 guildid = player->GetGuildId();
        /* Getting keypoint number from the database. */
        QueryResult result = CharacterDatabase.PQuery("SELECT COUNT(*) FROM aevum_guild_keypoints WHERE guildid = %u;", guildid);
        Field * fields = result->Fetch();
        uint8 keypoints = fields[0].GetUInt8();
        uint8 maxkeypoints = 2;

        QueryResult result2 = CharacterDatabase.PQuery("SELECT faction FROM aevum_guild_levels WHERE guid = %u;", guildid);
        Field * fields2 = result2->Fetch();
        uint8 faction = fields2[0].GetUInt8();
        //if((player->IsWithinDist(gobject, 100.0, true)) && (gobject->GetEntry)){
        if( (player->FindNearestGameObject(90000, 100.0) != NULL) || (player->FindNearestGameObject(90001, 100.0) != NULL) || (player->FindNearestGameObject(90002, 100.0) != NULL) )
        {
            ChatHandler(player->GetSession()).PSendSysMessage("You're too close to an existing keypoint. Try placing it somewhere else.");
        }

        /*Add outdoors check and capital city check*/

        else if (keypoints < maxkeypoints)
        {
            player->DestroyItemCount(60072, -1, true, false);
            ChatHandler(player->GetSession()).PSendSysMessage("You place your banner, marking the surrounding land as property of your guild.");
            /*To-do, how to spawn a game object permanently.*/

            /* COPY PASTING SPAWN GOB COMMAND*/
            uint32 objectId = 90002;
            if (faction == 1)
                uint32 objectId = 90000;
            else if (faction == 2)
                uint32 objectId = 90001;

            if (!objectId)
                return false;
            const GameObjectTemplate* objectInfo = sObjectMgr->GetGameObjectTemplate(objectId);

            if (!objectInfo)
            {
                return false;
            }

            if (objectInfo->displayId && !sGameObjectDisplayInfoStore.LookupEntry(objectInfo->displayId))
            {
                return false;
            }

            float x = float(player->GetPositionX());
            float y = float(player->GetPositionY());
            float z = float(player->GetPositionZ());
            float o = float(player->GetOrientation());
            Map* map = player->GetMap();

            GameObject* object = new GameObject;
            uint32 guidLow = sObjectMgr->GenerateLowGuid(HIGHGUID_GAMEOBJECT);

            if (!object->Create(guidLow, objectInfo->entry, map, player->GetPhaseMaskForSpawn(), x, y, z, o, 0.0f, 0.0f, 0.0f, 0.0f, 0, GO_STATE_READY))
            {
                delete object;
                return false;
            }

            object->SetRespawnTime(0);

            // fill the gameobject data and save to the db
            object->SaveToDB(map->GetId(), (1 << map->GetSpawnMode()), player->GetPhaseMaskForSpawn());

            // this will generate a new guid if the object is in an instance
            if (!object->LoadGameObjectFromDB(guidLow, map))
            {
                delete object;
                return false;
            }

            /// @todo is it really necessary to add both the real and DB table guid here ?
            sObjectMgr->AddGameobjectToGrid(guidLow, sObjectMgr->GetGOData(guidLow));

            /*Spawn Game object*/


//player->FindNearestGameObject(90000, 0.1);
            CharacterDatabase.PExecute("INSERT INTO aevum_guild_keypoints (guildid, guid) VALUES (%u, %u);", guildid, guidLow);
            uint32 guid = object->GetGUID();
        }
        else
            ChatHandler(player->GetSession()).PSendSysMessage("Your guild can't place any more keypoints.");
        return true;
    };

};

class cs_keypoint : public GameObjectScript
{

public:
    cs_keypoint() : GameObjectScript("cs_keypoint") {}

    /*bool OnGossipHello(Player* player, GameObject* object)
    {
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TABARD, "Inspect the banner.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Strike the colors.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
        player->PlayerTalkClass->SendGossipMenu(90010, object->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, GameObject* object, uint32 sender, uint32 actions)
    {
        player->PlayerTalkClass->ClearMenus();
        if (sender != GOSSIP_SENDER_MAIN)
            return false;

        switch(actions)
        {
        case GOSSIP_ACTION_INFO_DEF+1:
        {
            QueryResult result = CharacterDatabase.PQuery("SELECT guildid FROM aevum_guild_keypoints WHERE guid = %u;", object->GetGUID());
            Field * fields = result->Fetch();
            uint64 guildid = fields[0].GetUInt8();

            QueryResult result2 = CharacterDatabase.PQuery("SELECT name FROM guild WHERE guid = %u;", guildid);
            Field * fields2 = result2->Fetch();
            std::string guildname = fields2[0].c_str();
            ChatHandler(player->GetSession()).PSendSysMessage("This keypoint belongs to %c.", guildname);
            break;
        }
        case GOSSIP_ACTION_INFO_DEF+2:
        {
            CharacterDatabase.PExecute("DELETE FROM aevum_guild_keypoints WHERE guid = %u", object->GetGUID());
            uint32 objectId = 90004;

            if (!objectId)
                return false;
            const GameObjectTemplate* objectInfo = sObjectMgr->GetGameObjectTemplate(objectId);

            if (!objectInfo)
            {
                return false;
            }

            if (objectInfo->displayId && !sGameObjectDisplayInfoStore.LookupEntry(objectInfo->displayId))
            {
                return false;
            }

            float x = float(object->GetPositionX());
            float y = float(object->GetPositionY());
            float z = float(object->GetPositionZ());
            float o = float(object->GetOrientation());
            Map* map = object->GetMap();

            object->DeleteFromDB();
            object->Delete();
            GameObject* object2 = new GameObject;
            uint32 guidLow = sObjectMgr->GenerateLowGuid(HIGHGUID_GAMEOBJECT);

            if (!object2->Create(guidLow, objectInfo->entry, map, player->GetPhaseMaskForSpawn(), x, y, z, o, 0.0f, 0.0f, 0.0f, 0.0f, 0, GO_STATE_READY))
            {
                delete object;
                return false;
            }

            object2->SetRespawnTime(0);

            // fill the gameobject data and save to the db
            object2->SaveToDB(map->GetId(), (1 << map->GetSpawnMode()), player->GetPhaseMaskForSpawn());

            // this will generate a new guid if the object is in an instance
            if (!object2->LoadGameObjectFromDB(guidLow, map)){
                delete object2;
                return false;
            }

            /// @todo is it really necessary to add both the real and DB table guid here ?
            sObjectMgr->AddGameobjectToGrid(guidLow, sObjectMgr->GetGOData(guidLow));

            QueryResult result = CharacterDatabase.PQuery("SELECT guildid FROM aevum_guild_keypoints WHERE guid = %u;", object->GetGUID());
            Field * fields = result->Fetch();
            uint64 guildid = fields[0].GetUInt8();

            QueryResult result2 = CharacterDatabase.PQuery("SELECT COUNT(*) FROM aevum_guild_keypoints WHERE guildid = %u;", guildid);
            Field * fields2 = result2->Fetch();
            uint64 keypoints = fields[0].GetUInt8();

            if (keypoints == 0)
            {
                Guild * guild = player->GetGuild();
                guild->Disband();
            }
            break;
        }
        }
    } */
};

void AddSC_aevum_guildsystem()
{
    new cs_keypointitem;
    new cs_keypoint;
};
