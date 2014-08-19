#include "ScriptPCH.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "Player.h"
#include <cstring>
#include "ObjectMgr.h"
#include "MiscFunctions.h"

// added includes required for NPC gossip and player logic

/* NOTE  - Right now, this script doesn't do any actual work besides
           creating new NPC entries within the database, as well as
           deleting them when Aevum_Destroy_NPC is called.

           Further work still needs to be done to have the script handle
           NPC spawning within the actual world, player associations,
           and pretty much everything else at the moment. */

/* TODO: - Add name querying to get a name and a surname from the database.
           Progress: 100% - Main function complete; needs some placeholder names for testing.

         - Add a function that generates random statistics for each NPC.
           Possibly make these statistics vary depending on NPC race and type/class.
           Progress: 50% - Basic NPC stat gen done. Mercenary stat gen is a WIP.

         - Add proper factions for each NPC type.
           Progress: 0% - Need to figure out how exactly the faction bit mask works in practice.

         - Add a gender option.
           Progress: 70% - Gender is currently random, but the name and model ids support the selection.

         - Figure out how to implement random appearances when generating a companion.
           Progress: 20% - Did some simple research on random appearance generation.
                           Seems decently complex - will be done further down the road.

         - Find a proper modelid for each NPC type that supports the aforementioned appearance
           variety, taking into account different races.
           Progress: 30% - Currently using bugged player modelids for testing.

         - Add logic for checking whether the player has enough money
           to recruit one NPC or several NPCs at once.
           Progress: 0% - This can wait until the basic NPC systems are in place.

         - Possibly add more parameters in case we might want to add
           recruitment NPCs that allow the player to specify some
           specific traits they want for their companions.
           Progress: 30% - Tie in with stat variety based on NPC race.

         - Implement a function that is able to actively update the
           NPC status (rank, custom statistics, et cetera.)
           Progress: 20% - Did some of the basic function design.

         - Elsewhere, add functionality that allows the player to summon
           and desummon the generated NPCs.
           Progress: 0% - Again, this would require properly generated NPCs.

         - Design the framework that allows NPCs to be associated with
           custom scripts dynamically.
           Progress: 0% - The most complicated aspect - save for when basic NPCs are in. */

/* NOTE - THERE IS CURRENTLY NO ERROR CHECKING AS TO SEE WHETHER
          AN NPC ALREADY EXISTS WITHIN A CERTAIN DATABASE ENTRY.
          DATABASE QUERIES AND ERROR CHECKS WILL BE ADDED LATER. */

/* Maybe we want to put all the DB enumerators up top. Right now they work well as anonymous enums, though. */

/* Yes, we do: I'm moving all the enums up here and giving them names. They might be moved back later, once
   everything related to the main functions has been finalized, ensuring that things are promptly scoped.
   Don't forget to anonymize them again once they're relocated to their respective functions, by the way.   */

// the different class archetypes we currently have
      // melee units       ranged units            caster units        healer units
enum AEVUM_DB_COMPANION_TYPES // the basic unit type
    { AEVUM_TYPE_PHYSICAL,  AEVUM_TYPE_MAGICAL };

enum AEVUM_DB_COMPANION_UNITS // the two basic units
    { COMPANION_RECRUIT, COMPANION_APPRENTICE };

enum AEVUM_DB_COMPANION_MERCENARY_UNITS // the different mercenary units we currently have
    { MERCENARY_BANDIT,   MERCENARY_HUNTER,       MERCENARY_HEDGEWIZARD, MERCENARY_MENDER,
      MERCENARY_DESERTER, MERCENARY_RANGER,       MERCENARY_SCHOLAR,     MERCENARY_MEDIC,
      MERCENARY_VETERAN,  MERCENARY_SHARPSHOOTER, MERCENARY_THAUMATURGE, MERCENARY_PHYSICIAN };

enum AEVUM_DB_COMPANION_RANKS // these are internal: should reflect Warcraft lore and individual faction hierarchies in the actual game
    { RANK_CONSCRIPT, RANK_SQUADDIE, RANK_SERGEANT,
      RANK_CAPTAIN,   RANK_COLONEL,  RANK_COMMANDER };

