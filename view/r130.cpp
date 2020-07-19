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

    r130_uroven_pered = 50;
    r130_volume = 0;
}

R130::~R130()
{
    delete ui;
}

void R130::mousePressEvent(QMouseEvent *event) {
    qDebug() << "x: " << event->x() << " y: " << event->y();

    if (this->ui->tabWidget->currentIndex() == 2) {
        mousePressEventBp(event);
    } else if (this->ui->tabWidget->currentIndex() == 0) {
        mousePressEventRs(event);
    }
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
