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
        player->ADD_GOSSIP_ITEM(7, "|TInterface\\ICONS\\INV_Misc_GroupLooking:30|t Player", GOSSIP_SENDER_MAIN, PLAYER);
        player->ADD_GOSSIP_ITEM(7, "|TInterface\\ICONS\\INV_Misc_GroupNeedmore:30|t NPC", GOSSIP_SENDER_MAIN, NPC);
        player->ADD_GOSSIP_ITEM(7, "|TInterface\\ICONS\\Ability_Repair:30|t Objects", GOSSIP_SENDER_MAIN, OBJECTS);
        player->ADD_GOSSIP_ITEM(7, "|TInterface\\ICONS\\Ability_Spy:30|t Statistics", GOSSIP_SENDER_MAIN, STATISTICS);
        player->PlayerTalkClass->SendGossipMenu(123, item->GetGUID());
        return true;
    }

    void OnGossipSelect(Player* player, Item* item, uint32 sender, uint32 action)
    {
      switch(action)
      {
        case MAIN_MENU:
            player->PlayerTalkClass->ClearMenus();
            player->ADD_GOSSIP_ITEM(7, "|TInterface\\ICONS\\INV_Misc_GroupLooking:30|t Player", GOSSIP_SENDER_MAIN, PLAYER);
            player->ADD_GOSSIP_ITEM(7, "|TInterface\\ICONS\\INV_Misc_GroupNeedmore:30|t NPC", GOSSIP_SENDER_MAIN, NPC);
            player->ADD_GOSSIP_ITEM(7, "|TInterface\\ICONS\\Ability_Repair:30|t Objects", GOSSIP_SENDER_MAIN, OBJECTS);
            player->ADD_GOSSIP_ITEM(7, "|TInterface\\ICONS\\Ability_Spy:30|t Statistics", GOSSIP_SENDER_MAIN, STATISTICS);
            player->PlayerTalkClass->SendGossipMenu(123, item->GetGUID());

        case PLAYER:
            player->PlayerTalkClass->ClearMenus();
            player->ADD_GOSSIP_ITEM(5, "Release", GOSSIP_SENDER_MAIN, RELEASE_PLAYER); //Release the player from bonds or release the target from the deathstun
            player->ADD_GOSSIP_ITEM(5, "Restrain", GOSSIP_SENDER_MAIN, RESTRAIN_PLAYER); //Tie the player's hands up, so they can't use weapons
            player->ADD_GOSSIP_ITEM(5, "Escort", GOSSIP_SENDER_MAIN, ESCORT_PLAYER); //Force-feed when restrained, Feed player when a playerbot
            player->ADD_GOSSIP_ITEM(5, "Feed ", GOSSIP_SENDER_MAIN, FEED_PLAYER); //Works on Friendly players & Enemy players
            player->ADD_GOSSIP_ITEM(5, "Knockout", GOSSIP_SENDER_MAIN, KNOCKOUT_PLAYER); //Knocking out the target
            player->ADD_GOSSIP_ITEM(5, "Kill", GOSSIP_SENDER_MAIN, KILL_PLAYER); //Executes the player taking one of their lives
            player->ADD_GOSSIP_ITEM(5, "Rob", GOSSIP_SENDER_MAIN, ROB_PLAYER); //Robs 10% of current gold
            player->ADD_GOSSIP_ITEM(7, "Injure", GOSSIP_SENDER_MAIN, INJURE_PLAYER); //Injures the player with appling a debuff
            player->ADD_GOSSIP_ITEM(7, "Main Menu", GOSSIP_SENDER_MAIN,  MAIN_MENU);
            player->PlayerTalkClass->SendGossipMenu(123, item->GetGUID());

        case RELEASE_PLAYER:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");

        case RESTRAIN_PLAYER:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");

        case ESCORT_PLAYER:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");

        case FEED_PLAYER:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");

        case KNOCKOUT_PLAYER:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");

        case KILL_PLAYER:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");

        case ROB_PLAYER:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");


        case INJURE_PLAYER:
            player->PlayerTalkClass->ClearMenus();
            player->ADD_GOSSIP_ITEM(4, "Injure Head", GOSSIP_SENDER_MAIN, INJURE_HEAD); //Reduces cast time and attack speed
            player->ADD_GOSSIP_ITEM(4, "Injure Right Arm", GOSSIP_SENDER_MAIN, INJURE_RIGHT_ARM); //You can't wield anything in right hand
            player->ADD_GOSSIP_ITEM(4, "Injure Left Arm", GOSSIP_SENDER_MAIN, INJURE_LEFT_ARM); //Player can't wield anything in left hand
            player->ADD_GOSSIP_ITEM(4, "Injure Torso", GOSSIP_SENDER_MAIN, INJURE_TORSO); //Reduces stamina and unable to wear plate / mail
            player->ADD_GOSSIP_ITEM(4, "Injure Right Leg", GOSSIP_SENDER_MAIN, INJURE_RIGHT_LEG); //Reduces running speed, if both legs are broken then 80% reduce speed
            player->ADD_GOSSIP_ITEM(4, "Injure Left Leg", GOSSIP_SENDER_MAIN, INJURE_LEFT_LEG); //Reduces running speed, if both legs are broken then 80% reduce speed
            player->ADD_GOSSIP_ITEM(7, "Main Menu", GOSSIP_SENDER_MAIN, MAIN_MENU);
            player->PlayerTalkClass->SendGossipMenu(123, item->GetGUID());


        case INJURE_HEAD:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");


        case INJURE_RIGHT_ARM:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");


        case INJURE_LEFT_ARM:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");


        case INJURE_TORSO:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");


        case INJURE_RIGHT_LEG:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");


        case INJURE_LEFT_LEG:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");


        case NPC:
            player->PlayerTalkClass->ClearMenus();
            player->ADD_GOSSIP_ITEM(4, "Wait", GOSSIP_SENDER_MAIN, WAIT_FOLLOWER); //Makes the NPC wait in its current position
            player->ADD_GOSSIP_ITEM(4, "Follow", GOSSIP_SENDER_MAIN, FOLLOW_FOLLOWER); //NPC will follow the player
            player->ADD_GOSSIP_ITEM(4, "Go to Here", GOSSIP_SENDER_MAIN, GOTO_FOLLOWER); //NPC will go to position and hold
            player->ADD_GOSSIP_ITEM(4, "Attack Here", GOSSIP_SENDER_MAIN, ATTACK_FOLLOWER); //NPC will attack the targeted area
            player->ADD_GOSSIP_ITEM(4, "Stance", GOSSIP_SENDER_MAIN, STANCE_FOLLOWER); //Putting the NPC in an aggressive, defensive, passive stance
            player->ADD_GOSSIP_ITEM(4, "Trade Items", GOSSIP_SENDER_MAIN, TRADE_ITEMS_FOLLOWER); //Trading inventory with NPCs
            player->ADD_GOSSIP_ITEM(4, "Assign Armor & Weapons", GOSSIP_SENDER_MAIN, ASSIGN_ARMOR); //Allows player to dicatate what armor or wepaons NPC should use
            player->ADD_GOSSIP_ITEM(4, "Change Mount", GOSSIP_SENDER_MAIN, CHANGE_MOUNT); //Mount/Dismount a follower, boolean function
            player->ADD_GOSSIP_ITEM(4, "Pay Follower", GOSSIP_SENDER_MAIN, PAY_FOLLOWER); //Bi-weekly you will need to pay followers
            player->ADD_GOSSIP_ITEM(4, "Mark for Death", GOSSIP_SENDER_MAIN, MARK_DEATH); //Marks the creature for death
            player->ADD_GOSSIP_ITEM(7, "Patrols", GOSSIP_SENDER_MAIN, PATROLLING); //Patroling submenu for followers and guild NPCs
            player->ADD_GOSSIP_ITEM(7, "Main Menu", GOSSIP_SENDER_MAIN, MAIN_MENU);
            player->PlayerTalkClass->SendGossipMenu(123, item->GetGUID());

        case WAIT_FOLLOWER:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");

        case FOLLOW_FOLLOWER:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");

        case GOTO_FOLLOWER:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");

        case ATTACK_FOLLOWER:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");

        case STANCE_FOLLOWER:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");

        case TRADE_ITEMS_FOLLOWER:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");

        case ASSIGN_ARMOR:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");

        case CHANGE_MOUNT:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");

        case PAY_FOLLOWER:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");

        case MARK_DEATH:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");

        case PATROLLING:
            player->PlayerTalkClass->ClearMenus();
            player->ADD_GOSSIP_ITEM(4, "Add Waypoint", GOSSIP_SENDER_MAIN, ADD_WAYPOINT); //Adds a waypoint for the patrol route
            player->ADD_GOSSIP_ITEM(4, "Start Patrol", GOSSIP_SENDER_MAIN, START_PATROL); //Begin the patrol
            player->ADD_GOSSIP_ITEM(4, "End Patrol", GOSSIP_SENDER_MAIN, STOP_PATROL); //End the patrol on selected NPC
            player->ADD_GOSSIP_ITEM(7, "Main Menu", GOSSIP_SENDER_MAIN, MAIN_MENU);
            player->ADD_GOSSIP_ITEM(7, "|TInterface\\ICONS\\INV_Misc_GroupLooking:30|t NPC", GOSSIP_SENDER_MAIN, NPC);
            player->PlayerTalkClass->SendGossipMenu(123, item->GetGUID());


        case ADD_WAYPOINT:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");


        case START_PATROL:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");


        case STOP_PATROL:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");


        case OBJECTS:
            player->PlayerTalkClass->ClearMenus();
            player->ADD_GOSSIP_ITEM(4, "Select Object", GOSSIP_SENDER_MAIN, SELECT_OBJECT);
            player->ADD_GOSSIP_ITEM(4, "Pickup Object", GOSSIP_SENDER_MAIN, PICKUP_OBJECT);
            player->ADD_GOSSIP_ITEM(7, "Edit Object Position", GOSSIP_SENDER_MAIN, EDIT_OBJECT_POSITION);
            player->ADD_GOSSIP_ITEM(7, "Change Object Permissions", GOSSIP_SENDER_MAIN, CHANGE_OBJECT_PERMISSIONS);
            player->ADD_GOSSIP_ITEM(7, "Main Menu", GOSSIP_SENDER_MAIN, MAIN_MENU);
            player->PlayerTalkClass->SendGossipMenu(123, item->GetGUID());


        case SELECT_OBJECT:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");


        case PICKUP_OBJECT:
            gtargetpos = targetpos->GetDstPos();
            player->CastSpell(player, 90103, true);


        case EDIT_OBJECT_POSITION:
            player->PlayerTalkClass->ClearMenus();
            player->ADD_GOSSIP_ITEM(4, "Select Object", GOSSIP_SENDER_MAIN, SELECT_OBJECT);
            player->ADD_GOSSIP_ITEM(4, "Edit X Coordinates", GOSSIP_SENDER_MAIN, EDIT_X);
            player->ADD_GOSSIP_ITEM(4, "Edit Y Coordinates", GOSSIP_SENDER_MAIN, EDIT_Y);
            player->ADD_GOSSIP_ITEM(4, "Edit Z Coordinates", GOSSIP_SENDER_MAIN, EDIT_Z);
            player->ADD_GOSSIP_ITEM(4, "Edit Orientation", GOSSIP_SENDER_MAIN, EDIT_O);
            player->ADD_GOSSIP_ITEM(7, "|TInterface\\ICONS\\Ability_Repair:30|t Objects", GOSSIP_SENDER_MAIN, OBJECTS);
            player->ADD_GOSSIP_ITEM(7, "Main Menu", GOSSIP_SENDER_MAIN, MAIN_MENU);
            player->PlayerTalkClass->SendGossipMenu(123, item->GetGUID());


        case CHANGE_OBJECT_PERMISSIONS:
            player->PlayerTalkClass->ClearMenus();
            player->ADD_GOSSIP_ITEM(4, "Select Object", GOSSIP_SENDER_MAIN, SELECT_OBJECT);
            player->ADD_GOSSIP_ITEM(4, "Allow Player", GOSSIP_SENDER_MAIN, ALLOW_PLAYER); //Allows the targeted player to access the selected object
            player->ADD_GOSSIP_ITEM(4, "Allow Friends", GOSSIP_SENDER_MAIN, ALLOW_FRIENDS); //Allow everyone on your friend's list to access the selected object, if no object then access to all objects
            player->ADD_GOSSIP_ITEM(4, "Allow Guild", GOSSIP_SENDER_MAIN, ALLOW_GUILD); //Allow guild to access the selected object, if no object then access to all objects
            player->ADD_GOSSIP_ITEM(4, "Allow Anyone", GOSSIP_SENDER_MAIN, ALLOW_ANYONE); //Allow anyone to access the selected object, if no object then access to all objects
            player->ADD_GOSSIP_ITEM(4, "Transfer Ownership", GOSSIP_SENDER_MAIN, TRANSFER_OWNERSHIP); // The targeted player wiil be the owner the new owner
            player->ADD_GOSSIP_ITEM(7, "|TInterface\\ICONS\\Ability_Repair:30|t Objects", GOSSIP_SENDER_MAIN, OBJECTS);
            player->ADD_GOSSIP_ITEM(7, "Main Menu", GOSSIP_SENDER_MAIN, MAIN_MENU);
            player->PlayerTalkClass->SendGossipMenu(123, item->GetGUID());

        case ALLOW_PLAYER:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");


        case ALLOW_FRIENDS:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");


        case ALLOW_GUILD:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");


        case ALLOW_ANYONE:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");


        case TRANSFER_OWNERSHIP: //Transfer APT ownership
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");


        case STATISTICS:
            player->PlayerTalkClass->ClearMenus();
            player->ADD_GOSSIP_ITEM(4, "Census", GOSSIP_SENDER_MAIN, CENSUS); //Displays in chatbox the top five most populated zones
            player->ADD_GOSSIP_ITEM(4, "Deaths", GOSSIP_SENDER_MAIN, DEATHS); //Displays how many times you've died and how many lives you have.
            player->ADD_GOSSIP_ITEM(4, "Check your objects", GOSSIP_SENDER_MAIN, CHECK_OBJECTS); //Returns all objects you own and their permissions
            player->ADD_GOSSIP_ITEM(7, "Main Menu", GOSSIP_SENDER_MAIN, MAIN_MENU);
            player->PlayerTalkClass->SendGossipMenu(123, item->GetGUID());


        case CENSUS:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");


        case DEATHS:
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");


        case CHECK_OBJECTS: //To view how many objects you own & Display permissions for each object
            ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");


        default:
            player->PlayerTalkClass->ClearMenus();
            break;

      }

    }

  void OnGossipSelectCode(Player* player, Item* item, uint32 sender, uint32 action, char const* code) // Needed for selecting the player name in Game Object Template.
  {

  switch(action)
   {
    case EDIT_X:
        ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");

    case EDIT_Y:
        ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");

    case EDIT_Z:
        ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");

    case EDIT_O:
        ChatHandler(player->GetSession()).PSendSysMessage("This option is not implemented yet.");

    default:
        player->PlayerTalkClass->ClearMenus();
        break;
   }
  }
};

void AddSC_cs_menustone()
{
    new cs_menustone;
}
