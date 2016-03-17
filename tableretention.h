#ifndef TABLERETENTION_H
#define TABLERETENTION_H


#include <opencv/cv.hpp>
#include <tesseract/baseapi.h>
#include <vector>
#include <map>
#include <iostream>
#include <QString>
#include <QStringList>
#include <fstream>

#include "preprocessing.h"

using namespace cv;
using namespace tesseract;
using namespace std;

class TableRetention
{
    vector<vector<Mat>> segmentationData;
    vector<vector<int>> offsetData;
    int ACH;
    String filename;

    vector<vector<int>> blockRowSpanData;
    vector<vector<int>> blockColSpanData;
    vector<vector<int>> blockWidthData;
    vector<vector<int>> blockHeightData;
    vector<pair<int,int>> tableDimensions;
    vector<vector<string>> blockTextData;



    TessBaseAPI tessObj;

public:
    TableRetention(vector<vector<Mat>>, vector<vector<int>>, int, String);

    vector<Mat> cellExtraction(vector<Point>, Mat, int);

    vector<vector<Mat>> docRetention();

    void generateXML(vector<vector<Mat>>);

    vector<Point> extractIntersectionDataset(Mat);

    int findRetentionRowCount(vector<Point>);
    int findRetentionColCount(vector<Point>);

};

#endif // TABLERETENTION_H
