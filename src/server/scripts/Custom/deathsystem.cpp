#include "ScriptPCH.h"
#include "Player.h"
#include "DatabaseFunctions.h"
using namespace std;
#define maxdeaths 3
#define creatureMaxdeaths 2 //I'm off by one error, desired result 3 lives

enum DeathSystem {
    SPELL_CUSTOM_KILL = 90000,
    SPELL_CUSTOM_KNOCKOUT, //90001,
    SPELL_CUSTOM_ROB, //90002,
    SPELL_CUSTOM_DEATHSTUN, //90003,
    SPELL_CUSTOM_MARKED_FOR_DEATH, //90004
    SPELL_CUSTOM_OVERSTUFFED,
    SPELL_CUSTOM_STUFFED,
    SPELL_CUSTOM_FULL,
    SPELL_CUSTOM_SATISFIED,
    SPELL_CUSTOM_PECKISH,
    SPELL_CUSTOM_HUNGRY,
    SPELL_CUSTOM_STARVING,
    SPELL_CUSTOM_HIDDEN_POCKETS //90012
};

class cs_deathsystem : public PlayerScript
{
public:
    cs_deathsystem() : PlayerScript("cs_deathsystem") { }

    void OnPlayerKilledByCreature(Creature * killer, Player * victim) //When a player is killed by a creature, this happens.
    {
        DatabaseFunctions::SetDB_character_deaths(victim->GetGUIDLow()); //Add one death inside the database.
        uint8 deathcount = DatabaseFunctions::GetDB_character_deaths(victim->GetGUIDLow());
        uint8 totaldeaths = maxdeaths - deathcount;
        ChatHandler(victim->GetSession()).PSendSysMessage("You have been killed by %s. You lose one life. %u lives remain.", killer->GetName().c_str(), totaldeaths); // Send a message to the player with the number of lives.
    }

    void OnCreatureKill(Player* killer, Creature* killed) // When a creature is killed...
    {
        if((killed->HasAura(SPELL_CUSTOM_MARKED_FOR_DEATH)) == true) // If the creature is marked for death...
        {
            DatabaseFunctions::SetDB_creature_deaths(killed->GetGUIDLow()); //Set the creature's deaths.
            uint8 creatureDeaths = DatabaseFunctions::GetDB_creature_deaths(killed->GetGUIDLow()); // Holds the creature's current deaths.

            if(creatureDeaths < creatureMaxdeaths) // If the creature has died less than max times.
            {
            ChatHandler(killer->GetSession()).PSendSysMessage("You have taken one of %s's lives. %u lives remain.", killed->GetName().c_str(), (creatureMaxdeaths - creatureDeaths));
            }

            else if(creatureDeaths >= creatureMaxdeaths) // Or else, the creature is dead.
            {
                killed->Respawn(true); //Revive the creature
                killed->SetPhaseMask(8, true); //Put NPC in phase 8
                WorldDatabase.PExecute("UPDATE creature SET phaseMask = 8 WHERE guid = %u;", killed->GetGUIDLow()); // Update the database to set the creature's phase mask.
                ChatHandler(killer->GetSession()).PSendSysMessage("This creature is now dead. Its last life has been taken."); // Tell the player that it's last life has been taken.
            }

            else {}
        }
        else {} // Else, do nothing.
    }
};

class cs_deathsystemgossip : public CreatureScript
{
public:
        cs_deathsystemgossip() : CreatureScript("cs_deathsystemgossip") { }

public:

