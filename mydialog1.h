#ifndef MYDIALOG1_H
#define MYDIALOG1_H

#include <QDialog>

namespace Ui {
class myDialog1;
}

class myDialog1 : public QDialog
{
    Q_OBJECT

public:
    explicit myDialog1(QWidget *parent = 0);
    ~myDialog1();

private:
    Ui::myDialog1 *ui;
};

#endif // MYDIALOG1_H
