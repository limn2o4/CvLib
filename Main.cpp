#include <opencv2/opencv.hpp>
#include <opencv2\opencv_modules.hpp>
#include <iostream>
#define mat Mat
using namespace cv;
// very start of my proj

Scalar colorTab[] =     //10¸öÑÕÉ«  
{
	Scalar(0, 0, 255),
	Scalar(0, 255, 0),
	Scalar(255, 100, 100),
	Scalar(255, 0, 255),
	Scalar(0, 255, 255),
	Scalar(255, 0, 0),
	Scalar(255, 255, 0),
	Scalar(255, 0, 100),
	Scalar(100, 100, 100),
	Scalar(50, 125, 125)
};

int main()
{


	Mat img = imread("lena.bmp");
	//cvtColor(img,img, COLOR_RGB2GRAY);


	int row = img.rows;
	int col = img.cols;
	int ch =  img.channels();

	mat cluster(row, col, CV_8UC3);
	cluster.setTo(Scalar::all(0));

	mat pixels(row*col, 1, CV_32FC3);
	pixels.setTo(Scalar::all(0));


	for (int i = 0; i < row; i++)
	{
		const uchar *idata = img.ptr<uchar>(i);
		float *pdata = pixels.ptr<float>(0);

		for (int j = 0; j < col * ch; j++)
		{
			pdata[i*col*ch + j] = saturate_cast<float>(idata[j]);
		}

	}
	mat labels;
	int cnt = 5;
	kmeans(pixels, cnt, labels, TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 10, 0), 5, KMEANS_PP_CENTERS);
	int k = 0;
	for (int i = 0; i<row; i++)
	{
		uchar *p = cluster.ptr<uchar>(i);
		for (int j = 0; j < col*ch; j+= ch)
		{
			//int t = labels.at<int>(i * col +(j /ch));
			//p[j/ch] = colorTab[t][1] + colorTab[t][0] + colorTab[t][2];
			circle(cluster, Point(j / ch, i), 1, colorTab[labels.at<int>(i*col + (j / ch))]);
		}
	}


	
	
	imshow("yes", cluster);
	

	waitKey();
	return 0;

}