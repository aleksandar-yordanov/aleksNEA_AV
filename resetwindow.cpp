#include "resetwindow.h"
#include "ui_resetwindow.h"

resetWindow::resetWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::resetWindow)
{
    ui->setupUi(this);
}

resetWindow::~resetWindow()
{
    delete ui;
}
