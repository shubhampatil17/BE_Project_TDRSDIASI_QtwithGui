#ifndef RECONSTRUCTION_H
#define RECONSTRUCTION_H

#include <opencv/cv.hpp>
#include <vector>
#include <algorithm>
#include <map>

using namespace cv;
using namespace std;


class Reconstruction
{

    Mat img;
    int ACH;

public:
    Reconstruction(Mat, int);

    Mat reconstruction(Mat&);
};

#endif // RECONSTRUCTION_H
