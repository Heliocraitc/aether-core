#include "ScriptPCH.h"
#include "Player.h"
#include "Guild.h"
#include "groupsystem.h"
#include "guildsystem.h"
#include "Language.h"
#include "DatabaseFunctions.h"
using namespace std;

static Creature* summon;
static Item* clerkitem;
static Player* guildleader;

class cs_guildclerk_guild : public GuildScript
{
public:
    cs_guildclerk_guild() : GuildScript("cs_guildclerk_guild") {}

    void OnCreate(Guild* guild, Player* leader, const std::string& name)
    {
        uint32 itemId;
        switch(leader->getRace())
        {
        case RACE_HUMAN:
            itemId = CLERKITEM_STORMWIND_HUMAN;
            break;
        case RACE_DWARF:
            itemId = CLERKITEM_IRONFORGE_DWARF;
            break;
        case RACE_NIGHTELF:
           itemId = CLERKITEM_DARNASSIAN_NIGHTELF;
            break;
        case RACE_GNOME:
            itemId = CLERKITEM_GNOMEREGAN_GNOME;
            break;
        case RACE_DRAENEI:
            itemId = CLERKITEM_EXODAR_DRAENEI;
            break;
        case RACE_ORC:
           itemId = CLERKITEM_THRALL_ORC;
            break;
        case RACE_TROLL:
            itemId = CLERKITEM_JUNGLE_TROLL;
            break;
        case RACE_TAUREN:
            itemId = CLERKITEM_BLOODHOOF_TAUREN;
            break;
        case RACE_UNDEAD_PLAYER:
            itemId = CLERKITEM_FORSAKEN_UNDEAD;
            break;
        case RACE_BLOODELF:
            itemId = CLERKITEM_QUELTHAS_BLOODELF;
            break;
        default:
            break;
        }
        if(itemId != 0)
        {
            uint32 noSpaceForCount = 0;
            ItemPosCountVec dest;
            ChatHandler* handler;
            InventoryResult msg = leader->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, itemId, 1, &noSpaceForCount);

            if (noSpaceForCount > 0)
                handler->PSendSysMessage(LANG_ITEM_CANNOT_CREATE, itemId, noSpaceForCount);

            Item* item = leader->StoreNewItem(dest, itemId, true, Item::GenerateItemRandomPropertyId(itemId));

            clerkitem = item;
            guildleader = leader;
        }

    }

    void OnDisband(Guild* guild)
    {
        /*if(uint32 itemId = clerkitem->GetEntry())
        {
            guildleader->AddItem(itemId, -1);
            return;
        } else {
            WorldDatabase.PExecute("DELETE FROM creature WHERE guid = u%;", summon->GetGUIDLow());
        }*/
    }
};

class cs_guildclerk_npc : public CreatureScript
{
public:
    cs_guildclerk_npc() : CreatureScript("cs_guildclerk_npc") {}

    bool OnGossipHello(Player * player, Creature * creature)
    {
        if(player->GetGuildId() == DatabaseFunctions::GetDB_creature_guildid(summon->GetGUIDLow()))
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Let me see my belongings.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I need to reset my talents.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "We're moving somewhere else, come with me.(Guild Master Only)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
        }
        else
        {
            creature->MonsterWhisper("Who are you? Get out of here before I call the Master!", player);
            return false;
        }

