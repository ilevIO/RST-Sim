#include "r130.h"
#include "ui_r130.h"
#include <QMouseEvent>
#include <QPixmap>


void R130::mousePressEventRs(QMouseEvent *event) {
    if (event->x() > 62 && event->y() > 56 &&
            event->x() < 118 && event->y() < 181)
    {
        r130_vsu_cable_1_launched = !r130_vsu_cable_1_launched;
        this->ui->r130_cable_vsu1->setStyleSheet(
            r130_vsu_cable_1_launched ? "background-image: url(:/res/R130/Кабель.Всу.1.png);" : ""
        );
        // VSU CABLE 1 EVENT
    } else if (event->x() > 118 && event->y() > 56 &&
               event->x() < 174 && event->y() < 181)
    {
        r130_vsu_cable_2_launched = !r130_vsu_cable_2_launched;
        this->ui->r130_cable_vsu2->setStyleSheet(
            r130_vsu_cable_2_launched ? "background-image: url(:/res/R130/Кабель.Всу.2.png);" : ""
        );
        // VSU CABLE 2 EVENT
    } else if (event->x() > 714 && event->y() > 441 &&
               event->x() < 821 && event->y() < 568)
    {
        r130_cable_pit = !r130_cable_pit;
        this->ui->r130_cable_bp->setStyleSheet(
            r130_cable_pit ? "background-image: url(:/res/R130/Кабель.БП.png);" : ""
        );
        // PITANIYE EVENT
    } else if (event->x() > 41 && event->y() > 480 &&
               event->x() < 164 && event->y() < 560)
    {
        r130_cable_mtg = !r130_cable_mtg;
        this->ui->r130_cable_tlf2->setStyleSheet(
            r130_cable_mtg ? "background-image: url(:/res/R130/Кабель.ТЛФ-2.png);" : ""
        );
        // MTG EVENT (mikrotelefonnaya garnitura)
    } else if (event->x() > 744 && event->y() > 307 &&
               event->x() < 804 && event->y() < 352)
    {
        static QPixmap * r130_smouth_pixmap = new QPixmap(":/res/R130/ПЛАВНО.png");
        r130_smooth = r130_smooth == PLAVNO ? DISKRETNO : PLAVNO;

        this->apply_rotated_pixmap_to_widget(
            this->ui->r130_smooth, r130_smouth_pixmap,
            r130_smooth == PLAVNO ? 0 : 40
        );

        // R130 SMOOTH EVENT (plavno vs deskretno)
    } else if (event->x() > 146 && event->y() > 283 &&
               event->x() < 206 && event->y() < 343)
    {
        QPixmap * r130_control_pixmap = new QPixmap(":/res/R130/АВНАСТР.КОНТРОЛЬ.png");
        if (event->button() == Qt::LeftButton && r130_control < 11)
            r130_control++;
        if (event->button() == Qt::RightButton && r130_control > 1)
            r130_control--;

        this->apply_rotated_pixmap_to_widget(
            this->ui->r130_avnastr_control, r130_control_pixmap,
            30 * (r130_control - 1)
        );
        // R130 CONTROL EVENT
    }
}
