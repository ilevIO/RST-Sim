#ifndef R13VSUACONTROLLER_H
#define R13VSUACONTROLLER_H

class R130VSUAController
{
public:
    int freq_ukv = 20;
    int nastr_indication = 0;
    bool indication_tumbler = 0;
    int grub_nastr_antenn = 0;
    int grub_nastr_svyaz = 0;
    int plav_nastr_antenn = 0;

    //cables:
    bool ukv_connected = false;
    bool kv_connected = false;
    bool ground_connected = false;

    R130VSUAController();
};

#endif // R13VSUACONTROLLER_H