enum AEVUM_DB_COMPANION_IDRANGES // Companion ID ranges within the creature_template database
    { DB_FIRST_HUMAN    = 50000, DB_LAST_HUMAN    = 51999,
      DB_FIRST_DWARF    = 52000, DB_LAST_DWARF    = 52999,
      DB_FIRST_GNOME    = 53000, DB_LAST_GNOME    = 53999,
      DB_FIRST_NIGHTELF = 54000, DB_LAST_NIGHTELF = 54999,
      DB_FIRST_DRAENEI  = 55000, DB_LAST_DRAENEI  = 55999,

      DB_FIRST_ORC      = 60000, DB_LAST_ORC      = 61999,
      DB_FIRST_TROLL    = 62000, DB_LAST_TROLL    = 62999,
      DB_FIRST_TAUREN   = 63000, DB_LAST_TAUREN   = 63999,
      DB_FIRST_UNDEAD   = 64000, DB_LAST_UNDEAD   = 64999,
      DB_FIRST_BLOODELF = 65000, DB_LAST_BLOODELF = 65999 };

enum AEVUM_DB_COMPANION_MODELS // Corresponding models for each race/gender
    { AEVUM_HUMAN    = 49,    AEVUM_ORC      = 51,   AEVUM_DWARF = 53,   AEVUM_NIGHTELF = 55,
      AEVUM_UNDEAD   = 57,    AEVUM_TAUREN   = 59,   AEVUM_TROLL = 1478, AEVUM_GNOME    = 1563,
      AEVUM_BLOODELF = 15476, AEVUM_DRAENEI  = 16125 }; // BE reversed: female = 15475

enum AEVUM_DB_MAINFACTIONS
    { AEVUM_STORMWIND = 11,   AEVUM_IRONFORGE = 57,  AEVUM_GNOMEREGAN   = 64,   AEVUM_UNDERCITY = 71,
      AEVUM_DARNASSUS = 79,   AEVUM_ORGRIMMAR = 85,  AEVUM_THUNDERBLUFF = 105,  AEVUM_SENJIN    = 877,
      AEVUM_EXODAR    = 1639, AEVUM_SILVERMOON = 1603};



/*
struct Aevum_NPCstats // used later to keep companion stats in memory rather than constantly querying the DB
{
    uint8 energy_regen    = 0;
    uint8 energy          = 0;
    uint8 health          = 0;
    uint8 bravery         = 0;
    uint8 reactions       = 0;
    uint8 melee_accuracy  = 0;
    uint8 ranged_accuracy = 0;
    uint8 throw_accuracy  = 0;
    uint8 strength        = 0;
    uint8 magic_strength  = 0;
    uint8 magic_accuracy  = 0;

    uint8 npcRank         = 0;
    uint8 npcMorale       = 0;
    uint8 npcExperience   = 0;
};
*/
//std::string Aevum_Generate_First_Name(); NYI - possibly could draw on native WoW language files
//std::string Aevum_Generate_Last_Name();  NYI - same as above

std::string Aevum_DB_Generate_Random_Name( Races race, Gender gender )
{
    QueryResult name_result    = WorldDatabase.PQuery("SELECT name FROM aevum_companion_names WHERE race = '%u' AND type = '%u' ORDER BY RAND();", race, gender);
    Field *     name_field     = name_result->Fetch();
    std::string name           = name_field[0]->GetString();

    QueryResult surname_result = WorldDatabase.PQuery("SELECT name FROM aevum_companion_names WHERE race = '%u' ORDER BY RAND();", race);
    Field *     surname_field  = surname_result->Fetch();
    std::string surname        = surname_field[0]->GetString();

    std::string generated_name = ( name + " " ) + surname;
    return generated_name;
}

