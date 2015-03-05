#include "ScriptPCH.h"


class cs_first_login : public PlayerScript
{
public:
    cs_first_login() : PlayerScript("cs_first_login") { }

    void OnLogin(Player * player)
    {
        if (player->GetTotalPlayedTime() < 1) //If the character has no PlayedTime (A bit hacky)
        {
            /* This if-statement is used in order to modify reputation. Too lazy to create
            a whole new script when this one works just fine. */
            player->CastSpell(player, 63624, true);
            player->CastSpell(player, 63706, true);
            player->CastSpell(player, 63707, true);

            //Channel("aether OOC", Channel->GetChannelId(), 0)->JoinChannel(player, Channel->GetPassword()); Needs an addon for force joining

            switch(player->getRace())
            {

            case RACE_BLOODELF:
                player->SetReputation(72, 3000); //Set Stormwind to Neutral.
                player->SetReputation(69, 3000); //Set Darnassus to Neutral.
                player->SetReputation(47, 3000); //Set Ironforge to Neutral.
                player->SetReputation(54, 3000); //Set Gnomeregan Exiles to Neutral.
                player->SetReputation(76, 3000); //Set Orgrimmar to Neutral.
                player->SetReputation(68, 3000); //Set Undercity to Neutral.
                player->SetReputation(81, 3000); //Set Thunder Bluff to Neutral.
                player->SetReputation(530, 3000); //Set Darkspear Trolls to Neutral.
                break;

            case RACE_DRAENEI:
                player->SetReputation(72, 3000); //Set Stormwind to Neutral.
                player->SetReputation(69, 3000); //Set Darnassus to Neutral.
                player->SetReputation(47, 3000); //Set Ironforge to Neutral.
                player->SetReputation(54, 3000); //Set Gnomeregan Exiles to Neutral.
                player->SetReputation(76, 3000); //Set Orgrimmar to Neutral.
                player->SetReputation(68, 3000); //Set Undercity to Neutral.
                player->SetReputation(81, 3000); //Set Thunder Bluff to Neutral.
                player->SetReputation(530, 3000); //Set Darkspear Trolls to Neutral.
                break;

            default:
                break;

            }
            player->UpdateSkillsToMaxSkillsForLevel();
        }
    }
};

class cs_characterlogin : public PlayerScript
{

public:
    cs_characterlogin() : PlayerScript("cs_characterlogin") {}

    void OnLogin(Player* player)
    {
        Unit* playerUnit = player->ToUnit();
        player->AddAura(54844, playerUnit);
        player->Update(1);
        player->RemoveAura(54844, player->GetGUID(),0, AURA_REMOVE_BY_DEFAULT);
    }

    // Called when a player switches to a new zone
    void OnUpdateZone(Player* player, uint32 newZone, uint32 newArea)
    {
        Unit* playerUnit = player->ToUnit();
        player->AddAura(54844, playerUnit);
        player->Update(1);
        player->RemoveAura(54844, player->GetGUID(), 0, AURA_REMOVE_BY_DEFAULT);
    }

    // Called when a player changes to a new map (after moving to new map)
    void OnMapChanged(Player* player)
    {
        Unit* playerUnit = player->ToUnit();
        player->AddAura(54844, playerUnit);
        player->Update(1);
        player->RemoveAura(54844, player->GetGUID(), 0, AURA_REMOVE_BY_DEFAULT);
    }

    void OnDuelEnd(Player* winner, Player* loser, DuelCompleteType type)
    {
        winner->ModifyPowerPct(POWER_MANA, 20);
        winner->ModifyHealth(int32(winner->GetMaxHealth()/5));
        loser->ModifyPowerPct(POWER_MANA, 20);
        loser->ModifyHealth(int32(loser->GetMaxHealth()/5));
    }

};

void AddSC_aether_login()
{
    new cs_first_login;
    new cs_characterlogin;
}
