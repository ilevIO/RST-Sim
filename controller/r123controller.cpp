#include "r123controller.h"
#include "view/r123.h"
#include <QDebug>

void R123Controller::setNetworkState(bool state)
{
    if (nastr && isCorrectRegim && vsua_antena_launched && vsua_provod_launched
            && stateController.r123_isPowerOn() && r123_mtg_launched && r123_antena_launched) {
        if (state) {
            if (tonCallIsPressed)
            {
                networkController->config_send(freq);
                networkController->call_on();
            }
            else {
                networkController->config_send(freq);
                networkController->call_off();
            }
        }
        else
            networkController->config_listen(freq);
    } else networkController->config_kill();
}

void R123Controller::setR123MTGLaunched(bool is_launched) {
    this->r123_mtg_launched = is_launched;
}

R123Controller::R123Controller(R123 * parent, QString IP, bool is_server, AbstractNetworkController * networkController) :
    parent(parent), networkController(networkController)
{
    current_zpcz = 5;
    nastr = false;
    freq = 0;
    setIsCorrectRegim(false);
    setIsTonCallPressed(false);
    setVsuaProvodLauched(false);
    setVsuaAntenaLaunched(false);
    setR123MTGLaunched(false);
    setR123AntenaLaunched(false);
}

void R123Controller::setR123AntenaLaunched(bool is_launched) {
    this->r123_antena_launched = is_launched;
}

void R123Controller::setVsuaProvodLauched(bool is_launched) {
    this->vsua_provod_launched = is_launched;
}

void R123Controller::setVsuaAntenaLaunched(bool is_launched) {
    this->vsua_antena_launched = is_launched;
}

void R123Controller::keyPressHandler(QKeyEvent *ev)
{
    if (ev->key() == Qt::Key_Space)
        setNetworkState(true);
}

void R123Controller::keyReleaseHandler(QKeyEvent *ev)
{
    if (!ev || ev->key() == Qt::Key_Space)
        setNetworkState(false);
}

void R123Controller::setR123Zpcz(int zpcz)
{
    current_zpcz = zpcz;
}

int R123Controller::getCurrentZpcz() {
    return current_zpcz;
}

void R123Controller::setNastr(bool nastr, int frequency)
{
    qDebug() << "frequency: " << frequency;
    if (nastr) {
        freq = frequency;
        this->nastr = true;
//        this->networkController->config_listen(frequency);
    } else {
        this->nastr = false;
        setNetworkState(false);
//        this->networkController->config_kill();
    }
}

void R123Controller::actionResolver(R123StateController::Action action)
{
    this->stateController.actionResolver(action);
    switch (action) {
    case R123StateController::BP_ZIEM:
        this->parent->switch_BP_canTouch(this->stateController.BP_canTouch());
        break;
    default:
        break;
    }
    parent->setPowerState(this->stateController.r123_isPowerOn());
    parent->setLineState(stateController.isSzkalaOn());
}

void R123Controller::setVolume(float volume) {
    networkController->setVolume(volume * 100);
}

void R123Controller::setNoise(float noise) {
    networkController->setSzumLevel(noise);
}

void R123Controller::activateRst(bool isSpacePressed) {
    setNetworkState(isSpacePressed);
}

void R123Controller::setIsCorrectRegim(bool isCorrect) {
    isCorrectRegim = isCorrect;
}

void R123Controller::setIsTonCallPressed(bool isPressed) {
    this->tonCallIsPressed = isPressed;
}
