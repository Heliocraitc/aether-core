#include "ScriptPCH.h"
#include "MiscFunctions.h"


    /*Alliance*/
void TeleporterFunctions::ADD_HUMAN_ZONES(Player* player)
{
/*Eastern Kingdoms*/
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Elwynn Forest (Goldshire)", GOSSIP_SENDER_MAIN, 2001);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Redridge Mountains (Lakeshire)", GOSSIP_SENDER_MAIN, 2002);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Duskwood (Darkshire)", GOSSIP_SENDER_MAIN, 2003);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Westfall (Sentinel Hill)", GOSSIP_SENDER_MAIN, 2004);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Blasted Lands (Nethergarde Keep)", GOSSIP_SENDER_MAIN, 2005);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Burning Steppes (Morgan's Vigil)", GOSSIP_SENDER_MAIN, 2006);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Wetlands (Menethil Harbor)", GOSSIP_SENDER_MAIN, 2007);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Arathi Highlands (Refuge Pointe)", GOSSIP_SENDER_MAIN, 2008);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Hillsbrad Foothills (Southshore)", GOSSIP_SENDER_MAIN, 2009);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Western Plaguelands (Chillwind Camp)", GOSSIP_SENDER_MAIN, 2010);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Eastern Plaguelands (Light's Hope Chapel)", GOSSIP_SENDER_MAIN, 2011);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Stranglethorn Vale (Booty Bay)", GOSSIP_SENDER_MAIN, 2012);

/*Kalimdor*/
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Tanaris (Gadgetzan)", GOSSIP_SENDER_MAIN, 2013);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Barrens (Ratchet)", GOSSIP_SENDER_MAIN, 2063);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Un'goro Crater (Marshal's Refuge)", GOSSIP_SENDER_MAIN, 2014);
}
void TeleporterFunctions::ADD_DWARF_ZONES(Player* player)
{ /*Eastern Kingdoms*/
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Loch Modan (Thelsamar (Bronzebeard))", GOSSIP_SENDER_MAIN, 2020);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Dun Morogh (Kharanos (Bronzebeard))", GOSSIP_SENDER_MAIN, 2021);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Badlands (Angor Fortress (Dark Iron))", GOSSIP_SENDER_MAIN, 2022);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Searing George (Thorium Point (Dark Iron))", GOSSIP_SENDER_MAIN, 2023);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Wetlands (Dun Modr (Contested))", GOSSIP_SENDER_MAIN, 2024);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Hillsbrad Foothills (Dun Garok (Bronzebeard))", GOSSIP_SENDER_MAIN, 2025);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Hinterlands (Aerie Peak (Wildhammer))", GOSSIP_SENDER_MAIN, 2026);
 /*Kalimdor*/
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Tanaris (Gadgetzan)", GOSSIP_SENDER_MAIN, 2013);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Barrens (Ratchet)", GOSSIP_SENDER_MAIN, 2063);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Un'goro Crater (Marshal's Refuge)", GOSSIP_SENDER_MAIN, 2014);
}
void TeleporterFunctions::ADD_GNOME_ZONES(Player* player)
{/*Eastern Kingdoms*/
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Loch Modan (Thelsamar (Bronzebeard))", GOSSIP_SENDER_MAIN, 2020);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Dun Morogh (Kharanos(Bronzebeard))", GOSSIP_SENDER_MAIN, 2021);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Hillsbrad Foothills (Dun Garok (Bronzebeard))", GOSSIP_SENDER_MAIN, 2025);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Wetlands (Dun Modr (Contested))", GOSSIP_SENDER_MAIN, 2024);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Wetlands (Menethil Harbor)", GOSSIP_SENDER_MAIN, 2007);

