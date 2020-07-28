#ifndef R13VSUACONTROLLER_H
#define R13VSUACONTROLLER_H


#include <math.h>
#include <vector>
#include <algorithm>
#include <qdebug.h>

const int R130_VSUA_INDICATOR_MAX_VALUE = 50;

struct FrequencyRange {
public:
    float min;
    float max;
    bool equals(FrequencyRange range) {
        return (abs(range.min - min) < 0.01) && (abs(range.max - max) < 0.01);
    }
    bool contains(float frequency) {
        return (frequency > min) && (frequency < max);
    }
    FrequencyRange(float min, float max) {
        this->min = min;
        this->max = max;
    }
    FrequencyRange() {

    }
};

typedef class R130VSUATableRow {
public:
    FrequencyRange frequency_range;
    std::vector<int> tipi_antenni;
    std::vector<int> grub_nastr_antenn;
    std::vector<int> grub_nastr_svyaz;
    bool matches(/*float frequency, */int tip_antenni, int grubo, int svyaz) {
        /*if (!this->frequency_range.contains(frequency)) {
            return false;
        }*/
        bool antenni_match = std::find(tipi_antenni.begin(),
                                       tipi_antenni.end(), tip_antenni)
                != tipi_antenni.end();
        bool grubo_match = std::find(grub_nastr_antenn.begin(),
                                      grub_nastr_antenn.end(), grubo)
               != grub_nastr_antenn.end();
        bool svyaz_match = std::find(grub_nastr_svyaz.begin(),
                                      grub_nastr_svyaz.end(), svyaz)
               != grub_nastr_svyaz.end();
        return antenni_match && grubo_match && svyaz_match;

    }
    R130VSUATableRow(FrequencyRange frequency_range,
                     std::vector<int> tipi_antenni,
                     std::vector<int> grub_nastr_antenn,
                     std::vector<int> grub_nastr_svyaz) {
        this->frequency_range = frequency_range;
        this->tipi_antenni = tipi_antenni;
        this->grub_nastr_antenn = grub_nastr_antenn;
        this->grub_nastr_svyaz = grub_nastr_svyaz;
    }
} R130VSUATableRow;

const int SHTYR = 0;
const int NAKL_LUCH = 1;
const int EKV_ANT = 2;
const int DIPOL_1 = 3;
const int DIPOL_2 = 4;

const int ANTENNA_1 = EKV_ANT;
const int ANTENNA_2 = DIPOL_1;
const int ANTENNA_3 = DIPOL_2;

class R130VSUAController
{
public:
    std::vector<R130VSUATableRow> table_states {
        //DIPOL
                R130VSUATableRow(FrequencyRange(1.5, 3), {ANTENNA_1, ANTENNA_2}, {2}, {2,3,4,7}),
                R130VSUATableRow(FrequencyRange(3, 4), {ANTENNA_1}, {2}, {4, 5, 7}),
                R130VSUATableRow(FrequencyRange(4, 5), {ANTENNA_1, ANTENNA_2}, {2, 3}, {4, 5, 7}),
                R130VSUATableRow(FrequencyRange(5, 6), {ANTENNA_1, ANTENNA_2, ANTENNA_3}, {2, 3, 4}, {5, 6, 7}),
                R130VSUATableRow(FrequencyRange(6, 7), {ANTENNA_2, ANTENNA_3}, {2, 3, 4}, {6, 7}),
                R130VSUATableRow(FrequencyRange(7, 8), {ANTENNA_1, ANTENNA_2, ANTENNA_3}, {2, 4}, {5, 6, 7}),
                R130VSUATableRow(FrequencyRange(8, 9), {ANTENNA_1, ANTENNA_3}, {2, 4}, {6}),
                R130VSUATableRow(FrequencyRange(10, 10.99), {ANTENNA_1, ANTENNA_2}, {3, 4}, {6, 7}),
        //SHTYR 4M
                        R130VSUATableRow(FrequencyRange(1.5, 3), {SHTYR}, {1, 2}, {1, 2, 3}),
                        R130VSUATableRow(FrequencyRange(3, 4), {SHTYR}, {2}, {2, 3}),
                        R130VSUATableRow(FrequencyRange(4, 5), {SHTYR}, {2}, {3, 4}),
                        R130VSUATableRow(FrequencyRange(5, 6), {SHTYR}, {2}, {4, 5}),
                        R130VSUATableRow(FrequencyRange(6, 7), {SHTYR}, {2}, {4, 5}),
                        R130VSUATableRow(FrequencyRange(7, 8), {SHTYR}, {2}, {5}),
                        R130VSUATableRow(FrequencyRange(8, 9), {SHTYR}, {2}, {5, 6}),
                        R130VSUATableRow(FrequencyRange(10, 10.99), {SHTYR}, {2}, {6, 7}),
    };
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

    bool is_vsua_ok_with_this_frequency(float frequency) {
        int i = 0;
        for (;
             (i < table_states.size())
             && (table_states[i].matches(/*frequency,*/tip_antenni, grub_nastr_antenn_freq, grub_nastr_svyaz_freq));
             i++) {
        }
        if ((i < table_states.size()) && (table_states[i].frequency_range.contains(frequency))) {
            return true;
        }
        return false;
    }

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
        int i = 0;
        for (;
             (i < table_states.size())
             && (table_states[i].matches(/*frequency,*/tip_antenni, grub_nastr_antenn_freq, grub_nastr_svyaz_freq));
             i++) {
        }
        bool according_to_table = i < table_states.size();
        qDebug() << "tip_antenni: " << tip_antenni;
        qDebug() << "tipi_antenn_match: " << tipi_antenn_match;
        return nastr_indication_is_max && tipi_antenn_match && according_to_table;
    }

    void makeSoundFrequencyTone() {

    }

    R130VSUAController();
};

#endif // R13VSUACONTROLLER_H