/* fuck all this shit, implement later we xcom now

void Aevum_Generate_Stats( uint8 npcRank, uint8 npcType )
{
    // holocaust.cpp
}

void Aevum_DB_Update_NPC_Name( uint32 npcEntry )
{
    // Has your dwarf companion grown badass enough to deserve the name 'Trollslayer'? Possible feature.
}

void Aevum_DB_Update_NPC_Stats( uint32 npcEntry, uint8 npcRank, uint8 npcType )
{
    // This function takes care of the leveling logic once an NPC has gained enough experience.

    uint8 energy_regen,   energy,          health,   bravery,        reactions;
    uint8 melee_accuracy, ranged_accuracy, strength, magic_strength, magic_accuracy;

    Aevum_Generate_Stats( npcRank, npcType );
}

void Aevum_DB_Initialize_Mercenary_Stats( uint32 npcEntry, uint8 npcType )
{
    // Mercenary stat generation goes here.
}

*/

void Aevum_DB_Initialize_Companion_Stats( uint32 npcEntry, uint8 npcType )
{
    // will be redone later to avoid magic numbers once testing is in progress
    uint8 energy_regen    = urand( 1, 3 );
    uint8 energy          = urand( 1, 3 );
    uint8 health          = 0; // relies on NPC type, generated in switch statement
    uint8 bravery         = urand( 1, 3 );
    uint8 reactions       = 0; // relies on NPC type, generated in switch statement
    uint8 melee_accuracy  = 0; // relies on NPC type, generated in switch statement
    uint8 ranged_accuracy = 0; // relies on NPC type, generated in switch statement
    uint8 strength        = 0; // relies on NPC type, generated in switch statement
    uint8 magic_strength  = 0; // relies on NPC type, generated in switch statement
    uint8 magic_accuracy  = 0; // relies on NPC type, generated in switch statement

    switch(npcType)
    {
        case AEVUM_TYPE_MELEE:  health          = urand( 2, 4 );
                                reactions       = urand( 1, 3 );
                                melee_accuracy  = urand( 1, 3 );
                                ranged_accuracy = urand( 1, 3 );
                                strength        = urand( 1, 3 );
                                magic_strength  = urand( 0, 1 );
                                magic_accuracy  = urand( 0, 1 );
                                break;

        case AEVUM_TYPE_MAGIC:  health          = urand( 1, 3 );
                                reactions       = urand( 0, 2 );
                                melee_accuracy  = urand( 0, 2 );
                                ranged_accuracy = urand( 0, 2 );
                                strength        = urand( 0, 2 );
                                magic_strength  = urand( 1, 3 );
                                magic_accuracy  = urand( 1, 3 );
                                break;
    }

    // write the generated stats to the chosen NPC's stat entry in the companion stat DB
    WorldDatabase.PExecute("INSERT INTO 'aevum_companion_stats' ('entry', 'energy_regen', 'energy', 'health', 'bravery', 'reactions', 'melee_accuracy', 'ranged_accuracy', 'strength', 'magic_strength', 'magic_accuracy' )",
                           "VALUES (%u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u);", npcEntry, energy_regen, energy, health, bravery, reactions, melee_accuracy, ranged_accuracy, strength, magic_strength, magic_accuracy );
}

