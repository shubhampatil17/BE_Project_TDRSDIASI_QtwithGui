#ifndef PAGESEGMENTATION_H
#define PAGESEGMENTATION_H

#include <opencv/cv.hpp>
#include <vector>

using namespace cv;
using namespace std;


class PageSegmentation
{
    Mat reconstructImg;
    Mat pointReducedImage;
    Mat clrImg;
    String filename;

    vector<int> offsetx;
    vector<int> offsety;

public:
    PageSegmentation(Mat, Mat, Mat, String);

    vector<vector<Mat>> multiTablePageSegmentation();

    vector<vector<int>> getSegmentOffsetData();
};

#endif // PAGESEGMENTATION_H
