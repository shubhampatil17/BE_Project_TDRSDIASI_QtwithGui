#ifndef AVERAGECHARHEIGHT_H
#define AVERAGECHARHEIGHT_H

#include <opencv/cv.hpp>

using namespace cv;

class AverageCharHeight
{

    int ach;
    Mat img;

public:
    AverageCharHeight(Mat);

    int calculateACH();

};

#endif // AVERAGECHARHEIGHT_H