bool Aevum_DB_Generate_Companion( uint8 race, uint8 gender )
{
    uint32 modelid   = 0; // determined by race/gender
    uint16 faction   = 0; // locked
    uint32 min_entry = 0; // for SQL statements
    uint32 max_entry = 0;

    switch(race)
    { // we use the gender value as an offset for picking a modelid
    case RACE_HUMAN:         modelid = AEVUM_HUMAN    + gender; faction = AEVUM_STORMWIND;
                             min_entry = DB_FIRST_HUMAN;    max_entry = DB_LAST_HUMAN;      break;
    case RACE_DWARF:         modelid = AEVUM_DWARF    + gender; faction = AEVUM_IRONFORGE;
                             min_entry = DB_FIRST_DWARF;    max_entry = DB_LAST_DWARF;      break;
    case RACE_GNOME:         modelid = AEVUM_GNOME    + gender; faction = AEVUM_GNOMEREGAN;
                             min_entry = DB_FIRST_GNOME;    max_entry = DB_LAST_GNOME;      break;
    case RACE_NIGHTELF:      modelid = AEVUM_NIGHTELF + gender; faction = AEVUM_DARNASSUS;
                             min_entry = DB_FIRST_NIGHTELF; max_entry = DB_LAST_NIGHTELF;   break;
    case RACE_DRAENEI:       modelid = AEVUM_DRAENEI  + gender; faction = AEVUM_EXODAR;
                             min_entry = DB_FIRST_DRAENEI;  max_entry = DB_LAST_DRAENEI;    break;
    case RACE_ORC:           modelid = AEVUM_ORC      + gender; faction = AEVUM_ORGRIMMAR;
                             min_entry = DB_FIRST_ORC;      max_entry = DB_LAST_ORC;        break;
    case RACE_TROLL:         modelid = AEVUM_TROLL    + gender; faction = AEVUM_SENJIN;
                             min_entry = DB_FIRST_TROLL;    max_entry = DB_LAST_TROLL;      break;
    case RACE_TAUREN:        modelid = AEVUM_TAUREN   + gender; faction = AEVUM_THUNDERBLUFF;
                             min_entry = DB_FIRST_TAUREN;   max_entry = DB_LAST_TAUREN;     break;
    case RACE_UNDEAD_PLAYER: modelid = AEVUM_UNDEAD   + gender; faction = AEVUM_UNDERCITY;
                             min_entry = DB_FIRST_UNDEAD;   max_entry = DB_LAST_UNDEAD;     break;
    case RACE_BLOODELF:      modelid = AEVUM_BLOODELF - gender; faction = AEVUM_SILVERMOON;
                             min_entry = DB_FIRST_BLOODELF; max_entry = DB_LAST_BLOODELF;   break;
    } // special case: blood elves are gay and have reversed gender model ids

    uint8 unit_class = urand(AEVUM_TYPE_PHYSICAL, AEVUM_TYPE_MAGICAL); // NPC archetype randomization

    /* Bad News Bears 3.0: The Rewrite */

    std::string name = Aevum_Generate_Random_Name( race, gender ); // we draw on the name DB to get a fitting name for the race

    // add a new NPC to the creature_template DB
    WorldDatabase.PExecute("UPDATE creature_template SET modelid1 = %u, SET name = %s, SET minlevel = 75, SET maxlevel = 75, SET exp 2, ",
                           "SET faction %u, SET unit_class = 1 WHERE entry BETWEEN '%u' AND '%u' LIMIT 1;", modelid, name, faction, min_entry, max_entry);

    // TODO: Find a way to query the above SQL statement to get the picked entry back so we can generate stats.
    Aevum_DB_Initialize_Companion_Stats( npcEntry, type ); // generate random stats and write them to the creature's companion stat database
    return true; // assume success like the happy retards we are
}

void Aevum_DB_Destroy_NPC( uint32 npcEntry )
{
    // Called after death and de-spawn: This function just clears the companion entries from the creature and companion stat tables.
    if ( !( npcEntry < DB_FIRST_HUMAN_COMPANION ) || !( npcEntry > DB_LAST_BLOODELF_COMPANION ) )// check that we only delete randomized NPCs
    {
        WorldDatabase.PExecute("DELETE FROM 'creature_template' WHERE entry = '%u';", npcEntry);
        WorldDatabase.PExecute("DELETE FROM 'aevum_companion_stats' WHERE entry = '%u';", npcEntry);
    }
}

/* Recruitment Testing NPC code below */

enum AEVUM_RECRUITER_OPTIONS
    { HIRE_HUMAN = 1001, HIRE_DWARF, HIRE_GNOME,  HIRE_NIGHTELF, HIRE_DRAENEI,
      HIRE_ORC,          HIRE_TROLL, HIRE_TAUREN, HIRE_UNDEAD,   HIRE_BLOODELF,

      HIRE_FEMALE, HIRE_MALE };

class cs_recruiter : public CreatureScript
{
public:
    cs_recruiter() : CreatureScript("cs_recruiter") { }

