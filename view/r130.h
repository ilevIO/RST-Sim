#ifndef R130_H
#define R130_H

#include <QMainWindow>
#include "controller/networkcontroller/abstractnetworkcontroller.h"
#include <QLabel>

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

    int r130_uroven_pered;

    void apply_rotated_pixmap_to_widget(QLabel* widget_ptr, QPixmap * pixmap_ptr, qreal angle);

public:
    explicit R130(QString IP, bool is_server, AbstractNetworkController * controller);
    ~R130();
private:
    Ui::r130 *ui;
};

#endif // R130_H
