#include "r123.h"
#include "ui_r130.h"
#include "QDebug"
#include "r130.h"
#include <iostream>
#include <math.h>

void R130::changeIndicator(int angle_vrt, int delta) {
    static int angle_ustr = 0;
    if (this->bp_pit && this->bp_vsua) {
        static QPixmap * vsua_ustr = new QPixmap(":/res/r123/r123_ustr.png");
        QPixmap pixmap(*vsua_ustr);
        QMatrix rm;

        angle_ustr = (abs(angle_vrt/8.0) <= R130_VSUA_INDICATOR_MAX_VALUE ? abs(angle_vrt/8.0) : 2*R130_VSUA_INDICATOR_MAX_VALUE - abs(angle_vrt/8));

        rm.rotate(angle_ustr);

        pixmap = pixmap.transformed(rm);
        this->ui->vsua_ustr->setPixmap(QPixmap(pixmap.transformed(rm)));
    } else {
        int angle_vrt = 0;
        static QPixmap * vsua_ustr = new QPixmap(":/res/r123/r123_ustr.png");
        QPixmap pixmap(*vsua_ustr);
        QMatrix rm;

        angle_ustr = angle_vrt/8;

        rm.rotate(0);

        pixmap = pixmap.transformed(rm);
        this->ui->vsua_ustr->setPixmap(QPixmap(pixmap.transformed(rm)));
    }
}

void R130::wheelEventVsua(QWheelEvent * event) {
    static int angle_us_ch = -0;
    static QPixmap * vsua_nast_ch = new QPixmap(":/res/r123/vsua_naptr_kr.png");
    static QPixmap * vsua_vrt = new QPixmap(":/res/r123/vsua_vrt.png");

    static int delta = 8;
    if (event->pos().rx() > 276 && event->pos().ry() > 344 && vsua_controller.ground_connected
            && event->pos().rx() < 331 && event->pos().ry() < 397)
    {
        QPixmap pixmap(*vsua_nast_ch);
        QMatrix rm;
        if (event->angleDelta().ry() > 0) {
            if (angle_us_ch < 25) {
                if (delta > 3) {
                    delta -= 1;
                } else {
                    delta = 3;
                }
            } else if (angle_us_ch >= 26 && angle_us_ch <= 41) {
                delta = 3;
            } else if (angle_us_ch >= 42 && angle_us_ch <= 54) {
                delta = 2;
            } else if (angle_us_ch >= 55 && angle_us_ch < 64) {
                delta = 1;
            } else if (angle_us_ch >= 64) {
                delta = 0;
            }
            angle_us_ch += delta;
            if (angle_us_ch > 64) {
                angle_us_ch = 64;
                delta = 0;
            }
            if (delta != 0) {
                vsua_controller.freq_ukv += 1;

                rm.rotate(angle_us_ch - 83);

                pixmap = pixmap.transformed(rm);
                this->ui->vsua_ustcz->setPixmap(QPixmap(pixmap.transformed(rm)));

                qDebug() << angle_us_ch;
                qDebug() << "freq: " << vsua_controller.freq_ukv;
                qDebug() << "________";
            }
        }
        else if (event->angleDelta().ry() < 0) {
            if (angle_us_ch < 25 && angle_us_ch >= 0) {
                if (delta < 3) {
                    delta = 3;
                } else if (delta < 7) {
                    delta = delta + 1;
                } else if (delta == 7) {
                } else {
                    delta = 0;
                }
            } else if (angle_us_ch >= 26 && angle_us_ch <= 41) {
                delta = 3;
            } else if (angle_us_ch >= 42 && angle_us_ch <= 54) {
                delta = 2;
            } else if (angle_us_ch >= 55 && angle_us_ch < 64) {
                delta = 1;
            } else if (angle_us_ch == 0) {
                delta = 0;
            }
            angle_us_ch -= delta;
            if (delta == 0) {
                delta = 8;
            } else {

                rm.rotate(angle_us_ch - 83);

                pixmap = pixmap.transformed(rm);
                this->ui->vsua_ustcz->setPixmap(QPixmap(pixmap.transformed(rm)));
                vsua_controller.freq_ukv -= 1;
                if (angle_us_ch <= 0) {
                    angle_us_ch = 0;
                    vsua_controller.freq_ukv = 20;
                    delta = 8;
                }
                qDebug() << angle_us_ch;
                qDebug() << "freq: " << vsua_controller.freq_ukv;
                qDebug() << "________";
            }
        }
    }
    if (event->pos().rx() > 694 && event->pos().ry() > 374 && vsua_controller.ground_connected
            && event->pos().rx() < 762 && event->pos().ry() < 435)
    {
        //Плавная настройка антенн
        //влияет на Уй
        //издает звук
        QPixmap pixmap(*vsua_vrt);
        QMatrix rm;
        int delta = 4;
        if (event->angleDelta().ry() > 0) {
            delta = 4;
        }
        else if (event->angleDelta().ry() < 0)
            delta= -4;
        angle_vrt += delta;
        if (angle_vrt > 360)
            angle_vrt -= 360;
        if (angle_vrt < -360)
            angle_vrt += 360;

        rm.rotate(angle_vrt);

        pixmap = pixmap.transformed(rm);

        this->ui->vsua_vrt->setPixmap(QPixmap(pixmap.transformed(rm)));
        changeIndicator(angle_vrt, delta);

    }
    if (!this->vsua_controller.isSetupAsExample()) {
        this->ui->r130_vsua_error->setStyleSheet("background-image: url(:/res/R130/vsua_error.png);");
    } else {
        this->ui->r130_vsua_error->setStyleSheet("");
    }
}

