#ifndef LINEPROCESSING_H
#define LINEPROCESSING_H

#include <opencv/cv.hpp>

#include <vector>

using namespace cv;
using namespace std;

class LineProcessing
{
    Mat img;

public:
    LineProcessing(Mat);


    Mat horizontalProcessing(int);
    Mat verticalProcessing(int);

};

#endif // LINEPROCESSING_H
