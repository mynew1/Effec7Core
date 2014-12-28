#include "AnticheatScripts.h"
#include "AnticheatMgr.h"

AnticheatScripts::AnticheatScripts(): PlayerScript("AnticheatScripts") {}

void AnticheatScripts::OnLogouts(Player* player)
{
    sAnticheatMgr->HandlePlayerLogout(player);
}

void AnticheatScripts::OnLogins(Player* player)
{
    sAnticheatMgr->HandlePlayerLogin(player);
}
