#include "preprocessing.h"

Preprocessing::Preprocessing(Mat img)
{
    this->img = img;
}

Mat Preprocessing::binarization(){

    Mat binimg(img.rows,img.cols,img.type());

    //#pragma omp parallel for
    for(int i=0; i<img.rows; i++)
        for(int j=0; j<img.cols; j++)
            if((int)img.at<uchar>(i,j)>125 && (int)img.at<uchar>(i,j)<200)
                img.at<uchar>(i,j)=img.at<uchar>(i,j)-50;

    // Binarization using Otsu Method
    threshold(img,binimg,0,255,THRESH_BINARY_INV|THRESH_OTSU);

    return binimg;
}

void Preprocessing::skewCorrection(){

    Mat bin2;
    threshold(img,bin2,0,255,CV_THRESH_BINARY_INV |CV_THRESH_OTSU);
    imshow("asdsada",bin2);

    Mat src = img.clone();


    Size size = src.size();

    bitwise_not(src, src);

    vector<Vec4i> lines;
    HoughLinesP(img, lines, 1, CV_PI/180, 100, size.width / 2.f, 20);

    Mat disp_lines(size, CV_8UC1, Scalar(0, 0, 0));
    double angle = 0.;
    unsigned nb_lines = lines.size();

    for (unsigned i = 0; i < nb_lines; ++i)
    {
        line(disp_lines, Point(lines[i][0], lines[i][1]),
        Point(lines[i][2], lines[i][3]), Scalar(255, 0 ,0));
        angle += atan2((double)lines[i][3] - lines[i][1],
        (double)lines[i][2] - lines[i][0]);
    }


    deskew(angle * 180 / CV_PI);

    angle /= nb_lines; // mean angle, in radians.

}

void Preprocessing::deskew(double angle){


    bitwise_not(img, img);

    vector<Point> points;
    Mat_<uchar>::iterator it = img.begin<uchar>();
    Mat_<uchar>::iterator end = img.end<uchar>();
    for (; it != end; ++it)
        if (*it)
            points.push_back(it.pos());

    RotatedRect box = minAreaRect(Mat(points));
    Mat rot_mat = getRotationMatrix2D(box.center, angle, 1);

    Mat rotated;
    warpAffine(img, rotated, rot_mat, img.size(), INTER_CUBIC);

    //Size box_size = box.size;

    //if (box.angle < -45.)
      // swap(box_size.width, box_size.height);

    //Mat rot_mat_rev = getRotationMatrix2D(box.center, -angle, 1);
    //Mat rotated_rev;
    //warpAffine(rotated, rotated_rev, rot_mat_rev ,img.size(), INTER_CUBIC);

    Mat bin1;
    threshold(rotated,bin1,0,255,CV_THRESH_BINARY_INV|CV_THRESH_OTSU);
    imshow("qweqrasr",bin1);



    //Mat cropped;
    //getRectSubPix(rotated, box_size, box.center, cropped);

    //img = cropped;
}

Mat Preprocessing::pointClusterReduction(){

    //#pragma omp parallel for
    for(int i=1;i<img.rows-1;i++){
        for(int j=1;j<img.cols-1;j++){

            int neighbours[8];

            neighbours[0]  = (int)img.at<uchar>(i,j-1); //top
            neighbours[1] = (int)img.at<uchar>(i,j+1); //bottom
            neighbours[2] = (int)img.at<uchar>(i-1,j); //left
            neighbours[3] = (int)img.at<uchar>(i+1,j); //right
            neighbours[4] = (int)img.at<uchar>(i-1,j-1); //topLeft
            neighbours[5] = (int)img.at<uchar>(i+1,j-1); //topRight
            neighbours[6] = (int)img.at<uchar>(i-1,j+1); //bottomLeft
            neighbours[7] = (int)img.at<uchar>(i+1,j+1); //bottomRight


            int maximum = neighbours[0];

            for(int i=1;i<8;i++){
                maximum = max(maximum,neighbours[i]);
            }

            if(maximum != 0){
                img.at<uchar>(i,j)=0;
            }
        }
    }

    return img;
}
