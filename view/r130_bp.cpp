#include "r130.h"
#include "ui_r130.h"
#include <QDebug>
#include <QMouseEvent>

void R130::mousePressEventBp(QMouseEvent * event){
//    this->keyReleaseEvent(nullptr);
    static bool pit_zem = false, pit_pit = false, pit_vsua = false;
    qDebug() << "x: " << event->x() << " y: " << event->y();
    if (event->x() > 200 && event->y() > 485
            && event->x() < 600 && event->y() < 601 && pit_zem)
    {
        pit_pit = !pit_pit;
        if (pit_pit)
            this->ui->pit_pit->setStyleSheet(
                "background-image: url(:/res/r123/pit-pit.png);"
            );
        else
            this->ui->pit_pit->setStyleSheet("");
        //this->controller.actionResolver(R123StateController::BP_PIT);
    } // power on power
    else if (event->x() > 383 && event->y() > 310
             && event->x() < 802 && event->y() < 484 && pit_zem)
    {
        pit_vsua = !pit_vsua;
        if (pit_vsua)
            this->ui->pit_vsua->setStyleSheet("background-image: url(:/res/r123/pit-vsua-pit.png);");
        else
            this->ui->pit_vsua->setStyleSheet("");
        //this->controller.actionResolver(R123StateController::BP_PIT_RST);
    }
    else if (event->x() > 110 && event->y() > 497
             && event->x() < 199 && event->y() < 593)
    {
        pit_zem = !pit_zem;
        if (pit_zem)
            this->ui->pit_zem->setStyleSheet("background-image: url(:/res/r123/pit_zeml.png);");
        else
            this->ui->pit_zem->setStyleSheet("");
        //this->controller.actionResolver(R123StateController::BP_ZIEM);
    }
}
