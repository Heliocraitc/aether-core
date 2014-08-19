#include "ScriptPCH.h"
#include "TargetedMovementGenerator.h"


enum {};

class npc_companion_ai : public CreatureScript
{
    public:
        npc_companion_ai() : CreatureScript("npc_companion_ai")

        {
        }

        struct npc_companion : public ScriptedAI
        {
            npc_companion(Creature* creature) : ScriptedAI(creature) { }

            void Reset() override //This is called after spawn and whenever the core decides we need to evade
            {
            creature->GetMotionMaster()->MoveFollow(player, PET_FOLLOW_DIST, creature->GetFollowAngle()); // Start to follow.
            }

            void EnterCombat(Unit * unit) override
            {

            }

            void EnterEvadeMode() override
            {

            }

            void UpdateAI(uint32 uiDiff) override
            {

            }

        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return new npc_companion(creature);
        }
};

void AddSC_npc_companion_ai()
{
    new AddSC_npc_companion_ai();
}
