#include "wsretention.h"
WSretention::WSretention(){
    this->tessObj.Init(NULL,"eng",OEM_DEFAULT);
    this->tessObj.SetPageSegMode(PSM_AUTO_OSD);
}

vector<Mat> WSretention::retention(vector<Mat> s_lines,Mat imgg,vector<pair <Point, Point> > P,vector<int> line_no,int t)
{
	vector<Mat> single_lines=s_lines;
	Mat img=imgg;
	vector<pair <Point, Point> > Pairs=P;
	vector<int> final_line_no=line_no;
	int *VH;
	int pixel;
	int thres=t;

	Point topleft,bottomright;
		vector<Mat> blocks;
		int z=0;

        for(int k=0;unsigned(k)<final_line_no.size();k++)
		{
			int lineno=final_line_no[k];
			Mat line=single_lines[lineno];
			topleft=Pairs[lineno].first;
			bottomright.x=Pairs[lineno].first.x;
			bottomright.y=Pairs[lineno].second.y;

			VH = new int[line.size().width];
			for(int l = 0; l < line.size().width; l++)
			{
				VH[l] = 0;
			}

			for(int l=0;l<line.size().width;l++){
			for(int m=0;m<line.size().height;m++){
				pixel=line.at<uchar>(m,l);
				if( pixel==255 ){
					VH[l]++;
					}
				}
			}

			int q=0;
			while(VH[q]==0)
			{
				q++;
			}
			int tempspace;
            for(;q<line.size().width;q++)
			{
				tempspace=0;
				while(VH[q]!=0)
				{
					q++;
				}
				while(VH[q]==0)
				{
					tempspace++;
					q++;
				}
				if(tempspace>=thres)
				{
                    //cout<<"g"<<endl;
					bottomright.x=Pairs[lineno].first.x+q;
                    Rect rec= Rect(topleft.x,topleft.y,bottomright.x-topleft.x-1,bottomright.y-topleft.y);
					cout<<topleft<<"\t"<<bottomright<<endl;
					blocks.push_back(cv::Mat(img,rec));
					topleft.x=bottomright.x-3;

					Mat cropped=blocks.back();
					std::ostringstream ss;
					 long num = z;
					 ss << num;
					 std::cout << ss.str() << std::endl;

				//std::string s = std::to_string(42);

                    string imgname = "Table_part_" +ss.str();
                    imshow(imgname,cropped);
					z++;
				}


			}


		}
		return blocks;

}

void WSretention::passToTesseract(vector<Mat> blocks, String filename){

    QString fname = QString::fromStdString(filename);
    QStringList splitData = fname.split("/");
    fname = splitData[splitData.length()-1];

    splitData = fname.split(".");
    splitData[splitData.length()-1] = QString("txt");
    fname = splitData.join(".");
    fname = "target/"+fname;

    filename = fname.toStdString();

    ofstream fp;

    fp.open(filename, ios::out|ios::trunc);


    for(int i=0;unsigned(i)<blocks.size();i++){
        tessObj.SetImage((uchar*)blocks[i].data,
                         blocks[i].size().width,
                         blocks[i].size().height,
                         blocks[i].channels(),
                         blocks[i].step1());

        tessObj.Recognize(0);
        fp << tessObj.GetUTF8Text();
    }

    fp.close();

}
