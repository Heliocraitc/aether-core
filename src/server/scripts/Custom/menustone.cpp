#include "ScriptPCH.h"
#include "Player.h"
#include "menustone.h"
#include <string>
#include "objectsystem.h"
#include "Chat.h"

static const SpellCastTargets* targetpos;

class cs_menustone : public ItemScript
{


public:
    cs_menustone() : ItemScript("cs_menustone") {}

    bool OnUse(Player* player, Item* item, SpellCastTargets const& targets)
    {
        targetpos = &targets;
        player->PlayerTalkClass->ClearMenus();
        player->ADD_GOSSIP_ITEM(4, "Welcome to the Aetherstone, from this menu you can interface with all of our systems.", GOSSIP_SENDER_MAIN, 0);

        switch(player->getGender())  // Display the player's race icon as the player icon for their gender.
        {
            case GENDER_MALE:
                switch(player->getRace())
                {
                    case RACE_HUMAN:
                        player->ADD_GOSSIP_ITEM(4, HUMAN_MALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;

                    case RACE_BLOODELF:
                        player->ADD_GOSSIP_ITEM(4, BLOODELF_MALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;

                    case RACE_DRAENEI:
                        player->ADD_GOSSIP_ITEM(4, DRAENEI_MALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;

                    case RACE_DWARF:
                        player->ADD_GOSSIP_ITEM(4, DWARF_MALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;

                    case RACE_GNOME:
                        player->ADD_GOSSIP_ITEM(4, GNOME_MALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;

                    case RACE_NIGHTELF:
                        player->ADD_GOSSIP_ITEM(4, NIGHTELF_MALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;

                    case RACE_ORC:
                        player->ADD_GOSSIP_ITEM(4, ORC_MALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;

                    case RACE_TAUREN:
                        player->ADD_GOSSIP_ITEM(4, TAUREN_MALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;

                    case RACE_TROLL:
                        player->ADD_GOSSIP_ITEM(4, TROLL_MALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;

                    case RACE_UNDEAD_PLAYER:
                        player->ADD_GOSSIP_ITEM(4, FORSAKEN_MALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;
                }
                break;

            case GENDER_FEMALE:
                switch(player->getRace())
                {
                    case RACE_HUMAN:
                        player->ADD_GOSSIP_ITEM(4, HUMAN_FEMALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;

                    case RACE_BLOODELF:
                        player->ADD_GOSSIP_ITEM(4, BLOODELF_FEMALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;

                    case RACE_DRAENEI:
                        player->ADD_GOSSIP_ITEM(4, DRAENEI_FEMALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;

                    case RACE_DWARF:
                        player->ADD_GOSSIP_ITEM(4, DWARF_FEMALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;

                    case RACE_GNOME:
                        player->ADD_GOSSIP_ITEM(4, GNOME_FEMALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;

                    case RACE_NIGHTELF:
                        player->ADD_GOSSIP_ITEM(4, NIGHTELF_FEMALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;

                    case RACE_ORC:
                        player->ADD_GOSSIP_ITEM(4, ORC_FEMALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;

                    case RACE_TAUREN:
                        player->ADD_GOSSIP_ITEM(4, TAUREN_FEMALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;

                    case RACE_TROLL:
                        player->ADD_GOSSIP_ITEM(4, TROLL_FEMALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;

                    case RACE_UNDEAD_PLAYER:
                        player->ADD_GOSSIP_ITEM(4, FORSAKEN_FEMALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;
                }
                break;
        }
        player->ADD_GOSSIP_ITEM(4, "|TInterface\\ICONS\\INV_Misc_GroupLooking:30|t NPC", GOSSIP_SENDER_MAIN, NPC);
        player->ADD_GOSSIP_ITEM(4, "|TInterface\\ICONS\\Ability_Repair:30|t Objects", GOSSIP_SENDER_MAIN, OBJECTS);
        player->ADD_GOSSIP_ITEM(4, "|TInterface\\ICONS\\Ability_Spy:30|t Statistics", GOSSIP_SENDER_MAIN, STATISTICS);
        player->PlayerTalkClass->SendGossipMenu(123, item->GetGUID());
        return true;
    }

    void OnGossipSelect(Player* player, Item* item, uint32 sender, uint32 action)
    {

    switch(action)
    {
        case MAIN_MENU:
            player->PlayerTalkClass->ClearMenus();

        switch(player->getGender())  // Display the player's race icon as the player icon for their gender.
        {
            case GENDER_MALE:
                switch(player->getRace())
                {
                    case RACE_HUMAN:
                        player->ADD_GOSSIP_ITEM(4, HUMAN_MALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;

                    case RACE_BLOODELF:
                        player->ADD_GOSSIP_ITEM(4, BLOODELF_MALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;

                    case RACE_DRAENEI:
                        player->ADD_GOSSIP_ITEM(4, DRAENEI_MALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;

                    case RACE_DWARF:
                        player->ADD_GOSSIP_ITEM(4, DWARF_MALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;

                    case RACE_GNOME:
                        player->ADD_GOSSIP_ITEM(4, GNOME_MALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;

                    case RACE_NIGHTELF:
                        player->ADD_GOSSIP_ITEM(4, NIGHTELF_MALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;

                    case RACE_ORC:
                        player->ADD_GOSSIP_ITEM(4, ORC_MALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;

                    case RACE_TAUREN:
                        player->ADD_GOSSIP_ITEM(4, TAUREN_MALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;

                    case RACE_TROLL:
                        player->ADD_GOSSIP_ITEM(4, TROLL_MALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;

                    case RACE_UNDEAD_PLAYER:
                        player->ADD_GOSSIP_ITEM(4, FORSAKEN_MALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;
                }
                break;

            case GENDER_FEMALE:
                switch(player->getRace())
                {
                    case RACE_HUMAN:
                        player->ADD_GOSSIP_ITEM(4, HUMAN_FEMALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;

                    case RACE_BLOODELF:
                        player->ADD_GOSSIP_ITEM(4, BLOODELF_FEMALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;

                    case RACE_DRAENEI:
                        player->ADD_GOSSIP_ITEM(4, DRAENEI_FEMALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;

                    case RACE_DWARF:
                        player->ADD_GOSSIP_ITEM(4, DWARF_FEMALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;

                    case RACE_GNOME:
                        player->ADD_GOSSIP_ITEM(4, GNOME_FEMALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;

                    case RACE_NIGHTELF:
                        player->ADD_GOSSIP_ITEM(4, NIGHTELF_FEMALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;

                    case RACE_ORC:
                        player->ADD_GOSSIP_ITEM(4, ORC_FEMALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;

                    case RACE_TAUREN:
                        player->ADD_GOSSIP_ITEM(4, TAUREN_FEMALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;

                    case RACE_TROLL:
                        player->ADD_GOSSIP_ITEM(4, TROLL_FEMALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;

                    case RACE_UNDEAD_PLAYER:
                        player->ADD_GOSSIP_ITEM(4, FORSAKEN_FEMALE, GOSSIP_SENDER_MAIN, PLAYER);
                        break;
                }
                break;
        }
        player->ADD_GOSSIP_ITEM(4, "|TInterface\\ICONS\\INV_Misc_GroupLooking:30|t NPC", GOSSIP_SENDER_MAIN, NPC);
        player->ADD_GOSSIP_ITEM(4, "|TInterface\\ICONS\\Ability_Repair:30|t Objects", GOSSIP_SENDER_MAIN, OBJECTS);
        player->ADD_GOSSIP_ITEM(4, "|TInterface\\ICONS\\Ability_Spy:30|t Statistics", GOSSIP_SENDER_MAIN, STATISTICS);
        player->PlayerTalkClass->SendGossipMenu(123, item->GetGUID());
        break;

        case PLAYER:
            player->PlayerTalkClass->ClearMenus();
            player->ADD_GOSSIP_ITEM(0, "Friendly Actions", GOSSIP_SENDER_MAIN, FRIENDLY_PLAYER);
            player->ADD_GOSSIP_ITEM(0, "Hostile Actions", GOSSIP_SENDER_MAIN, ENEMY_PLAYER);
            player->ADD_GOSSIP_ITEM(4, "Main Menu", GOSSIP_SENDER_MAIN, MAIN_MENU);
            player->PlayerTalkClass->SendGossipMenu(123, item->GetGUID());
            break;

        case FRIENDLY_PLAYER:
            player->PlayerTalkClass->ClearMenus();
            player->ADD_GOSSIP_ITEM(0, "Release Player", GOSSIP_SENDER_MAIN, RELEASE_PLAYER);
            player->ADD_GOSSIP_ITEM(0, "Escort Player Bot", GOSSIP_SENDER_MAIN, ESCORT_PLAYER_BOT);
            player->ADD_GOSSIP_ITEM(0, "Feed Player Bot", GOSSIP_SENDER_MAIN, FEED_PLAYER_BOT);
            player->ADD_GOSSIP_ITEM(0, "Main Menu", GOSSIP_SENDER_MAIN,  MAIN_MENU);
            player->PlayerTalkClass->SendGossipMenu(123, item->GetGUID());
            break;

        case RELEASE_PLAYER:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case ESCORT_PLAYER_BOT:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case FEED_PLAYER_BOT:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case ENEMY_PLAYER:
            player->PlayerTalkClass->ClearMenus();
            player->ADD_GOSSIP_ITEM(0, "Restrain Player", GOSSIP_SENDER_MAIN, RESTRAIN_PLAYER);
            player->ADD_GOSSIP_ITEM(0, "Haul Player", GOSSIP_SENDER_MAIN, HAUL_PLAYER);
            player->ADD_GOSSIP_ITEM(0, "Force-feed Player", GOSSIP_SENDER_MAIN, FORCEFEED_PLAYER);
            player->ADD_GOSSIP_ITEM(0, "Injure Player", GOSSIP_SENDER_MAIN, INJURE_PLAYER);
            player->ADD_GOSSIP_ITEM(4, "Main Menu", GOSSIP_SENDER_MAIN, MAIN_MENU);
            player->PlayerTalkClass->SendGossipMenu(123, item->GetGUID());
            break;

        case RESTRAIN_PLAYER:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case HAUL_PLAYER:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case FORCEFEED_PLAYER:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case INJURE_PLAYER:
            player->PlayerTalkClass->ClearMenus();
            player->ADD_GOSSIP_ITEM(0, "Injure Head", GOSSIP_SENDER_MAIN, INJURE_HEAD);
            player->ADD_GOSSIP_ITEM(0, "Injure Right Arm", GOSSIP_SENDER_MAIN, INJURE_RIGHT_ARM);
            player->ADD_GOSSIP_ITEM(0, "Injure Left Arm", GOSSIP_SENDER_MAIN, INJURE_LEFT_ARM);
            player->ADD_GOSSIP_ITEM(0, "Injure Torso", GOSSIP_SENDER_MAIN, INJURE_TORSO);
            player->ADD_GOSSIP_ITEM(0, "Injure Right Leg", GOSSIP_SENDER_MAIN, INJURE_RIGHT_LEG);
            player->ADD_GOSSIP_ITEM(0, "Injure Left Leg", GOSSIP_SENDER_MAIN, INJURE_LEFT_LEG);
            player->ADD_GOSSIP_ITEM(4, "Main Menu", GOSSIP_SENDER_MAIN, MAIN_MENU);
            player->PlayerTalkClass->SendGossipMenu(123, item->GetGUID());
            break;

        case INJURE_HEAD:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case INJURE_RIGHT_ARM:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case INJURE_LEFT_ARM:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case INJURE_TORSO:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case INJURE_RIGHT_LEG:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case INJURE_LEFT_LEG:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case NPC:
            player->PlayerTalkClass->ClearMenus();
            player->ADD_GOSSIP_ITEM(0, "Mount", GOSSIP_SENDER_MAIN, MOUNT);
            player->ADD_GOSSIP_ITEM(0, "Followers", GOSSIP_SENDER_MAIN, FOLLOWER);
            player->ADD_GOSSIP_ITEM(0, "Guild NPCs", GOSSIP_SENDER_MAIN, GUILD_NPC);
            player->ADD_GOSSIP_ITEM(4, "Main Menu", GOSSIP_SENDER_MAIN, MAIN_MENU);
            player->PlayerTalkClass->SendGossipMenu(123, item->GetGUID());
            break;

        case MOUNT:
            player->PlayerTalkClass->ClearMenus();
            player->ADD_GOSSIP_ITEM(0, "Wait", GOSSIP_SENDER_MAIN, WAIT_MOUNT);
            player->ADD_GOSSIP_ITEM(0, "Follow", GOSSIP_SENDER_MAIN, FOLLOW_MOUNT);
            player->ADD_GOSSIP_ITEM(0, "Harness Mount", GOSSIP_SENDER_MAIN, HARNESS_MOUNT);
            player->ADD_GOSSIP_ITEM(0, "Armor Mount", GOSSIP_SENDER_MAIN, ARMOR_MOUNT);
            player->ADD_GOSSIP_ITEM(4, "Main Menu", GOSSIP_SENDER_MAIN, MAIN_MENU);
            player->PlayerTalkClass->SendGossipMenu(123, item->GetGUID());
            break;

        case WAIT_MOUNT:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case FOLLOW_MOUNT:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case HARNESS_MOUNT:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case ARMOR_MOUNT:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case FOLLOWER:
            player->PlayerTalkClass->ClearMenus();
            player->ADD_GOSSIP_ITEM(0, "Wait", GOSSIP_SENDER_MAIN, WAIT_FOLLOWER);
            player->ADD_GOSSIP_ITEM(0, "Follow", GOSSIP_SENDER_MAIN, FOLLOW_FOLLOWER);
            player->ADD_GOSSIP_ITEM(0, "Go to Point", GOSSIP_SENDER_MAIN, GOTO_FOLLOWER);
            player->ADD_GOSSIP_ITEM(0, "Attack This", GOSSIP_SENDER_MAIN, ATTACK_FOLLOWER);
            player->ADD_GOSSIP_ITEM(0, "Stance", GOSSIP_SENDER_MAIN, STANCE_FOLLOWER);
            player->ADD_GOSSIP_ITEM(0, "Trade Items", GOSSIP_SENDER_MAIN, TRADE_ITEMS_FOLLOWER);
            player->ADD_GOSSIP_ITEM(0, "Mount Follower", GOSSIP_SENDER_MAIN, MOUNT_FOLLOWER);
            player->ADD_GOSSIP_ITEM(0, "Dismount Follower", GOSSIP_SENDER_MAIN, UNMOUNT_FOLLOWER);
            player->ADD_GOSSIP_ITEM(0, "Pay Follower", GOSSIP_SENDER_MAIN, PAY_FOLLOWER);
            player->ADD_GOSSIP_ITEM(0, "Give Armor", GOSSIP_SENDER_MAIN, GIVE_ARMOR);
            player->ADD_GOSSIP_ITEM(0, "Patrols", GOSSIP_SENDER_MAIN, PATROLLING);
            player->ADD_GOSSIP_ITEM(4, "Main Menu", GOSSIP_SENDER_MAIN, MAIN_MENU);
            player->PlayerTalkClass->SendGossipMenu(123, item->GetGUID());
            break;

        case GOTO_FOLLOWER:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case ATTACK_FOLLOWER:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case FOLLOW_FOLLOWER:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case STANCE_FOLLOWER:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case TRADE_ITEMS_FOLLOWER:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case MOUNT_FOLLOWER:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case UNMOUNT_FOLLOWER:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case PAY_FOLLOWER:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case GIVE_ARMOR:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case PATROLLING:
            player->PlayerTalkClass->ClearMenus();
            player->ADD_GOSSIP_ITEM(0, "Add Waypoint", GOSSIP_SENDER_MAIN, ADD_WAYPOINT);
            player->ADD_GOSSIP_ITEM(0, "Start Patrol", GOSSIP_SENDER_MAIN, START_PATROL);
            player->ADD_GOSSIP_ITEM(0, "End Patrol", GOSSIP_SENDER_MAIN, STOP_PATROL);
            player->ADD_GOSSIP_ITEM(4, "Main Menu", GOSSIP_SENDER_MAIN, MAIN_MENU);
            player->PlayerTalkClass->SendGossipMenu(123, item->GetGUID());
            break;

        case ADD_WAYPOINT:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case START_PATROL:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case STOP_PATROL:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case GUILD_NPC:
            player->PlayerTalkClass->ClearMenus();
            player->ADD_GOSSIP_ITEM(0, "Wait", GOSSIP_SENDER_MAIN, WAIT_GUILD);
            player->ADD_GOSSIP_ITEM(0, "Follow", GOSSIP_SENDER_MAIN, FOLLOW_GUILD);
            player->ADD_GOSSIP_ITEM(0, "Attack Target", GOSSIP_SENDER_MAIN, ATTACK_GUILD);
            player->ADD_GOSSIP_ITEM(0, "Go to Point", GOSSIP_SENDER_MAIN, GOTO_GUILD);
            player->ADD_GOSSIP_ITEM(4, "Main Menu", GOSSIP_SENDER_MAIN, MAIN_MENU);
            player->PlayerTalkClass->SendGossipMenu(123, item->GetGUID());
            break;

        case WAIT_GUILD:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case FOLLOW_GUILD:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case ATTACK_GUILD:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case GOTO_GUILD:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case ENEMY_GUILD:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case OBJECTS:
            player->PlayerTalkClass->ClearMenus();
            player->ADD_GOSSIP_ITEM(4, "Select Object", GOSSIP_SENDER_MAIN, SELECT_OBJECT);
            player->ADD_GOSSIP_ITEM(4, "Pickup Object", GOSSIP_SENDER_MAIN, PICKUP_OBJECT);
            player->ADD_GOSSIP_ITEM(4, "Edit Object Position", GOSSIP_SENDER_MAIN, EDIT_OBJECT_POSITION);
            player->ADD_GOSSIP_ITEM(4, "Change Object Owner", GOSSIP_SENDER_MAIN, CHANGE_OBJECT_OWNER);
            player->ADD_GOSSIP_ITEM(0, "Change Object Permissions", GOSSIP_SENDER_MAIN, CHANGE_OBJECT_PERMISSIONS);
            player->ADD_GOSSIP_ITEM(4, "Main Menu", GOSSIP_SENDER_MAIN, MAIN_MENU);
            player->PlayerTalkClass->SendGossipMenu(123, item->GetGUID());
            break;

        case SELECT_OBJECT:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case PICKUP_OBJECT:
            gtargetpos = targetpos->GetDstPos();
            player->CastSpell(player, 90103, true);
            ChatHandler(player->GetSession()).PSendSysMessage("You have picked up your item!");
            break;

        case EDIT_OBJECT_POSITION:
            player->PlayerTalkClass->ClearMenus();
            player->ADD_GOSSIP_ITEM(4, "Select Object", GOSSIP_SENDER_MAIN, SELECT_OBJECT);
            player->ADD_GOSSIP_ITEM(0, "Edit X Coordinates", GOSSIP_SENDER_MAIN, EDIT_X);
            player->ADD_GOSSIP_ITEM(0, "Edit Y Coordinates", GOSSIP_SENDER_MAIN, EDIT_Y);
            player->ADD_GOSSIP_ITEM(0, "Edit Z Coordinates", GOSSIP_SENDER_MAIN, EDIT_Z);
            player->ADD_GOSSIP_ITEM(0, "Edit Orientation", GOSSIP_SENDER_MAIN, EDIT_O);
            player->ADD_GOSSIP_ITEM(4, "Main Menu", GOSSIP_SENDER_MAIN, MAIN_MENU);
            player->PlayerTalkClass->SendGossipMenu(123, item->GetGUID());
            break;

        case CHANGE_OBJECT_PERMISSIONS:
            player->PlayerTalkClass->ClearMenus();
            player->ADD_GOSSIP_ITEM(0, "Allow Friends", GOSSIP_SENDER_MAIN, ALLOW_FRIENDS);
            player->ADD_GOSSIP_ITEM(0, "Allow Player", GOSSIP_SENDER_MAIN, ALLOW_PLAYER);
            player->ADD_GOSSIP_ITEM(0, "Allow Guild", GOSSIP_SENDER_MAIN, ALLOW_GUILD);
            player->ADD_GOSSIP_ITEM(0, "Allow Anyone", GOSSIP_SENDER_MAIN, ALLOW_ANYONE);
            player->ADD_GOSSIP_ITEM(0, "Transfer Ownership", GOSSIP_SENDER_MAIN, TRANSFER_OWNERSHIP_ENTRY);
            player->ADD_GOSSIP_ITEM(4, "Main Menu", GOSSIP_SENDER_MAIN, MAIN_MENU);
            player->PlayerTalkClass->SendGossipMenu(123, item->GetGUID());
            break;

        case ALLOW_FRIENDS:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case ALLOW_GUILD:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case ALLOW_ANYONE:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case TRANSFER_OWNERSHIP_ENTRY: //Transfer APT ownership
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case STATISTICS:
            player->PlayerTalkClass->ClearMenus();
            player->ADD_GOSSIP_ITEM(4, "Census", GOSSIP_SENDER_MAIN, CENSUS);
            player->ADD_GOSSIP_ITEM(4, "Deaths", GOSSIP_SENDER_MAIN, DEATHS);
            player->ADD_GOSSIP_ITEM(4, "Main Menu", GOSSIP_SENDER_MAIN, MAIN_MENU);
            player->ADD_GOSSIP_ITEM(4, "Check your objects", GOSSIP_SENDER_MAIN, MAIN_MENU);
            player->PlayerTalkClass->SendGossipMenu(123, item->GetGUID());
            break;

        case CENSUS:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case DEATHS:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        case PORTABLEGOBJECT: //To view how many objects you own & Display permissions for each object
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;

        default:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
            break;
    }

    }

  void OnGossipSelectCode(Player* player, Item* item, uint32 sender, uint32 action, char const* code) // Needed for selecting the player name in Game Object Template.
  {

  switch(action)
   {
    case EDIT_X:
        ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
        break;
    case EDIT_Y:
        ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
        break;
    case EDIT_Z:
        ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
        break;
    case EDIT_O:
        ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
        break;
    case CHANGE_OBJECT_OWNER:
        ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");
        break;
    default:
        break;
   }
  }
};



void AddSC_cs_menustone()
{
    new cs_menustone;
}
