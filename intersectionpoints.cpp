#include "intersectionpoints.h"


IntersectionPoints::IntersectionPoints(Mat img, int ACH)
{
    this->img = img;
    this->ACH = ACH;
}

Mat IntersectionPoints::findIntersectionPts(){

    Mat new_image = img.clone();	//copy image data


    Mat top_left= hitmiss(new_image, pattern(0,0,ACH));
    top_left=top_left*10;

    Mat bottom_left= hitmiss(new_image, pattern(1,0,ACH));
    bottom_left=bottom_left*70;
    Mat top_right= hitmiss(new_image, pattern(0,1,ACH));
    top_right=top_right*20;
    Mat bottom_right= hitmiss(new_image, pattern(1,1,ACH));

    bottom_right=bottom_right*40;

    Mat output_image=Mat :: zeros(img.rows,img.cols,img.type());

    output_image = top_left+bottom_left+top_right+bottom_right;
    //output_image = (output_image==0);
    //output_image = output_image*255;
    //imshow("Merged Image", output_image);

    return output_image;

}

Mat IntersectionPoints::findNonIntersectionPts(){

    Mat new_image = img.clone();	//copy image data

    Mat left= hitmiss(new_image, horizontalPattern(1,ACH));
    left=left*200;

    Mat right= hitmiss(new_image, horizontalPattern(0,ACH));
    right=right*210;

    Mat top= hitmiss(new_image, verticalPattern(1,ACH));
    top=top*220;

    Mat bottom= hitmiss(new_image, verticalPattern(0,ACH));
    bottom=bottom*230;

    //-----------------------------------------------------------------
    //align points in same line
    //if possible check if image is non empty

    Mat tb=Mat :: zeros(img.rows,img.cols,img.type());
    Mat tb_aligned = alignVerticalPoints(top+bottom, ACH);

    Mat lr=Mat :: zeros(img.rows,img.cols,img.type());
    Mat lr_aligned = alignHorizontalPoints(left+right , ACH);

    //imshow("tb_aligned", tb_aligned);
    //imshow("lr_aligned", lr_aligned);

    Mat output_image=Mat :: zeros(img.rows,img.cols,img.type());
    output_image = tb_aligned + lr_aligned;

    //display(output_image);
    //imshow("modified",output_image);
    //output_image = left + right + top + bottom;
    //imshow("non modified",output_image);

    return output_image;
}

Mat IntersectionPoints::hitmiss(Mat src, Mat kernel){
    CV_Assert(src.type() == CV_8U && src.channels() == 1);

    Mat kernel_foregnd_pix = (kernel == 1) / 255;
    Mat kernel_backgnd_pix = (kernel == -1) / 255;

    normalize(src, src, 0, 1, cv::NORM_MINMAX);

    Mat match_mat, ignore_mat;

    erode(src, match_mat, kernel_foregnd_pix, Point(-1,-1), 1, BORDER_CONSTANT, Scalar(0)); //matches foreground pixels

    erode(1-src, ignore_mat, kernel_backgnd_pix, Point(-1,-1), 1, BORDER_CONSTANT, Scalar(0));  //matches background pixels

    return (match_mat & ignore_mat);
}

Mat IntersectionPoints::pattern(int top_bottom, int left_right, int ACH){

    Mat kernel_mat = Mat::zeros(3*ACH, 3*ACH, CV_32S);

    if(top_bottom){

    //---------------Bottom
        for(int m=0; m <= 3*ACH/2; m++)
            kernel_mat.at<int>(m, 3*ACH/2) = 1;
    }

    else{
    //--------------Top
        for(int m=3*ACH/2 ; m<3*ACH; m++)
            kernel_mat.at<int>(m,3*ACH/2) = 1;
    }

    if(left_right){

    //--------------Right
        for(int m=0 ; m<=3*ACH/2; m++)
            kernel_mat.at<int>(3*ACH/2, m) = 1;
    }
    else{
    //---------------Left
        for(int m=3*ACH/2; m<3*ACH; m++)
            kernel_mat.at<int>(3*ACH/2,m) = 1;
    }

    kernel_mat.at<int>(0,0) = -1;
    kernel_mat.at<int>(3*ACH - 1,0) = -1;
    kernel_mat.at<int>(0,3*ACH - 1) = -1;
    kernel_mat.at<int>(3*ACH -1,3*ACH -1) = -1;

    return kernel_mat;
}

