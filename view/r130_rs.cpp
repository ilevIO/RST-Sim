#include "r130.h"
#include "ui_r130.h"
#include <QMouseEvent>
#include <QPixmap>
#include <QDebug>


void R130::mousePressEventRs(QMouseEvent *event) {

    int x1000centerX = 430, x1000centerY = 270, x1000radiusW = 111/2, x1000radiusH = 111/2;
    int x100centerX = 605, x100centerY = 270, x100radiusW = 101/2, x100radiusH = 101/2;
    int x1centerX = 740, x1centerY = 270, x1radiusW = 101/2, x1radiusH = 101/2;

    int x1000minX = x1000centerX - x1000radiusW, x1000maxX = x1000centerX + x1000radiusW, x1000minY = x1000centerY - x1000radiusH, x1000maxY = x1000centerY + x1000radiusH;
    int x100minX = x100centerX - x100radiusW, x100maxX = x100centerX + x100radiusW, x100minY = x100centerY - x100radiusH, x100maxY = x100centerY + x100radiusH;
    int x1minX = x1centerX - x1radiusW, x1maxX = x1centerX + x1radiusW, x1minY = x1centerY - x1radiusH, x1maxY = x1centerY + x1radiusH;


    if (this->vsua_controller.isSetupAsExample()) {
        this->ui->r130_vsua_error->setStyleSheet("");

    } else {
        this->ui->r130_vsua_error->setStyleSheet("background-image: url(:/res/R130/vsua_error.png);");
    }
    if (event->x() > 714 && event->y() > 441 &&
            event->x() < 821 && event->y() < 568)
       {
           r130_cable_pit = !r130_cable_pit;
           r130_ziem = !r130_ziem;
           this->ui->r130_cable_bp->setStyleSheet(
               r130_cable_pit ? "background-image: url(:/res/R130/Кабель.БП.png);" : ""
           );
           // PITANIYE AND ZIEMLYA EVENT
    }

    if (!r130_ziem)
        return;

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

        auto old_regim = r130_regim;
        if (event->button() == Qt::LeftButton && r130_regim != NASTR_CZAST)
            (*reinterpret_cast<int*>(&r130_regim))++;
        if (event->button() == Qt::RightButton && r130_regim != DEGURN)
            (*reinterpret_cast<int*>(&r130_regim))--;

        this->apply_rotated_pixmap_to_widget(
            this->ui->r130_avnast_regime, r130_regim_pixmap,
            30 * (*reinterpret_cast<int*>(&r130_regim))
        );

        if (r130_regim == NASTR_CZAST && bp_pit && bp_vsua && r130_cable_pit && r130_vkl_switcher &&
                old_regim != r130_regim && r130_rru_aru_switcher == RRU)
        {
            this->r130_nastroyka_thread.start();
        }
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
    } else if (event->x() > 661 && event->y() > 441 &&
               event->x() < 705 && event->y() < 481)
    {
        r130_vkl_switcher = !r130_vkl_switcher;

        this->ui->r130_vkl_switch->setStyleSheet(
            r130_vkl_switcher ? "background-image: url(:/res/R130/power_vert.png);"
                              : "background-image: url(:/res/R130/power_vert_r.png);"
        );
        // R130 POWER VKL SWITCHER EVENT
    } else if (event->x() > 563 && event->y() > 130 &&
               event->x() < 613 && event->y() < 177)
    {
        r130_prm_prd_switcher = r130_prm_prd_switcher == PRD ? PRM : PRD;

        this->ui->r130_prm_prd_switch->setStyleSheet(
            r130_prm_prd_switcher == PRM ? "background-image: url(:/res/R130/power_r.png);" :
                                           "background-image: url(:/res/R130/power.png);"
        );
        // R130 PRM PRD SWITCHER EVENT
    } else if (event->x() > 682 && event->y() > 125 &&
               event->x() < 726 && event->y() < 177)
    {
        r130_rru_aru_switcher = r130_rru_aru_switcher == RRU ? ARU : RRU;

        this->ui->r130_rru_aru_switch->setStyleSheet(
            r130_rru_aru_switcher == RRU ? "background-image: url(:/res/R130/power_r.png);" :
                                           "background-image: url(:/res/R130/power.png);"
        );
        // R130 RRU ARU SWITCHER EVENT
    }
    else if (event->x() > x1000minX && event->y() > x1000minY && r130_nastr_is_allowed
             && event->x() < x1000maxX && event->y() < x1000maxY)
    {
        static QPixmap * r130_x1000_pixmap = new QPixmap(":/res/R130/X100.png");

//        if (event->angleDelta().ry() > 0)
//            r130_x1000_angle += 40;
//        if (event->angleDelta().ry() < 0)
//            r130_x1000_angle -= 40;

        if (event->button() == Qt::LeftButton)
            r130_x1000_angle += r130_x1000_angle == 108 ? 0 : 36;
        if (event->button() == Qt::RightButton)
            r130_x1000_angle += r130_x1000_angle == -216 ? 0 : -36;

//        r130_x1000_angle = r130_x1000_angle > 360 ? r130_x1000_angle - 360 : r130_x1000_angle;
//        r130_x1000_angle = r130_x1000_angle < 0 ? r130_x1000_angle + 360  : r130_x1000_angle;

        this->apply_rotated_pixmap_to_widget(
            this->ui->r130_freq_x1000, r130_x1000_pixmap,
            r130_x1000_angle
        );
        // R130 FREQUENCY X1000 ROTATING EVENT
    } else if (event->x() > 550 && event->y() > 212 && r130_nastr_is_allowed &&
               event->x() < 655 && event->y() < 322)
