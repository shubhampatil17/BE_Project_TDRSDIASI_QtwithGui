#include "lineprocessing.h"


LineProcessing::LineProcessing(Mat img)
{
    this->img = img;
}

Mat LineProcessing::horizontalProcessing(int ACH){
    vector<Point> procVector;


    //Mat hProcessedImage = img.clone();
    Mat hProcessedImage = Mat:: zeros(img.rows, img.cols, img.type());


    // Horizontal Processing of Horizontal Lines : Stage 1

    for(int i=0; i< img.rows;i++){

        int pointer=0;

        while(true){

            while( (int)img.at<uchar>(i,pointer) == 0){

                pointer++;

                if (pointer >= img.cols )
                    break;

            }

            if(pointer >= img.cols)
                break;

            while( (int)img.at<uchar>(i,pointer) != 0){

                procVector.push_back(Point(i,pointer));
                pointer++;


                if( pointer >= img.cols)
                    break;
            }

            if( procVector.size() > unsigned(ACH)){
                while( procVector.size() != 0){

                    Point P = procVector.back();

                    procVector.pop_back();

                    //img.at<uchar>(P.x, P.y) = 127;

                    hProcessedImage.at<uchar>(P.x, P.y) = 255;
                }

            }else{
                    procVector.clear();
            }

        }
    }

    procVector.clear();



    //Vertical Processing of Horizontal Lines : Stage 2

    for(int i=0; i< hProcessedImage.cols ; i++){


        int pointer=0;

        while(true){

            while( (int)hProcessedImage.at<uchar>(pointer,i) == 0){

                pointer++;

                if (pointer >= hProcessedImage.rows )
                    break;

            }

            if(pointer >= hProcessedImage.rows)
                break;

            while( (int)hProcessedImage.at<uchar>(pointer,i) != 0){

                procVector.push_back(Point(pointer,i));
                pointer++;


                if( pointer >= hProcessedImage.rows)
                    break;
            }

            if( procVector.size() > unsigned(ACH/2)){

                while( procVector.size() != 0){

                    Point P = procVector.back();

                    procVector.pop_back();

                    //img.at<uchar>(P.x, P.y) = 127;

                    hProcessedImage.at<uchar>(P.x, P.y) = 0;
                }

            }else{
                    procVector.clear();
            }

        }

    }

    return hProcessedImage;
}

Mat LineProcessing::verticalProcessing(int ACH){

    vector<Point> procVector;

    Mat vProcessedImage = Mat::zeros (img.rows, img.cols, img.type());

    // Vertical Processing of Vertical Lines : Stage 1

    for(int i=0; i< img.cols;i++){


        int pointer=0;

        while(true){

            while( (int)img.at<uchar>(pointer,i) == 0){

                pointer++;

                if (pointer >= img.rows )
                    break;

            }

            if(pointer >= img.rows)
                break;

            while( (int)img.at<uchar>(pointer,i) != 0){

                procVector.push_back(Point(pointer,i));
                pointer++;


                if( pointer >= img.rows)
                    break;
            }

            if( procVector.size() > unsigned(ACH)){
                while( procVector.size() != 0){

                    Point P = procVector.back();

                    procVector.pop_back();

                    //img.at<uchar>(P.x, P.y) = 127;

                    vProcessedImage.at<uchar>(P.x, P.y) = 255;
                }

            }else{
                    procVector.clear();
            }

        }


    }

    procVector.clear();


    // Horizontal Processing of Vertical Lines : Stage 2

    for(int i=0; i< vProcessedImage.rows ; i++){

        int pointer=0;

        while(true){

            while( (int)vProcessedImage.at<uchar>(i,pointer) == 0){

                pointer++;

                if (pointer >= vProcessedImage.cols )
                    break;

            }

            if(pointer >= vProcessedImage.cols)
                break;

            while( (int)vProcessedImage.at<uchar>(i, pointer) != 0){

                procVector.push_back(Point(i, pointer));
                pointer++;


                if( pointer >= vProcessedImage.cols)
                    break;
            }

            if( procVector.size() > unsigned(ACH/2)){

                while( procVector.size() != 0){

                    Point P = procVector.back();

                    procVector.pop_back();

                    //img.at<uchar>(P.x, P.y) = 127;

                    vProcessedImage.at<uchar>(P.x, P.y) = 0;
                }

            }else{
                    procVector.clear();
            }

        }

    }

    return vProcessedImage;

}
