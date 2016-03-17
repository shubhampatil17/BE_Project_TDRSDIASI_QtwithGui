#ifndef INTERSECTIONPOINTS_H
#define INTERSECTIONPOINTS_H

#include <opencv/cv.hpp>
#include <vector>

using namespace cv;
using namespace std;


class IntersectionPoints
{
    Mat img;
    int ACH;

public:
    IntersectionPoints(Mat, int);

    Mat findIntersectionPts();
    Mat findNonIntersectionPts();


    Mat hitmiss(Mat,Mat);
    Mat pattern(int, int, int);

    Mat hrpattern(int, int);
    Mat vtpattern(int, int);
    Mat h(Mat, int);
    Mat t(Mat, int);
};

#endif // INTERSECTIONPOINTS_H