//    else if (event->x() > x100minX && event->y() > x100minY
//             && event->x() < x100maxX && event->y() < x100maxY)

        {
        static QPixmap * r130_x100_pixmap = new QPixmap(":/res/R130/X100.png");

//        if (event->angleDelta().ry() > 0)
//            r130_x100_angle += 40;
//        if (event->angleDelta().ry() < 0)
//            r130_x100_angle -= 40;

        if (event->button() == Qt::LeftButton)
            r130_x100_angle += r130_x100_angle == 108 ? 0 : 36;
        if (event->button() == Qt::RightButton)
            r130_x100_angle += r130_x100_angle == -216 ? 0 : -36;


//        r130_x100_angle = r130_x100_angle > 360 ? r130_x100_angle - 360 : r130_x100_angle;
//        r130_x100_angle = r130_x100_angle < 0 ? r130_x100_angle + 360  : r130_x100_angle;

        this->apply_rotated_pixmap_to_widget(
            this->ui->r130_freq_x100, r130_x100_pixmap,
            r130_x100_angle
        );
        // R130 FREQUENCY X100 ROTATING EVENT
    }
    /*else if (event->x() > 678 && event->y() > 211 && r130_nastr_is_allowed &&
               event->x() < 788 && event->y() < 331)*/
    else if (event->x() > x1minX && event->y() > x1minY && r130_nastr_is_allowed
             && event->x() < x1maxX && event->y() < x1maxY)
    {
        static QPixmap * r130_x1_pixmap = new QPixmap(":/res/R130/X1.png");

//        if (event->angleDelta().ry() > 0)
//            r130_x1_angle += 60;
//        if (event->angleDelta().ry() < 0)
//            r130_x1_angle -= 60;

        if (event->button() == Qt::LeftButton)
            r130_x1_angle += r130_x1_angle == 72 ? 0 : 36;
        if (event->button() == Qt::RightButton)
            r130_x1_angle += r130_x1_angle == -252 ? 0 : -36;


//        r130_x1_angle = r130_x1_angle > 360 ? r130_x1_angle - 360 : r130_x1_angle;
//        r130_x1_angle = r130_x1_angle < 0 ? r130_x1_angle + 360  : r130_x1_angle;

        this->apply_rotated_pixmap_to_widget(
            this->ui->r130_freq_x1, r130_x1_pixmap,
            r130_x1_angle
        );
        // R130 FREQUENCY X1 ROTATING EVENT
    } else if (event->x() > 435 && event->y() > 495 &&
               event->x() < 495 && event->y() < 650) {
        r130_cable_key = !r130_cable_key;
        this->ui->r130_cable_key->setStyleSheet(
            r130_cable_key ? "background-image: url(:/res/R130/Кабель.Ключ.png);" : ""
        );
        //KLYUCH CABLE
    }
}

