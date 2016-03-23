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

class Detect_table{
	vector<int> final_line_no;
	int thres;
public:
    Mat detecttable (vector<Mat>,Mat,Mat,vector<pair <Point, Point> >);
    vector<int> returnfinal_line_no();
    int returnthres();
};
