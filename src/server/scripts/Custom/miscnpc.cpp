#include "ScriptPCH.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "Player.h"
#include <cstring>
#include "ObjectMgr.h"
#include "MiscFunctions.h"
class cs_dalarangatekeeper : public CreatureScript
{
public:
    cs_dalarangatekeeper() : CreatureScript("cs_dalarangatekeeper") { }

  bool OnGossipHello(Player * player, Creature * creature)
    {
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I wish to enter Dalaran.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        player->PlayerTalkClass->SendGossipMenu(90025, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player * player, Creature * creature, uint32 sender, uint32 actions)
    {
        player->PlayerTalkClass->ClearMenus();

        switch(actions)
        {
        case GOSSIP_ACTION_INFO_DEF+1:
        {
            switch(player->getClass())
            {
            case CLASS_MAGE:
                player->TeleportTo(0, 127.054245, 313.983093, 42.155067, 0.384183,0);
                creature->MonsterWhisper("Welcome to Dalaran, learn well here.", player, true);
                break;
            case CLASS_WARLOCK:
                player->TeleportTo(0, 127.054245, 313.983093, 42.155067, 0.384183,0);
                creature->MonsterWhisper("Welcome to Dalaran, learn well here.", player, true);
                break;
            default:
                creature->MonsterWhisper("The Magocracy does not wish for non-magic users to enter the city.", player, false);
                break;
            }
            player->CLOSE_GOSSIP_MENU();
            break;
        }
        return true;
        }
    }
};

class cs_cartographer : public CreatureScript
{
public:
    cs_cartographer() : CreatureScript("cs_cartographer") {}

