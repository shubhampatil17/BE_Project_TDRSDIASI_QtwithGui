#ifndef MYDIALOG2_H
#define MYDIALOG2_H

#include <QDialog>

namespace Ui {
class myDialog2;
}

class myDialog2 : public QDialog
{
    Q_OBJECT

public:
    explicit myDialog2(QWidget *parent = 0);
    ~myDialog2();

private:
    Ui::myDialog2 *ui;
};

#endif // MYDIALOG2_H
