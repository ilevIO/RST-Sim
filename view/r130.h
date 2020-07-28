#ifndef R130_H
#define R130_H

//#define R130_DEBUG false

#include <QMainWindow>
#include "controller/networkcontroller/abstractnetworkcontroller.h"
#include <QLabel>
#include "controller/r130controller.h"
#include "controller/r130vsuacontroller.h"
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
    void changeIndicator(int angle_vrt, int delta);
    void wheelEventRs(QWheelEvent * event);

    bool bp_zem;
    bool bp_pit;
    bool bp_vsua;

    int angle_vrt = 0;
    bool r130_vsu_cable_1_launched;
    bool r130_vsu_cable_2_launched;
    bool r130_cable_pit;
    bool r130_ziem;
    bool r130_cable_mtg;
    enum { PLAVNO, DISKRETNO } r130_smooth;
    int r130_control;
    enum { DEGURN, _20, _100, KALIBR, NASTR_CZAST } r130_regim;
    enum { CZT, AM, OM, ATU, ATH } r130_rod_raboty;
    bool r130_nastr_is_allowed;
    bool r130_vkl_switcher;
    enum { PRM, PRD } r130_prm_prd_switcher;
    enum { RRU, ARU } r130_rru_aru_switcher;

    int r130_uroven_pered;
    int r130_volume;
    int r130_amplify;
    int r130_ton_tlg;
    int r130_x1_angle;
    int r130_x100_angle;
    int r130_x1000_angle;

    void apply_rotated_pixmap_to_widget(QLabel* widget_ptr, QPixmap * pixmap_ptr, qreal angle);
    //From R123
//    friend class R130Controller;
//    R130controller controller;

    void mouseReleaseEvent(QMouseEvent * event) override;

    bool ukv_ziem;

    bool vsua_nast_is_pressed;
    bool vsua_clk_ind_is_pressed;

    bool did_setup = false;
public:
    R130VSUAController vsua_controller;
    explicit R130(QString IP, bool is_server, AbstractNetworkController * controller);
    ~R130();
private:
    Ui::r130 *ui;
};

#endif // R130_H
