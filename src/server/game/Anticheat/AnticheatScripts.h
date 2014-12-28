#ifndef SC_ACSCRIPTS_H
#define SC_ACSCRIPTS_H

#include "ScriptPCH.h"

class AnticheatScripts: public PlayerScript
{
    public:
        AnticheatScripts();

       void OnLogouts(Player* player);
       void OnLogins(Player* player);
};

#endif