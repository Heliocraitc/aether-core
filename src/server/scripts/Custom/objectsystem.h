#ifndef OBJECT_SYSTEM_H
#define OBJECT_SYSTEM_H

using namespace std;
/* Variables for managing objects */
static uint32 selected_object; // GUID of selected object.

enum directions
{
    LEFT = 1,
    RIGHT,
    UP,
    DOWN,
    FORWARD,
    BACKWARD
};

/* Functions for managing objects */

/*  VARIABLE DEFINITIONS:
    gameobject - the GUID of a specific game object, from the 'gameobject' table.'
    direction - an integer from the direction enumerator above.
    amount (move) - the amount in yards the object will move.
    amount (rotate) - the amount in degrees the object will move.
    recipient - the guid of the player the object is being transferred to.
    owner - guid of the player who owns objects.
 */
class ManageObject{
public:
static void Select(Player* player);
static void Pickup(uint32 gameobject, Player* player);
static void Move(uint32 gameobject, uint8 direction, float amount, Player* player);
static void Rotate(uint32 gameobject, uint8 direction, float amount, Player* player);
static void ChangeOwner(uint32 gameobject, uint32 recipient);
};

/*enum Object_Selection{
SELECT_OBJECT = 1,
PREVIOUS_OBJECT,
NEXT_OBJECT,
POINT_SELECT_OBJECT,
PICKUP_OBJECT,
EDIT_OBJECT_POSITION,
CHANGE_OBJECT_OWNER,
LIST_ALL_OBJECTS
};
*/
enum aether_item_objects_orc
{
    ORC_SMALL_TABLE_ITEM = 73000,
    ORC_SIT_MAT_ITEM,
    ORC_CRATE1_ITEM
};

enum aether_objects_orc
{
    ORC_SMALL_TABLE_OBJECT = 5001000,
    ORC_SIT_MAT_OBJECT,
    ORC_CRATE1_OBJECT
};


enum aether_item_objects_human
{
    HU_SMALL_SQUARE_TABLE_ITEM = 73500,
    HU_WOOD_CHAIR_ITEM,
    HU_CRATE1_ITEM
};

enum aether_objects_human
{
    HU_SMALL_SQUARE_TABLE_OBJECT = 5001500,
    HU_WOOD_CHAIR_OBJECT,
    HU_CRATE1_OBJECT
};

/*Destructible Buildings*/

enum aether_item_destruct_objects
{
ORC_HUT_ITEM = 72000,
ORC_KENNAL_ITEM,
ORC_TOWER_ITEM,
ORC_BLACKSMITH_ITEM,
ORC_MAGETOWER_ITEM,
ORC_GREATHALL_ITEM,
ORC_MEDIUM_INN_ITEM,
ORC_BARRACKS_ITEM,
HU_SCOUT_TOWER_ITEM,
HU_INN_ITEM,
HU_STABLE_ITEM,
HU_MAGETOWER_ITEM,
HU_BLACKSMITH_ITEM,
HU_HOUSE_ITEM,
HU_TOWNHALL_ITEM,
HU_BARRACKS_ITEM,
HU_LUMBERMILL_ITEM
};

enum aether_destruct_objects
{
ORC_HUT_OBJECT = 90010,
ORC_KENNAL_OBJECT,
ORC_TOWER_OBJECT,
ORC_BLACKSMITH_OBJECT,
ORC_MAGETOWER_OBJECT,
ORC_GREATHALL_OBJECT,
ORC_MEDIUM_INN_OBJECT,
ORC_BARRACKS_OBJECT,
HU_SCOUT_TOWER_OBJECT,
HU_INN_OBJECT,
HU_STABLE_OBJECT,
HU_MAGETOWER_OBJECT,
HU_BLACKSMITH_OBJECT,
HU_HOUSE_OBJECT,
HU_TOWNHALL_OBJECT,
HU_BARRACKS_OBJECT,
HU_LUMBERMILL_OBJECT,
HU_TWO_STORY_HOUSE_OBJECT
};

#endif
