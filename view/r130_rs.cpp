#include "r130.h"
#include "ui_r130.h"
#include <QMouseEvent>
#include <QPixmap>
#include <QDebug>


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
        static QPixmap * r130_control_pixmap = new QPixmap(":/res/R130/АВНАСТР.КОНТРОЛЬ.png");
        if (event->button() == Qt::LeftButton && r130_control < 11)
            r130_control++;
        if (event->button() == Qt::RightButton && r130_control > 1)
            r130_control--;

        this->apply_rotated_pixmap_to_widget(
            this->ui->r130_avnastr_control, r130_control_pixmap,
            30 * (r130_control - 1)
        );
        // R130 CONTROL EVENT
    } else if (event->x() > 142 && event->y() > 370 &&
               event->x() < 201 && event->y() < 424)
    {
        static QPixmap *r130_regim_pixmap = new QPixmap(":/res/R130/АВНАСТР.РЕЖИМ.png");

        if (event->button() == Qt::LeftButton && r130_regim != NASTR_CZAST)
            (*reinterpret_cast<int*>(&r130_regim))++;
        if (event->button() == Qt::RightButton && r130_regim != DEGURN)
            (*reinterpret_cast<int*>(&r130_regim))--;

        this->apply_rotated_pixmap_to_widget(
            this->ui->r130_avnast_regime, r130_regim_pixmap,
            30 * (*reinterpret_cast<int*>(&r130_regim))
        );
        // R130 REGIM RABOTY EVENT
    } else if (event->x() > 236 && event->y() > 365 &&
               event->x() < 301 && event->y() < 428)
    {
        static QPixmap * r130_rod_raboty_pixmap = new QPixmap(":/res/R130/АВНАСТР.РОД РАБОТЫ.png");

        if (event->button() == Qt::LeftButton && r130_rod_raboty != ATH)
            (*reinterpret_cast<int*>(&r130_rod_raboty))++;
        if (event->button() == Qt::RightButton && r130_rod_raboty != CZT)
            (*reinterpret_cast<int*>(&r130_rod_raboty))--;

        this->apply_rotated_pixmap_to_widget(
            this->ui->r130_avnastr_rod, r130_rod_raboty_pixmap,
            30 * (*reinterpret_cast<int*>(&r130_rod_raboty) - 3)
        );
        // R130 ROD RABOTY EVENT
    } else if (event->x() > 364 && event->y() > 107 &&
               event->x() < 406 && event->y() < 151)
    {
        static QPixmap * r130_nastr_is_allowed_pixmap = new QPixmap(":/res/R130/НАСТРОЙКА.png");
        r130_nastr_is_allowed = !r130_nastr_is_allowed;

        this->apply_rotated_pixmap_to_widget(
            this->ui->r130_btn_nastroika, r130_nastr_is_allowed_pixmap,
            r130_nastr_is_allowed ? 60 : 0
        );
        // R130 NASTR IS ALLOWED EVENT
    }
}

void R130::wheelEventRs(QWheelEvent *event) {
    if (event->x() > 250 && event->y() > 293 &&
            event->x() < 289 && event->y() < 333)
    {
        static QPixmap * r130_uroven_pered_pixmap = new QPixmap(":/res/R130/АВНАСТР.УРОВЕНЬ ПЕРЕДАЧИ.png");

        if (event->angleDelta().ry() > 0 && r130_uroven_pered < 100)
            r130_uroven_pered += 5;
        if (event->angleDelta().ry() < 0 && r130_uroven_pered > 0)
            r130_uroven_pered -= 5;

        this->apply_rotated_pixmap_to_widget(
            this->ui->r130_avnastr_level, r130_uroven_pered_pixmap,
            (r130_uroven_pered - 50) * 1.8
        );
        // R130 UROVEN PEREDACZI EVENT
    } else if (event->x() > 328 && event->y() > 293 &&
               event->x() < 369 && event->y() < 333)
    {
        static QPixmap * r130_volume_pixmap = new QPixmap(":/res/R130/ГРОМКОСТЬ.png");

        if (event->angleDelta().ry() > 0 && r130_volume < 100)
            r130_volume += 5;
        if (event->angleDelta().ry() < 0 && r130_volume > 0)
            r130_volume -= 5;

        this->apply_rotated_pixmap_to_widget(
            this->ui->r130_volume, r130_volume_pixmap,
            r130_volume * 1.8
        );
        // R130 VOLUME EVENT
    } else if (event->x() > 497 && event->y() > 295 &&
               event->x() < 540 && event->y() < 335)
    {
        static QPixmap * r130_amplify_pixmap = new QPixmap(":/res/R130/УСИЛЕНИЕ.png");

        if (event->angleDelta().ry() > 0 && r130_amplify < 100)
            r130_amplify += 5;
        if (event->angleDelta().ry() < 0 && r130_amplify > 0)
            r130_amplify -= 5;

        this->apply_rotated_pixmap_to_widget(
            this->ui->r130_amplify, r130_amplify_pixmap,
            r130_amplify * 1.8
        );
        // R130 AMPLIFY EVENT
    }
}
//From R123
void R130::updateOpacity()
{
    /*int rotate_delta = abs(getAngleToBeSetup() - angle_nastr);

    if (regim_raboty == 3 && this->space_is_pressed && power_on)
    {

        setOpacity(0.0);
        rotate_r123_ustr(33);
        return;
    }

    if (!this->space_is_pressed) {
        if (rotate_delta < 12)
        {
            this->controller.setNastr(true, countFrequency());
            this->controller.activateRst(space_is_pressed);
        } else {
            this->controller.setNastr(false);
            this->controller.activateRst(space_is_pressed);
        }
        setOpacity(0.);
        rotate_r123_ustr(0);
    }
    else if (!this->power_on)
    {

        setOpacity(0.);
        rotate_r123_ustr(0);
        this->controller.setNastr(false);
    }
    else if (rotate_delta < 12)
    {
        setOpacity(1.0f);
        rotate_r123_ustr(33);
        this->controller.setNastr(true, countFrequency());
        this->controller.activateRst(space_is_pressed);
    } else if (rotate_delta < 40)
    {
        setOpacity(1.0f - float(rotate_delta - 12) / 28);
        rotate_r123_ustr(int((1.0f - float(rotate_delta - 12) / 28) * 33));
        this->controller.setNastr(false);
    }
    else
    {
        rotate_r123_ustr(0);
        setOpacity(0.);
        this->controller.setNastr(false);
    }

    this->controller.activateRst(this->space_is_pressed);*/
}
