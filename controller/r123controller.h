#pragma once

#include "controller/networkcontroller/abstractnetworkcontroller.h"
#include "controller/r123statecontroller.h"


class R123;

class R123Controller
{
    int current_zpcz;
    R123 * parent;
    AbstractNetworkController * networkController;
    R123StateController stateController;

    bool nastr;
    int freq;
    bool isCorrectRegim;
    bool tonCallIsPressed;

    bool vsua_antena_launched;
    bool vsua_provod_launched;

    bool r123_mtg_launched;
    bool r123_antena_launched;

    void setNetworkState(bool state);
public:
    R123Controller(R123 * parent, QString IP, bool is_server, AbstractNetworkController * networkController);

    void setR123MTGLaunched(bool is_launched);
    void setR123AntenaLaunched(bool is_launched);

    void setVsuaAntenaLaunched(bool is_launched);
    void setVsuaProvodLauched(bool is_launched);

    void keyPressHandler(QKeyEvent * ev);
    void keyReleaseHandler(QKeyEvent * ev);

    void setR123Zpcz(int zpcz);
    int getCurrentZpcz();
    void setNastr(bool nastr, int frequency = 0);
    void actionResolver(R123StateController::Action);
    void setVolume(float volume);
    void setNoise(float noise);
    void activateRst(bool isSpacePressed);
    void setIsCorrectRegim(bool isCorrect);
    void setIsTonCallPressed(bool isPressed);
};

