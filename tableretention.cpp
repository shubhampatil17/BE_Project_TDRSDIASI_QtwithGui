#include "tableretention.h"

struct comparison_struct {

    bool operator() (Point p, Point q) {
        if(p.x == q.x)
            return p.y < q.y;
        return (p.x < q.x);
    }

} sort_y;

struct comparison_xstruct {

    bool operator() (Point p, Point q) {
        if(p.y == q.y)
            return p.x < q.x;
        return (p.y < q.y);
    }

} sort_x;


TableRetention::TableRetention(vector<vector<Mat>> segmentationData,
                               vector<vector<int>> offsetData,
                               int ACH,
                               String filename)
{
    this->segmentationData = segmentationData;
    this->offsetData = offsetData;
    this->ACH = ACH;
    this->filename = filename;

    this->tessObj.Init(NULL,"eng",OEM_DEFAULT);
    this->tessObj.SetPageSegMode(PSM_AUTO_OSD);
}

vector<Mat> TableRetention::cellExtraction(vector<Point> dataPoints, Mat img, int tableId){

    int rows = findRetentionRowCount(dataPoints);
    int cols = findRetentionColCount(dataPoints);

    //cout<<rows<<"\n";
    //cout<<cols<<"\n";

    map<string,int> rowIndexer;
    map<string,int> colIndexer;

    vector<Mat> segmentedMats;

    Point retentionTable[rows][cols];

    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            retentionTable[i][j] = Point(-1,-1);
        }
    }

    for(int i=0; unsigned(i)<dataPoints.size();i++){

        int rowcount=0;

        for(int j=0; unsigned(j) <dataPoints.size();j++){

            if(dataPoints[i] == dataPoints[j])
                break;

            if(abs(dataPoints[j].y - dataPoints[j+1].y) > 2 ){
                rowcount++;
            }
        }

        rowIndexer.insert(pair<string, int>(to_string(dataPoints[i].x) + "," + to_string(dataPoints[i].y), rowcount));

    }



    sort(dataPoints.begin(), dataPoints.end(), sort_y);

    for(int i=0; unsigned(i)<dataPoints.size();i++){

        int colcount=0;

        for(int j=0; unsigned(j)<dataPoints.size();j++){

            if(dataPoints[i] == dataPoints[j])
                break;

            if(abs(dataPoints[j].x - dataPoints[j+1].x) > 2 ){
                colcount++;
            }
        }

        colIndexer.insert(pair<string, int>(to_string(dataPoints[i].x) + "," + to_string(dataPoints[i].y), colcount));

    }


    for(int i=0; unsigned(i)< dataPoints.size(); i++){

        int row = rowIndexer.at(to_string(dataPoints[i].x) + "," + to_string(dataPoints[i].y));
        int col = colIndexer.at(to_string(dataPoints[i].x) + "," + to_string(dataPoints[i].y));

        retentionTable[row][col] = dataPoints[i];
    }

    /*for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            cout<<"["<<retentionTable[i][j].x<<","<<retentionTable[i][j].y<<"]";
        cout<<"\n";*/

    vector<int> rowSpanVector;
    vector<int> colSpanVector;
    vector<int> blockWidthVector;
    vector<int> blockHeightVector;
    pair<int,int> dimensions;
    vector<string> blockTextVector;
    vector<Point> blockIdVector;

    for(int i=0; i<rows-1;i++){
        for(int j=0; j<cols-1;j++){

            Point topLeft, topRight, bottomLeft, bottomRight;

            int rowSpan =1, colSpan=1;

            topLeft = retentionTable[i][j];


            if(topLeft != Point(-1,-1)){

                int row = i+1;
                int col = j+1;

                while(retentionTable[row][j] == Point(-1,-1)){
                    if(row == rows-1)
                        break;

                    row++;
                    rowSpan++;
                }

                while(retentionTable[i][col] == Point(-1,-1)){
                    if(col == cols-1)
                        break;

                    col++;
                    colSpan++;
                }

                bottomLeft = retentionTable[row][j];
                topRight = retentionTable[i][col];

                bottomRight = Point(topRight.x, bottomLeft.y);

                /*bottomRight = retentionTable[row][col];


                bool hrConnected=true, vtConnected=true;

                if(bottomRight == Point(-1,-1)){

                    bottomRight = Point(topRight.x, bottomLeft.y);

                    cout<<bottomRight.x<<","<<bottomRight.y<<"\n";
                    cout<<bottomLeft.x<<","<<bottomLeft.y<<"\n";


                    Mat grayScale;
                    cvtColor(img, grayScale, CV_BGR2GRAY);
                    Preprocessing *procObj = new Preprocessing(grayScale);
                    Mat binimg = procObj->binarization();
                    //cout<<binimg;

                    imshow("asadasd",binimg);
                    int run =0 ;

                    for(int i= bottomLeft.x ;i<=bottomRight.x;i++ ){
                        //if(binimg.at<uchar>(i, bottomLeft.y) > 0){
                          //  run++;
                        //}

                        cout<< (int) binimg.at<uchar>(i,bottomLeft.y)<<" ";
                    }

                    //cout<<run<<"/"<<(bottomRight.x -bottomLeft.x)<<"\n";
                    hrConnected = (run > 0.75*(bottomRight.x - bottomLeft.x))? true:false;
                    //cout<<hrConnected<<"\n";

                    run = 0;
                    cout<<"\n\n";

                    for(int i= topRight.y ;i<=bottomRight.y;i++ ){
                        //if(binimg.at<uchar>( topRight.x, i) > 0){
                          //  run++;
                        //}

                        cout<< (int)binimg.at<uchar>(topRight.x,i)<<" ";
                    }

                    //cout<<run<<"/"<<(bottomRight.y - topRight.y)<<"\n";
                    vtConnected = (run > 0.75*(bottomRight.y - topRight.y))? true:false;
                    //cout<<vtConnected<<"\n";


                    if(!hrConnected && !vtConnected)
                        continue;

                    if(hrConnected){

                        while(true){
                            col++;

                            if(retentionTable[i][col] != Point(-1,-1) || col == cols-1)
                                break;
                        }
                    }

                    if(vtConnected){

                        while(true){
                            row++;

                            if(retentionTable[row][j] != Point(-1,-1) || row == rows-1)
                                break;
                        }
                    }

                    bottomRight = retentionTable[row][col];


                }
                */


                //if(bottomLeft==Point(-1,-1) || topRight==Point(-1,-1)|| bottomRight ==Point(-1,-1))
                  //  continue;

                if(bottomLeft==Point(-1,-1) || topRight==Point(-1,-1))
                    continue;


                //cout<<topLeft<<":"<<bottomLeft<<":"<<topRight<<":"<<bottomRight<<"\n";

                Mat croppedimage = img(Rect(topLeft, bottomRight));
                segmentedMats.push_back(croppedimage);
                string blockText = "";

                if( (bottomLeft.y - topLeft.y) > ACH && (topRight.x - topLeft.x) > ACH){

                    resize(croppedimage,croppedimage, Size(), 10, 10, INTER_LINEAR);

                    tessObj.SetImage((uchar*)croppedimage.data,
                                     croppedimage.size().width,
                                     croppedimage.size().height,
                                     croppedimage.channels(),
                                     croppedimage.step1());

                    tessObj.Recognize(0);
                    blockText = tessObj.GetUTF8Text();

                    //string imgname = filename+ "_Table"+to_string(tableId)+"_part_" + to_string(i+1)+"x"+to_string(j+1);
                    //imshow(imgname,croppedimage);
                }

                rowSpanVector.push_back(rowSpan);
                colSpanVector.push_back(colSpan);
                blockWidthVector.push_back(bottomRight.x - topLeft.x);
                blockHeightVector.push_back(bottomRight.y - topLeft.y);
                blockTextVector.push_back(blockText);
                blockIdVector.push_back(Point(i,j));
            }

        }
    }

    dimensions.first = rows - 1;
    dimensions.second = cols -1 ;

    blockRowSpanData.push_back(rowSpanVector);
    blockColSpanData.push_back(colSpanVector);
    blockWidthData.push_back(blockWidthVector);
    blockHeightData.push_back(blockHeightVector);
    blockTextData.push_back(blockTextVector);
    blockIdData.push_back(blockIdVector);

    tableDimensions.push_back(dimensions);

    return segmentedMats;

}

