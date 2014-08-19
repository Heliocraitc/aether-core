#include "ScriptPCH.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "Player.h"
#include <cstring>
#include "ObjectMgr.h"
#include "Chat.h"
#include "ScriptMgr.h"
#include "AccountMgr.h"
#include "ArenaTeamMgr.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "Group.h"
#include "InstanceSaveMgr.h"
#include "Language.h"
#include "MovementGenerator.h"
#include "ObjectAccessor.h"
#include "Opcodes.h"
#include "SpellAuras.h"
#include "TargetedMovementGenerator.h"
#include "WeatherMgr.h"
#include "ace/INET_Addr.h"
#include "Pet.h"
#include "LFG.h"
#include "GroupMgr.h"
#include "MMapFactory.h"
#include "Language.h"

class cs_itemrequest : public CreatureScript
{
public:
    cs_itemrequest() : CreatureScript("cs_itemrequest") { }

    bool OnGossipHello(Player * player, Creature * creature)
    {
        player->ADD_GOSSIP_ITEM_EXTENDED(0, "I'd like to request an item.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1,"", 0, true);
        player->ADD_GOSSIP_ITEM_EXTENDED(0, "I'd like to look up an item.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2,"", 0, true);
        player->PlayerTalkClass->SendGossipMenu(90004, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player * player, Creature * creature, uint32 sender, uint32 actions)
    {
        return true;
    }

    bool OnGossipSelectCode(Player* player, Creature* creature, uint32 sender, uint32 action, char const* code)
    {
        uint32 itemId = uint32(atol(code));
        ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(itemId);
        player->PlayerTalkClass->ClearMenus();

        if (sender == GOSSIP_SENDER_MAIN)
        {
            QueryResult result;
            Field* field;
            uint8 itemRequests;
            switch (action)
            {
            case GOSSIP_ACTION_INFO_DEF+1:
                result = CharacterDatabase.PQuery("SELECT item_requests FROM characters WHERE guid = %u;", player->GetGUIDLow());
                field = result->Fetch();
                itemRequests = field[0].GetUInt8();
                if(itemRequests <= 0)
                {
                    ChatHandler(player->GetSession()).PSendSysMessage("You have no more remaining item requests.");
                    player->CLOSE_GOSSIP_MENU();
                    break;
                }

                /*Check if the item exists*/
                if (!itemTemplate)
                {
                    ChatHandler(player->GetSession()).PSendSysMessage("That item doesn't appear to exist. Ensure the id is correct and try again.");
                }
                else
                {
                    if(itemTemplate->Quality == ITEM_QUALITY_LEGENDARY || itemTemplate->Quality == ITEM_QUALITY_EPIC || itemTemplate->Quality == ITEM_QUALITY_ARTIFACT || itemTemplate->Quality == ITEM_QUALITY_HEIRLOOM)
                    {
                        ChatHandler(player->GetSession()).PSendSysMessage("That item is too expensive to give away. Try something Rare (blue) quality or lower.");
                    }
                    else if ((itemTemplate->Class != ITEM_CLASS_ARMOR) && (itemTemplate->Class != ITEM_CLASS_WEAPON))
                    {
                        ChatHandler(player->GetSession()).PSendSysMessage("You can't request that type of item. You may only request armor and weapons.");
                    }
                    else
                    {
                        // Adding items
                        // check space and find places
                        uint32 noSpaceForCount = 0;
                        ItemPosCountVec dest;
                        InventoryResult msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, itemId, 1, &noSpaceForCount);

                        if (noSpaceForCount > 0)
                            ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_CANNOT_CREATE, itemId, noSpaceForCount);

                        Item* requestedItem = player->StoreNewItem(dest, itemId, true, 0);
                        // apply soulbound binding
                        requestedItem->SetBinding(true);

                        player->SendNewItem(requestedItem, 1, true, false, true);
                        CharacterDatabase.PExecute("UPDATE characters SET item_requests = (item_requests - 1) WHERE guid = %u", player->GetGUIDLow());
                        ChatHandler(player->GetSession()).PSendSysMessage("You have %u item requests remaining.", (itemRequests - 1));
                    }
                    creature->CastSpell(creature, 57552, true);
                }
                player->CLOSE_GOSSIP_MENU();
                break;
            case GOSSIP_ACTION_INFO_DEF+2:

                std::string namePart = code;
                std::wstring wNamePart;

                // converting string that we try to find to lower case
                if (!Utf8toWStr(namePart, wNamePart))
                    player->CLOSE_GOSSIP_MENU();

                wstrToLower(wNamePart);

                bool found = false;
                uint32 count = 0;
                uint32 maxResults = 300;

                // Search in `item_template`
                ItemTemplateContainer const* its = sObjectMgr->GetItemTemplateStore();
                for (ItemTemplateContainer::const_iterator itr = its->begin(); itr != its->end(); ++itr)
                {
                    int localeIndex = player->GetSession()->GetSessionDbLocaleIndex();
                    if (localeIndex >= 0)
                    {
                        uint8 ulocaleIndex = uint8(localeIndex);
                        if (ItemLocale const* il = sObjectMgr->GetItemLocale(itr->second.ItemId))
                        {
                            if (il->Name.size() > ulocaleIndex && !il->Name[ulocaleIndex].empty())
                            {
                                std::string name = il->Name[ulocaleIndex];

                                if (Utf8FitTo(name, wNamePart))
                                {
                                    if (maxResults && count++ == maxResults)
                                    {
                                        ChatHandler(player->GetSession()).PSendSysMessage("Result limit reached (max results: %d)", maxResults);
                                    }

                                    if (player->GetSession())
                                    {
                                        ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(itr->second.ItemId);
                                        if ((itemTemplate->Class == ITEM_CLASS_ARMOR) || (itemTemplate->Class == ITEM_CLASS_WEAPON))
                                        {
                                            switch(itemTemplate->Quality)
                                            {
                                            case ITEM_QUALITY_POOR:
                                                ChatHandler(player->GetSession()).PSendSysMessage("%d - |cff9d9d9d|Hitem:%d:0:0:0:0:0:0:0:0|h[%s]|h|r", itr->second.ItemId, itr->second.ItemId, name.c_str());
                                                break;
                                            case ITEM_QUALITY_NORMAL:
                                                ChatHandler(player->GetSession()).PSendSysMessage("%d - |cffffffff|Hitem:%d:0:0:0:0:0:0:0:0|h[%s]|h|r", itr->second.ItemId, itr->second.ItemId, name.c_str());
                                                break;
                                            case ITEM_QUALITY_UNCOMMON:
                                                ChatHandler(player->GetSession()).PSendSysMessage("%d - |cff1eff00|Hitem:%d:0:0:0:0:0:0:0:0|h[%s]|h|r", itr->second.ItemId, itr->second.ItemId, name.c_str());
                                                break;
                                            case ITEM_QUALITY_RARE:
                                                ChatHandler(player->GetSession()).PSendSysMessage("%d - |cff0070dd|Hitem:%d:0:0:0:0:0:0:0:0|h[%s]|h|r", itr->second.ItemId, itr->second.ItemId, name.c_str());
                                                break;
                                            default:
                                                break;
                                            }
                                        }
                                    }
                                    if (!found)
                                        found = true;

                                    continue;
                                }
                            }
                        }
                    }

                    std::string name = itr->second.Name1;
                    if (name.empty())
                        continue;

                    if (Utf8FitTo(name, wNamePart))
                    {
                        if (maxResults && count++ == maxResults)
                        {
                            ChatHandler(player->GetSession()).PSendSysMessage("Result limit reached (max results: %d)", maxResults);
                        }

                        if (player->GetSession() && maxResults && count++ != maxResults)
                        {
                            ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(itr->second.ItemId);
                            if ((itemTemplate->Class == ITEM_CLASS_ARMOR) || (itemTemplate->Class == ITEM_CLASS_WEAPON))
                            {
                                switch(itemTemplate->Quality)
                                {
                                case ITEM_QUALITY_POOR:
                                    ChatHandler(player->GetSession()).PSendSysMessage("%d - |cff9d9d9d|Hitem:%d:0:0:0:0:0:0:0:0|h[%s]|h|r", itr->second.ItemId, itr->second.ItemId, name.c_str());
                                    break;
                                case ITEM_QUALITY_NORMAL:
                                    ChatHandler(player->GetSession()).PSendSysMessage("%d - |cffffffff|Hitem:%d:0:0:0:0:0:0:0:0|h[%s]|h|r", itr->second.ItemId, itr->second.ItemId, name.c_str());
                                    break;
                                case ITEM_QUALITY_UNCOMMON:
                                    ChatHandler(player->GetSession()).PSendSysMessage("%d - |cff1eff00|Hitem:%d:0:0:0:0:0:0:0:0|h[%s]|h|r", itr->second.ItemId, itr->second.ItemId, name.c_str());
                                    break;
                                case ITEM_QUALITY_RARE:
                                    ChatHandler(player->GetSession()).PSendSysMessage("%d - |cff0070dd|Hitem:%d:0:0:0:0:0:0:0:0|h[%s]|h|r", itr->second.ItemId, itr->second.ItemId, name.c_str());
                                    break;
                                default:
                                    break;
                                }
                            }
                        }
                        if (!found)
                            found = true;
                    }
                }

                if (!found)
                    ChatHandler(player->GetSession()).PSendSysMessage("No items found!");

                player->CLOSE_GOSSIP_MENU();
                break;
            }
        }
    }
};

void AddSC_cs_itemrequest()
{
    new cs_itemrequest;
}