		bool OnGossipHello(Player * player, Creature * creature) //Triggers when player talks to the NPC.
        {
                //Defines the two gossip options, then sends the player the gossip window.
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Can you send me back? I'm not yet done with this world.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Nevermind.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                        player->PlayerTalkClass->SendGossipMenu(90000, creature->GetGUID());
                        return true;
        }

public:
		//When a player selects a gossip option, this happens.
        bool OnGossipSelect(Player * player, Creature * creature, uint32 sender, uint32 actions)
        {
            char overseerQuotes[16][120]=
                {
                {"\"The day which we fear as our last is but the birthday of eternity.\""},
                {"\"Our dead are never dead to us, until we have forgotten them.\""},
                {"\"Death is a very dull, dreary affair, and my advice to you is to have nothing whatsoever to do with it.'"},
                {"\"Mortal danger is an effective antidote for fixed ideas.\""},
                {"\"Death is not the opposite of life; it exists as a part of them.\""},
                {"\"To die would be an awfully big adventure.\""},
                {"\"We begin to die as soon as we are born, and the end is linked to the beginning.\""},
                {"\"They whom the gods love dies young.\""},
                {"\"Let no one fear to die, we all love to sleep and death is, but the sounder sleep.\""},
                {"\"Death's but a path that must be trod.\""},
                {"\"Hushed in the alabaster arms of Death, does one sleep.\""},
                {"\"To die without fear of death is to be desired.\""},
                {"\"The babe is at peace within the womb, the corpse is at rest within the tomb. We begin in what we end.\""},
                {"\"Is it then so sad a thing to die?\""},
                {"\"It is vain for the coward to flee, death follows close behind, it is only by defying it that the brave escape.\""},
                {"\"I am not in the least surprised that your impression of death becomes more lively.\""}
                };
                uint8 race = 0;
              player->PlayerTalkClass->ClearMenus();  //Good practice, otherwise it results in stacked windows.
                if (sender != GOSSIP_SENDER_MAIN) // If the sender is invalid, exit.
                        return false;

                switch(actions)
                {
                case GOSSIP_ACTION_INFO_DEF+1:
                                {
                                uint32 guid = player->GetGUIDLow(); //Gets me the player GUID.
                                QueryResult result = CharacterDatabase.PQuery("SELECT deaths FROM characters WHERE guid = %u;", guid); //Reads the number of deaths.
                                Field * fields = result->Fetch(); //Reads the above query's result.
                                uint8 deaths = fields[0].GetUInt8(); //Sends the integer to an array.

                                if (deaths >= maxdeaths){
                                player->CLOSE_GOSSIP_MENU();
                                creature->MonsterWhisper("\"It is only the dead who do not return. I cannot bring you back.\"", player, false); // Sends the player a whisper after having too many deaths.
                                break;
                                } else {

                                    QueryResult bindResult = CharacterDatabase.PQuery("SELECT mapid FROM character_homebind WHERE guid = %u;", guid);
                                    Field* bindArray = bindResult->Fetch();
                                    uint32 resultMapid = bindArray[0].GetUInt32();

                                    QueryResult bindResult1 = CharacterDatabase.PQuery("SELECT posX FROM character_homebind WHERE guid = %u;", guid);
                                    Field* bindArray1 = bindResult1->Fetch();
                                    float resultPosX = bindArray1[0].GetFloat();

                                    QueryResult bindResult2 = CharacterDatabase.PQuery("SELECT posY FROM character_homebind WHERE guid = %u;", guid);
                                    Field* bindArray2 = bindResult2->Fetch();
                                    float resultPosY = bindArray2[0].GetFloat();

                                    QueryResult bindResult3 = CharacterDatabase.PQuery("SELECT posZ FROM character_homebind WHERE guid = %u;", guid);
                                    Field* bindArray3 = bindResult3->Fetch();
                                    float resultPosZ = bindArray3[0].GetFloat();

                                    if((player->IsInRange3d(resultPosX,resultPosY,resultPosZ,0.0f,200.0f)) &&
                                       (player->GetMapId() == resultMapid)){
                                       //Alliance
                                       race = player->getRace();
                                        if(race == 1)
                                            player->TeleportTo(0,-9115.0,423.0,96.0,player->GetOrientation()); // Stormwind
                                        if((race == 3) || (race == 7))
                                            player->TeleportTo(0,-5049.45,-809.697,495.127,player->GetOrientation()); //Ironforge
                                        if(race == 4)
                                            player->TeleportTo(1,10054.3,2117.12,1329.63,player->GetOrientation()); //Darnassus
                                        if(race == 11)
                                            player->TeleportTo(530,-4312.78,-12441.0,17.1903,player->GetOrientation()); //Exodor
                                        //Horde
                                        if((race == 2) || (race == 8))
                                            player->TeleportTo(1, 1357.1,-4412.01,28.3841,player->GetOrientation()); // Orgrimmar
                                        if(race == 6)
                                            player->TeleportTo(1,-981.917,-74.6465,20.1265,player->GetOrientation()); //Thunderbluff
                                        if(race == 5)
                                            player->TeleportTo(0,1822.61,214.674,60.1402,player->GetOrientation()); // Undercity
                                        if(race == 10)
                                            player->TeleportTo(530,9407.0,-6847.67,16.0 ,player->GetOrientation()); //Silvermoon
                                    } else {
                                        player->TeleportTo(resultMapid,
                                                           resultPosX,
                                                           resultPosY,
                                                           resultPosZ,
                                                           player->GetOrientation());
                                       }
                                player->ResurrectPlayer(player->GetSession()->HasPermission(rbac::RBAC_PERM_RESURRECT_WITH_FULL_HPS) ? 1.0f : 0.5f);
                                player->SpawnCorpseBones();
								creature->MonsterWhisper(overseerQuotes[rand() % 15], player, false); // Sends the player a whisper after the teleport.
                                player->CLOSE_GOSSIP_MENU(); //Close the gossip window as a nevermind.
                                break;
                                    }
                                }

                case GOSSIP_ACTION_INFO_DEF+2:
                        player->CLOSE_GOSSIP_MENU(); //Close the gossip window as a nevermind.
                        break;
                        }
                return true;
        }
};