void R130::mousePressEventVsua(QMouseEvent * event) {
   static bool ukv_connected = false;
   static bool kv_connected = false;
   static bool ukv_ant = false, ukv_ant_launch[4] = {false, false, false, false};

   qDebug() << "x - " << event->x() << " y - " << event->y();
    static bool help_open = false;
    if (help_open) {
        this->ui->vsua_help->setStyleSheet("");
        help_open = false;
    } else if (event->x() > 460 && event->y() > 285
               && event->x() < 620 && event->y() < 365) {
        this->ui->vsua_help->setStyleSheet("background-image: url(:/res/r123/vsua_help.png);");
        help_open = true;
    }
   else if (event->x() > 209 && event->y() > 234 && vsua_controller.ground_connected
           && event->x() < 257 && event->y() < 339)
   {
       ukv_connected = !ukv_connected;
       this->vsua_controller.ukv_connected = !this->vsua_controller.ukv_connected;
       //this->controller.setVsuaProvodLauched(ukv_connected);
       if (this->vsua_controller.ukv_connected)
           this->ui->vsua_ukv->setStyleSheet("background-image: url(:/res/r123/launch_ukv_vsua.png);");
       else
           this->ui->vsua_ukv->setStyleSheet("");
   }
   else if (event->x() > 265 && event->y() > 472
            && event->x() < 368 && event->y() < 575)
   {
       ukv_ziem = !ukv_ziem;
       this->vsua_controller.ground_connected = !vsua_controller.ground_connected;
       if (vsua_controller.ground_connected)
           this->ui->vsua_ziem->setStyleSheet("background-image: url(:/res/r123/vsua-ziem.png);");
       else
           this->ui->vsua_ziem->setStyleSheet("");
   }
   else if (event->x() > 286 && event->y() > 174 && vsua_controller.ground_connected
            && event->x() < 340 && event->y() < 223)
   {
       qDebug() << "ukv_ant_launch 0";
       this->ui->vsua_ant2->setStyleSheet("");
       this->ui->vsua_ant3->setStyleSheet("");
       this->ui->vsua_ant4->setStyleSheet("");

       if (ukv_ant_launch[0] == false)
       {
           ukv_ant = true;
           for (int i = 0; i < 4; i++)
               ukv_ant_launch[i] = false;
           ukv_ant_launch[0] = true;

           //this->controller.setVsuaAntenaLaunched(true);
           this->ui->vsua_ant1->setStyleSheet("background-image: url(:/res/r123/vsua-antenna.png);");
           this->vsua_controller.connected_tip_antenni = 0;
       }
       else
       {
            ukv_ant = false;
            ukv_ant_launch[0] = false;
            //this->controller.setVsuaAntenaLaunched(false);
            this->ui->vsua_ant1->setStyleSheet("");
            this->vsua_controller.connected_tip_antenni = -1;
       }
   }
   else if (event->x() > 372 && event->y() > 174 && vsua_controller.ground_connected
            && event->x() < 426 && event->y() < 223)
   {
       qDebug() << "ukv_ant_launch 1";
       this->ui->vsua_ant1->setStyleSheet("");
       this->ui->vsua_ant3->setStyleSheet("");
       this->ui->vsua_ant4->setStyleSheet("");

       if (ukv_ant_launch[1] == false)
       {
           ukv_ant = true;
           for (int i = 0; i < 4; i++)
               ukv_ant_launch[i] = false;
           ukv_ant_launch[1] = true;
           //this->controller.setVsuaAntenaLaunched(true);
           this->ui->vsua_ant2->setStyleSheet("background-image: url(:/res/r123/vsua-antenna.png);");
           this->vsua_controller.connected_tip_antenni = 1;
       }
       else
       {
           //this->controller.setVsuaAntenaLaunched(false);
            ukv_ant = false;
            ukv_ant_launch[1] = false;
            this->ui->vsua_ant2->setStyleSheet("");
            this->vsua_controller.connected_tip_antenni = -1;
       }
   }
   else if (event->x() > 434 && event->y() > 174 && vsua_controller.ground_connected
            && event->x() < 487 && event->y() < 223)
   {
       qDebug() << "ukv_ant_launch 2";
       this->ui->vsua_ant1->setStyleSheet("");
       this->ui->vsua_ant2->setStyleSheet("");
       this->ui->vsua_ant4->setStyleSheet("");

       if (ukv_ant_launch[2] == false)
       {
           ukv_ant = true;
           for (int i = 0; i < 4; i++)
               ukv_ant_launch[i] = false;
           ukv_ant_launch[2] = true;
           //this->controller.setVsuaAntenaLaunched(true);
           this->ui->vsua_ant3->setStyleSheet("background-image: url(:/res/r123/vsua-antenna.png);");
           this->vsua_controller.connected_tip_antenni = 2;
       }
       else
       {
            //this->controller.setVsuaAntenaLaunched(false);
            ukv_ant = false;
            ukv_ant_launch[2] = false;
            this->ui->vsua_ant3->setStyleSheet("");
            this->vsua_controller.connected_tip_antenni = -1;
       }
   }
   else if (event->x() > 488 && event->y() > 174 && vsua_controller.ground_connected
            && event->x() < 533 && event->y() < 223)
   {
       qDebug() << "ukv_ant_launch 3";
       this->ui->vsua_ant1->setStyleSheet("");
       this->ui->vsua_ant2->setStyleSheet("");
       this->ui->vsua_ant3->setStyleSheet("");

       if (ukv_ant_launch[3] == false)
       {
           ukv_ant = true;
           for (int i = 0; i < 4; i++)
               ukv_ant_launch[i] = false;
           ukv_ant_launch[3] = true;
           //this->controller.setVsuaAntenaLaunched(true);
           this->ui->vsua_ant4->setStyleSheet("background-image: url(:/res/r123/vsua-antenna.png);");
           this->vsua_controller.connected_tip_antenni = 3;
       }
       else
       {
           // this->controller.setVsuaAntenaLaunched(false);
            ukv_ant = false;
            ukv_ant_launch[3] = false;
            this->ui->vsua_ant4->setStyleSheet("");
            this->vsua_controller.connected_tip_antenni = -1;
       }
   }
   else if (event->x() > 648 && event->y() > 281 && vsua_controller.ground_connected
            && event->x() < 690 && event->y() < 314)
   {
       static int position = 7, napr = -1;
       auto rotate = [this](int angle) {
           static QPixmap pix(":/res/r123/vsua_net.png");
           QPixmap pixmap(pix);
           QMatrix rm;

           rm.rotate(angle);

           pixmap = pixmap.transformed(rm);

           ui->vsua_net->setPixmap(QPixmap(pixmap.transformed(rm)));
       };
       switch(position)
       {
       case 1:
           napr = 1;
           position++;
           rotate(-80);
           break;
       case 2:
           if (napr < 0) {
               rotate(-92);
               position--;
           }
           else {
               position++;
               rotate(-64);
           }
           break;
       case 3:
           if (napr < 0) {
               rotate(-80);
               position--;
           }
           else {
               position++;
               rotate(-48);
           }
           break;
       case 4:
           if (napr < 0) {
               rotate(-64);
               position--;
           }
           else {
               position++;
               rotate(-32);
           }
           break;
       case 5:
           if (napr < 0) {
               rotate(-48);
               position--;
           }
           else {
               position++;
               rotate(-12);
           }
           break;
       case 6:
           if (napr < 0) {
               rotate(-32);
               position--;
           }
           else {
               position++;
               rotate(0);
           }
           break;
       case 7:
           rotate(-12);
           napr = -1;
           position--;
           break;
       }
   }
   else if (event->x() > 571 && event->y() > 197 && vsua_controller.ground_connected
            && event->x() < 615 && event->y() < 237)
   {
       static int position = 3, napr = -1;
       auto rotate = [this](int angle) {
           static QPixmap pix(":/res/r123/vsua_ind.png");
           QPixmap pixmap(pix);
           QMatrix rm;

           rm.rotate(angle);

           pixmap = pixmap.transformed(rm);

           ui->vsua_ind->setPixmap(QPixmap(pixmap.transformed(rm)));
       };
       switch(position)
       {
       case 3:
           napr = -1;
           rotate(-16);
           position--;
           break;
       case 2:
           if (napr < 0) {
               position--;
               rotate(-32);
           }
           else {
               position++;
               rotate(0);
           }
           break;
       case 1:
           position++;
           napr = 1;
           rotate(-16);
           break;
       }
   }
   else if (event->x() > 540 && event->y() > 392 && vsua_controller.ground_connected
            && event->x() < 588 && event->y() < 433)
   {
       static int position = 3, napr = 1;
       auto rotate = [this](int angle) {
           static QPixmap pix(":/res/r123/vsua_raw.png");
           QPixmap pixmap(pix);
           QMatrix rm;

           rm.rotate(angle);

           pixmap = pixmap.transformed(rm);

           ui->vsua_raw->setPixmap(QPixmap(pixmap.transformed(rm)));
       };
       switch(position)
       {
       case 1:
           napr = 1;
           position++;
           rotate(-16);
           break;
       case 2:
           if (napr > 0) {
               position++;
               rotate(0);
           }
           else {
               position--;
               rotate(-28);
           }
           break;
       case 3:
           if (napr > 0) {
               position++;
               rotate(16);
           }
           else {
               position --;
               rotate(-16);
           }
           break;
       case 4:
           if (napr > 0) {
               position++;
               rotate(32);
           }
           else {
               position--;
               rotate(0);
           }
           break;
       case 5:
           position--;
           napr = -1;
           rotate(16);
           break;
       }
   }
   else if (event->x() > 404 && event->y() > 333 && vsua_controller.ground_connected
            && event->x() < 459 && event->y() < 388)
   {
       static int position = 2, napr = 1;
       auto rotate = [this](int angle) {
           static QPixmap pix(":/res/r123/vsua_ant.png");
           QPixmap pixmap(pix);
           QMatrix rm;

           rm.rotate(angle);

           pixmap = pixmap.transformed(rm);

           ui->vsua_ant_vrt->setPixmap(QPixmap(pixmap.transformed(rm)));
       };
       switch(position)
       {
       case 1:
           napr = 1;
           position++;
           rotate(0);
           break;
       case 2:
           if (napr > 0) {
               position++;
               rotate(16);
           }
           else {
               position--;
               rotate(-16);
           }
           break;
       case 3:
           if (napr > 0) {
               position++;
               rotate(34);
           }
           else {
               position --;
               rotate(0);
           }
           break;
       case 4:
           if (napr > 0) {
               position++;
               rotate(52);
           }
           else {
               position--;
               rotate(16);
           }
           break;
       case 5:
           position--;
           napr = -1;
           rotate(34);
           break;
       }
       this->vsua_controller.grub_nastr_antenn_freq = napr;
   }
   else if (event->x() > 311 && event->y() > 234 && vsua_controller.ground_connected
            && event->x() < 349 && event->y() < 265)
   {
        static bool is_on = true;
        static QPixmap on(":/res/r123/vsua_switch_ind.jpg.png");
        static QPixmap off(":/res/r123/vsua_switch_ind_r.jpg.png");
        if (is_on) {
            this->ui->vsua_ind_switch->setPixmap(off);
            is_on = false;
            this->vsua_controller.indication_tumbler = false;
        }
        else {
            this->ui->vsua_ind_switch->setPixmap(on);
            is_on = true;
            this->vsua_controller.indication_tumbler = true;
        }
   }
   else if (event->x() > 288 && event->y() > 438 && vsua_controller.ground_connected
            && event->x() < 322 && event->y() < 464)
   {
       static QPixmap pix(":/res/r123/vsua-nastr_fil_r.png");
       this->vsua_nast_is_pressed = true;
       this->ui->vsua_nastr_fil->setPixmap(pix);
   }
   else if (event->x() > 316 && event->y() > 284 && vsua_controller.ground_connected
            && event->x() < 344 && event->y() < 304)
   {
       static QPixmap pix(":/res/r123/vsua-clk_ind.png");
       this->vsua_clk_ind_is_pressed = true;
       this->ui->vsua_clk_ind->setPixmap(pix);
   }
   else if (event->x() > 770 && event->y() > 300 && vsua_controller.ground_connected
            && event->x() < 830 && event->y() < 350)
   {
       //KV VSUA CORD
       kv_connected = !kv_connected;
       //this->controller.setVsuaProvodLauched(ukv_connected);
       if (kv_connected)
           this->ui->vsua_kv->setStyleSheet("background-image: url(:/res/r123/launch_kv_vsua.png);");
       else
           this->ui->vsua_kv->setStyleSheet("");
   }

    if (!this->vsua_controller.isSetupAsExample()) {
        this->ui->r130_vsua_error->setStyleSheet("background-image: url(:/res/R130/vsua_error.png);");
    } else {
        this->ui->r130_vsua_error->setStyleSheet("");
    }
}
