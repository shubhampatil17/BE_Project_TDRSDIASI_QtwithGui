#include "white_space_processing.h"

whitespaceprocessing::whitespaceprocessing(Mat img)
{
    this->img = img;
}

Mat whitespaceprocessing::white_space_process()
{

		Mat element;

        Mat binary(img.rows,img.cols,img.type());
        //threshold(img,binary,0,255,CV_THRESH_OTSU |CV_THRESH_BINARY_INV);

		//namedWindow("binary");
		//imshow("binary",binary);

		element = getStructuringElement(cv::MORPH_RECT, cv::Size(2,2) );
        morphologyEx(img, binary, CV_MOP_OPEN, element);

		return binary;
}
