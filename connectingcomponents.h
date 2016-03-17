#ifndef CONNECTINGCOMPONENTS_H
#define CONNECTINGCOMPONENTS_H

#include <opencv/cv.hpp>
using namespace cv;

class ConnectingComponents
{

    int ACH;
    Mat img;

public:
    ConnectingComponents(Mat, int);

    Mat connectBrokenLines();
};

#endif // CONNECTINGCOMPONENTS_H
