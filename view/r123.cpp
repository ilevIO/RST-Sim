#include "r123.h"
#include "ui_r123.h"
#include <QMouseEvent>
#include <QDebug>
#include "controller/r123controller.h"
#include <sstream>
#include <random>
#include <time.h>
#include <QGraphicsOpacityEffect>
#include <QPainter>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <set>

// 36.0 - 248
// 36.1 - 88
// step = 40px

// 35825 = 368 +- 20
//init 400 - 35.8

int countFreq(QLabel *lab1, QLabel *lab2)
{
    int lab1val = int(atof(lab1->text().toStdString().c_str()) * 1000);
    int lab2val = int(atof(lab2->text().toStdString().c_str()) * 1000);
    //489
    int deltaLab1 = lab1->geometry().x() - 489;
    int deltaLab2 = lab2->geometry().x() - 489;

    int resVal, resDelta;

    if (deltaLab1 < 0 && deltaLab2 < 0)
    {
        resDelta = abs(deltaLab1 > deltaLab2 ? deltaLab1 : deltaLab2);
        resVal = deltaLab1 > deltaLab2 ? lab1val : lab2val;
    }
    else if (deltaLab1 > 0 && deltaLab2 < 0)
    {
        resDelta = abs(deltaLab2);
        resVal = lab2val;
    }
    else if (deltaLab1 < 0 && deltaLab2 > 0)
    {
        resDelta = abs(deltaLab1);
        resVal = lab1val;
    }
    else
    {
        resDelta = deltaLab1 < deltaLab2 ? deltaLab1 : deltaLab2;
        resVal = deltaLab1 < deltaLab2 ? lab1val : lab2val;
        resDelta -= 96;
        resDelta = abs(resDelta);
        resVal -= 100;
    }
    //96
    qDebug() << resDelta;
    if (resDelta < 12)
    {
        return resVal - 25;
    }
    else if (resDelta >= 12 && resDelta < 36)
    {
        return resVal;
    }
    else if (resDelta >= 36 && resDelta < 60)
    {
        return resVal + 25;
    }
    else if (resDelta >= 84)
    {
        return resVal + 75;
    }
    else
    {
        return resVal + 50;
    }

}

void R123::wheelEvent(QWheelEvent *event)
{

    if (this->ui->tabWidget->currentIndex() == 1)
    {
       wheelEventVsua(event);
    }
    else if (this->ui->tabWidget->currentIndex() == 0 && this->r123_ziemLaunched)
    {
        wheelEventRs(event);
    }
    updateOpacity();
}

void R123::mousePressEvent(QMouseEvent *event)
{
    if(this->ui->tabWidget->currentIndex() == 2)
    {
        mousePressEventBp(event);
    }
    else if (this->ui->tabWidget->currentIndex() == 1)
    {
        mousePressEventVsua(event);
    }
    else if (this->ui->tabWidget->currentIndex() == 0)
    {
        mousePressEventRs(event);
    }
    updateOpacity();
}

void R123::mouseReleaseEvent(QMouseEvent *event)
{
    if (this->vsua_nast_is_pressed == true)
    {
        static QPixmap pix(":/res/r123/vsua-nastr_fil.png");
        this->vsua_nast_is_pressed = false;
        this->ui->vsua_nastr_fil->setPixmap(pix);
    }
    if (this->vsua_clk_ind_is_pressed == true)
    {
        static QPixmap pix(":/res/r123/vsua-clk_ind_r.png");
        this->vsua_clk_ind_is_pressed = false;
        this->ui->vsua_clk_ind->setPixmap(pix);
    }
    if (this->r123_ton_call_pressed == true)
    {
        static QPixmap pix(":/res/r123/vsua-nastr_fil.png");
        this->r123_ton_call_pressed = false;
        controller.setIsTonCallPressed(false);
        this->ui->r123_ton_call->setPixmap(pix);
    }
    updateOpacity();
}

int R123::countFrequency()
{
    const int startFreqUp = 20150;
    const int startFreqDown = 35900;

    int position = 428 - this->ui->r123_line->pos().x();
    int steps = (position / 40);
    freqUp = startFreqUp + 25 * steps;
    freqDown = startFreqDown + 25 * steps;

    if (!currentPoddiap)
        return freqUp;
    else return freqDown;
}