/*Kalimdor*/
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Tanaris (Gadgetzan)", GOSSIP_SENDER_MAIN, 2013);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Barrens (Ratchet)", GOSSIP_SENDER_MAIN, 2063);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Un'goro Crater (Marshal's Refuge)", GOSSIP_SENDER_MAIN, 2014);
}
void TeleporterFunctions::ADD_NIGHTELF_ZONES(Player* player)
{
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Teldrassil (Dolanaar)", GOSSIP_SENDER_MAIN, 2030);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Darkshore (Auberdine)", GOSSIP_SENDER_MAIN, 2031);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Felwood (Emerald Sanctuary)", GOSSIP_SENDER_MAIN, 2032);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Moonglade (Nighthaven)", GOSSIP_SENDER_MAIN, 2033);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Winterspring (Everlook)", GOSSIP_SENDER_MAIN, 2034);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Ashenvale (Astranaar)", GOSSIP_SENDER_MAIN, 2035);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Azshara (Talrendis Point)", GOSSIP_SENDER_MAIN, 2036);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Stonetalon Mountains (Stonetalon Peak)", GOSSIP_SENDER_MAIN, 2037);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Desolace (Nijel's Point)", GOSSIP_SENDER_MAIN, 2038);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Ferelas (Feathermoon Stronghold)", GOSSIP_SENDER_MAIN, 2039);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Silithus (Cenarion Hold)", GOSSIP_SENDER_MAIN, 2040);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Un'goro Crater (Marshal's Refuge)", GOSSIP_SENDER_MAIN, 2014);
}
void TeleporterFunctions::ADD_DRAENEI_ZONES(Player* player)
{
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Azuremyst Isle (Azure Watch)", GOSSIP_SENDER_MAIN, 2050);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Bloodmyst Isle (Blood Watch)", GOSSIP_SENDER_MAIN, 2051);
}

/*Horde*/
void TeleporterFunctions::ADD_ORC_ZONES(Player* player)
{
/*Kalimdor*/
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Durotar (Razor Hill)", GOSSIP_SENDER_MAIN, 2060);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Barrens (Crossroads)", GOSSIP_SENDER_MAIN, 2061);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Barrens (Camp Taurajo)", GOSSIP_SENDER_MAIN, 2062);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Barrens (Ratchet)", GOSSIP_SENDER_MAIN, 2063);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Ashenvale (Splintertree Post)", GOSSIP_SENDER_MAIN, 2064);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Azshara (Valormok)", GOSSIP_SENDER_MAIN, 2065);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Stonetalon Mountains (Sun Rock Retreat)", GOSSIP_SENDER_MAIN, 2066);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Desolace (Shadowprey Village)", GOSSIP_SENDER_MAIN, 2067);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Feralas (Camp Mojache)", GOSSIP_SENDER_MAIN, 2068);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Dustwhallow Marsh (Brackenwall Village)", GOSSIP_SENDER_MAIN, 2069);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Un'goro Crater (Marshal's Refuge)", GOSSIP_SENDER_MAIN, 2014);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Tanaris (Gadgetzan)", GOSSIP_SENDER_MAIN, 2013);

