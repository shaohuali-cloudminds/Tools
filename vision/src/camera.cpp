#include <iostream>
#include <iomanip>
#include <string>
#include <opencv2/opencv.hpp>
#include "camera.hpp"

using namespace vision_tools;

namespace vision_tools {

void Camera::display() {
	cv::Mat frame;
	cv::namedWindow("Displaying Video");
	while(1) {
		capture_ >> frame;
		cv::imshow("Displaying Video", frame);
		if(cv::waitKey(40) == 27) break;
	}
	cv::destroyWindow("Displaying Video");
} // function display()

void Camera::record_video(const std::string& file_name, double fps, int fourcc) { 
	int frame_width = capture_.get(CV_CAP_PROP_FRAME_WIDTH);
	int frame_height = capture_.get(CV_CAP_PROP_FRAME_HEIGHT);
	cv::VideoWriter video(file_name, fourcc, fps, cv::Size(frame_width, frame_height));
	cv::Mat frame;
	cv::namedWindow("Recording Video");
	while(1) {
		capture_ >> frame;
		video << frame;	
		cv::imshow("Recording Video", frame);
		if(cv::waitKey(40) == 27) break;
	}	
	cv::destroyWindow("Recording Video");
} // function record_video()

void Camera::record_imgs(const std::string& folder_name, double fps) {
	cv::namedWindow("Recording Images");
	cv::Mat frame;
	int counter = 0;
	std::string folder_n_name;
	while(1) {
		capture_ >> frame;
		cv::imshow("Recording Images", frame);
		std::stringstream name;
		name << std::setw(4) << std::setfill('0') << counter;
		folder_n_name = folder_name + "img_" + name.str() + ".png";
		cv::imwrite(folder_n_name, frame);
		++counter;
		if(cv::waitKey(1000/int(fps)) == 27) {
			break;
		}
	}
	cv::destroyWindow("Recording Images");	
} // function record_imgs()

void Camera::select_imgs(const std::string& folder_name) {
	// display video
	cv::namedWindow("Selecting Images");
	cv::Mat frame;

	// press 's' to invoke selection and save images
	std::cout << "Press s to select images" << std::endl;
	int counter = 0;
	std::string folder_n_name;
	while(1) {
		capture_ >> frame;
		cv::imshow("Selecting Images", frame);
		auto rval = cv::waitKey(40);
		if(rval == 115) {        // is 's' is pressed
			std::stringstream name;
			name << std::setw(4) << std::setfill('0') << counter;
			folder_n_name = folder_name + "img_" + name.str() + ".png";
			cv::imwrite(folder_n_name, frame);
			std::cout << "file img_" << name.str() << ".png saved" << std::endl;
			++counter;
		}
		else if(rval == 27) {
			break;	
		}
	}
	// destroy window
	cv::destroyWindow("Selecting Images");
} // function select_imgs()


} // namespace vision_tools