Mat IntersectionPoints::horizontalPattern(int leftORight, int ACH){

    Mat kernel_mat = Mat::zeros(ACH+2,3*ACH, CV_32S);

    //for(int k=0;k<3*ACH;k++)						//cols

        for(int i=0;i<3*ACH ; i++){		//cols
            kernel_mat.at<int>(0,i) = -1;
            kernel_mat.at<int>(ACH+1,i) = -1;
        }

        if( leftORight){

            for(int i=0;i<ACH ; i++){
                kernel_mat.at<int>(ACH/2+1,i) = -1;
            }

            for(int i=ACH;i<3*ACH ; i++){
                kernel_mat.at<int>(ACH/2+1,i) = 1;
            }
        }

        else{
            for(int i=0;i<2*ACH ; i++){
                kernel_mat.at<int>(ACH/2+1,i) = 1;
            }

            for(int i=2*ACH;i<3*ACH ; i++){
                kernel_mat.at<int>(ACH/2+1,i) = -1;
            }
        }

    return kernel_mat;

}

Mat IntersectionPoints::verticalPattern(int topObottom, int ACH){

    Mat kernel_mat = Mat::zeros(3*ACH,ACH+2, CV_32S);

    for(int k=0;k<3*ACH;k++)

    //for(int i=0,j=2*ACH;i<ACH ; i++,j++)
    {

        kernel_mat.at<int>(k,0) = -1;
        kernel_mat.at<int>(k,ACH+1) = -1;

    }

    if( topObottom){
        //line ending on top

        for(int i=0;i<3*ACH/2 ; i++){
            kernel_mat.at<int>(i,ACH/2+1) = -1;
        }

        for(int i=3*ACH/2;i<3*ACH ; i++){
            kernel_mat.at<int>(i,ACH/2+1) = 1;
        }
    }
    else{

        for(int i=0;i<3*ACH/2 ; i++){
            kernel_mat.at<int>(i,ACH/2+1) = 1;
        }

        for(int i=3*ACH/2;i<3*ACH ; i++){
            kernel_mat.at<int>(i,ACH/2+1) = -1;
        }

        //line ending on bottom
    }

    return kernel_mat;

}

Mat IntersectionPoints::alignHorizontalPoints(Mat lr, int ACH){

    Mat img=lr.clone();

    for(int i=0; i<img.cols; i=i+(ACH/2)){

        vector <Point> p;
        int avgx[ACH];

        for(int m=0; m<ACH; m++){
            avgx[m]=0;
        }

        for(int j=i; j<i+ACH && j<img.cols; j++){
            for(int k=0; k<img.rows; k++){

                if(img.at<uchar>(k,j)!=0){

                    p.push_back(Point(j,k));
                    avgx[j%ACH]++;
                }
            }
        }

        int max=0;
        int x=-1;

        for(int m=0; m<ACH; m++){

            if(avgx[m]>max){
                max = avgx[m];
                x=m;
            }
        }

        int X;

        if(x!=-1){
            int temp = i%ACH;

            if (x < temp)
                X= x + (ACH-temp)+i;
            else
                X = x-temp+i;

            for(int j=0; unsigned(j)< p.size(); j++){

                if(p[j].x!=X){

                    img.at<uchar>(p[j].y,X) = img.at<uchar>(p[j]);
                    img.at<uchar>(p[j]) = 0;
                }
            }
        }
    }

    return img;

}

Mat IntersectionPoints::alignVerticalPoints(Mat tb, int ACH){

    Mat img=tb.clone();

    for(int i=0; i<img.rows; i=i+(ACH/2)){

        vector <Point> p;
        int avgy[ACH];

        for(int m=0; m<ACH; m++){
            avgy[m]=0;
        }


        for(int j=i; j<i+ACH && j<img.rows; j++){
            for(int k=0; k<img.cols; k++){

                if(img.at<uchar>(j,k)!=0){

                    p.push_back(Point(k,j));
                    avgy[j%ACH]++;
                }
            }
        }

        int max=0;
        int y=-1;

        for(int m=0; m<ACH; m++){

            if(avgy[m]>max){
                max = avgy[m];
                y=m;
            }
        }

        int Y;

        if(y!=-1){

            int temp = i%ACH;

            if (y < temp)
                Y= y + (ACH-temp)+i;
            else
                Y = y-temp+i;

            for(int j=0; unsigned(j)< p.size(); j++){

                if(p[j].y!=Y){
                    //cout<<p[j].x<<"\t"<<p[j].y<<"\t"<<Y<<endl;
                    img.at<uchar>(Y,p[j].x) = img.at<uchar>(p[j]);
                    img.at<uchar>(p[j]) = 0;
                }
            }
        }
    }

    return img;

}
