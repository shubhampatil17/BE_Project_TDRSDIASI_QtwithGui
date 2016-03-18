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

class whitespaceprocessing{
	Mat img;
public:
	whitespaceprocessing(Mat img);
	Mat white_space_process();
};
