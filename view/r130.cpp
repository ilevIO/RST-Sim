#include "r130.h"
#include "ui_r130.h"
#include <QDebug>
#include <QMouseEvent>

R130::R130(QString IP, bool is_server, AbstractNetworkController * controller) :
    QMainWindow(nullptr),
    ui(new Ui::r130)
{
    setFocusPolicy(Qt::FocusPolicy::StrongFocus);

    QObject::connect(&r130_nastroyka_thread, SIGNAL(block_until_nastroyka_done()), this, SLOT(block_until_nastroyka_done()), Qt::QueuedConnection);

    this->setFixedSize(916, 691);

    block_all = false;

    ui->setupUi(this);
    bp_zem = false;
    bp_pit = false;
    bp_vsua = false;

    r130_setup_is_done = false;
    r130_vsu_cable_1_launched = false;
    r130_vsu_cable_2_launched = false;
    r130_cable_pit = false;
    r130_cable_mtg = false;
    r130_ziem = false;
    r130_smooth = PLAVNO;
    r130_control = 1;
    r130_regim = DEGURN;
    r130_rod_raboty = ATU;
    r130_nastr_is_allowed = false;
    r130_vkl_switcher = false;
    r130_prm_prd_switcher = PRD;
    r130_rru_aru_switcher = ARU;

    r130_uroven_pered = 50;
    r130_volume = 0;
    r130_amplify = 0;
    r130_ton_tlg = 0;
    r130_x1_angle = 0;
    r130_x100_angle = 0;
    r130_x1000_angle = 0;

    r130_done_setup_frequency = 0;
}

R130::~R130()
{
    delete ui;
}

void R130::mousePressEvent(QMouseEvent *event) {
    qDebug() << "x: " << event->x() << " y: " << event->y();

    if (block_all)
        return;

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
    update_r130_rst();
}

void R130::wheelEvent(QWheelEvent *event) {
    if (block_all)
        return;

    if (this->ui->tabWidget->currentIndex() == 1)
    {
       wheelEventVsua(event);
    }
    else if (this->ui->tabWidget->currentIndex() == 0)
    {
        wheelEventRs(event);
    }
    update_r130_rst();
}

void R130::apply_rotated_pixmap_to_widget(QLabel *widget_ptr, QPixmap *pixmap_ptr, qreal angle) {
    QPixmap pixmap(*pixmap_ptr);
    QMatrix rotate_matrix;

    rotate_matrix.rotate(angle);
    pixmap = pixmap.transformed(rotate_matrix);

    widget_ptr->setPixmap(pixmap);
}


void R130::mouseReleaseEvent(QMouseEvent *event)
{
    if (block_all)
        return;

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
    update_r130_rst();
}

void R130::block_until_nastroyka_done() {
    block_all = !block_all;

    if (block_all) {
        this->r130_setup_is_done = true;
        this->r130_done_setup_frequency = count_frequency();
        qDebug() << r130_done_setup_frequency;
        this->ui->r130_nastroyka_diod->setStyleSheet("background-image: url(:/res/R130/r130_nastroyka.png);");
    } else {
        this->ui->r130_nastroyka_diod->setStyleSheet("");
    }
}

void R130NastroykaThread::run() {
    emit block_until_nastroyka_done();

    this->msleep(3000);

    emit block_until_nastroyka_done();
}



