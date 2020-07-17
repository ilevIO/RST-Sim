#include "r123.h"
#include "ui_r123.h"

void R123::mousePressEventBp(QMouseEvent * event){
    this->keyReleaseEvent(nullptr);
    static bool pit_zem = false, pit_pit = false, pit_vsua = false;

    if (event->x() > 271 && event->y() > 472
            && event->x() < 671 && event->y() < 588 && this->BP_active)
    {
        pit_pit = !pit_pit;
        if (pit_pit)
            this->ui->pit_pit->setStyleSheet(
                "background-image: url(:/res/r123/pit-pit.png);"
            );
        else
            this->ui->pit_pit->setStyleSheet("");
        this->controller.actionResolver(R123StateController::BP_PIT);
    } // power on power
    else if (event->x() > 454 && event->y() > 297
             && event->x() < 873 && event->y() < 471 && this->BP_active)
    {
        pit_vsua = !pit_vsua;
        if (pit_vsua)
            this->ui->pit_vsua->setStyleSheet("background-image: url(:/res/r123/pit-vsua-pit.png);");
        else
            this->ui->pit_vsua->setStyleSheet("");
        this->controller.actionResolver(R123StateController::BP_PIT_RST);
    }
    else if (event->x() > 181 && event->y() > 484
             && event->x() < 270 && event->y() < 580)
    {
        pit_zem = !pit_zem;
        if (pit_zem)
            this->ui->pit_zem->setStyleSheet("background-image: url(:/res/r123/pit_zeml.png);");
        else
            this->ui->pit_zem->setStyleSheet("");
        this->controller.actionResolver(R123StateController::BP_ZIEM);
    }
}
