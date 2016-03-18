#include "detecttabularlines.h"


Mat Detect_table::detecttable(vector<Mat> s_lines,Mat imgg,vector<pair <Point, Point> > P)
{
	Mat img=imgg;
	vector<Mat>single_lines= s_lines;
	vector<pair <Point, Point> > Pairs=P;
	int flag[single_lines.size()];
    for(int i=0;unsigned(i)<single_lines.size();i++)
		flag[i]=0;


	int space[400];
	int tempspace[400];
	int tempspace_high[single_lines.size()];
	int *VH,spcnt;
	int pixel;

	int max_line_height=2*(img.size().height/single_lines.size());

	for(int z=0;z<400;z++)
		space[z]=0;

    for(int k=0;unsigned(k)<single_lines.size();k++)
	{
		Mat ip = single_lines[k];
		for(int z=0;z<400;z++)
			tempspace[z]=0;
		spcnt=0;

		VH = new int[ip.size().width];
		for(int l = 0; l < ip.size().width; l++)
		{
			VH[l] = 0;
		}

		for(int l=0;l<ip.size().width;l++){
		//count=0;
		for(int m=0;m<ip.size().height;m++){
			pixel=ip.at<uchar>(m,l);
				if( pixel==255 ){
					VH[l]++;
					//count++;
				}
			}
			//printf("count :%d \t %d\n",l, count);
		}

		int q=0;
		int cnt=0;
		int s_space=0;
		while(VH[q]==0)
		{
			q++;
		}
		s_space=q;
		for(;q<ip.size().width;q++)
		{
			cnt=1;
			while(VH[q]==0)
			{
				cnt++;
				q++;
			}
		while(VH[q]!=0)
		{
			q++;
		}
		//cout<<"cnt"<<cnt<<"\n";
		space[cnt]=space[cnt]+1;
		tempspace[spcnt]=cnt;
		spcnt++;
	}
		if(tempspace[--spcnt]>300)
			flag[k]=2;
		if(s_space>300)
			flag[k]=3;
		tempspace[spcnt]=0;
		space[cnt]=space[cnt]-1;

		tempspace_high[k]=tempspace[0];
		for(int i=1;i<400;i++)
		{
			if(tempspace_high[k]<tempspace[i])
				tempspace_high[k]=tempspace[i];
		}

	}

		thres=3;
		for(int i=4;i<16;i++)
		{
			if(space[i]>=thres)
				thres=i;
			}
		thres=2.5*thres;

        for(int i=0;unsigned(i)<single_lines.size();i++)
		{
			if(tempspace_high[i]>thres && flag[i]!=2)
				flag[i]=1;
		}

        for(int i=0;unsigned(i)<single_lines.size();i++)
		{
			if(((Pairs[i].second.y)-(Pairs[i].first.y))>max_line_height && i!=0)
								rectangle(img,Pairs[i].first,Pairs[i].second,Scalar(255,255,255),-1,8);
					else if(flag[i]==3 && (flag[i-1]==1 || flag[i-1]==2)){
                        //cout<<i<<Pairs[i].first<<"\t"<<Pairs[i].second<<"\n";
                        flag[i]=1;
						final_line_no.push_back(i);
					}

					else if(flag[i]==2 && (/*i==single_lines.size()-2 ||*/ (flag[i-1]==1 && flag[i+1]==1) || (flag[i-1]==2 && flag[i+1]==1) || (flag[i-1]==1 && flag[i+1]==2) ||(flag[i-1]==2 && flag[i+1]==2)))
					{
                        //cout<<i<<Pairs[i].first<<"\t"<<Pairs[i].second<<"\n";
						final_line_no.push_back(i);
					}
					else if(flag[i]==1 && (flag[i+1]==1 || flag[i-1]==1 || flag[i-1]==2 || flag[i+1]==2 || flag[i+1]==3 || flag[i-1]==3))
					{
                        //cout<<i<<Pairs[i].first<<"\t"<<Pairs[i].second<<"\n";
						final_line_no.push_back(i);
					}
					else
						rectangle(img,Pairs[i].first,Pairs[i].second,Scalar(255,255,255),-1,8);
			}

			return img;
}

vector<int> Detect_table::returnfinal_line_no()
{
    return this->final_line_no;
}

int Detect_table::returnthres()
{
    return this->thres;
}
