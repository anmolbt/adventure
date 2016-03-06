#include<stdlib.h>
#include <stdio.h>
#include <iostream>
#include <stack>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;

typedef struct
{
	int i;
	int j;
}point;

point start;
point e;

Mat img,cimg;

int isValid(int i, int j)
{

	if (i<0 || i >= img.rows || j < 0 || j >= img.cols)
		return 0;
	else
		return 1;
}

int visited[500][500]={0};


float cald(int i,int j)
{
float d;
int a=abs(e.i-i);
int b=abs(e.j-j);
	if(a>b)
		{
			 d=(0.414)*(b)+(a);
				//printf("%f\n",d);
				return d;
		}
	else 
		{		
			d=(0.414)*(a)+(b);
			//printf("%f\n",d);
			return d;
		}

}


Mat binary(Mat img2)
{
	
	Mat img3(img2.rows, img2.cols, CV_8UC1);

	for (int i = 0; i < img2.rows; i++)
	{
		for (int j = 0; j < img2.cols; j++)
		{
			if (img2.at<uchar>(i, j) < 200)
				img3.at<uchar>(i, j) = 0;
			else if (img2.at<uchar>(i, j) > 200)
				img3.at<uchar>(i, j) = 255;

		}
	}
return img3;

}



void dfs()
{
	int i,j,flag=0;
	float d,min=10000.0;
	point closest;
	stack<point>s;
	stack<point>r;
	
	s.push(start);
	
	point temp;
	while(1)
	{
		point A=s.top();
		
		
		
	
		visited[A.i][A.j]=1;
		if(A.i==e.i && A.j==e.j)
			break;
		for(i=(A.i-1);i<=(A.i+1);i++)
		{
			for(j=(A.j-1);j<=(A.j+1);j++)
			{
				
				if(isValid(i,j))
				{
				
					if(img.at<uchar>(i,j)<10 && visited[i][j]==0)
					{
						d=cald(i,j);
						if(d<=min)
						{
							closest.i=i;
							closest.j=j;
							
							min=d;
							flag=1;
						}
					}
				}
			}
		}
	if(flag)
		{
			s.push(closest);
		
			flag=0;	
		}
	else
		{
		
		s.pop();
		}
		min = 10000.0;
	}

// As you travel back in stack the points should get farther..
float lim=-1.0;
while(!s.empty())
{
	
	point temp=s.top();
	float d=cald(temp.i,temp.j);
	if(d>=(lim) )
	{
	cimg.at<Vec3b>(temp.i,temp.j)[0]=255;	
	lim=d;
	}
	s.pop();

}


return ;

}

void findstartend()
{

int cr=1,sx=0,sy=0,cg=1,s2x=0,s2y=0;

for(int i=0;i<cimg.rows;i++)
{
	for(int j=0;j<cimg.cols;j++)
	{
		if(cimg.at<Vec3b>(i, j)[2]>200 && cimg.at<Vec3b>(i, j)[1]<100 && cimg.at<Vec3b>(i, j)[0]<100)
		{
			cr++;
			sx=sx+i;
			sy=sy+j;
		}
	if(cimg.at<Vec3b>(i, j)[1]>100 && cimg.at<Vec3b>(i, j)[2]<100 && cimg.at<Vec3b>(i, j)[0]<100)
		{
			cg++;
			s2x=s2x+i;
			s2y=s2y+j;
		}
	}
}
start.i=(int)(sx/cr);
start.j=(int)(sy/cr);

e.i=(int)(s2x/cg);
e.j=(int)(s2y/cg);
printf("End : cr-%d,cg-%d \n",cr,cg);

	
	
printf("The start position, End position is \n");
printf("Start : %d,%d \n",start.i,start.j);
printf("End : %d,%d \n",e.i,e.j);
return;
}


int main()
{

	img = imread("/home/anmol/codes/img.png", 0);
	cimg= imread("/home/anmol/codes/img.png", 1);
	
	img=binary(img);
	imshow("original", cimg);

	 findstartend();

	dfs();

	
imshow("Path",cimg);
waitKey(0);
return 0;
}
