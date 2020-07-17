#ifndef R123RSTSTATECONTROLLER_H
#define R123RSTSTATECONTROLLER_H


class R123RSTStateController
{
    bool pit;
    bool power_on;
    bool szkala;
    bool pit_bp;
    bool nastr;
    bool antena;
    int zpcz[4];
    int current_zpcz;
    bool bolts[4];
    int plavn;
public:
    enum Action {
      PIT, SZKALA, POWER, PIT_BP, ANTENA,
    };
    R123RSTStateController();
    void actionResolver(Action action);
    void select_zpcz(int indexOfZpcz);
    void setFrequency(int frequency);
    void setNastr(bool nastr);
    void changeBolt(int bolt);

    bool isReadyToNetwork();
    bool isPowerLaunch();
    bool isSzkalaOn();
    bool isAllowedToRotedFrequency();
};

#endif // R123RSTSTATECONTROLLER_H
