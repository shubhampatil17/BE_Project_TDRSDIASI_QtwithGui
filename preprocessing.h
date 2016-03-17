#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include <opencv/cv.hpp>
#include <omp.h>

using namespace cv;

class Preprocessing
{
    Mat img;

public:
    Preprocessing(Mat);

    Mat binarization();
    Mat pointClusterReduction();

};

#endif // PREPROCESSING_H
