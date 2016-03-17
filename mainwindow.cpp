#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Automatic Table Detection from Scanned Document Images Via Analysis of Structural Information");
    setFixedSize(800,500);

    md1 = new myDialog1();
    md2 = new myDialog2();

    achFactor = 0;

    ui->frame->setEnabled(true);
    ui->frame_2->setEnabled(false);
    ui->frame_3->setEnabled(false);

    ui->singleProcSet->setChecked(false);
    ui->batchProcSet->setChecked(true);

    ui->statusLabel->setText("Status : Input files not loaded");

    ui->menuInput->actions().at(0)->setEnabled(false);
    ui->achSlider->setSliderPosition(7);
    ui->achValue->setText(QString::number(ui->achSlider->value()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSelect_File_triggered()
{
    files.clear();

    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Choose Image File"),
                QDir::homePath(),
                tr("Image files (*.png *jpg *jpeg *tif *tiff *bmp)")
                );

    files.push_back(filename.toStdString());

    if(files.size() != 0){
        ui->statusLabel->setText("Status : Input files loaded. Please click on 'Next'.");
        ui->inputPathLabel->setText("Input Path : " + filename);
    }
}

void MainWindow::on_actionSelect_Folder_triggered()
{
    files.clear();

    QString foldername = QFileDialog::getExistingDirectory(this, tr("Choose Folder"), QDir::homePath());

    glob(foldername.toStdString(),files);

    if(files.size() != 0){
        ui->statusLabel->setText("Status : Input files loaded. Please click on 'Next'.");
        ui->inputPathLabel->setText("Input Path : " + foldername);
    }

}

void MainWindow::on_commandLinkButton_clicked()
{
    if( files.size() == 0){
        md1->show();
    }else{

        ui->frame->setEnabled(false);
        ui->frame_2->setEnabled(true);
        ui->statusLabel->setText("Status : Select a multiplication factor for ACH");
    }
}


void MainWindow::on_commandLinkButton_3_clicked()
{
    ui->frame->setEnabled(true);
    ui->frame_2->setEnabled(false);
    ui->statusLabel->setText("Status : Input files loaded. Please click on 'Next'. ");
}

void MainWindow::on_commandLinkButton_2_clicked()
{
    ui->frame_2->setEnabled(false);
    ui->frame_3->setEnabled(true);
    ui->statusLabel->setText("Status : ACH Factor is set. Execute algorithm to obtain results.");
}


void MainWindow::on_commandLinkButton_4_clicked()
{
    ui->frame_2->setEnabled(true);
    ui->frame_3->setEnabled(false);
    ui->statusLabel->setText("Status : Select a multiplication factor for ACH");
}

void MainWindow::on_singleProcSet_clicked()
{
    ui->menuInput->actions().at(0)->setEnabled(true);
    ui->menuInput->actions().at(2)->setEnabled(false);
}

void MainWindow::on_batchProcSet_clicked()
{
    ui->menuInput->actions().at(0)->setEnabled(false);
    ui->menuInput->actions().at(2)->setEnabled(true);
}

void MainWindow::on_achSlider_valueChanged(int value)
{
    ui->achValue->setText(QString::number(value));
    achFactor = ui->achSlider->value();
}

void MainWindow::on_wordgapSlider_valueChanged(int value)
{
    ui->wordgapValue->setText(QString::number(value));
}

void MainWindow::on_algoFireButton_clicked()
{
    int totalFiles = files.size();

    float progressSteps = 100.0/totalFiles;
    float progressValue =0.0;

    omp_lock_t myLock;
    omp_init_lock(&myLock);


    //Preprocessing preprocessObj;        //Object of preprocessing class to apply preprocessing operations
    //AverageCharHeight achObj;           //Object of AverageCharHeight class to calculate ACH of doc
    //ConnectingComponents connectObj;    //Object of Connectingcomponents class to connect brokn lines
    //LineProcessing lineProcObj;         //Object of LineProcessing Class to extract horizontal and vertical lines

    QElapsedTimer timer;
    timer.start();

    //#pragma omp parallel for
    for(int i=0;i< totalFiles;i++){

        Mat image = imread(files[i], IMREAD_GRAYSCALE);
        Mat clrImage = imread(files[i], IMREAD_COLOR);

        if(!image.data){
            ui->progressLabel->setText("Skipping file : "+QString::number(i+1)+"/"
                                       +QString::number(totalFiles)+". Error: Not an Image.");
        }else{

            //imshow("Image"+files[i],clrImage);
            ui->progressLabel->setText("Processing file : "+QString::number(i+1)+"/"
                                       +QString::number(totalFiles)+".");


            Preprocessing *preprocessObj = new Preprocessing(image);
            Mat binimg = preprocessObj->binarization();
            //imshow("Binary"+files[i],binimg);

            AverageCharHeight *achObj = new AverageCharHeight(binimg);
            int ACH = achObj->calculateACH();
            //cout<<ACH<<"\n";

            if(ACH > 15){
                ACH = 7;
            }

            ConnectingComponents *connectObj = new ConnectingComponents(binimg, ACH);
            Mat connectedImg = connectObj->connectBrokenLines();

            LineProcessing *lineProcObj = new LineProcessing(connectedImg);

            //=========== PHASE I =======================================================

            Mat horizProcessedImg = lineProcObj->horizontalProcessing(2*ACH);
            Mat vertiProcessedImg = lineProcObj->verticalProcessing(2*ACH);

            //=========== PHASE II ======================================================

            horizProcessedImg = lineProcObj->horizontalProcessing(achFactor*ACH);
            vertiProcessedImg = lineProcObj->verticalProcessing(achFactor*ACH);

            //===========================================================================

            Mat mergedImg = horizProcessedImg + vertiProcessedImg;        //Operator Overloading
            //imshow("Merged"+files[i],mergedImg);


            IntersectionPoints *findPtsObj = new IntersectionPoints(mergedImg, ACH);
            Mat intersectionPts = findPtsObj->findIntersectionPts();
            //imshow("Intersection"+files[i],intersectionPts);

            Mat singleIntersectionPts = findPtsObj->findNonIntersectionPts();
            //imshow("SingleIntersection"+files[i], singleIntersectionPts);


            Mat reconstructedImg = Mat::zeros(binimg.rows, binimg.cols, binimg.type());

            Reconstruction *reconsObj = new Reconstruction(intersectionPts + singleIntersectionPts, ACH);
            Mat dataPoints = reconsObj->reconstruction(reconstructedImg);
            //imshow("Reconstruct"+files[i],reconstructedImg);


            preprocessObj = new Preprocessing(dataPoints.clone());
            Mat pointClusterReducedImg = preprocessObj->pointClusterReduction();
            //imshow("pointReduced"+files[i], pointClusterReducedImg);


            PageSegmentation *pageSegObj = new PageSegmentation(reconstructedImg.clone(),
                                                                pointClusterReducedImg,
                                                                clrImage,
                                                                files[i] );

            vector<vector<Mat>> segmentationData = pageSegObj->multiTablePageSegmentation();
            vector<vector<int>> offsetData = pageSegObj->getSegmentOffsetData();


            TableRetention *tableRetObj = new TableRetention(segmentationData, offsetData, ACH, files[i]);
            vector<vector<Mat>> segmentedCellsInDoc = tableRetObj->docRetention();

            tableRetObj->generateXML(segmentedCellsInDoc);
        }

        //============LOCK_SET ===========================
        omp_set_lock(&myLock);

        progressValue += progressSteps;
        ui->progressBar->setValue(int(progressValue));

        omp_unset_lock(&myLock);
        //============LOCK_UNSET =========================

    }

    cout << timer.elapsed();

    ui->progressBar->setValue(100);

    ui->frame->setEnabled(true);
    ui->frame_2->setEnabled(false);
    ui->frame_3->setEnabled(false);

    md2->show();

    omp_destroy_lock(&myLock);

}
