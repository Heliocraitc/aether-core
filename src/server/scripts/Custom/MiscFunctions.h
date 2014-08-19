#ifndef MISC_FUNCTIONS_H
#define MISC_FUNCTIONS_H
class TeleporterFunctions
{ /*Teleporter*/
public:
    /*Alliance*/
    static void ADD_HUMAN_ZONES(Player* player);
    static void ADD_DWARF_ZONES(Player* player);
    static void ADD_GNOME_ZONES(Player* player);
    static void ADD_NIGHTELF_ZONES(Player* player);
    static void ADD_DRAENEI_ZONES(Player* player);

    /*Horde*/
    static void ADD_ORC_ZONES(Player* player);
    static void ADD_TROLL_ZONES(Player* player);
    static void ADD_TAUREN_ZONES(Player* player);
    static void ADD_UNDEAD_PLAYER_ZONES(Player* player);
    static void ADD_BLOOELF_ZONES(Player* player);
};
#endif
