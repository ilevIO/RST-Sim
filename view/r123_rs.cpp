#include "r123.h"
#include "ui_r123.h"
#include <QDebug>
#include <iostream>
#include <stdio.h>
#include <set>
#include <cmath>

struct Point {
    int x;
    int y;
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

Point wheelCenter(495, 340);
double pi = 3.1415;

int sqr(int a) {
    return a * a;
}

struct Bolt {
    int logPosX;
    int logPosY;
    Point transformed(int anglee) {
        //angle = angle * 180 / pi;
        double xui = 90;
        double xui2 = 90;
        double angle = anglee;
        auto nullWidth = logPosX;// - wheelCenter.x;
        auto nullHeight = logPosY;// - wheelCenter.y;
        return Point(wheelCenter.x + (nullWidth) * cos(angle/xui2 * pi) - (nullHeight) * sin(angle/xui2 * pi),
                    wheelCenter.y + (nullWidth) * sin(angle/xui * pi) + nullHeight * cos(angle/xui * pi));

    }

    Bolt(int x, int y) {
        logPosX = x;
        logPosY = y;
    }
};


Bolt bolts[] = {
    Bolt(-35, -45),
    Bolt(40, -45),
    Bolt(45, 40),
    Bolt(-40, 40),
};


std::set<int> openBolts = {
};

char* rotations[] = {
    ":/res/r123/Rotations/r123_cz_0000.png",
    ":/res/r123/Rotations/r123_cz_0001.png",
    ":/res/r123/Rotations/r123_cz_0010.png",
    ":/res/r123/Rotations/r123_cz_0011.png",
    ":/res/r123/Rotations/r123_cz_0100.png",
    ":/res/r123/Rotations/r123_cz_0101.png",
    ":/res/r123/Rotations/r123_cz_0110.png",
    ":/res/r123/Rotations/r123_cz_0111.png",
    ":/res/r123/Rotations/r123_cz_1000.png",
    ":/res/r123/Rotations/r123_cz_1001.png",
    ":/res/r123/Rotations/r123_cz_1010.png",
    ":/res/r123/Rotations/r123_cz_1011.png",
    ":/res/r123/Rotations/r123_cz_1100.png",
    ":/res/r123/Rotations/r123_cz_1101.png",
    ":/res/r123/Rotations/r123_cz_1110.png",
    ":/res/r123/Rotations/r123_cz_1111.png",
    ":/res/r123/Rotations/empty.png"
};
int currentWheelState = 16;
//int angle_ust_cz = 0;


int logCurrentWheelState = 16;

void R123::chooseZPCZ(QMouseEvent *event) {
    static int state = 1;
    this->keyReleaseEvent(nullptr);
    auto rotate = [this](int angle) {
        static QPixmap pix(":/res/r123/r123_zpcz.png");
        QPixmap pixmap(pix);
        QMatrix rm;

        rm.rotate(angle);

        pixmap = pixmap.transformed(rm);

        ui->r123_zpcz->setPixmap(QPixmap(pixmap.transformed(rm)));
    };
    switch (state) {
    case 1:
        if (event->button() == Qt::LeftButton)
        {rotate(30); state = 2; this->controller.setR123Zpcz(1); currentzpcz = 1;} else { rotate(150); state = 6;this->controller.setR123Zpcz(5); currentzpcz = 5;}
        break;
    case 2:
        if (event->button() == Qt::LeftButton)
        {rotate(60); state = 3;this->controller.setR123Zpcz(2); currentzpcz = 2;} else { rotate(0); state = 1;this->controller.setR123Zpcz(6); currentzpcz = 6;}
        break;
    case 3:
        if (event->button() == Qt::LeftButton)
        {rotate(90); state = 4;this->controller.setR123Zpcz(3); currentzpcz = 3;} else { rotate(30); state = 2;this->controller.setR123Zpcz(1); currentzpcz = 1;}
        break;
    case 4:
        if (event->button() == Qt::LeftButton)
        {rotate(120); state = 5;this->controller.setR123Zpcz(4); currentzpcz = 4;} else { rotate(60); state = 3;this->controller.setR123Zpcz(2); currentzpcz = 2;}
        break;
    case 5:
        if (event->button() == Qt::LeftButton)
        {rotate(150); state = 6;this->controller.setR123Zpcz(5); currentzpcz = 5;} else { rotate(90); state = 4;this->controller.setR123Zpcz(3); currentzpcz = 3;}
        break;
    case 6:
        if (event->button() == Qt::LeftButton)
        {rotate(0); state = 1;this->controller.setR123Zpcz(6); currentzpcz = 6;} else { rotate(120); state = 5;this->controller.setR123Zpcz(4); currentzpcz = 4;}
        break;
    }
    if (power_on)
        setUpZpczWhileChanging();
    if (currentzpcz == 5)
        this->currentPoddiap = true;
    else if (currentzpcz == 6)
        this->currentPoddiap = false;
    else {
        this->currentPoddiap = this->r123_zpcz_switchers[currentzpcz - 1];
    }
    updateszkl();
    this->controller.setR123Zpcz(currentzpcz);
}

void R123::wheelFlow(QMouseEvent *event)
{
    this->keyReleaseEvent(nullptr);
    const int offsetX = 12;
    const int offsetY = 3;
    static int cz_state = 0;

    int boltRadius = 15;
// 439 277 475 309
    bool roted_bolt_succed = false;
    if (cz_state == 2) {
        for (int i = 0; i < 4; i++) {
            qDebug() << "bolt[" << i << "]: " << bolts[i].transformed(angle_ust_cz).x << ", " << bolts[i].transformed(angle_ust_cz).y << "\n";
            auto offset = 0;

            if ((event->x() - offset > bolts[i].transformed(angle_ust_cz).x - boltRadius) && (event->x() - offset < bolts[i].transformed(angle_ust_cz).x + boltRadius)
                    &&
                  (event->y() - offset > bolts[i].transformed(angle_ust_cz).y - boltRadius && event->y() - offset < bolts[i].transformed(angle_ust_cz).y + boltRadius)) {
                roted_bolt_succed = true;
                if (openBolts.find(i) != openBolts.end()) {
                    auto iter = openBolts.find(i);
                    openBolts.erase(iter);
                } else {
                    openBolts.insert(i);
                }
                break;
            }
        }

        QPixmap x(10, 10);
        x.fill();
        QMatrix matr;
        matr.translate(bolts[0].transformed(angle_ust_cz).x, bolts[0].transformed(angle_ust_cz).y);
        x = x.transformed(matr);

        if (openBolts.find(0) != openBolts.end()) {
            if  (openBolts.find(1) != openBolts.end()) {
                if  (openBolts.find(2) != openBolts.end()) {
                    if  (openBolts.find(3) != openBolts.end()) {
                        logCurrentWheelState = 15;
                    } else {
                        logCurrentWheelState = 7;
                    }
                    qDebug() << "1";
                } else {
                    if  (openBolts.find(3) != openBolts.end()) {
                        logCurrentWheelState = 11;
                    } else {
                        logCurrentWheelState = 3;
                    }
                }
            } else {
                if  (openBolts.find(2) != openBolts.end()) {
                    if  (openBolts.find(3) != openBolts.end()) {
                        logCurrentWheelState = 13;
                    } else {
                        logCurrentWheelState = 5;
                    }
                } else {
                    if  (openBolts.find(3) != openBolts.end()) {
                        logCurrentWheelState = 9;
                    } else {
                        logCurrentWheelState = 1;
                    }
                }
            }
        } else {
            if  (openBolts.find(1) != openBolts.end()) {
                if  (openBolts.find(2) != openBolts.end()) {
                    if  (openBolts.find(3) != openBolts.end()) {
                        logCurrentWheelState = 14;
                    } else {
                        logCurrentWheelState = 6;
                    }
                } else {
                    if  (openBolts.find(3) != openBolts.end()) {
                        logCurrentWheelState = 10;
                    } else {
                        logCurrentWheelState = 2;
                    }
                }
            } else {
                if  (openBolts.find(2) != openBolts.end()) {
                    if  (openBolts.find(3) != openBolts.end()) {
                        logCurrentWheelState = 12;
                    } else {
                        logCurrentWheelState = 4;
                    }
                } else {
                    if  (openBolts.find(3) != openBolts.end()) {
                        logCurrentWheelState = 8;
                    } else {
                        logCurrentWheelState = 0;
                    }
                }
            }

        }
        currentWheelState = logCurrentWheelState;

        auto normalMatrix = QMatrix();
        normalMatrix.rotate(angle_ust_cz);

        this->ui->r123_wheel_bolt_rot->setPixmap(QPixmap(rotations[currentWheelState]).transformed(normalMatrix).transformed(normalMatrix));
    }
    if (!roted_bolt_succed)
        if (cz_state == 0)
        {
            static QPixmap pix(":/res/r123/open_detail/r123_cz_otkr.png");
            this->ui->r123_cz->setPixmap(pix);
            cz_state = 1;
            currentWheelState = 16;
            this->ui->r123_wheel_bolt_rot->setPixmap(QPixmap());
        } else if (cz_state == 1)
        {
            static QPixmap pix(":/res/r123/open_detail/r123_cz_open.png");
            this->ui->r123_cz->move(ui->r123_cz->pos().x() - offsetX, ui->r123_cz->pos().y() - offsetY);
            this->ui->r123_cz->setPixmap(pix);
            cz_state = 2;
            currentWheelState = logCurrentWheelState;

            auto normalMatrix = QMatrix();
            normalMatrix.rotate(angle_ust_cz);

            this->ui->r123_wheel_bolt_rot->setPixmap(QPixmap(rotations[currentWheelState]).transformed(normalMatrix).transformed(normalMatrix));
        } else if (cz_state == 2)
        {
            static QPixmap pix(":/res/r123/open_detail/r123_cz_otkr.png");
            this->ui->r123_cz->move(ui->r123_cz->pos().x() + offsetX, ui->r123_cz->pos().y() + offsetY);
            this->ui->r123_cz->setPixmap(pix);
            this->ui->r123_wheel_bolt_rot->clear();
            cz_state = 3;
            this->ui->r123_wheel_bolt_rot->setPixmap(QPixmap());
            currentWheelState = 16;
        } else if (cz_state == 3) {
        static QPixmap pix(":/res/r123/open_detail/r123_cz_zakr.png");
        this->ui->r123_cz->setPixmap(pix);
        cz_state = 0;
        currentWheelState = 16;
        this->ui->r123_wheel_bolt_rot->setPixmap(QPixmap());
    }
}

void R123::update_zpcz() {

    if (this->controller.getCurrentZpcz() <= 4) {
        this->zpcz_angles[this->controller.getCurrentZpcz() - 1] = angle_nastr;
        countFrequency();
        this->zpcz_frequencies[this->controller.getCurrentZpcz() - 1] = this->ui->r123_line->geometry().x();
        this->zpcz_angle_ust_cz[this->controller.getCurrentZpcz() - 1] = angle_ust_cz;
        qDebug() << this->zpcz_angles[this->controller.getCurrentZpcz() - 1] << " ! " << this->zpcz_frequencies[this->controller.getCurrentZpcz() - 1];
    }
}

void R123::wheelEventRs(QWheelEvent *event) {

    static QPixmap *szum = new QPixmap(":/res/r123/r123-szum.png");
    static QPixmap *ust_cz = new QPixmap(":/res/r123/r123-ust_cz.png");
    static QPixmap *nastr = new QPixmap(":/res/r123/r123_nastr.png");
    static QPixmap *volume = new QPixmap(":/res/r123/r123_volume.png");
    qDebug() << "CurrentWheelState" << currentWheelState <<  ": " << rotations[currentWheelState] << "\n";
    QPixmap *mierdaDeRound = new QPixmap(rotations[currentWheelState]);
    static int angle_szum = 0,
             angle_volume = 0;
    qDebug() << event->x() << " " << event->y();
    if (event->x() > 179 && event->y() > 136
            && event->x() < 253 && event->y() < 198)
    {
        this->keyReleaseEvent(nullptr);
        QPixmap pixmap(*szum);
        QMatrix rm;
        if (event->angleDelta().ry() > 0 && angle_szum <= 8)
            angle_szum += 4;
        else if (event->angleDelta().ry() < 0 && angle_szum >= -72)
            angle_szum -= 4;

        if (angle_szum > 360)
            angle_szum -= 360;
        if (angle_szum < -360)
            angle_szum += 360;
        rm.rotate(angle_szum);

        pixmap = pixmap.transformed(rm);

        ui->r123_szum->setPixmap(QPixmap(pixmap.transformed(rm)));
        controller.setNoise(2. - float(angle_szum + 76) * 2 / 88);
    }
    else if (event->x() > 255 && event->y() > 264
             && event->x() < 358 && event->y() < 360 && this->r123_ustcz_can_move) {


        this->keyReleaseEvent(nullptr);

        getAngleToBeSetup();
        countFrequency();

        if (this->controller.getCurrentZpcz() <= 4) {

            bool bolt_is_opened = false;
            for (int i : openBolts) {
                if (i == this->controller.getCurrentZpcz() - 1) {
                    bolt_is_opened = true;
                }
            }

            if (!bolt_is_opened)
                return;
        }

        static int substep = 3;
        static int step = 20;
        QPixmap pixmap(*ust_cz);
        QMatrix rm;
        int position = 0;
        if (event->angleDelta().ry() > 0)
        { angle_ust_cz += 4; position = 8; }
        else if (event->angleDelta().ry() < 0)
        { angle_ust_cz -= 4; position = -8; }
        QRect rect = this->ui->r123_line->geometry();
        bool rotating_condition = !(position > 0 && rect.x() >= 400) && !(position < 0 && rect.x() <= -25211 + 800);

        if (rotating_condition)
        {
            if (angle_ust_cz > 360)
                angle_ust_cz -= 360;
            if (angle_ust_cz < -360)
                angle_ust_cz += 360;
            rm.rotate(angle_ust_cz);

            pixmap = pixmap.transformed(rm);

            ui->r123_ust_cz->setPixmap(QPixmap(pixmap.transformed(rm)));

            QPixmap pixWheel = QPixmap(*mierdaDeRound);
            auto normalMatrix = QMatrix();
            normalMatrix.rotate(angle_ust_cz);
            pixWheel = pixWheel.transformed(normalMatrix);
            ui->r123_wheel_bolt_rot->setPixmap(QPixmap(pixWheel.transformed(normalMatrix)));

            rect.moveTo(rect.x() + position, rect.y());

            this->ui->r123_line->setGeometry(rect);

            step -= position;
            if (step > 20) { step -= substep % 3 == 0 ? 24 : 20; substep+=1; substep%=3; substep+=3; }
            else if (step <= 0) { step += substep % 3 == 0 ? 24 : 20; substep-=1; substep%=3; substep+=3; }

            this->currentFrequency = countFrequency();
            update_zpcz();
        }

    }
    else if (event->x() > 629 && event->y() > 188
             && event->x() < 787 && event->y() < 322)
    {

        QPixmap pixmap(*nastr);
        QMatrix rm;

        if (event->angleDelta().ry() > 0)
            angle_nastr += 4;
        else if (event->angleDelta().ry() < 0)
            angle_nastr -= 4;

        if (angle_nastr > 360)
            angle_nastr -= 720;
        if (angle_nastr < -360)
            angle_nastr += 720;
        rm.rotate(angle_nastr);

        pixmap = pixmap.transformed(rm);

        ui->r123_nastr->setPixmap(QPixmap(pixmap.transformed(rm)));

        update_zpcz();

        updateOpacity();
    }
    else if (event->x() > 869 && event->y() > 389
             && event->x() < 965 && event->y() < 476)
    {
        this->keyReleaseEvent(nullptr);
        QPixmap pixmap(*volume);
        QMatrix rm;
        if (event->angleDelta().ry() > 0 && angle_volume <= 4)
            angle_volume += 4;
        else if (event->angleDelta().ry() < 0 && angle_volume >= -116)
            angle_volume -= 4;

        if (angle_volume > 360)
            angle_volume -= 360;
        if (angle_volume < -360)
            angle_volume += 360;
        rm.rotate(angle_volume);

        pixmap = pixmap.transformed(rm);

        ui->r123_volume->setPixmap(QPixmap(pixmap.transformed(rm)));
        controller.setVolume(float(angle_volume + 120) / 128);
    }
}

void R123::updateszkl()
{

    static QPixmap zpcz1_off(":/res/r123/numbers/r123_zpcz1.png");
    static QPixmap zpcz1_on(":/res/r123/numbers/r123_zpcz1_on.png");

    static QPixmap zpcz2_off(":/res/r123/numbers/r123_zpcz2.png");
    static QPixmap zpcz2_on(":/res/r123/numbers/r123_zpcz2_on.png");

    static QPixmap zpcz3_off(":/res/r123/numbers/r123_zpcz3.png");
    static QPixmap zpcz3_on(":/res/r123/numbers/r123_zpcz3_on.png");

    static QPixmap zpcz4_off(":/res/r123/numbers/r123_zpcz4.png");
    static QPixmap zpcz4_on(":/res/r123/numbers/r123_zpcz4_on.png");

    static QPixmap poddiap1_off(":/res/r123/numbers/r123_poddiap1.png");
    static QPixmap poddiap1_on(":/res/r123/numbers/r123_poddiap1_on.png");

    static QPixmap poddiap2_off(":/res/r123/numbers/r123_poddiap2.png");
    static QPixmap poddiap2_on(":/res/r123/numbers/r123_poddiap2_on.png");
    static auto off_all = [this](){
        this->ui->r123_zpcz1->setPixmap(zpcz1_off);
        this->ui->r123_zpcz2->setPixmap(zpcz2_off);
        this->ui->r123_zpcz3->setPixmap(zpcz3_off);
        this->ui->r123_zpcz4->setPixmap(zpcz4_off);
        this->ui->r123_poddiap1->setPixmap(poddiap1_off);
        this->ui->r123_poddiap2->setPixmap(poddiap2_off);
    };
    if (szkl_on)
    {
        switch(currentzpcz) {
        case 1:
            off_all();
            this->ui->r123_zpcz1->setPixmap(zpcz1_on);
            break;
        case 2:
            off_all();
            this->ui->r123_zpcz2->setPixmap(zpcz2_on);
            break;
        case 3:
            off_all();
            this->ui->r123_zpcz3->setPixmap(zpcz3_on);
            break;
        case 4:
            off_all();
            this->ui->r123_zpcz4->setPixmap(zpcz4_on);
            break;
        default:
            off_all();
        }
        if (!currentPoddiap)
        {
            this->ui->r123_poddiap1->setPixmap(poddiap1_on);
            this->ui->r123_poddiap2->setPixmap(poddiap2_off);
        }
        else
        {
            this->ui->r123_poddiap1->setPixmap(poddiap1_off);
            this->ui->r123_poddiap2->setPixmap(poddiap2_on);
        }
    }
    else {
        off_all();
    }
}

void R123::mousePressEventRs(QMouseEvent *event) {
    QPixmap pixUpped(":/res/r123/vsua_switch_ind.jpg.png");
    QPixmap pixDwned(":/res/r123/vsua_switch_ind_r.jpg.png");
    QPixmap empty;


    if (event->x() > 997 && event->y() > 418
            && event->x() < 1038 && event->y() < 511)
    {
        this->keyReleaseEvent(nullptr);
        this->r123_ziemLaunched = !this->r123_ziemLaunched;
        if (r123_ziemLaunched)
            this->ui->r123_ziem->setStyleSheet("background-image: url(:/res/r123/r123_ziem.png);");
        else
            this->ui->r123_ziem->setStyleSheet("");
    } else if (event->x() > 966 && event->y() > 42
               && event->x() < 1045 && event->y() < 346 && r123_ziemLaunched)
    {
        this->keyReleaseEvent(nullptr);
        static bool antena_launched = false;
        antena_launched = !antena_launched;
        if (antena_launched)
            ui->r123_antena->setStyleSheet("background-image: url(:/res/r123/r123_ant.png);");
        else
            ui->r123_antena->setStyleSheet("");
        controller.setR123AntenaLaunched(antena_launched);
        controller.actionResolver(R123StateController::R123_ANTENA);
    } else if (event->x() > 131 && event->y() > 232
        && event->x() < 222 && event->y() < 329 && r123_ziemLaunched)
    {
        this->keyReleaseEvent(nullptr);
        // -4 8 20 36 52 68 88 96 116 136 148 168
        static int state = 1;
        auto rotate = [this](int angle) {
            static QPixmap pix(":/res/r123/r123_control_ui.png");
            QPixmap pixmap(pix);
            QMatrix rm;

            rm.rotate(angle);

            pixmap = pixmap.transformed(rm);

            ui->r123_controlu->setPixmap(QPixmap(pixmap.transformed(rm)));
        };
        switch(state) {
        case 1:
            if (event->button() == Qt::LeftButton)
            { rotate(12); state = 2; } else { rotate(172); state = 12; }
            break;
        case 2:
            if (event->button() == Qt::LeftButton)
            { rotate(24); state = 3; } else { rotate(0); state = 1; }
            break;
        case 3:
            if (event->button() == Qt::LeftButton)
            { rotate(40); state = 4; } else { rotate(12); state = 2; }
            break;
        case 4:
            if (event->button() == Qt::LeftButton)
            { rotate(56); state = 5; } else { rotate(24); state = 3; }
            break;
        case 5:
            if (event->button() == Qt::LeftButton)
            { rotate(72); state = 6; } else { rotate(40); state = 4; }
            break;
        case 6:
            if (event->button() == Qt::LeftButton)
            { rotate(92); state = 7; } else { rotate(56); state = 5; }
            break;
        case 7:
            if (event->button() == Qt::LeftButton)
            { rotate(100); state = 8; } else { rotate(72); state = 6; }
            break;
        case 8:
            if (event->button() == Qt::LeftButton)
            { rotate(120); state = 9; } else { rotate(92); state = 7; }
            break;
        case 9:
            if (event->button() == Qt::LeftButton)
            { rotate(140); state = 10; } else { rotate(100); state = 8; }
            break;
        case 10:
            if (event->button() == Qt::LeftButton)
            { rotate(152); state = 11; } else { rotate(120); state = 9; }
            break;
        case 11:
            if (event->button() == Qt::LeftButton)
            { rotate(172); state = 12; } else { rotate(140); state = 10; }
            break;
        case 12:
            if (event->button() == Qt::LeftButton)
            { rotate(0); state = 1; } else { rotate(152); state = 11; }
            break;
        }
        if (state == 2)
            regim_raboty = 1;
        else if (state == 3)
            regim_raboty = 2;
        else if (state == 8)
            regim_raboty = 0;
        else
            regim_raboty = 3;

        if (regim_raboty == 1 || regim_raboty == 2) {
            controller.setIsCorrectRegim(true);
            controller.activateRst(space_is_pressed);
        } else {
            controller.setIsCorrectRegim(false);
            controller.activateRst(space_is_pressed);
        }
    }
    else if (event->x() > 387 && event->y() > 237
             && event->x() < 596 && event->y() < 480 && r123_ziemLaunched) {
        wheelFlow(event);
    } else if (event->x() > 23 && event->y() > 464
               && event->x() < 216 && event->y() < 631 && r123_ziemLaunched)
    {
        this->keyReleaseEvent(nullptr);
        static bool launched = false;
        if (launched) {
            this->ui->r123_pit->setStyleSheet("");
            launched = false;
        } else {
            this->ui->r123_pit->setStyleSheet("background-image: url(:/res/r123/r123_pit.png);");
            launched = true;
        }
        this->controller.actionResolver(R123StateController::R123_PIT);
        this->controller.activateRst(space_is_pressed);
    } else if (event->x() > 241 && event->y() > 463
               && event->x() < 340 && event->y() < 631 && r123_ziemLaunched)
    {
        this->keyReleaseEvent(nullptr);
        static bool launched = false;
        if (launched) {
            this->ui->r123_mtg->setStyleSheet("");
            launched = false;
        } else {
            this->ui->r123_mtg->setStyleSheet("background-image: url(:/res/r123/r123_mtg.png);");
            launched = true;
        }
        this->controller.setR123MTGLaunched(launched);
    } else if (event->x() > 115 && event->y() > 353
               && event->x() < 146 && event->y() < 380 && r123_ziemLaunched)
    {
        this->keyReleaseEvent(nullptr);
        //szkala
        static bool launched = false;
        static QPixmap pix(":/res/r123/vsua-clk_ind.png");
        static QPixmap pix_r(":/res/r123/vsua-clk_ind_r.png");
        if (launched)
        {
            this->ui->r123_szkalaswitch->setPixmap(pix);
            launched = !launched;
        } else {
            this->ui->r123_szkalaswitch->setPixmap(pix_r);
            launched = !launched;
        }
        this->controller.actionResolver(R123StateController::R123_SZKALA);
    } else if (event->x() > 194 && event->y() > 353
               && event->x() < 224 && event->y() < 380 && r123_ziemLaunched)
    {
        this->keyReleaseEvent(nullptr);
        //rst vkl
        static bool launched = false;
        static QPixmap pix(":/res/r123/vsua-clk_ind.png");
        static QPixmap pix_r(":/res/r123/vsua-clk_ind_r.png");
        if (launched)
        {
            this->ui->r123_powerswitcher->setPixmap(pix);
            launched = !launched;
        } else {
            this->ui->r123_powerswitcher->setPixmap(pix_r);
            launched = !launched;
        }
        this->controller.actionResolver(R123StateController::R123_POWER);
    } else if (event->x() > 150 && event->y() > 353
               && event->x() < 190 && event->y() < 380 && r123_ziemLaunched)
    {
        //ton call
        static QPixmap pix(":/res/r123/vsua-nastr_fil_r.png");
        this->ui->r123_ton_call->setPixmap(pix);
        this->r123_ton_call_pressed = true;
        controller.setIsTonCallPressed(true);
    } else if (event->x() > 628 && event->y() > 347
               && event->x() < 824 && event->y() < 537 && r123_ziemLaunched) {
        chooseZPCZ(event);
    } else if (event->x() > 267 && event->y() > 129
               && event->x() < 370 && event->y() < 228 && r123_ziemLaunched)
    {
        this->keyReleaseEvent(nullptr);
        static int state = 1;
        auto rotate = [this](int angle) {
            static QPixmap pix(":/res/r123/r123_simp.png");
            QPixmap pixmap(pix);
            QMatrix rm;

            rm.rotate(angle);

            pixmap = pixmap.transformed(rm);

            ui->r123_simp->setPixmap(QPixmap(pixmap.transformed(rm)));
        };
        switch(state) {
        case 1:
            rotate(18); state = 2;
            break;
        case 2:
            rotate(0); state = 1;
            break;
        }
    } else if (event->x() > 853 && event->y() > 216
               && event->x() < 872 && event->y() < 242 && this->r123_vechko_upped && r123_ziemLaunched) {
        this->keyReleaseEvent(nullptr);
        if (this->r123_zpcz_switchers[0]) this->ui->r123_zpcz1_poddiap_sl->setPixmap(pixUpped);
        else this->ui->r123_zpcz1_poddiap_sl->setPixmap(pixDwned);
        this->r123_zpcz_switchers[0] = !this->r123_zpcz_switchers[0];
        if (this->currentzpcz == 1)
            this->currentPoddiap = this->r123_zpcz_switchers[0];
        this->updateszkl();
    } else if (event->x() > 887 && event->y() > 216
               && event->x() < 913 && event->y() < 242 && this->r123_vechko_upped && r123_ziemLaunched) {
        this->keyReleaseEvent(nullptr);
        if (this->r123_zpcz_switchers[1]) this->ui->r123_zpcz2_poddiap_sl->setPixmap(pixUpped);
        else this->ui->r123_zpcz2_poddiap_sl->setPixmap(pixDwned);
        this->r123_zpcz_switchers[1] = !this->r123_zpcz_switchers[1];
        if (this->currentzpcz == 2)
            this->currentPoddiap = this->r123_zpcz_switchers[1];
        this->updateszkl();
    } else if (event->x() > 922 && event->y() > 216
               && event->x() < 945 && event->y() < 242 && this->r123_vechko_upped && r123_ziemLaunched) {
        this->keyReleaseEvent(nullptr);
        if (this->r123_zpcz_switchers[2]) this->ui->r123_zpcz3_poddiap_sl->setPixmap(pixUpped);
        else this->ui->r123_zpcz3_poddiap_sl->setPixmap(pixDwned);
        this->r123_zpcz_switchers[2] = !this->r123_zpcz_switchers[2];
        if (this->currentzpcz == 3)
            this->currentPoddiap = this->r123_zpcz_switchers[2];
        this->updateszkl();
    } else if (event->x() > 953 && event->y() > 216
               && event->x() < 972 && event->y() < 242 && this->r123_vechko_upped && r123_ziemLaunched) {
        this->keyReleaseEvent(nullptr);
        if (this->r123_zpcz_switchers[3]) this->ui->r123_zpcz4_poddiap_sl->setPixmap(pixUpped);
        else this->ui->r123_zpcz4_poddiap_sl->setPixmap(pixDwned);
        this->r123_zpcz_switchers[3] = !this->r123_zpcz_switchers[3];
        if (this->currentzpcz == 4)
            this->currentPoddiap = this->r123_zpcz_switchers[3];
        this->updateszkl();

    }else if (event->x() > 815 && event->y() > 106
               && event->x() < 998 && event->y() < 251 && r123_ziemLaunched)
    {
        this->keyReleaseEvent(nullptr);
        static bool launched = false;
        if (launched) {

            this->ui->r123_zpcz1_poddiap_sl->setPixmap(empty);
            this->ui->r123_zpcz2_poddiap_sl->setPixmap(empty);
            this->ui->r123_zpcz3_poddiap_sl->setPixmap(empty);
            this->ui->r123_zpcz4_poddiap_sl->setPixmap(empty);

            this->ui->r123_poddiap_switchers->setStyleSheet("");
            launched = false;

        } else {

            this->ui->r123_zpcz1_poddiap_sl->setPixmap(!this->r123_zpcz_switchers[0] ? pixUpped : pixDwned);
            this->ui->r123_zpcz2_poddiap_sl->setPixmap(!this->r123_zpcz_switchers[1] ? pixUpped : pixDwned);
            this->ui->r123_zpcz3_poddiap_sl->setPixmap(!this->r123_zpcz_switchers[2] ? pixUpped : pixDwned);
            this->ui->r123_zpcz4_poddiap_sl->setPixmap(!this->r123_zpcz_switchers[3] ? pixUpped : pixDwned);

            this->ui->r123_poddiap_switchers->setStyleSheet("background-image: url(:/res/r123/r123_poddiap_switchers.png);");
            launched = true;
        }
        this->r123_vechko_upped = launched;
    }
}

void R123::updateOpacity()
{
    int rotate_delta = abs(getAngleToBeSetup() - angle_nastr);

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

    this->controller.activateRst(this->space_is_pressed);
}

void R123::setUpZpczWhileChanging() {
    if (currentzpcz >= 5)
        return;

    rotateFrequency(
            this->zpcz_frequencies[currentzpcz - 1],
            this->zpcz_angle_ust_cz[currentzpcz - 1]
            );
    rotateSetUp(this->zpcz_angles[currentzpcz - 1]);
}

void R123::rotateFrequency(int to_frequency, int to_angle) {

    QPixmap *mierdaDeRound = new QPixmap(rotations[currentWheelState]);
    static QPixmap *ust_cz = new QPixmap(":/res/r123/r123-ust_cz.png");

    const int startFreq = 35900;
    getAngleToBeSetup();
    countFrequency();

    static int substep = 3;
    static int step = 20;
    QPixmap pixmap(*ust_cz);
    QMatrix rm;
    int position = 0;

    QRect rect = this->ui->r123_line->geometry();

    rm.rotate(to_angle);

    pixmap = pixmap.transformed(rm);

    ui->r123_ust_cz->setPixmap(QPixmap(pixmap.transformed(rm)));

    QPixmap pixWheel = QPixmap(*mierdaDeRound);
    auto normalMatrix = QMatrix();
    normalMatrix.rotate(to_angle);
    pixWheel = pixWheel.transformed(normalMatrix);
    ui->r123_wheel_bolt_rot->setPixmap(QPixmap(pixWheel.transformed(normalMatrix)));

    rect.moveTo(to_frequency, rect.y());

    this->ui->r123_line->setGeometry(rect);

    step -= position;
    if (step > 20) { step -= substep % 3 == 0 ? 24 : 20; substep+=1; substep%=3; substep+=3; }
    else if (step <= 0) { step += substep % 3 == 0 ? 24 : 20; substep-=1; substep%=3; substep+=3; }

    angle_ust_cz = to_angle;

    this->currentFrequency = countFrequency();
}

void R123::rotateSetUp(int to_angle) {
    static QPixmap *nastr = new QPixmap(":/res/r123/r123_nastr.png");
    QPixmap pixmap(*nastr);
    QMatrix rm;

    angle_nastr = to_angle;
    if (angle_nastr > 360)
        angle_nastr -= 720;
    if (angle_nastr < -360)
        angle_nastr += 720;
    rm.rotate(angle_nastr);

    pixmap = pixmap.transformed(rm);

    ui->r123_nastr->setPixmap(QPixmap(pixmap.transformed(rm)));

    update_zpcz();

    updateOpacity();
}
