//  ���ڻ�ϸ�˹ģ�͵��˶�Ŀ����

#include <iostream>
#include <string>

#include <opencv2/opencv.hpp>
#include <opencv2/video/background_segm.hpp>

int main(int argc, char** argv)
{
	std::string videoFile = "768x576.avi";

	cv::VideoCapture capture;
	capture.open(videoFile);

	if (!capture.isOpened())
	{
		std::cout << "read video failure" << std::endl;
		return -1;
	}

	/******************************************************/
	// YOUR CODE HERE :
	//����һ������ΪBackgroundSubtractorMOG2������Ϊmog�� �������������еĲ������鿴Ч��
	//history 100  varThreshold  detectShadows
	cv::Ptr<cv::BackgroundSubtractorMOG2> mog = cv::createBackgroundSubtractorMOG2(100, 25, false);


	/******************************************************/

	cv::Mat foreground;
	cv::Mat background;

	cv::Mat frame;
	long frameNo = 0;
	while (capture.read(frame))
	{
		++frameNo;

		std::cout << frameNo << std::endl;
		cv::Mat ff;
		resize(frame, ff, cvSize(frame.cols / 2, frame.rows / 2));

		/******************************************************/
		// YOUR CODE HERE :
		//ʹ��BackgroundSubtractorMOG2���()��������±������ҵ�ǰ��
		mog->apply(ff, foreground);


		/******************************************************/


		// ��ʴ
		cv::erode(foreground, foreground, cv::Mat());

		// ����
		cv::dilate(foreground, foreground, cv::Mat());

		mog->getBackgroundImage(background);   // ���ص�ǰ����ͼ��

		cv::imshow("video", ff);
		cv::imshow("foreground", foreground);
		cv::imshow("background", background);


		if (cv::waitKey(25) >= 0)
		{
			break;
		}
	}



	return 0;
}