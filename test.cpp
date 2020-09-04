#include<iostream>
#include<highgui/highgui.hpp>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
Mat buhuo;
Mat shibie;
Mat mask1;
Mat mask2;
Mat mask3;
Mat mask4;
Mat Right1;
Mat Left1;
Mat Middle1;
int counter1 = 0;         //左
int counter2 = 0;         //右
int counter3 = 0;         //中
int Left(int rows, int cols) 
{
	mask1 = Mat::zeros(shibie.size(), CV_8UC1);
	Rect r1(0, 0, 200, 480);
	mask1(r1).setTo(255);
	shibie.copyTo(Left1, mask1);
	
	Mat_<uchar>::iterator it = Left1.begin<uchar>();	
	Mat_<uchar>::iterator itend = Left1.end<uchar>();			
	for (; it != itend; ++it) 
	{
		if ((*it) == 0) 			
		counter1 ++; 
	}
	return 0;
}
int Right(int rows, int cols)
{
	mask2 = Mat::zeros(shibie.size(), CV_8UC1);
	Rect r2(440, 0, 200, 480);
	mask2(r2).setTo(255);
	shibie.copyTo(Right1, mask2);
	Mat_<uchar>::iterator it = Right1.begin<uchar>();
	Mat_<uchar>::iterator itend = Right1.end<uchar>();
	for (; it != itend; ++it)
	{
		if ((*it) == 0)
			counter2 ++;
	}
	return 0;
}
int Middle(int rows, int cols)
{
	mask3 = Mat::zeros(shibie.size(), CV_8UC1);
	Rect r3(200, 0, 240, 480);
	mask3(r3).setTo(255);
	shibie.copyTo(Middle1, mask3);
	Mat_<uchar>::iterator it = Right1.begin<uchar>();
	Mat_<uchar>::iterator itend = Right1.end<uchar>();
	for (; it != itend; ++it)
	{
		if ((*it) == 0)
			counter3++;
	}
	return 0;
}
int main()
{
	VideoCapture capture(0);
	while (1)
	{
		capture >> buhuo;
		cvtColor(buhuo, shibie, COLOR_BGR2GRAY);                //转化为灰度图像
		threshold(shibie, shibie, 100, 255, THRESH_BINARY);     //二值化（有线条的像素设置为255，没有的为零）
		blur(shibie, shibie, Size(3, 3));   //降噪	
		Right(buhuo.rows, buhuo.cols);
		Left(buhuo.rows, buhuo.cols);
		Middle(buhuo.rows, buhuo.cols);
		if (counter1 < counter2 && counter1 < counter3) 
		{
			putText(shibie, "turn right", Point(0, 20), 2, 1, CV_RGB(255, 255, 255));//左转
			counter1 = 0;
			counter2 = 0;
		}
		else if(counter1 > counter2 && counter2 < counter3)
		{
			putText(shibie, "turn left", Point(0, 20), 2, 1, CV_RGB(255, 255, 255));//右转
			counter1 = 0;
			counter2 = 0;
		}
		else 
		{
			putText(shibie, "straight", Point(0, 20), 2, 1, CV_RGB(255, 255, 255));//直走
			counter1 = 0;
			counter2 = 0;
		}
		imshow("图像",shibie);
		waitKey (30);
	}
	return 0;
}