R123::R123(QString IP, bool is_server, AbstractNetworkController * controller) :
    QMainWindow(nullptr),
    ui(new Ui::r123),
    controller(this, IP, is_server, controller)
{
    ui->setupUi(this);
    this->currentWheelState = 16;
    this->vsua_nast_is_pressed = false;
    this->vsua_clk_ind_is_pressed = false;
    this->BP_active = false;
    this->r123_ustcz_can_move = true;
    this->r123_vechko_upped = false;
    this->currentFrequency = 20050;
    this->currentPoddiap = false;

    this->freqUp = 20150;
    this->freqDown = 35900;
    this->szkl_on = false;
    this->angle_ust_cz = 0;
    for (int i = 0; i < 4; i++)
        this->r123_zpcz_switchers[i] = false;

    this->r123_ziemLaunched = false;


    srand(time(nullptr));

    for (int i = 0; i < 4; i++)
    {
        this->zpcz_angles[i] = 0;
        this->zpcz_frequencies[i] = this->ui->r123_line->geometry().x();
        this->zpcz_angle_ust_cz[i] = angle_ust_cz;
    }

    this->currentzpcz = 6;
    this->controller.setR123Zpcz(currentzpcz);

    angle_nastr = 0;

    updateOpacity();

    regim_raboty = 3;
    this->r123_canHandleKeys = true;
    power_on = false;
    ukv_ziem = false;
}

R123::~R123()
{
    delete ui;
}

void R123::rotate_r123_ustr(int angle)
{
    static QPixmap pix(":/res/r123/r123_ustr.png");
    QPixmap pixmap(pix);
    QMatrix rm;

    rm.rotate(angle);

    pixmap = pixmap.transformed(rm);

    ui->r123_ustr->setPixmap(QPixmap(pixmap.transformed(rm)));
}

void R123::rotate_vsua_ustr(int angle)
{
    static QPixmap pix(":/res/r123/vsua-ustr.png");
    QPixmap pixmap(pix);
    QMatrix rm;

    rm.rotate(angle);

    pixmap = pixmap.transformed(rm);

    ui->vsua_ustr->setPixmap(QPixmap(pixmap.transformed(rm)));
}

void R123::switch_BP_canTouch(bool state)
{
    this->BP_active = state;
}

void R123::setLineState(bool isActive)
{
    this->szkl_on = isActive;
    if (isActive)
    {
        this->ui->r123_line_off->setStyleSheet("");
    }
    else
    {
        this->ui->r123_line_off->setStyleSheet("background-image: url(:/res/r123/line/r123_line_black.png);");
    }
    updateszkl();
}

void R123::keyPressEvent(QKeyEvent *ev)
{
    if (!ev->isAutoRepeat() && this->r123_canHandleKeys && this->r123_ziemLaunched)
    {
        if (regim_raboty == 1 || regim_raboty == 2)
        {
            if (ev->key() == Qt::Key_Space)
            {
                this->space_is_pressed = true;
                updateOpacity();
            }
            controller.keyPressHandler(ev);
        }
        else if (regim_raboty == 3)
        {
            if (ev->key() == Qt::Key_Space)
            {
                this->rotate_vsua_ustr(33);
                this->space_is_pressed = true;
                updateOpacity();
            }
        }
    }
}

void R123::keyReleaseEvent(QKeyEvent *ev)
{
    if (!ev || (ev->key() == Qt::Key_Space && !ev->isAutoRepeat()))
    {
        controller.keyReleaseHandler(ev);
        this->space_is_pressed = false;
        updateOpacity();
    }
}

void R123::setFrequency(int frequency)
{

}

int R123::getAngleToBeSetup()
{
    countFrequency();
    return freqUp % 360;
}

void R123::setOpacity(float opacity)
{
    opacity *= 255;
    QImage image(":/res/r123/r123_setup_diod.png");
    QPainter p;
    p.begin(&image);
    p.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    p.fillRect(image.rect(), QColor(0, 0, 0, int(opacity)));
    p.end();

    this->ui->r123_diod_setup->setPixmap(QPixmap::fromImage(image));
}

void R123::setPoddiap(bool poddiap)
{

}

void R123::setPowerState(bool power)
{
    this->power_on = power;
    updateOpacity();
}

void R123::r123_setHandleKeys(bool canHandle)
{
    this->r123_canHandleKeys = canHandle;
}
