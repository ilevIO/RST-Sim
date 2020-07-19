#ifndef R130_H
#define R130_H

#include <QMainWindow>
#include "controller/networkcontroller/abstractnetworkcontroller.h"
#include <QLabel>
#include "controller/r130controller.h"

namespace Ui {
class r130;
}

class R130 : public QMainWindow
{
    Q_OBJECT

    bool BP_active;

    void mousePressEvent(QMouseEvent * event) override;
    void mousePressEventVsua(QMouseEvent * event);
    void mousePressEventBp(QMouseEvent * event);
    void mousePressEventRs(QMouseEvent * event);

    void wheelEvent(QWheelEvent * event) override;
    void wheelEventVsua(QWheelEvent * event);
    void wheelEventRs(QWheelEvent * event);

    bool bp_zem;
    bool bp_pit;
    bool bp_vsua;

    bool r130_vsu_cable_1_launched;
    bool r130_vsu_cable_2_launched;
    bool r130_cable_pit;
    bool r130_cable_mtg;
    enum { PLAVNO, DISKRETNO } r130_smooth;
    int r130_control;
    enum { DEGURN, _20, _100, KALIBR, NASTR_CZAST } r130_regim;
    enum { CZT, AM, OM, ATU, ATH } r130_rod_raboty;
    bool r130_nastr_is_allowed;

    int r130_uroven_pered;
    int r130_volume;
    int r130_amplify;

    void apply_rotated_pixmap_to_widget(QLabel* widget_ptr, QPixmap * pixmap_ptr, qreal angle);
    //From R123
    friend class R130Controller;
    R130controller controller;

    void mouseReleaseEvent(QMouseEvent * event) override;

    bool ukv_ziem;

    bool vsua_nast_is_pressed;
    bool vsua_clk_ind_is_pressed;
    bool r123_ton_call_pressed;

    bool r123_vechko_upped;
    bool r123_zpcz_switchers[4];

    int zpcz_frequencies[4];
    int zpcz_angles[4];
    int zpcz_angle_ust_cz[4];

    bool r123_ustcz_can_move;

    int currentFrequency;
    bool currentPoddiap;

    bool r123_ziemLaunched;
    int currentWheelState;

    int countFrequency();

    int freqUp;
    int freqDown;

    int currentzpcz;

    bool szkl_on;
    void updateszkl();
    void updateOpacity();

    int angle_nastr;
    int angle_ust_cz;

    bool power_on;

    int regim_raboty;

    bool r123_canHandleKeys;

    bool space_is_pressed;

    void keyPressEvent(QKeyEvent * ev) override;
    void keyReleaseEvent(QKeyEvent * ev) override;

    void chooseZPCZ(QMouseEvent *event);
    void wheelFlow(QMouseEvent *event);

    void update_zpcz();
public:
    explicit R130(QString IP, bool is_server, AbstractNetworkController * controller);
    ~R130();

    void rotate_r123_ustr(int angle);
    void rotate_vsua_ustr(int angle);

    void switch_BP_canTouch(bool state);
    void setLineState(bool isActive);

    void setFrequency(int frequency);

    int getAngleToBeSetup();
    void setOpacity(float opacity);
    void setPoddiap(bool poddiap);
    void setPowerState(bool power);
    void r123_setHandleKeys(bool canHandle);

    void rotateFrequency(int to_frequency, int to_angle);
    void rotateSetUp(int to_angle);
    void setUpZpczWhileChanging();
private:
    Ui::r130 *ui;
};

#endif // R130_H
