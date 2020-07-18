#ifndef R130_H
#define R130_H

#include <QMainWindow>
#include "controller/networkcontroller/abstractnetworkcontroller.h"

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

public:
    explicit R130(QString IP, bool is_server, AbstractNetworkController * controller);
    ~R130();
private:
    Ui::r130 *ui;
};

#endif // R130_H
