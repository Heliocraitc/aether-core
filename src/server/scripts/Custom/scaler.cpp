#include "ScriptPCH.h"
#include "Player.h"
using namespace std;


class cs_scaler : public PlayerScript
{
        public:
                cs_scaler() : PlayerScript("cs_scaler") { }

                void OnLogin(Player * player)
                {
                    QueryResult result = CharacterDatabase.PQuery("SELECT height FROM characters WHERE guid = %u;", player->GetGUIDLow());
                    Field * fields = result->Fetch();
                    float height = fields[0].GetFloat();

                    player->SetObjectScale(height);
                }
};

class cs_scalernpc : public CreatureScript

{
public:
	cs_scalernpc() : CreatureScript("cs_scalernpc") { }

public:


	bool OnGossipHello(Player * player, Creature * creature)
	{
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Tiny.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Small.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Normal.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Large.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Huge.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
		player->PlayerTalkClass->SendGossipMenu(90001, creature->GetGUID());
		return true;
	}
	public:

	bool OnGossipSelect(Player * player, Creature * creature, uint32 sender, uint32 actions)
	{
	    		char shaperQuotes[16][120]=
                {
                {"\"Art is never finished, only abandoned.\""},
                {"\"The Shaper has the Universe in his mind and hands.\""},
                {"\"Where the spirit does not work with the hand, there is no art.\""},
                {"\"Everything has beauty, but not everyone sees it.\""},
                {"\"The beginning is the most important part of the work.\""},
                {"\"It is well with me only when I have a chisel in my hand.\""},
                {"\"Carving is easy, you just go down to the skin and stop.\""},
                {"\"The more the marble wastes, the more the statue grows.\""},
                {"\"The best of artists has no conception that the marble alone does not contain within itself.\""},
                {"\"Life is a quarry, out of which we are to mold and chisel and complete a character.\""},
                {"\"A sculptor wields the chisel, and the stricken marble grows to beauty.\""},
                {"\"Man cannot remake himself without suffering, for he is both the marble and the sculptor.\""},
                {"\"Every block of stone has a statue inside it and it is the task of the sculptor to discover it.\""},
                {"\"In this world a man must either be anvil or hammer.\""},
                {"\"You cannot dream yourself into a character; you must hammer and forge yourself one.\""},
                {"\"To build may have to be the slow and laborious task of years. To destroy can be the thoughtless act of a single day.\""}
				};
		player->PlayerTalkClass->ClearMenus();
		if (sender != GOSSIP_SENDER_MAIN)
			return false;

			switch(actions)
			{

				case GOSSIP_ACTION_INFO_DEF+1:
				{
					uint32 guid = player->GetGUIDLow();
					player->SetObjectScale(0.90);
					CharacterDatabase.PExecute("UPDATE characters SET height = 0.90 WHERE guid = %u;", guid);
					creature->CastSpell(creature, 57552, true);
					player->CastSpell(player, 27123, true);
					player->CLOSE_GOSSIP_MENU();
					creature->MonsterWhisper(shaperQuotes[rand() % 15], player, false);
					break;
				}
				case GOSSIP_ACTION_INFO_DEF+2:
				{
					uint32 guid = player->GetGUIDLow();
					player->SetObjectScale(0.95);
					CharacterDatabase.PExecute("UPDATE characters SET height = 0.95 WHERE guid = %u;", guid);
                    creature->CastSpell(creature, 57552, true);
					player->CastSpell(player, 27123, true);
					player->CLOSE_GOSSIP_MENU();
					creature->MonsterWhisper(shaperQuotes[rand() % 15], player, false);
					break;
				}
				case GOSSIP_ACTION_INFO_DEF+3:
				{
					uint32 guid = player->GetGUIDLow();
					player->SetObjectScale(1);
					CharacterDatabase.PExecute("UPDATE characters SET height = 1 WHERE guid = %u;", guid);
					creature->CastSpell(creature, 57552, true);
					player->CastSpell(player, 27123, true);
					player->CLOSE_GOSSIP_MENU();
					creature->MonsterWhisper(shaperQuotes[rand() % 15], player, false);
					break;
				}
				case GOSSIP_ACTION_INFO_DEF+4:
				{
					uint32 guid = player->GetGUIDLow();
					player->SetObjectScale(1.05);
					CharacterDatabase.PExecute("UPDATE characters SET height = 1.05 WHERE guid = %u;", guid);
					creature->CastSpell(creature, 57552, true);
					player->CastSpell(player, 27123, true);
					player->CLOSE_GOSSIP_MENU();
					creature->MonsterWhisper(shaperQuotes[rand() % 15], player, false);
					break;
				}
				case GOSSIP_ACTION_INFO_DEF+5:
				{
					uint32 guid = player->GetGUIDLow();
					player->SetObjectScale(1.1);
					CharacterDatabase.PExecute("UPDATE characters SET height = 1.1 WHERE guid = %u;", guid);
					creature->CastSpell(creature, 57552, true);
					player->CastSpell(player, 27123, true);
					player->CLOSE_GOSSIP_MENU();
					creature->MonsterWhisper(shaperQuotes[rand() % 15], player, false);
					break;
				}
		}
			return true;
	}
};

void AddSC_cs_scaler()
{
 new cs_scaler;
}

void AddSC_cs_scalernpc()
{
new cs_scalernpc;
}