    void Insert_Gender_Selections()
    {
        player->PlayerTalkClass->ClearMenus();
        player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "Male.",   GOSSIP_SENDER_MAIN, HIRE_MALE   );
        player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "Female.", GOSSIP_SENDER_MAIN, HIRE_FEMALE );
        player->PlayerTalkClass->SendGossipMenu(90030, creature->GetGUID());
    }

    bool OnGossipHello(Player * player, Creature * creature)
    {
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I want to hire an NPC.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        player->PlayerTalkClass->SendGossipMenu(90030, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player * player, Creature * creature, uint32 sender, uint32 actions)
    {
        uint8 racechoice   = 0; // unknown: needs to be selected
        uint8 genderchoice = 0; // male by default

        player->PlayerTalkClass->ClearMenus();
        switch(actions)
        {
        case GOSSIP_ACTION_INFO_DEF+1:
        {
            player->PlayerTalkClass->ClearMenus();
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "I want to hire a Human.",     GOSSIP_SENDER_MAIN, HIRE_HUMAN    );
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "I want to hire a Dwarf.",     GOSSIP_SENDER_MAIN, HIRE_DWARF    );
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "I want to hire a Gnome.",     GOSSIP_SENDER_MAIN, HIRE_GNOME    );
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "I want to hire a Night Elf.", GOSSIP_SENDER_MAIN, HIRE_NIGHTELF );
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "I want to hire a Draenei.",   GOSSIP_SENDER_MAIN, HIRE_DRAENEI  );
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "I want to hire an Orc.",      GOSSIP_SENDER_MAIN, HIRE_ORC      );
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "I want to hire a Troll.",     GOSSIP_SENDER_MAIN, HIRE_TROLL    );
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "I want to hire a Tauren.",    GOSSIP_SENDER_MAIN, HIRE_TAUREN   );
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "I want to hire a Forsaken.",  GOSSIP_SENDER_MAIN, HIRE_UNDEAD   );
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, "I want to hire a Blood Elf.", GOSSIP_SENDER_MAIN, HIRE_BLOODELF );
            player->PlayerTalkClass->SendGossipMenu(90030, creature->GetGUID());
            break;
        }
        case HIRE_FEMALE:
        {
            genderchoice = GENDER_FEMALE;
        }
        case HIRE_MALE:
        {
            player->PlayerTalkClass->ClearMenus();
            Aevum_DB_Generate_Companion(racechoice, genderchoice);
            player->PlayerTalkClass->SendGossipMenu(90030, creature->GetGUID());
            player->CLOSE_GOSSIP_MENU();
            break;
        }
        case HIRE_HUMAN:
        {
            racechoice = RACE_HUMAN;
            Insert_Gender_Selections();
            break;
        }
        case HIRE_DWARF:
        {
            racechoice = RACE_DWARF;
            Insert_Gender_Selections();
            break;
        }
        case HIRE_GNOME:
        {
            racechoice = RACE_GNOME;
            Insert_Gender_Selections();
            break;
        }
        case HIRE_NIGHTELF:
        {
            racechoice = RACE_NIGHTELF;
            Insert_Gender_Selections();
            break;
        }
        case HIRE_DRAENEI:
        {
            racechoice = RACE_DRAENEI;
            Insert_Gender_Selections();
            break;
        }
        case HIRE_ORC:
        {
            racechoice = RACE_ORC;
            Insert_Gender_Selections();
            break;
        }
        case HIRE_TROLL:
        {
            racechoice = RACE_TROLL;
            Insert_Gender_Selections();
            break;
        }
        case HIRE_TAUREN:
        {
            racechoice = RACE_TAUREN;
            Insert_Gender_Selections();
            break;
        }
        case HIRE_UNDEAD:
        {
            racechoice = RACE_UNDEAD_PLAYER;
            Insert_Gender_Selections();
            break;
        }
        case HIRE_BLOODELF:
        {
            racechoice = RACE_BLOODELF;
            Insert_Gender_Selections();
            break;
        }
        return true;
        }
    }
};

void AddSC_aevum_recruiter_npc()
{
    new cs_recruiter;
}
