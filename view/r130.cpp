#include "r130.h"
#include "ui_r130.h"

R130::R130(QString IP, bool is_server, AbstractNetworkController * controller) :
    QMainWindow(nullptr),
    ui(new Ui::r130)
{
    setFocusPolicy(Qt::FocusPolicy::StrongFocus);

    this->setFixedSize(992, 671);

    ui->setupUi(this);
}

R130::~R130()
{
    delete ui;
}