/*Eastern Kingdoms*/
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Stranglethorn Vale (Grom'gol)", GOSSIP_SENDER_MAIN, 2070);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Swamp of Sorrows (Stonard)", GOSSIP_SENDER_MAIN, 2071);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Redridge Mountains (Stonewatch Keep (Dark Horde))", GOSSIP_SENDER_MAIN, 2072);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Burning Steppes (Pillar of Ash (Dark Horde))", GOSSIP_SENDER_MAIN, 2073);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Badlands (Kargath)", GOSSIP_SENDER_MAIN, 2074);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Hinterlands (Revantusk Village)", GOSSIP_SENDER_MAIN, 2075);
}
void TeleporterFunctions::ADD_TROLL_ZONES(Player* player)
{/*Kalimdor*/
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Durotar (Sen'jin Village)", GOSSIP_SENDER_MAIN, 2080);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Barrens (Crossroads)", GOSSIP_SENDER_MAIN, 2061);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Barrens (Camp Taurajo)", GOSSIP_SENDER_MAIN, 2062);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Barrens (Ratchet)", GOSSIP_SENDER_MAIN, 2063);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Ashenvale (Splintertree Post)", GOSSIP_SENDER_MAIN, 2064);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Azshara (Valormok)", GOSSIP_SENDER_MAIN, 2065);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Stonetalon Mountains (Sun Rock Retreat)", GOSSIP_SENDER_MAIN, 2066);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Desolace (Shadowprey Village)", GOSSIP_SENDER_MAIN, 2067);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Feralas (Camp Mojache)", GOSSIP_SENDER_MAIN, 2068);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Dustwhallow Marsh (Brackenwall Village)", GOSSIP_SENDER_MAIN, 2069);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Un'goro Crater (Marshal's Refuge)", GOSSIP_SENDER_MAIN, 2014);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Tanaris (Gadgetzan)", GOSSIP_SENDER_MAIN, 2013);
    /*Eastern Kingdoms*/
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Stranglethorn Vale (Grom'gol)", GOSSIP_SENDER_MAIN, 2070);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Hinterlands (Revantusk Village)", GOSSIP_SENDER_MAIN, 2075);
}
void TeleporterFunctions::ADD_TAUREN_ZONES(Player* player)
{/*Kamildor*/
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Mulgore (Bloodhoof Village)", GOSSIP_SENDER_MAIN, 2090);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Thousand Needles (Freewind Post)", GOSSIP_SENDER_MAIN, 2091);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Thousand Needles (Darkcloud Pinnacle (Grimtotem))", GOSSIP_SENDER_MAIN, 2092);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Stonetalon Mountains (Camp Aparaje (Grimtotem))", GOSSIP_SENDER_MAIN, 2093);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Stonetalon Mountains (Grimtotem Post (Grimtotem))", GOSSIP_SENDER_MAIN, 2094);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Dustwallow Marsh (Blackhoof Village (Grimtotem))", GOSSIP_SENDER_MAIN, 2095);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Barrens (Crossroads)", GOSSIP_SENDER_MAIN, 2061);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Barrens (Camp Taurajo)", GOSSIP_SENDER_MAIN, 2062);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Barrens (Ratchet)", GOSSIP_SENDER_MAIN, 2063);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Ashenvale (Splintertree Post)", GOSSIP_SENDER_MAIN, 2064);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Azshara (Valormok)", GOSSIP_SENDER_MAIN, 2065);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Stonetalon Mountains (Sun Rock Retreat)", GOSSIP_SENDER_MAIN, 2066);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Desolace (Shadowprey Village)", GOSSIP_SENDER_MAIN, 2067);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Feralas (Camp Mojache)", GOSSIP_SENDER_MAIN, 2068);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Dustwhallow Marsh (Brackenwall Village)", GOSSIP_SENDER_MAIN, 2069);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Un'goro Crater (Marshal's Refuge)", GOSSIP_SENDER_MAIN, 2014);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Tanaris (Gadgetzan)", GOSSIP_SENDER_MAIN, 2013);
}
void TeleporterFunctions::ADD_UNDEAD_PLAYER_ZONES(Player* player)
{
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Tirisfal Glades (Brill (Forsaken))", GOSSIP_SENDER_MAIN, 2100);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Silverpine Forest (The Sepulcher (Forsaken))", GOSSIP_SENDER_MAIN, 2101);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Western Plaguelands (Stratholme (Scourge))", GOSSIP_SENDER_MAIN, 2102);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Eastern Plaguelands (Andorhal (Scourge))", GOSSIP_SENDER_MAIN, 2103);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Duskwood (Raven Hill Cemetery (Independent))", GOSSIP_SENDER_MAIN, 2104);
}
void TeleporterFunctions::ADD_BLOOELF_ZONES(Player* player)
{
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Eversong Woods (Fairbreeze Village)", GOSSIP_SENDER_MAIN, 2110);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Ghostlands (Tranquillien)", GOSSIP_SENDER_MAIN, 2111);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Ghostlands (An'owyn (High Elves))", GOSSIP_SENDER_MAIN, 2112);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Ghostlands (Farstrider Enclave (High Elves))", GOSSIP_SENDER_MAIN, 2113);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Bloodmyst Isle (The Sun Gate (Kael's Forces))", GOSSIP_SENDER_MAIN, 2114);
}
