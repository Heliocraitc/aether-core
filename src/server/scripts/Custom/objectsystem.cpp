#include "ScriptPCH.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "Player.h"
#include "Chat.h"
#include <cstring>
#include "ObjectMgr.h"
#include "MapManager.h"
#include "objectsystem.h"
#include "Language.h"
#include "DatabaseFunctions.h"
#include "ObjectAccessor.h"
#include "ScriptMgr.h"
#include "GameEventMgr.h"
#include "PoolMgr.h"
#include "Opcodes.h"

static const WorldLocation* gtargetpos;
static uint32 gitemId = 0;
static GameObject* gObject = NULL;

class cs_object_pickup : public SpellScriptLoader
{
public:
    cs_object_pickup() : SpellScriptLoader("cs_object_pickup") {}

    class cs_spell_pickup : public SpellScript
    {
        PrepareSpellScript(cs_spell_pickup);

        void spell_pickup()
        {

        Player* player = GetCaster()->ToPlayer();
        GameObject* object = NULL;
        const WorldLocation* targetpos = gtargetpos;

        QueryResult guidResult = WorldDatabase.PQuery("SELECT guid FROM gameobject WHERE postion_x = %f AND position_y = %f AND position_z = %f AND orientation = %f AND map = %u;", targetpos->GetPositionX(), targetpos->GetPositionY(), targetpos->GetPositionZ(), targetpos->GetOrientation(), targetpos->GetMapId());
        Field* guidField = guidResult->Fetch();
        uint32 guidLow = guidField[0].GetUInt32();


        if (GameObjectData const* gameObjectData = sObjectMgr->GetGOData(guidLow)) // by DB guid
            object = player->GetMap()->GetGameObject(MAKE_NEW_GUID(guidLow, gameObjectData->id, HIGHGUID_GAMEOBJECT));

        if (!object)
        {
            ChatHandler(player->GetSession()).PSendSysMessage(LANG_COMMAND_OBJNOTFOUND, guidLow);
            ChatHandler(player->GetSession()).SetSentErrorMessage(true);
            return;
        }

        uint64 ownerGuid = object->GetOwnerGUID();
        if (ownerGuid)
        {
            if (!player || !IS_PLAYER_GUID(ownerGuid))
            {
                ChatHandler(player->GetSession()).PSendSysMessage(LANG_COMMAND_DELOBJREFERCREATURE, GUID_LOPART(ownerGuid), object->GetGUIDLow());
                ChatHandler(player->GetSession()).SetSentErrorMessage(true);
                return;
            }

            player->RemoveGameObject(object, false);
        }

        object->SetRespawnTime(0);                                 // not save respawn time
        object->Delete();
        object->DeleteFromDB();
        player->AddItem(object->GetEntry(), 1);

        ChatHandler(player->GetSession()).PSendSysMessage(LANG_COMMAND_DELOBJMESSAGE, object->GetGUIDLow());

        return;
        }

        void Register()
        {
            AfterCast += SpellCastFn(cs_spell_pickup::spell_pickup);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new cs_spell_pickup();
    }
};

class cs_aether_item_object : public ItemScript
{
public:

    cs_aether_item_object() : ItemScript("cs_aether_item_object") {}

    bool OnUse(Player* player, Item* item, SpellCastTargets const& targets)
   {
        gtargetpos = targets.GetDstPos(); //The position at which the item will spawn, used to get the spell position.
        gitemId = item->GetEntry(); //Item ID corresponds to the game object's ID.
        player->CastSpell(player, 90102, true);
        return true;
   }
};

class cs_aether_object_place : public SpellScriptLoader
{
public:
    cs_aether_object_place() : SpellScriptLoader("cs_aether_object_place") {}

    class cs_spell_place : public SpellScript
    {
        PrepareSpellScript(cs_spell_place);
        void spell_place()
        {
        Player* player = GetCaster()->ToPlayer();
        const WorldLocation* targetpos = gtargetpos;
        uint32 itemId = gitemId;
        uint32 objectId = itemId;

        const GameObjectTemplate* objectInfo = sObjectMgr->GetGameObjectTemplate(objectId); //Loads information from gameobject templates.

        if (!objectInfo) //If the game object doesn't exist...
        {
            ChatHandler(player->GetSession()).PSendSysMessage(LANG_GAMEOBJECT_NOT_EXIST, objectId);
            ChatHandler(player->GetSession()).SetSentErrorMessage(true);
            return;
        }

        if (objectInfo->displayId && !sGameObjectDisplayInfoStore.LookupEntry(objectInfo->displayId)) //If the game has corrupt or invalid data...
        {
            // report to DB errors log as in loading case
            ChatHandler(player->GetSession()).PSendSysMessage(LANG_GAMEOBJECT_HAVE_INVALID_DATA, objectId);
            ChatHandler(player->GetSession()).SetSentErrorMessage(true);
            return;
        }

        float x = float(targetpos->GetPositionX()); // Load the target position of the object.
        float y = float(targetpos->GetPositionY());
        float z = float(targetpos->GetPositionZ());
        float o = float(player->GetOrientation());
        Map* map = player->GetMap();

        if(player->GetDistance(x, y, z) > 20) // Prevent players from placing from over 20 yds away.
        {
            ChatHandler(player->GetSession()).PSendSysMessage("You cannot place objects more than 20 yards from yourself.");
            return;
        }

        if(player->GetMapId() == 725) // Prevent players from using Game Objects in the start area.
        {
            ChatHandler(player->GetSession()).PSendSysMessage("You cannot place objects in aether startzone.");
            return;
        }

        GameObject* object = new GameObject;
        uint32 guidLow = sObjectMgr->GenerateLowGuid(HIGHGUID_GAMEOBJECT);

        if (!object->Create(guidLow, objectInfo->entry, map, player->GetPhaseMaskForSpawn(), x, y, z, o, 0.0f, 0.0f, 0.0f, 0.0f, 0, GO_STATE_READY))
        {
            delete object;
            return;
        }
        // fill the gameobject data and save to the db
        object->SaveToDB(map->GetId(), (1 << map->GetSpawnMode()), player->GetPhaseMaskForSpawn());

        // this will generate a new guid if the object is in an instance
        if (!object->LoadGameObjectFromDB(guidLow, map))
        {
            delete object;
            return;
        }

        sObjectMgr->AddGameobjectToGrid(guidLow, sObjectMgr->GetGOData(guidLow)); //Actually spawns the new game object.

        if(player->GetGuildId())
           DatabaseFunctions::SetDB_gameobject_guildid(guidLow, player->GetGuildId());

        ChatHandler(player->GetSession()).PSendSysMessage("You have successfully placed %s at X:%5.2f, Y:%5.2f, Z:%5.2f, O:%5.2f.", objectInfo->name.c_str(), x, y, z, o);
        player->DestroyItemCount(itemId, -1, true, false); // Removes the item from the player.
        }

        void Register()
        {
            AfterCast += SpellCastFn(cs_spell_place::spell_place);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new cs_spell_place();
    }
};

void AddSC_aether_objects()
{
    new cs_aether_object_place;
    new cs_aether_item_object;
    new cs_object_pickup;
}
