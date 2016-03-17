#include "mydialog2.h"
#include "ui_mydialog2.h"

myDialog2::myDialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::myDialog2)
{
    ui->setupUi(this);
}

myDialog2::~myDialog2()
{
    delete ui;
}

void myDialog2::on_pushButton_clicked()
{
    this->close();
}
