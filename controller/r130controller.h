#ifndef R130CONTROLLER_H
#define R130CONTROLLER_H

#include "controller/networkcontroller/abstractnetworkcontroller.h"

class R130controller
{
    AbstractNetworkController * networkController;
public:
    R130controller(AbstractNetworkController * networkController);


    void config_send(int frequency) {
        networkController->config_send(frequency);
    }
    void config_listen(int frequecy) {
        networkController->config_listen(frequecy);
    }
    void config_kill() {
        networkController->config_kill();
    }

    void call_on() {
        networkController->call_on();
    }
    void call_off() {
        networkController->call_off();
    }

    void setVolume(char level) {
        networkController->setVolume(level);
    }
    void setSzumLevel(float level) {
        networkController->setSzumLevel(level);
    }
    void setRecordVolume(char level) {
        networkController->setRecordVolume(level);
    }
    void setRestrictedReceiveCall(bool flag) {
        networkController->setRestrictedReceiveCall(flag);
    }
    void setRestrictedReceiveSound(bool flag) {
        networkController->setRestrictedReceiveSound(flag);
    }

};

#endif // R130CONTROLLER_H
