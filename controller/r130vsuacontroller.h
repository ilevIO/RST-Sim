#ifndef R13VSUACONTROLLER_H
#define R13VSUACONTROLLER_H

#define R130_VSUA_INDICATOR_MAX_VALUE 50

#include <math.h>

class R130VSUAController
{
public:
    int freq_ukv = 20;
    int nastr_indication = 0;
    bool indication_tumbler = 0;
    int grub_nastr_antenn_freq = 0;
    int grub_nastr_svyaz_freq = 0;
    int plav_nastr_antenn_freq = 0;

    int tip_antenni = 0;
    int connected_tip_antenni = -1;
    int fiksatsia_nastr = 0;

    //cables:
    bool ukv_connected = false;
    bool kv_connected = false;
    bool ground_connected = false;

    bool isSetupAsExample() {
        bool nastr_indication_is_max = (abs(nastr_indication - R130_VSUA_INDICATOR_MAX_VALUE) < 5);
        bool tipi_antenn_match = (tip_antenni == connected_tip_antenni);
        return nastr_indication_is_max && tipi_antenn_match;
    }

    void makeSoundFrequencyTone() {

    }

    R130VSUAController();
};

#endif // R13VSUACONTROLLER_H
