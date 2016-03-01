#include<stdlib.h>
#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp> //for canny


using namespace cv;
using namespace std;

int main()
{
    Mat img;
    img = imread("/home/anmol/codes/i3.jpg", 1);
    imshow("Original", img);
    Mat out(img.rows, img.cols, CV_8UC1, 255);
    Canny(img, out, 0, 255, 3);
    imshow("Canny", out);
    
    int iKey = waitKey(50);
    waitKey(0);
    return 0;
}