        player->PlayerTalkClass->SendGossipMenu(90010, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 actions)
    {
        player->PlayerTalkClass->ClearMenus();
        switch(actions)
        {
        case GOSSIP_ACTION_INFO_DEF+1:
            player->GetSession()->SendShowBank(player->GetGUID()); //Shows personal bank
            player->CLOSE_GOSSIP_MENU();
            break;
        case GOSSIP_ACTION_INFO_DEF+2:  //Reset talents
            player->resetTalents();
            player->InitTalentForLevel();
            player->CLOSE_GOSSIP_MENU();
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
             //Moving the NPC
        if(player->IsGuildMaster())
        {
            switch (player->getRace())
            {
            case RACE_HUMAN:
                player->AddItem(CLERKITEM_STORMWIND_HUMAN,1);
                break;
            case RACE_DWARF:
                player->AddItem(CLERKITEM_IRONFORGE_DWARF,1);
                break;
            case RACE_NIGHTELF:
                player->AddItem(CLERKITEM_DARNASSIAN_NIGHTELF,1);
                break;
            case RACE_GNOME:
                player->AddItem(CLERKITEM_GNOMEREGAN_GNOME,1);
                break;
            case RACE_DRAENEI:
                player->AddItem(CLERKITEM_EXODAR_DRAENEI,1);
                break;
            case RACE_ORC:
                player->AddItem(CLERKITEM_THRALL_ORC,1);
                break;
            case RACE_TROLL:
                player->AddItem(CLERKITEM_JUNGLE_TROLL,1);
                 break;
            case RACE_TAUREN:
                player->AddItem(CLERKITEM_BLOODHOOF_TAUREN,1);
                break;
            case RACE_UNDEAD_PLAYER:
                player->AddItem(CLERKITEM_FORSAKEN_UNDEAD,1);
                break;
            case RACE_BLOODELF:
                player->AddItem(CLERKITEM_QUELTHAS_BLOODELF,1);
                break;
            default:
                creature->MonsterWhisper("DEBUG: Cannot find your race. Alert a developer.", player);
                break;
            }
            creature->DespawnOrUnsummon(); //Despawning the NPC
            break;
        } else
        {
            creature->MonsterWhisper("You are not the Guild Master!", player);
        }
            player->CLOSE_GOSSIP_MENU();
            break;
        }
        return true;
    }

};

class cs_guildclerk_item : public ItemScript
{
public:
    cs_guildclerk_item() : ItemScript("cs_guildclerk_item") {}

    bool OnUse(Player* player, Item* item, SpellCastTargets const& targets)
    {
        if(!player->IsGuildMaster())
            return false;

        uint32 entryID = 0;
        switch(player->getRace())
        {
        case RACE_HUMAN:
            entryID = CLERKNPC_STORMWIND_HUMAN;
            break;
        case RACE_DWARF:
            entryID = CLERKNPC_IRONFORGE_DWARF;
            break;
        case RACE_GNOME:
            entryID = CLERKNPC_GNOMEREGAN_GNOME;
            break;
        case RACE_NIGHTELF:
            entryID = CLERKNPC_DARNASSIAN_NIGHTELF;
            break;
        case RACE_DRAENEI:
            entryID = CLERKNPC_EXODAR_DRAENEI;
            break;
        case RACE_ORC:
            entryID = CLERKNPC_THRALL_ORC;
            break;
        case RACE_TROLL:
            entryID = CLERKNPC_JUNGLE_TROLL;
            break;
        case RACE_TAUREN:
            entryID = CLERKNPC_BLOODHOOF_TAUREN;
            break;
        case RACE_UNDEAD_PLAYER:
            entryID = CLERKNPC_FORSAKEN_UNDEAD;
            break;
        case RACE_BLOODELF:
            entryID = CLERKNPC_QUELTHAS_BLOODELF;
            break;
        default:
            break;
        }
        if(entryID != 0)
        {
        summon = player->SummonCreature(entryID, player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), player->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN, 0);
        summon->SaveToDB();
        DatabaseFunctions::SetDB_creature_guildid(summon->GetGUIDLow(), player->GetGuildId());
        DatabaseFunctions::SetDB_creature_playerguid(summon->GetGUIDLow(), player->GetGUIDLow());
        }
        return true;
    }
};

void AddSC_aevum_groupsystem(){
    new cs_guildclerk_npc;
    new cs_guildclerk_guild;
    new cs_guildclerk_item;
}
