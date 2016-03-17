#include "pagesegmentation.h"


PageSegmentation::PageSegmentation(Mat reconstructImg, Mat pointReducedImage, Mat clrImg, String filename)
{
    this->reconstructImg = reconstructImg;
    this->pointReducedImage = pointReducedImage;
    this->clrImg = clrImg;
    this->filename = filename;
}

vector<vector<Mat>> PageSegmentation::multiTablePageSegmentation(){

                    reconstructImg = (255 - reconstructImg);        //operator overloading

                    Mat labels;
                    Mat stats;
                    Mat centroids;

                    int totalLabels = connectedComponentsWithStats(reconstructImg, labels, stats, centroids, 8, CV_32S);

                    vector<Mat> tableSegments;
                    vector<Mat> pointSegments;


                    int margin = 2;

                    for(int i=1;i< totalLabels; i++){

                        Point topLeft, bottomRight;
                        topLeft.x = stats.at<int>(i, CC_STAT_LEFT) - margin;
                        topLeft.y = stats.at<int>(i, CC_STAT_TOP) - margin;

                        offsetx.push_back(topLeft.x);
                        offsety.push_back(topLeft.y);

                        bottomRight.x = topLeft.x + stats.at<int>(i, CC_STAT_WIDTH) + 2*margin;
                        bottomRight.y = topLeft.y + stats.at<int>(i, CC_STAT_HEIGHT) + 2*margin;

                        Mat croppedTableImage = clrImg(Rect(topLeft, bottomRight));
                        Mat croppedPointImage = pointReducedImage(Rect(topLeft, bottomRight));

                        //imshow(filename+"_ConnectedTable"+ to_string(i), croppedTableImage);
                        //imshow("ConnectedPoints"+ to_string(i), croppedPointImage);

                        tableSegments.push_back(croppedTableImage);
                        pointSegments.push_back(croppedPointImage);
                    }

                    vector<vector<Mat>> segmentationData;

                    segmentationData.push_back(tableSegments);
                    segmentationData.push_back(pointSegments);


                    return segmentationData;

}


vector<vector<int>> PageSegmentation::getSegmentOffsetData(){

                    vector<vector<int>> offsetData;
                    offsetData.push_back(offsetx);
                    offsetData.push_back(offsety);

                    return offsetData;
                    }