    bool OnGossipHello(Player * player, Creature * creature)
    {
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Captial Cities", GOSSIP_SENDER_MAIN, 1000);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Zones", GOSSIP_SENDER_MAIN, 2000);
        player->PlayerTalkClass->SendGossipMenu(91000, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player * player, Creature * creature, uint32 sender, uint32 actions)
    {
        player->PlayerTalkClass->ClearMenus();
        uint8 pRace = player->getRace();
        switch(actions)
        {
        case 1000:
            player->PlayerTalkClass->ClearMenus();
            switch(pRace)
            {/*Alliance*/
            case RACE_HUMAN:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Stormwind", GOSSIP_SENDER_MAIN, 1001);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Ironforge", GOSSIP_SENDER_MAIN, 1002);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Theramore", GOSSIP_SENDER_MAIN, 1009);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Dalaran", GOSSIP_SENDER_MAIN, 1010);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Back", GOSSIP_SENDER_MAIN, 1050);
                break;
            case RACE_DWARF:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Stormwind", GOSSIP_SENDER_MAIN, 1001);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Ironforge", GOSSIP_SENDER_MAIN, 1002);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Theramore", GOSSIP_SENDER_MAIN, 1009);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Back", GOSSIP_SENDER_MAIN, 1050);
                break;
            case RACE_GNOME:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Stormwind", GOSSIP_SENDER_MAIN, 1001);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Ironforge", GOSSIP_SENDER_MAIN, 1002);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Theramore", GOSSIP_SENDER_MAIN, 1009);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Gnomeregan", GOSSIP_SENDER_MAIN, 1011);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Back", GOSSIP_SENDER_MAIN, 1050);
                break;
            case RACE_NIGHTELF:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Darnassus", GOSSIP_SENDER_MAIN, 1004);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Back", GOSSIP_SENDER_MAIN, 1050);
                break;
            case RACE_DRAENEI:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Exodar", GOSSIP_SENDER_MAIN, 1003);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Back", GOSSIP_SENDER_MAIN, 1050);
                break;
            /*Horde*/
            case RACE_ORC:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Orgrimmar", GOSSIP_SENDER_MAIN, 1005);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Thunder Bluff", GOSSIP_SENDER_MAIN, 1007);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Back", GOSSIP_SENDER_MAIN, 1050);
                break;
            case RACE_TROLL:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Orgrimmar", GOSSIP_SENDER_MAIN, 1005);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Thunder Bluff", GOSSIP_SENDER_MAIN, 1007);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Echo Isles", GOSSIP_SENDER_MAIN, 1012);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Back", GOSSIP_SENDER_MAIN, 1050);
                break;
            case RACE_TAUREN:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Orgrimmar", GOSSIP_SENDER_MAIN, 1005);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Thunder Bluff", GOSSIP_SENDER_MAIN, 1007);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Back", GOSSIP_SENDER_MAIN, 1050);
                break;
            case RACE_UNDEAD_PLAYER:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Undercity", GOSSIP_SENDER_MAIN, 1006);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Back", GOSSIP_SENDER_MAIN, 1050);
                break;
            case RACE_BLOODELF:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Silvermoon", GOSSIP_SENDER_MAIN, 1008);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Back", GOSSIP_SENDER_MAIN, 1050);
                break;
            default:
                break;
            }
            player->PlayerTalkClass->SendGossipMenu(91000, creature->GetGUID());
            break;
        case 1001: //Stormwind
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, -8960.14f, 516.266f, 96.3568f, 0.0f);
            break;
        case 1002: //Ironforge
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, -4924.07f, -951.95f, 501.55f, 5.40f);
            break;
        case 1003: //Exodar
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(530, -3954.20f, -11656.54f, -138.69f, 0.0f);
            break;
        case 1004: //Darnassus
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, 9947.52f, 2482.73f, 1316.21f, 0.0f);
            break;
        case 1005: //Orgrimmar
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, 1552.5f, -4420.66f, 8.94802f, 0.0f);
            break;
        case 1006: //Undercity
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, 1819.71f, 238.79f, 60.5321f, 0.0f);
            break;
        case 1007: //Thunderbluff
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, -1290.0f, 147.033997f, 129.682007f, 4.919000f);
            break;
        case 1008: //Silvermoon
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(530, 9338.74f, -7277.27f, 13.7895f, 0.0f);
            break;
        case 1009: //Theramore
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, -3641.3f, -4358.93f, 9.35467f, 3.81559f);
            break;
        case 1010: //Dalaran
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, 81.5438f, 255.932f, 41.7007f, 0.718756f);
            break;
        case 1011: //Gnomeregan
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, -5163.54f, 925.423f, 257.181f, 1.57423f);
            break;
        case 1012: //Echo Isles
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, -1041.59f, -5346.67f, 0.218679f, 4.0102f);
            break;
        case 1050: //<-Back
            player->PlayerTalkClass->ClearMenus();
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Captial Cities", GOSSIP_SENDER_MAIN, 1000);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Towns", GOSSIP_SENDER_MAIN, 2000);
            player->PlayerTalkClass->SendGossipMenu(91000, creature->GetGUID());
            break;
        case 2000:
            player->PlayerTalkClass->ClearMenus();
            switch(pRace)
            {/*Alliance*/
            case RACE_HUMAN:
                TeleporterFunctions::ADD_HUMAN_ZONES(player);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Back", GOSSIP_SENDER_MAIN, 1050);
                break;
            case RACE_DWARF:
                TeleporterFunctions::ADD_DWARF_ZONES(player);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Back", GOSSIP_SENDER_MAIN, 1050);
                break;
            case RACE_GNOME:
                TeleporterFunctions::ADD_GNOME_ZONES(player);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Back", GOSSIP_SENDER_MAIN, 1050);
                break;
            case RACE_NIGHTELF:
                TeleporterFunctions::ADD_NIGHTELF_ZONES(player);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Back", GOSSIP_SENDER_MAIN, 1050);
                break;
            case RACE_DRAENEI:
                TeleporterFunctions::ADD_DRAENEI_ZONES(player);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Back", GOSSIP_SENDER_MAIN, 1050);
                break;
            /*Horde*/
            case RACE_ORC:
                TeleporterFunctions::ADD_ORC_ZONES(player);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Back", GOSSIP_SENDER_MAIN, 1050);
                break;
            case RACE_TROLL:
                TeleporterFunctions::ADD_TROLL_ZONES(player);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Back", GOSSIP_SENDER_MAIN, 1050);
                break;
            case RACE_TAUREN:
                TeleporterFunctions::ADD_TAUREN_ZONES(player);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Back", GOSSIP_SENDER_MAIN, 1050);
                break;
            case RACE_UNDEAD_PLAYER:
                TeleporterFunctions::ADD_UNDEAD_PLAYER_ZONES(player);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Back", GOSSIP_SENDER_MAIN, 1050);
                break;
            case RACE_BLOODELF:
                TeleporterFunctions::ADD_BLOOELF_ZONES(player);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Back", GOSSIP_SENDER_MAIN, 1050);
                break;
            }
            player->PlayerTalkClass->SendGossipMenu(91000, creature->GetGUID());
            break;
        /*Human*/
        case 2001: //Elwynn Forest->Goldshire
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0,-9448.55,68.236,56.3225,2.1115);
            break;
        case 2002: //Redridge Mountains->Lakeshire
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, -9266.59, -2188.77,64.0892, 2.10205);
            break;
        case 2003: //Duskwood->Darkshire
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0,-10573,-1182.51,28.0148,0.309022);
            break;
        case 2004: //Westfall->Sentinel Hill
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0,-10624.5,1096.66,33.7641,1.31041);
            break;
        case 2005: //Blasted Lands->Nethergarde Keep
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0,-10999.8,-3380.08,62.2525,4.63501);
            break;
        case 2006: //Burning Stepps->Morgan's Vigil
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0,-8372.77,-2754.46,186.622,3.43486);
            break;
        case 2007: //Wetlands->Menethil Harbor
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0,-3769.32,-744.26,8.01027,1.95752);
            break;
        case 2008: //Arathi Highlands->Refuge Pointe
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0,-1246.61,-2529.32,20.6098,0.741709);
            break;
        case 2009: //Hillsbrad Foothills->Southshore
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0,-853.221,-533.529,9.98556,0.242866);
            break;
        case 2010: //Western Plaguelands->Chillwind Camp
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0,967.964,-1443.99,65.0399,2.05398);
            break;
        case 2011: //Eastern Plaguelands->Light's Hope Chapel
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0,2279.65,-5310.01,87.0759,5.07618);
            break;
        case 2012: //Stranglethorn Vale->Booty Bay
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0,-14297.2,530.993,8.77916,3.98863);
            break;
        case 2013: //Tanaris->Gadgetzan
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1,-7177.15,-3785.34,8.36981,6.10237);
            break;
        case 2014: //Un'goro Crater->Marshal's Refuge
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1,-6152.25,-1087.6,-201.435,0.707637);
            break;

        /*Dwarf*/
        case 2020: //Loch Modan->Thelsamar
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0,-5352.54,-2948.53,323.78,5.34258);
            break;
        case 2021: //Dun Morogh->Kharanos
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0,-5597.31,-483.398,396.981,3.17566);
            break;
        case 2022: //Badlands->Angor Fortress
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0,-6398.46,-3166.67,299.812,0.769213);
            break;
        case 2023: //Searing George->Thorium Point
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0,-6506.47,-1149.95,307.708,4.18256);
            break;
        case 2024: //Wetlands->Dun Modr
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0,-2600.48,-2350.81,82.9572,0.914501);
            break;
        case 2025: //Hillsbrad Foothills->Dun Garok
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0,-1256.99,-1189.47,38.9804,3.82979);
            break;
        case 2026: //Hinterlands->Aerie Peak
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0,260.366,-2125.21,119.565,3.18494);
            break;

        /*Gnome*/
        //None

        /*Night Elf*/
        case 2030: //Teldrassil->Dolanaar
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1,9848.37,966.953,1306.38,3.77457);
            break;
        case 2031: //Darkshore->Auberdine
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1,6501.4,481.607,6.27062,1.70033);
            break;
        case 2032: //Felwood->Emerald Sanctuary
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1,3986.71,-1293.58,250.144,5.74591);
            break;
        case 2033: //Moonglade->Nighthaven
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1,7966.85,-2491.04,487.734,3.20562);
            break;
        case 2034: //Winterspring->Everlook
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1,6725.69,-4619.44,720.909,4.66802);
            break;
        case 2035: //Ashenvale->Astranaar
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1,2676.19,-422.905,107.123,0.648691);
            break;
        case 2036: //Azshara->Talrendis Point
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1,2735.06,-3867.44,98.6548,3.56139);
            break;
        case 2037: //Stonetalon Mountains->Stonetalon Peak
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1,2678.38,1497.46,233.869,6.26038);
            break;
        case 2038: //Desolace->Nijel's Point
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1,176.426,1309.76,190.18,0.556817);
            break;
        case 2039: //Ferelas->Feathermoon Stronghold
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1,-4317.47,3287.35,18.2864,3.12825);
            break;
        case 2040: //Silithus->Cenarion Hold
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1,-6818.09,733.814,41.5661,2.3082);
            break;

        /*Draenei*/
        case 2050: //Azuremyst Isle->Azure Watch
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(530,-4190.85,-12516.5,44.5276,1.34225);

            break;
        case 2051: //Bloodmyst Isle->Blood Watch
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(530,-1944.5,-11873.7,49.3983,6.04835);
            break;

        /*Orc*/
        case 2060: //Durotar->Razorhill
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1,326.81,-4706.65,15.3665,4.16414);
            break;
        case 2061: //Barrens->Crossroads
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1,-452.84,-2650.76,95.5209,0.241081);
            break;
        case 2062: //Barrens->Camp Taurajo
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1,-2363.11,-1913.78,95.7829,0.165556);
            break;
        case 2063: //Barrens->Ratchet
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1,-956.664,-3754.71,5.33239,0.996637);
            break;
        case 2064: //Ashenvale->Splintertree Post
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1,2270.94,-2538.19,93.9198,0.060429);
            break;
        case 2065: //Azshara->Valormok
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1,3608.59,-4414.43,113.047,1.62303);
            break;
        case 2066: //Stonetalon Mountains->Sun Rock Retreat
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1,966.147,926.499,104.649,1.27231);
            break;
        case 2067: //Desolace->Shadowprey Village
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1,-1664.79,3091.67,30.5552,6.07818);
            break;
        case 2068: //Feralas->Camp Mojache
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1,-4396.7,224.841,25.4136,4.93684);
            break;
        case 2069: //Dustwhallow Marsh->Brackenwall Vilage
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1,-3130.67,-2908.43,34.0976,1.42798);
            break;
        case 2070: //Stranglethorn Vale->Grom'gol
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0,-12388.9,172.578,2.83358,1.91753);
            break;
        case 2071: //Swamp of Sorrows->Stonard
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0,-10446.9,-3261.91,20.1795,5.02142);
            break;
        case 2072: //Redridge Mountains->Stonewatch Keep
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0,-9386.59,-3039.03,139.437,4.8054);
            break;
        case 2073: //Burning Stepps->Pillar of Ash
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0,-8075.47,-1686.41,131.836,1.28519);
            break;
        case 2074: //Badlands->Kargath
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0,-6692.48,-2175.31,244.145,0.427571);
            break;
        case 2075: //Hinterlands->Revantusk Village
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0,-557.226,-4581.27,9.5884,1.01724);
            break;

        /*Troll*/
        case 2080: //Durotar->Sen'jin Village
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1,-813.097,-4880.08,18.995,4.42647);
            break;

        /*Tauren*/
        case 2090: //Mulgore->Bloodhoof Village
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1,-2240.91,-399.174,-9.42446,2.53353);
            break;
        case 2091: //Thousand Needles->Freewind Post
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1,-5431.78,-2449.38,89.2848,2.32854);
            break;
        case 2092: //Thousand Needles->Darkcloud Pinnacle
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1,-4779.79,-1882.54,90.1741,3.77625);
            break;
        case 2093: //Stonetalon Mountains->Camp Aparaje
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1,-44.6129,-505.122,-46.1274,1.84172);
            break;
        case 2094: //Stonetalon Mountains->Grimtotem Post
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1,108.029,-322.863,3.36205,4.62591);
            break;
        case 2095: //Dustwallow Marsh->Blackhoof Village
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1,-2462.03,-3157.79,35.5825,4.91817);
            break;

        /*Undead*/
        case 2100: //Tirisfal Glades->Brill
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0,2259.25,290.43,34.1137,0.987414);
            break;
        case 2101: //Silverpine Forest->The Sepulcher
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0,504.534,1539.08,129.502,1.35812);
            break;
        case 2102: //Western Plaguelands->Stratholme
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0,3352.92,-3379.03,144.782,6.25978);
            break;
        case 2103: //Eastern Plaguelands->Andorhal
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0,1400.61,-1493.87,54.7844,4.08661);
            break;
        case 2104: //Duskwood->Raven Hill Cemetery
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0,-10526.7,295.889,31.0954,6.27724);
            break;

        /*Blood Elven*/
        case 2110: //Eversong Woods->Fairbreeze Village
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(530,8714.14,-6650.33,72.7517,2.39205);
            break;
        case 2111: //Ghostlands->Tranquillien
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(530,7564.25,-6872.23,96.0413,4.3579);
            break;
        case 2112: //Ghostlands->An'owyn
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(530,6828.47,-7186.99,24.7617,4.91465);
            break;
        case 2113: //Ghostlands->Farstrider Enclave
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(530,7544.57,-7667.85,151.258,6.22794);
            break;
        case 2114: //Bloodmyst Isle->The Sun Gate
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1,-6818.09,733.814,41.5661,2.3082);
            break;
        }
    return true;
    }
};

void AddSC_aether_misc_npcs()
{
    new cs_dalarangatekeeper;
    new cs_cartographer;
}
