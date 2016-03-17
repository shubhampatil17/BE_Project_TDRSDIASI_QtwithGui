#include "connectingcomponents.h"

ConnectingComponents::ConnectingComponents(Mat img, int ACH)
{
    this->ACH = ACH;
    this->img = img;
}

Mat ConnectingComponents::connectBrokenLines(){

    Mat hr_line_left, hr_line_right, vt_line_top, vt_line_bottom;

    int const anchor_pt1 = 1.7*ACH - 1, anchor_pt2 = 2*ACH - 1;

    //--------------------------------------------------------------------------
    // Joining Vertical broken lines


    Mat kernel_mat_vt = Mat::ones(1.7*ACH,1,CV_32S);		//kernel matrix for erosion

    erode(img, vt_line_top, kernel_mat_vt, Point(0,0), 1, BORDER_CONSTANT, Scalar(0));
    erode(img, vt_line_bottom, kernel_mat_vt, Point(0, anchor_pt1), 1, BORDER_CONSTANT, Scalar(0));

    Mat vt_union = vt_line_top|vt_line_bottom;
    Mat kernel_mat_dil = Mat::ones(ACH, 1, CV_32S);	//kernel matrix for dilation

    dilate(vt_union, vt_union, kernel_mat_dil, Point(-1,-1), 1, BORDER_CONSTANT, Scalar(0));

    Mat IMv = img | vt_union;			//Image merged vertical lines

    //---------------------------------------------------------------------------
    //Joining Horizontal broken lines

    Mat kernel_mat_hr = Mat::ones(1, 2*ACH, CV_32S);

    erode(img, hr_line_left, kernel_mat_hr, Point(0,0), 1, BORDER_CONSTANT, Scalar(0));
    erode(img, hr_line_right, kernel_mat_hr, Point(anchor_pt2,0), 1, BORDER_CONSTANT, Scalar(0));

    Mat hr_union = hr_line_left|hr_line_right;
    Mat kernel_mat_dil2= Mat::ones(1, 1.2*ACH, CV_32S);

    dilate(hr_union, hr_union, kernel_mat_dil2, Point(-1,-1), 1, BORDER_CONSTANT, Scalar(0));

    Mat IMh= img | hr_union;			//Image merged horizontal lines

    return IMh|IMv;

}