class cs_deathkill : public SpellScriptLoader
{
    public:
        cs_deathkill () : SpellScriptLoader("cs_deathkill") { }

        class cs_deathkill_SpellScript : public SpellScript
        {
            PrepareSpellScript(cs_deathkill_SpellScript);
            void KillPlayer()
            {
            Unit* caster = GetCaster();
            Player* killer = caster->ToPlayer();
            Player* victim = killer->GetSelectedPlayer();

              if((victim != NULL)&&(victim != caster)&&(victim->HasAura(SPELL_CUSTOM_DEATHSTUN)))
                {
                    if(killer->IsInRange(victim, 0.0f, 5.0f))
                    {
                    caster->Kill(victim);

                        DatabaseFunctions::SetDB_character_deaths(victim->GetGUIDLow()); //Add one death inside the database.
                        ChatHandler(victim->GetSession()).PSendSysMessage("You have been killed by %s. You lose one life. %u lives remaining.", killer->GetName().c_str(), (maxdeaths - DatabaseFunctions::GetDB_character_deaths(victim->GetGUIDLow())));
                        ChatHandler(killer->GetSession()).PSendSysMessage("You have killed %s. They have lost one life.", victim->GetName().c_str());
                    }
                    else
                    {
                        killer->RemoveSpellCooldown(SPELL_CUSTOM_KILL);
                        killer->GetSession()->SendAreaTriggerMessage("|cffFF0000You are too far away!|r");
                    }
                }
                else if(!victim && !killer->HasSpellCooldown(SPELL_CUSTOM_KILL))
                {
                    killer->RemoveSpellCooldown(SPELL_CUSTOM_KILL);
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(cs_deathkill_SpellScript::KillPlayer);
            }

        };
    SpellScript* GetSpellScript() const
    {
        return new cs_deathkill_SpellScript();
    }
};

class cs_deathknockout : public SpellScriptLoader
{
    public:
        cs_deathknockout () : SpellScriptLoader("cs_deathknockout") { }