vector<vector<Mat>> TableRetention::docRetention(){

    vector<Mat> tableSegments = segmentationData[0];
    vector<Mat> pointSegments = segmentationData[1];

    vector<vector<Mat>> segmentedCellsInDoc;


    for(int i=0; unsigned(i)< tableSegments.size(); i++){
        vector<Point> pointDataset = extractIntersectionDataset(pointSegments[i]);
        segmentedCellsInDoc.push_back(cellExtraction(pointDataset, tableSegments[i], i)) ;
    }

    return segmentedCellsInDoc;
}

void TableRetention::generateXML(vector<vector<Mat>> segmentedCellsInDoc){

    string filenameCopy = filename;

    QString fname = QString::fromStdString(filenameCopy);
    QStringList splitData = fname.split("/");
    fname = splitData[splitData.length()-1];

    splitData = fname.split(".");
    splitData[splitData.length()-1] = QString("xml");
    fname = splitData.join(".");

    filenameCopy = fname.toStdString();

    //open xml file

    ofstream fp;
    fp.open(filenameCopy,ios::out| ios::trunc);

    //write <document> to xml file
    fp << "<Document>\n";

    for(int i=0;unsigned(i)< segmentedCellsInDoc.size();i++){
        //write <table>
        fp << "\t<Table>\n";
        fp << "\t\t<OffsetX>" + to_string(offsetData[0][i]) + "</OffsetX>\n";
        fp << "\t\t<OffsetY>" + to_string(offsetData[1][i]) + "</OffsetY>\n";

        pair<int,int> dimension = tableDimensions[i];

        fp << "\t\t<Rows>" + to_string(dimension.first) + "</Rows>\n";
        fp << "\t\t<Cols>" + to_string(dimension.second) + "</Cols>\n";

        for(int j=0; unsigned(j)< segmentedCellsInDoc[i].size();j++){
            //write<block>
            fp << "\t\t<Block>\n";

            fp << "\t\t\t<Id>\n";
            fp << "\t\t\t\t<x>" + to_string(blockIdData[i][j].x) + "</x>\n";
            fp << "\t\t\t\t<y>" + to_string(blockIdData[i][j].y) + "</y>\n";
            fp << "\t\t\t</Id>\n";

            fp << "\t\t\t<RowSpan>" + to_string(blockRowSpanData[i][j]) + "</RowSpan>\n";
            fp << "\t\t\t<ColSpan>" + to_string(blockColSpanData[i][j]) + "</ColSpan>\n";
            fp << "\t\t\t<Width>" + to_string(blockWidthData[i][j]) + "</Width>\n";
            fp << "\t\t\t<Height>" + to_string(blockHeightData[i][j]) + "</Height>\n";
            fp << "\t\t\t<Text>" + blockTextData[i][j] + "</Text>\n";

            fp << "\t\t</Block>\n";

        }

        fp << "\t</Table>\n";

    }

    //write </document>
    fp << "</Document>\n";

    fp.close();

}

vector<Point> TableRetention::extractIntersectionDataset(Mat img){

    vector<Point> reducedIntersectionPts;

    for(int i=0;i<img.rows;i++){
        for(int j=0;j<img.cols;j++){

            if((int)img.at<uchar>(i,j) !=0 ){
                reducedIntersectionPts.push_back(Point(j,i));
            }
        }
    }

    return reducedIntersectionPts;

}


int TableRetention::findRetentionColCount(vector<Point> dataPoints){

    sort(dataPoints.begin(), dataPoints.end(), sort_y);

    int cols=0;

    for(int i=1;unsigned(i)< dataPoints.size();i++){
        if( abs(dataPoints[i].x - dataPoints[i-1].x) > 2)
            cols++;
    }

    return cols+1;
}

int TableRetention::findRetentionRowCount(vector<Point> dataPoints){

    sort(dataPoints.begin(), dataPoints.end(), sort_x);

    int rows=0;

    for(int i=1;unsigned(i)< dataPoints.size();i++){
        if( abs(dataPoints[i].y - dataPoints[i-1].y) > 2)
            rows++;
    }

    return rows+1;
}
