#include <tesseract/baseapi.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <opencv/cv.hpp>

#include <QString>
#include <QStringList>

#include <fstream>

using namespace tesseract;
using namespace cv;
using namespace std;


class WSretention{
	vector<Mat> blocks;
    TessBaseAPI tessObj;

public:
    WSretention();

	vector<Mat> retention(vector<Mat>,Mat,vector<pair <Point, Point> >,vector<int>,int);

    void passToTesseract(vector<Mat>, String);

};
