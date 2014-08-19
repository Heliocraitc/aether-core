#include "ObjectAccessor.h"
#include "ScriptMgr.h"
#include "Chat.h"
#include "CellImpl.h"
#include "Language.h"
#include "MapManager.h"
#include "Map.h"
#include "Object.h"

#ifndef M_PI_F
# define M_PI_F float(M_PI)
#endif

class gps_commandscript : public CommandScript
{
public:
    gps_commandscript() : CommandScript("gps_commandscript") { }

    ChatCommand* GetCommands() const
    {
        static ChatCommand commandTable[] =
        {
            { "gps",           SEC_ADMINISTRATOR,  false, &HandleGPSCommand,                  "", NULL },
            { NULL,       0,                  false, NULL,                              "", NULL }
        };
        return commandTable;
    }

    static bool HandleGPSCommand(ChatHandler* handler, const char *args)
    {
        if(!*args)
                        return false;
                Player * plr = handler->GetSession()->GetPlayer();
                if(!plr)
                        return false;

                 char* arg1 = strtok((char*)args, " ");
                 char* arg2 = strtok(NULL, " ");

                if (!arg1 || !arg2)
                                return false;

                char dir = arg1[0];
                float value = float(atof(arg2));
                float x = plr->GetPositionX();
                float y = plr->GetPositionY();
                float z = plr->GetPositionZ();
                float o = plr->GetOrientation();

                if ((dir != 'x' && dir != 'y' && dir != 'z' && dir != 'o') || value == 0.f)
                {
                        ChatHandler(plr->GetSession()).SendSysMessage("Incorrect values, correct direction parameters are: x, y, z and o. Correct range/degree parameter is everything above or under 0.");
                        return true;
                }

                switch (dir)
                {
                        case 'x':
                        {
                                x = x + cos(o-(M_PI/2))*value;
                                y = y + sin(o-(M_PI/2))*value;

                                plr->NearTeleportTo(x,y,z,o);

                                ChatHandler(plr->GetSession()).PSendSysMessage("You teleported %g yards in x direction.",value);
                        }
                        break;

                        case 'y':
                        {
                                x = x + cosf(o)*value;
                                y = y + sinf(o)*value;

                                plr->NearTeleportTo(x,y,z,o);

                                ChatHandler(plr->GetSession()).PSendSysMessage("You teleported %g yards in y direction.",value);
                        }
                        break;

                        case 'z':
                        {
                                ChatHandler(plr->GetSession()).PSendSysMessage("You teleported %g yards in z direction.",value);
                                 plr->NearTeleportTo(x,y,z+value,o);

                        }
                        break;

                        case 'o':
                        {
                                o = Position::NormalizeOrientation((value * M_PI_F/180.0f)+o);

                                plr->NearTeleportTo(x,y,z,o);
                                ChatHandler(plr->GetSession()).PSendSysMessage("You rotated %g degrees. (%g radians)",value,value * M_PI / 180.0f);
                                ChatHandler(plr->GetSession()).PSendSysMessage("Current radian/degree: %g %g.",o,o*180.0f/M_PI);
                        }
                        break;
                }

        return true;

    }
};

 void AddSC_gps_commandscript(){
    new gps_commandscript;
}
