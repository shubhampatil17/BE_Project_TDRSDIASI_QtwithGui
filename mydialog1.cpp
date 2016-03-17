#include "mydialog1.h"
#include "ui_mydialog1.h"

myDialog1::myDialog1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::myDialog1)
{
    ui->setupUi(this);

    setWindowTitle("Select Input Files");
}

myDialog1::~myDialog1()
{
    delete ui;
}

void myDialog1::on_pushButton_clicked()
{
    this->close();
}
