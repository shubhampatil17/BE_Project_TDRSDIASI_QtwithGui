#include "whitespacesegmentation.h"

whitespaceseg::whitespaceseg(){
}

vector<Mat> whitespaceseg:: white_space_seg(Mat processedImage)
{
	Mat binary=processedImage;
	int pixel;
	int height=binary.size().height;


	int *HorizontalHistogram = new int[height];
	for(int i = 0; i < height; i++)
	{
		HorizontalHistogram[i] = 0;
	}

			//Line segmentation

	for(int j=0;j<(binary.size().height);j++){
		for(int i=0;i<(binary.size().width);i++){
			pixel=binary.at<uchar>(j,i);
				if( pixel==255 ){
					HorizontalHistogram[j]++;
				}
			}
		}

    int x1=0,x4, x3=x4=binary.size().width;
    int y1,y2,y3;
	int c=0;
    //cout<<"height \t"<<binary.size().height<<"\n";



	for(int i=0;i<binary.size().height;)
	{

        y1=i;
		c++;
		int co=0;
		while(HorizontalHistogram[i]==0)
			i++;

		while(HorizontalHistogram[i]!=0){
			i++;co++;}
        y2=i;

		while(y2>binary.size().height)
			y2--;
        y3=y2;
        i++;



        cout<<"x1y1\t"<<x1<<y1<<"\t\t x2y2"<<"\n";
        cout<<"x3y3\t"<<x3<<y3<<"\t\t x4y4"<<"\n";

		Pairs.push_back(make_pair( Point(x1,y1), Point(x3,y3) ));



		Rect rect= Rect(x1,y1,binary.size().width-1,y2-y1);
		single_lines.push_back(cv::Mat(binary,rect));
	}
			return single_lines;
}

vector<pair <Point, Point> > whitespaceseg::getpairs()
{
    return this->Pairs;
}


