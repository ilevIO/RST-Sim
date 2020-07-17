#include "r123rststatecontroller.h"

R123RSTStateController::R123RSTStateController()
{
    power_on = false;
    pit = false;
    szkala = false;
    pit_bp = false;
    nastr = false;
    antena = false;
    current_zpcz = -1;
    for (int i = 0; i < 4; i++)
        bolts[i] = false;
}

void R123RSTStateController::actionResolver(R123RSTStateController::Action action)
{
    switch (action) {
    case PIT:
        pit = !pit;
        break;
    case SZKALA:
        szkala = !szkala;
        break;
    case POWER:
        power_on = !power_on;
        break;
    case PIT_BP:
        pit_bp = !pit_bp;
        break;
    case ANTENA:
        antena = !antena;
        break;
    }
}

void R123RSTStateController::select_zpcz(int indexOfZpcz)
{
    this->current_zpcz = indexOfZpcz >= 4 ? indexOfZpcz : -1;
}

void R123RSTStateController::setNastr(bool nastr)
{
    this->nastr = nastr;
}

void R123RSTStateController::changeBolt(int bolt)
{
    bolts[bolt] = !bolts[bolt];
}

bool R123RSTStateController::isReadyToNetwork()
{
    return nastr && isPowerLaunch() && antena;
}

bool R123RSTStateController::isPowerLaunch()
{
   return pit && power_on && pit_bp;
}

bool R123RSTStateController::isSzkalaOn()
{
    return power_on && pit && szkala && pit_bp;
}

bool R123RSTStateController::isAllowedToRotedFrequency()
{
    return power_on && pit && (current_zpcz < 0 || bolts[current_zpcz]);
}
