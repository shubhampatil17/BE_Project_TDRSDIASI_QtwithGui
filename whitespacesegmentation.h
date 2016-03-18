#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

class whitespaceseg{
	vector<Mat> single_lines;
	vector<pair <Point, Point> >Pairs;

public:
	whitespaceseg();
	vector<Mat> white_space_seg(Mat);
    vector<pair <Point, Point> > getpairs();
};