        class cs_deathknockout_SpellScript : public SpellScript
        {
            PrepareSpellScript(cs_deathknockout_SpellScript);
            void KnockoutPlayer()
            {
            Unit* caster = GetCaster();
            Player* killer = caster->ToPlayer();
            Player* victim = killer->GetSelectedPlayer();

              if((victim != NULL)&&(victim != caster)&&(victim->HasAura(SPELL_CUSTOM_DEATHSTUN)))
                {
                    if(killer->IsInRange(victim, 0.0f, 5.0f))
                    {
                    victim->CastSpell(victim, 48129, true);
                    ChatHandler(victim->GetSession()).PSendSysMessage("You have been knocked out by %s. You wake up somewhere else.", killer->GetName().c_str());
                    ChatHandler(killer->GetSession()).PSendSysMessage("You have knocked out %s. No lives taken.", victim->GetName().c_str());
                    }
                    else
                    {
                        killer->RemoveSpellCooldown(SPELL_CUSTOM_KNOCKOUT);
                        killer->GetSession()->SendAreaTriggerMessage("|cffFF0000You are too far away!|r");
                    }
                }
                else if(!victim && !killer->HasSpellCooldown(SPELL_CUSTOM_KNOCKOUT))
                {
                    killer->RemoveSpellCooldown(SPELL_CUSTOM_KNOCKOUT);
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(cs_deathknockout_SpellScript::KnockoutPlayer);
            }

        };
    SpellScript* GetSpellScript() const
    {
        return new cs_deathknockout_SpellScript();
    }
};

class cs_deathrob : public SpellScriptLoader
{
public:
    cs_deathrob () : SpellScriptLoader("cs_deathrob") { }

    class cs_deathrob_SpellScript : public SpellScript
    {
        PrepareSpellScript(cs_deathrob_SpellScript);
        void RobPlayer()
        {
            Unit* caster = GetCaster();
            Player* killer = caster->ToPlayer();
            Player* victim = killer->GetSelectedPlayer();

                if((victim != NULL)&&(victim != caster)&&(victim->HasAura(SPELL_CUSTOM_DEATHSTUN)))
                {
                    if(killer->IsInRange(victim, 0.0f, 5.0f))
                    {
                    uint32 victimGold = victim->GetMoney();
                    uint32 goldCoins, silverCoins, copperCoins;
                    if((victimGold > 9)&&(!victim->HasAura(SPELL_CUSTOM_HIDDEN_POCKETS)))
                    {
                        uint32 stolenGold = (uint32)((float)victimGold * 0.1);
                        victim->ModifyMoney(-stolenGold);
                        killer->ModifyMoney(stolenGold);
                        goldCoins = stolenGold / GOLD;
                        stolenGold = stolenGold - (goldCoins * 10000);
                        silverCoins = stolenGold / SILVER;
                        stolenGold = stolenGold - (silverCoins * 100);
                        copperCoins = stolenGold;
                        ChatHandler(victim->GetSession()).PSendSysMessage("You have been robbed for %ug, %us, %uc by %s.", goldCoins, silverCoins, copperCoins, killer->GetName().c_str());
                        ChatHandler(killer->GetSession()).PSendSysMessage("You have stolen %ug, %us, %uc from %s.", goldCoins, silverCoins, copperCoins, victim->GetName().c_str());
                        victim->CastSpell(victim, SPELL_CUSTOM_HIDDEN_POCKETS, true);
                    }
                    else
                    {
                        ChatHandler(killer->GetSession()).PSendSysMessage("You search %s's pockets, but it appears they have no coins on them.", victim->GetName().c_str());
                    }
                    }
                    else
                    {
                        killer->RemoveSpellCooldown(SPELL_CUSTOM_KNOCKOUT);
                        killer->GetSession()->SendAreaTriggerMessage("|cffFF0000You are too far away!|r");
                    }
                }
                else if(!victim && !killer->HasSpellCooldown(SPELL_CUSTOM_KNOCKOUT))
                {
                    killer->RemoveSpellCooldown(SPELL_CUSTOM_KNOCKOUT);
                }
            }

        void Register()
        {
            AfterCast += SpellCastFn(cs_deathrob_SpellScript::RobPlayer);
        }
    };
    SpellScript* GetSpellScript() const
    {
        return new cs_deathrob_SpellScript();
    }
};

void AddSC_aevum_deathsystem(){
    new cs_deathsystem;
    new cs_deathsystemgossip;
    new cs_deathkill;
    new cs_deathknockout;
    new cs_deathrob;
}
