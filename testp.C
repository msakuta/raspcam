#include <iostream>
#include <opencv2/opencv.hpp>

#define CAM_W 320
#define CAM_H 240
#define WINNAME "cameratest"

int main(){
	std::cout << "Hello, world!" << std::endl;
	cv::VideoCapture cap;
	cv::Mat frame, disp;
	cap.open(0);
	if(!cap.isOpened()){
		std::cout << "Camera open failed" << std::endl;
		return 1;
	}
	cap.set(CV_CAP_PROP_FRAME_WIDTH, CAM_W);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, CAM_H);
	cv::namedWindow(WINNAME, CV_WINDOW_AUTOSIZE);
	cap.read(frame);
	disp.create(cv::Size(CAM_W, CAM_H), CV_8UC3);
	while(1){
		if(cap.grab() == 0)
			continue;
		if(cap.retrieve(frame, 0) == 0)
			continue;
		cv::imshow(WINNAME, disp);
		int key = cv::waitKey(1);
		if(0 <= key){
			std::cerr << "Camera display failed" << std::endl;
			break;
		}
	}
	cap.release();
	disp.release();
	cv::destroyWindow(WINNAME);
	return 0;
}

