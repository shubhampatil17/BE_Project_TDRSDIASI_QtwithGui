#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include <opencv/cv.hpp>
#include <omp.h>

using namespace cv;
using namespace std;

class Preprocessing
{
    Mat img;

public:
    Preprocessing(Mat);

    Mat binarization();
    Mat pointClusterReduction();
    void skewCorrection();
    void deskew(double);

};

#endif // PREPROCESSING_H
