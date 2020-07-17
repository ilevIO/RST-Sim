
#include "controller/networkcontroller/abstractnetworkcontroller.h"
#include <QMainWindow>
#include "controller/r123controller.h"

#ifndef R123_H
#define R123_H

namespace Ui {
class r123;
}


class R123 : public QMainWindow
{
    Q_OBJECT

    Ui::r123 *ui;

    friend class R123Controller;
    R123Controller controller;

    void wheelEvent(QWheelEvent * event) override;
    void mousePressEvent(QMouseEvent * event) override;

    void mouseReleaseEvent(QMouseEvent * event) override;

    bool ukv_ziem;

    bool vsua_nast_is_pressed;
    bool vsua_clk_ind_is_pressed;
    bool r123_ton_call_pressed;

    bool BP_active;
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

    void mousePressEventVsua(QMouseEvent * event);
    void mousePressEventBp(QMouseEvent * event);
    void mousePressEventRs(QMouseEvent * event);

    void wheelEventVsua(QWheelEvent * event);
    void wheelEventRs(QWheelEvent * event);

    void update_zpcz();
public:
    explicit R123(QString IP, bool is_server, AbstractNetworkController * controller);
    ~R123() override;
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
};

#endif // R123_H
