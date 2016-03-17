#include "reconstruction.h"



struct comparison_struct {

    bool operator() (Point p, Point q) {
        if(p.x == q.x)
            return p.y < q.y;
        return (p.x < q.x);
    }

} comparison_y;

struct comparison_xstruct {

    bool operator() (Point p, Point q) {
        if(p.y == q.y)
            return p.x < q.x;
        return (p.y < q.y);
    }

} comparison_x;

Reconstruction::Reconstruction(Mat img, int ACH)
{
    this->img = img;
    this->ACH = ACH;
}

Mat Reconstruction::reconstruction(Mat &output){

    map<int, vector<Point> > pointsx,pointsy;

    for( int i = 0; i < img.rows-1; i++ ){
        for( int j = 0; j < img.cols-1; j++ ){

            if(img.at<uchar>(i,j)!=0){

                //int s=(int)img.at<uchar>(y,x);
                //cout<<s<<endl;
                Point P(j,i);

                pointsy[i].push_back(P);
                pointsx[j].push_back(P);
            }
        }
    }

    Mat output_image=Mat :: zeros(img.rows,img.cols,img.type());

    //=================================================
    //Draw horizontal lines

    vector <Point> xpoints;

    Mat Dataset = Mat :: zeros(img.rows,img.cols,img.type());

    for (map<int, vector <Point> >::iterator it=pointsx.begin(); it!=pointsx.end(); ++it)
    {
        int count = 0 ,i=1;

        while( unsigned(i)<it->second.size() && count<3){

            if(abs(it->second[i].y - it->second[i-1].y)>ACH)
                count ++;
            i++;
        }

        if(count>=2){
            xpoints.insert(xpoints.end(), it->second.begin(), it->second.end());
        }
    }

    sort(xpoints.begin(), xpoints.end(), comparison_x);

    for(int i=1; unsigned(i)< xpoints.size(); i++){

        int s=(int)img.at<uchar>(xpoints[i-1]);
        int p = (int)img.at<uchar>(xpoints[i]);

        //=========================================================
        //Remove squares

        if(s==70 && p==40){
            continue;
        }
        else if(s==10 && p==20){
            continue;
        }
        else if(s==200 && p==210){
            continue;
        }
        else if(s==40 && p==40){
            line( output_image,xpoints[i-1],xpoints[i],Scalar(255,255,255), 1, 8 , 0);
            Dataset.at<uchar>(xpoints[i])=255;
            Dataset.at<uchar>(xpoints[i-1])=255;

        }


        if(s!=20 && s!=40 && s!=60 && s!=210 && s!=220 && s!=230 && xpoints[i-1].y==xpoints[i].y){

            line( output_image,xpoints[i-1],xpoints[i],Scalar(255,255,255), 1, 8 , 0);

            Dataset.at<uchar>(xpoints[i])=255;
            Dataset.at<uchar>(xpoints[i-1])=255;
        }

    }

    //===================================================================================================================
    //Draw Vertical lines
    vector <Point> ypoints;

    for (map<int, vector <Point> >::iterator it=pointsy.begin(); it!=pointsy.end(); ++it)
    {
        int count = 0 ,i=1;

        while( unsigned(i) <it->second.size() && count<3){
            if(abs(it->second[i].x - it->second[i-1].x)>ACH)
                count ++;
            i++;
        }

        if(count>=2){
            ypoints.insert(ypoints.end(), it->second.begin(), it->second.end());
        }
    }

    sort(ypoints.begin(), ypoints.end(), comparison_y);

    for(int i=1; unsigned(i) < ypoints.size(); i++){
        int s=(int)img.at<uchar>(ypoints[i-1]);
        int p=(int)img.at<uchar>(ypoints[i]);

        //=========================================================
        //Remove squares

        if(s==10 && p==70){
            continue;
        }
        else if(s==20 && p==40){
            continue;
        }
        else if(s==220 && p==230){
            continue;
        }else if(s==40 && p==40){
            line( output_image,ypoints[i-1],ypoints[i],Scalar(255,255,255), 1, 8 , 0);
            Dataset.at<uchar>(ypoints[i])=255;
            Dataset.at<uchar>(ypoints[i-1])=255;
        }

        //================================================================================================
        //Draw lines
        //cout<<s<<endl;
        if(s!=110 && s!=70 && s!=40 && s!=230 && s!=200 && s!=210 && ypoints[i-1].x==ypoints[i].x){

            line( output_image,ypoints[i-1],ypoints[i],Scalar(255,0,0), 1, 8 , 0);

            Dataset.at<uchar>(ypoints[i])=255;
            Dataset.at<uchar>(ypoints[i-1])=255;
        }

    }

    output_image=(output_image==0);
    output_image=output_image*255;
    output=output_image;

    return Dataset;
}
