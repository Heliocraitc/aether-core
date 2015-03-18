#ifndef MENU_STONE_H
#define MENU_STONE_H

/* Interface Icons */
#define HUMAN_MALE "|TInterface/ICONS/Achievement_Character_Human_Male:30|t Player"
#define HUMAN_FEMALE "|TInterface/ICONS/Achievement_Character_Human_Female:30|t Player"
#define DWARF_MALE "|TInterface/ICONS/Achievement_Character_Dwarf_Male:30|t Player"
#define DWARF_FEMALE "|TInterface/ICONS/Achievement_Character_Dwarf_Female:30|t Player"
#define NIGHTELF_MALE "|TInterface/ICONS/Achievement_Character_Nightelf_Male:30|t Player"
#define NIGHTELF_FEMALE "|TInterface/ICONS/Achievement_Character_Nightelf_Female:30|t Player"
#define GNOME_MALE "|TInterface/ICONS/Achievement_Character_Gnome_Male:30|t Player"
#define GNOME_FEMALE "|TInterface/ICONS/Achievement_Character_Gnome_Female:30|t Player"
#define DRAENEI_MALE "|TInterface/ICONS/Achievement_Character_Draenei_Male:30|t Player"
#define DRAENEI_FEMALE "|TInterface/ICONS/Achievement_Character_Draenei_Female:30|t Player"
#define ORC_MALE "|TInterface/ICONS/Achievement_Character_Orc_Female:30|t Player"
#define ORC_FEMALE "|TInterface/ICONS/Achievement_Character_Orc_Male:30|t Player"
#define FORSAKEN_MALE "|TInterface/ICONS/Achievement_Character_Undead_Male:30|t Player"
#define FORSAKEN_FEMALE "|TInterface/ICONS/Achievement_Character_Undead_Female:30|t Player"
#define TAUREN_MALE "|TInterface/ICONS/Achievement_Character_Tauren_Male:30|t Player"
#define TAUREN_FEMALE "|TInterface/ICONS/Achievement_Character_Tauren_Female:30|t Player"
#define TROLL_MALE "|TInterface/ICONS/Achievement_Character_Troll_Male:30|t Player"
#define TROLL_FEMALE "|TInterface/ICONS/Achievement_Character_Troll_Female:30|t Player"
#define BLOODELF_MALE "|TInterface/ICONS/Achievement_Character_Bloodelf_Male:30|t Player"
#define BLOODELF_FEMALE "|TInterface/ICONS/Achievement_Character_Bloodelf_Female:30|t Player"

enum Aetherstone {
    MAIN_MENU = 1,
    PLAYER,
    RELEASE_PLAYER,
    RESTRAIN_PLAYER,
    ESCORT_PLAYER,
    FEED_PLAYER,
    KNOCKOUT_PLAYER,
    KILL_PLAYER,
    ROB_PLAYER,
    INJURE_PLAYER,
    INJURE_HEAD,
    INJURE_RIGHT_ARM,
    INJURE_LEFT_ARM,
    INJURE_TORSO,
    INJURE_RIGHT_LEG,
    INJURE_LEFT_LEG,
    NPC,
    FOLLOWER,
    WAIT_FOLLOWER,
    FOLLOW_FOLLOWER,
    GOTO_FOLLOWER,
    ATTACK_FOLLOWER,
    STANCE_FOLLOWER,
    TRADE_ITEMS_FOLLOWER,
    CHANGE_MOUNT,
    PAY_FOLLOWER,
    ASSIGN_ARMOR,
    PATROLLING,
    ADD_WAYPOINT,
    START_PATROL,
    STOP_PATROL,
    OBJECTS,
    SELECT_OBJECT,
    PICKUP_OBJECT,
    EDIT_OBJECT_POSITION,
    CHANGE_OBJECT_PERMISSIONS,
    ALLOW_PLAYER,
    ALLOW_FRIENDS,
    ALLOW_GUILD,
    ALLOW_ANYONE,
    TRANSFER_OWNERSHIP,
    STATISTICS,
    CENSUS,
    DEATHS,
    CHECK_OBJECTS,
    EDIT_X,
    EDIT_Y,
    EDIT_Z,
    EDIT_O

    };
#endif
