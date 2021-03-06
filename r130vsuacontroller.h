#ifndef R13VSUACONTROLLER_H
#define R13VSUACONTROLLER_H


#include <math.h>
#include <vector>
#include <algorithm>

const int R130_VSUA_INDICATOR_MAX_VALUE = 50;

struct R130VSUATableRow {
    std::vector<int> tipi_antenni;
    std::vector<int> grub_nastr_svyaz;
    std::vector<int> grub_nastr_antenn;
    bool matches(int tip_antenni, int grubo, int svyaz) {
        bool antenni_match = std::find(tipi_antenni.begin(),
                                       tipi_antenni.end(), tip_antenni)
                != tipi_antenni.end();
        return false;
    }
};

class R130VSUAController
{
public:
    static std::vector<R130VSUATableRow> table_states;
    int freq_ukv = 20;
    int nastr_indication = 0;
    bool indication_tumbler = 0;
    int grub_nastr_antenn_freq = 0;
    int grub_nastr_svyaz_freq = 0;
    int plav_nastr_antenn_freq = 0;

    int tip_antenni = 0;
    int connected_tip_antenni = -1;
    int indikatsia_nastr = 0;

    //cables:
    bool ukv_connected = false;
    bool kv_connected = false;
    bool ground_connected = false;

    bool isSetupAsExample() {
        bool nastr_indication_is_max = true; //affects noise //((abs(nastr_indication - R130_VSUA_INDICATOR_MAX_VALUE) < 5) || true);
        bool tipi_antenn_match = false;// (tip_antenni == connected_tip_antenni);
        if (connected_tip_antenni == 0) {
            tipi_antenn_match = (tip_antenni == 0) && (indikatsia_nastr == 0) || (tip_antenni == 1) && (indikatsia_nastr == 1);
        } else {
            switch (connected_tip_antenni) {
            case 1:
                tipi_antenn_match = (indikatsia_nastr == 0) && (tip_antenni == 2);
                break;
            case 2:
                tipi_antenn_match = (tip_antenni == 3) && (indikatsia_nastr == 2);
                break;
            case 3:
                tipi_antenn_match = (tip_antenni == 4) && (indikatsia_nastr == 2);
                break;
            }
        }
        return nastr_indication_is_max && tipi_antenn_match;
    }

    void makeSoundFrequencyTone() {

    }

    R130VSUAController();
};

#endif // R13VSUACONTROLLER_H
