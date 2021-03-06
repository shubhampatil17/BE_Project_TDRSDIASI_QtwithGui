#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>

#include "tableretention.h"
#include "wsretention.h"


#include "mydialog1.h"
#include "mydialog2.h"

#include "preprocessing.h"
#include "averagecharheight.h"
#include "connectingcomponents.h"
#include "lineprocessing.h"
#include "intersectionpoints.h"
#include "reconstruction.h"
#include "pagesegmentation.h"

#include "white_space_processing.h"
#include "whitespacesegmentation.h"
#include "detecttabularlines.h"

#include <vector>
#include <omp.h>
#include <iostream>

#include <QFileDialog>
#include <QElapsedTimer>

using namespace cv;
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_commandLinkButton_clicked();

    void on_actionSelect_File_triggered();

    void on_actionSelect_Folder_triggered();

    void on_commandLinkButton_3_clicked();

    void on_commandLinkButton_2_clicked();

    void on_commandLinkButton_4_clicked();

    void on_singleProcSet_clicked();

    void on_batchProcSet_clicked();

    void on_achSlider_valueChanged(int value);

    void on_wordgapSlider_valueChanged(int value);

    void on_algoFireButton_clicked();

    void on_method1CheckBox_toggled(bool checked);

    void on_method2CheckBox_toggled(bool checked);

private:
    Ui::MainWindow *ui;

    myDialog1 *md1;
    myDialog2 *md2;

    std::vector<String> files;
    int achFactor;
    int wordgapFactor;
};

#endif // MAINWINDOW_H