void R130::wheelEventRs(QWheelEvent *event) {

    if (!r130_ziem)
        return;

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
    } else if (event->x() > 422 && event->y() > 113 &&
               event->x() < 507 && event->y() < 194)
    {
        static QPixmap * r130_ton_tlg_pixmap = new QPixmap(":/res/R130/ТОН ТЛГ.png");

        if (event->angleDelta().ry() > 0)
            r130_ton_tlg += 4;
        if (event->angleDelta().ry() < 0)
            r130_ton_tlg -= 4;

        r130_ton_tlg = r130_ton_tlg > 360 ? r130_ton_tlg - 360 : r130_ton_tlg;
        r130_ton_tlg = r130_ton_tlg < 0 ? r130_ton_tlg + 360  : r130_ton_tlg;

        this->apply_rotated_pixmap_to_widget(
            this->ui->r130_ton_tlg, r130_ton_tlg_pixmap,
            r130_ton_tlg
        );
        // R130 TON TLG EVENT
    }
    /*else if (event->x() > 374 && event->y() > 227 && r130_nastr_is_allowed &&
               event->x() < 476 && event->y() < 324)*/
}

void R130::r130_rotate_ampermetr(int angle) {
    static QPixmap * arrow = new QPixmap(":/res/R130/Амперметр.Стрелка.png");
    this->apply_rotated_pixmap_to_widget(
      this->ui->r130_ampermetr_line, arrow, angle
    );
}

void R130::update_r130_rst() {

    if (r130_prm_prd_switcher == PRM && r130_regim == DEGURN && isRstPowerOn()) {
        this->ui->r130_dezh_priyom_opacity->setStyleSheet("background-image: url(:/res/R130/r130_diezh_priyom.png);");
        this->r130_rotate_ampermetr(45);
    } else {
        this->ui->r130_dezh_priyom_opacity->setStyleSheet("");
        this->r130_rotate_ampermetr(0);
    }

    if (isPrd() && (r130_regim == KALIBR) && isRstPowerOn()
            && (r130_rod_raboty == OM || r130_rod_raboty == AM) && r130_control == 3)
    {
        this->r130_rotate_ampermetr((r130_uroven_pered - 15) * 45. / 65.);
        if (r130_uroven_pered >= 70 && r130_uroven_pered <= 95) {
            // NASTR IS OK FOR CALL (ALSO NEED CHECK VSUA AND PROVODKI)
        } else if (r130_uroven_pered > 95) {
            // NASTR IS BAD
        } else if (r130_uroven_pered < 70)  {
            // NASTR IS BAD
        }
    } else if (isPrd() && (r130_regim == _20 || r130_regim == _100) && r130_control == 3
               && (r130_rod_raboty == ATH || r130_rod_raboty == CZT || r130_rod_raboty == ATU)) {
        this->r130_rotate_ampermetr((r130_uroven_pered - 15) * 45. / 65.);
        if (r130_uroven_pered >= 70 && r130_uroven_pered <= 95) {
            // NASTR IS OK FOR TLG (ALSO NEED CHECK VSUA AND PROVODKI)
        } else if (r130_uroven_pered > 95) {
            // NASTR IS BAD
        } else if (r130_uroven_pered < 70)  {
            // NASTR IS BAD
        }
    } else if (!(r130_prm_prd_switcher == PRM && r130_regim == DEGURN && isRstPowerOn()))  {
        this->r130_rotate_ampermetr(0);
    }
}

int R130::count_frequency() {
    int frequency_x1000 = (r130_x1000_angle + 216) / 36;
    int frequency_x100 = (r130_x100_angle + 216) / 36;
    int frequency_x1 = (r130_x1_angle + 252) * 10 / 36;

    int frequency = frequency_x1000 * 1000 + frequency_x100 * 100 + frequency_x1;

    return frequency;
}
