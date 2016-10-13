#include <iostream>
#include <fstream>
#include <vector>
#include "fisheye.hpp"

using namespace vision_tools;

namespace vision_tools {

void Fisheye::extract_corners(const cv::Mat& src_img,
		cv::Size board_size, std::vector<cv::Point2f>& corners) {
	cv::Mat img_gray;
	cv::cvtColor(src_img, img_gray, cv::CV_RGB2Gray);
	bool pattern_found = cv::findChessboardCorners(src_img, board_size, corners, cv::CALIB_CB_ADAPTIVE_THRESH+cv::CALIB_CB_NORMALIZE_IMAGE+CALIB_CB_FAST_CHECK);	
	if(!pattern_found) {
		std::cerr << "Corners not found" << std::endl;
	}
	else {
		cornerSubPix(img_gray, corners, cv::Size(11,11), cv::Size(-1,-1), TermCriteria(cv::CV_TERMCRIT_EPS+cv::CV_TERMCRIT_ITER, 30, 0.1));
		cv::Mat imgTemp = 
	}
}

void Fisheye::calibrate(std::string sample_folder,
		cv::Size board_size, std::string outfile_name) const {

	cv::Mat new_model = cv::Mat(3,3,CV_32FC1);
	cv::Mat new_coeffs = cv::Mat(1,4, CV_32FC1);

	// extract corners
	std::vector<cv::Point2f> corners;
	std::vector<std::vector<cv::Point2f> > corners_batch;
	std::vector<cv::Mat> sample_images;

	// call extract corners
	// call calib()

	// reset and write output file
	reset(new_model, new_coeffs);	
	ofstream fout(outfile_name);
	fout << "CameraModel" << camera_model_;
	fout << "DistCoeffs" << dist_coeffs_;
	fout.release();
}

} // namespace vision_tools


int main() {
	Fisheye my_obj;
	cout << (my_obj.camera_model()).at<float>(1,1) << endl;
	return 0;
}
