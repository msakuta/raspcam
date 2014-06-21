#include <iostream>
#include <opencv2/opencv.hpp>

#define CAM_W 320
#define CAM_H 240
#define WINNAME "cameratest"

int main(int argc, char *argv[]){
	int cam_w = CAM_W;
	int cam_h = CAM_H;
	int disp_w = cam_w;
	int disp_h = cam_h;

	if(2 < argc){
		// Get desired capture size if provided
		cam_w = atoi(argv[1]);
		cam_h = atoi(argv[2]);
		if(cam_w == 0 || cam_h == 0){
			std::cerr << "capture size arguments must be positive integer" << std::endl;
			return -1;
		}

		// Get desired display size if provided
		disp_w = 3 < argc ? atoi(argv[3]) : cam_w;
		disp_h = 4 < argc ? atoi(argv[4]) : cam_h;
		if(disp_w == 0 || disp_h == 0){	
			std::cerr << "display size arguments must be positive integer" << std::endl;
			return -1;
		}
			
		std::cout << "Camera resolution is set: "
			<< cam_w << " x " << cam_h << std::endl;
		std::cout << "Display resolution is set: "
			<< disp_w << " x " << disp_h << std::endl;
	}

	cv::VideoCapture cap;
	cv::Mat frame, disp;
	cap.open(0);
	if(!cap.isOpened()){
		std::cout << "Camera open failed" << std::endl;
		return 1;
	}
	cap.set(CV_CAP_PROP_FRAME_WIDTH, cam_w);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, cam_h);
	cv::namedWindow(WINNAME, CV_WINDOW_AUTOSIZE);
	cap.read(frame);
	while(1){
		if(cap.grab() == 0)
			continue;
		if(cap.retrieve(frame, 0) == 0)
			continue;

		// resize only if display size differs from capture size to reduce copies
		if(cam_w != disp_w || cam_h != disp_h){
			cv::resize(frame, disp, cv::Size(disp_w, disp_h), cv::INTER_NEAREST);
			cv::imshow(WINNAME, disp);
		}
		else
			cv::imshow(WINNAME, frame);
		int key = cv::waitKey(1);
		if(0 <= key){
			std::cerr << "Input" << std::endl;
			break;
		}
	}
//	cv::imwrite("image.jpg", frame);
	cap.release();
	cv::destroyWindow(WINNAME);
	return 0;
}

