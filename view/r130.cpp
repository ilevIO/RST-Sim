#include "r130.h"
#include "ui_r130.h"
#include <QDebug>
#include <QMouseEvent>

R130::R130(QString IP, bool is_server, AbstractNetworkController * controller) :
    QMainWindow(nullptr),
    ui(new Ui::r130)
{
    setFocusPolicy(Qt::FocusPolicy::StrongFocus);

    this->setFixedSize(916, 691);

    ui->setupUi(this);
    bp_zem = false;
    bp_pit = false;
    bp_vsua = false;

    r130_vsu_cable_1_launched = false;
    r130_vsu_cable_2_launched = false;
    r130_cable_pit = false;
    r130_cable_mtg = false;
    r130_smooth = PLAVNO;
    r130_control = 1;
    r130_regim = DEGURN;
    r130_rod_raboty = ATU;
    r130_nastr_is_allowed = false;

    r130_uroven_pered = 50;
    r130_volume = 0;
    r130_amplify = 0;
    r130_ton_tlg = 0;
}

R130::~R130()
{
    delete ui;
}

void R130::mousePressEvent(QMouseEvent *event) {
    qDebug() << "x: " << event->x() << " y: " << event->y();

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

void R130::wheelEvent(QWheelEvent *event) {
    if (this->ui->tabWidget->currentIndex() == 0) {
        this->wheelEventRs(event);
    }
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
        //controller.setIsTonCallPressed(false);
        //this->ui->r123_ton_call->setPixmap(pix);
    }
    //updateOpacity();
}

void R130::keyPressEvent(QKeyEvent *ev)
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
            //controller.keyPressHandler(ev);
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

void R130::keyReleaseEvent(QKeyEvent *ev)
{
    if (!ev || (ev->key() == Qt::Key_Space && !ev->isAutoRepeat()))
    {
        //controller.keyReleaseHandler(ev);
        this->space_is_pressed = false;
        updateOpacity();
    }
}

void R130::rotate_vsua_ustr(int angle)
{
    static QPixmap pix(":/res/r123/vsua-ustr.png");
    QPixmap pixmap(pix);
    QMatrix rm;

    rm.rotate(angle);

    pixmap = pixmap.transformed(rm);

    ui->vsua_ustr->setPixmap(QPixmap(pixmap.transformed(rm)));
}

