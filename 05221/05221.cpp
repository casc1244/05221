#include <iostream>  
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int bgSub_demo()
{
	VideoCapture capVideo(0);
//如果打开失败
	if (!capVideo.isOpened()) {
		std::cout << "Unable to open video!" << std::endl;
		return -1;
	}
   //计数
	int cnt = 0;
	Mat frame;
	Mat bgMat;
	Mat subMat;
	Mat bny_subMat;
	Mat bgModelMat;

	while (1) {
		capVideo >> frame;
		cvtColor(frame, frame, COLOR_BGR2GRAY);
		if (cnt == 0) {
			//第一帧，获得背景图像
			frame.copyTo(bgMat);
		}
		else {
			//第二差分
			//相减
			absdiff(frame, bgMat, subMat);
			//二值化
			threshold(subMat, bny_subMat, 20, 255, CV_THRESH_BINARY);

			imshow("b_subMat", bny_subMat);
			imshow("frame", frame);
			waitKey(30);
		}
		cnt++;

	}
	return 0;
}
int main()
{
	//开始计时
	double start = static_cast<double>(cvGetTickCount());
	bgSub_demo();
	//结束计时
	double time = ((double)cvGetTickCount() - start) / cvGetTickFrequency();
	//显示时间
	cout << "processing time:" << time / 1000 << "ms" << endl;
	//按任意键结束程序
	system("pause");
	return 0;
}