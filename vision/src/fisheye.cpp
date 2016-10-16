#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "fisheye.hpp"

using namespace vision_tools;

namespace vision_tools {

void Fisheye::extract_corners(int img_num, cv::Size board_size, 
		const std::vector<std::string>& img_names, 
		std::vector<std::vector<cv::Point2f> >& vec_vec_corners,
		int& success_img_num,
		int& corners_num,
		cv::Size& img_size) const {
	std::cout << "Extracting corners ..." << std::endl;
	std::vector<cv::Point2f> vec_corners;                 // coordinates of corners in 1 image

	for(int i = 0; i < img_num; ++i) {
		// find corners
		cv::Mat img = cv::imread(img_names[i]);
		if(i == 0) img_size = img.size();
		bool corners_found = cv::findChessboardCorners(img, board_size, vec_corners,
				cv::CALIB_CB_ADAPTIVE_THRESH+cv::CALIB_CB_NORMALIZE_IMAGE+cv::CALIB_CB_FAST_CHECK);
		if(!corners_found) {
			std::cout << "Corners cannot be found"<< std::endl;
			continue;
		}
		else {
			// subpixelize
			cv::Mat img_gray;
			cv::cvtColor(img, img_gray, CV_RGB2GRAY);
			cv::cornerSubPix(img_gray, vec_corners, cv::Size(11,11), cv::Size(-1,-1),
					cv::TermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1));
			// draw circles on corners
			cv::Mat img_corners;
			img.copyTo(img_corners);
			for(int j = 0; j < vec_corners.size(); ++j) {
				cv::circle(img_corners, vec_corners[j], 10, cv::Scalar(0,0,255), 2, 8, 0);
			}
			// show original image and cornered image
			cv::imshow("Original Image", img);
			cv::imshow("Corners", img_corners);
			cv::waitKey(0);

			// save cornered images
			auto position = img_names[i].find_last_of('.');         // truncate extention to change
																															// file name 
			std::string corner_img_name = img_names[i].substr(0, position) + "_corners.png";
			cv::imwrite(corner_img_name, img_corners);

			corners_num += vec_corners.size();
			++success_img_num;
			vec_vec_corners.push_back(vec_corners);
		}
	}
	cv::destroyAllWindows();
} // function extract_corners()

void Fisheye::calib_(std::vector<std::vector<cv::Point2f> >& vec_vec_corners, 
		cv::Size board_size, cv::Size img_size, 
		int success_img_num, int corners_num,
		cv::Mat& new_model, cv::Mat& new_coeffs) const {
	std::cout << "Calibrating ..." << std::endl;
	cv::Size square_size = cv::Size(20,20);
	std::vector<std::vector<cv::Point3f> > object_points;
	cv::Mat img_points = cv::Mat(1, corners_num, CV_32FC2, cv::Scalar::all(0));

	std::vector<int> point_counts(success_img_num, board_size.width*board_size.height);

	for(int t = 0; t < success_img_num; ++t) {
		std::vector<cv::Point3f> temp_point_set;
		for(int i = 0; i < board_size.height; ++i) {
			for(int j = 0; j < board_size.width; ++j) {
				cv::Point3f temp_point;
				temp_point.x = i * square_size.width;
				temp_point.y = j * square_size.height;
				temp_point.z = 0;
				temp_point_set.push_back(temp_point);
			}
		}
		object_points.push_back(temp_point_set);
	}

	std::vector<cv::Vec3d> rotation_vectors;
	std::vector<cv::Vec3d> translation_vectors;

	int flags = 0;
	flags |= cv::fisheye::CALIB_RECOMPUTE_EXTRINSIC;
	flags |= cv::fisheye::CALIB_CHECK_COND;
	flags |= cv::fisheye::CALIB_FIX_SKEW;
	cv::fisheye::calibrate(object_points, vec_vec_corners, img_size, new_model, new_coeffs, 
			rotation_vectors, translation_vectors, flags, cv::TermCriteria(3, 20, 1e-6));
} // function calib_()

void Fisheye::calibrate(int img_num, cv::Size board_size, 
		const std::vector<std::string>& img_names,
		const std::string& outfile_name) {
	// initialize
	cv::Mat new_model = cv::Mat(3,3,CV_32FC1);
	cv::Mat new_coeffs = cv::Mat(1,4,CV_32FC1);
	std::vector<std::vector<cv::Point2f> > vec_vec_corners;
	int success_img_num = 0;
	int corners_num = 0;
	cv::Size img_size;

	std::cout << "initialized ..." << std::endl;
	extract_corners(img_num, board_size, img_names, vec_vec_corners, 
			success_img_num, corners_num, img_size);	
	calib_(vec_vec_corners, board_size, img_size, success_img_num, corners_num,
			new_model, new_coeffs);

	// save parameters
	this->reset(new_model, new_coeffs);
	cv::FileStorage fout(outfile_name, cv::FileStorage::WRITE);
	fout << "CameraModel" << camera_model_;
	fout << "DistCoeffs" << dist_coeffs_;
	fout.release();
} // function calibrate()


void Fisheye::display_distorted() {
	cv::Mat frame;
	cv::namedWindow("Displaying Distorted Video");
	while(1){
		capture_ >> frame;
		cv::imshow("Displaying Distorted Video", frame);
		if(cv::waitKey(40) == 27) break;
	}
	cv::destroyWindow("Displaying Distorted Video");
} // function display_distort()

void Fisheye::display_undistorted() {
	cv::Mat frame_dist;
	cv::Mat frame_undist;
	cv::namedWindow("Displaying Undistorted Video");
	while(1) {
		capture_ >> frame_dist;
		this->undistort(frame_dist, frame_undist);
		cv::imshow("Displaying Undistorted Video", frame_undist);
		if(cv::waitKey(40) == 27) break;
	}
	cv::destroyWindow("Displaying Undistorted Video");
} // function display_undistort()


void Fisheye::record_distorted_video(const std::string& file_name, double fps, int fourcc) {
	int frame_width = capture_.get(CV_CAP_PROP_FRAME_WIDTH);	
	int frame_height = capture_.get(CV_CAP_PROP_FRAME_HEIGHT);	
	cv::VideoWriter video(file_name, fourcc, fps, cv::Size(frame_width, frame_height));
	cv::Mat frame;
	cv::namedWindow("Recording Distorted Video");
	while(1) {
		capture_ >> frame;
		video << frame;
		cv::imshow("Recording Distorted Video", frame);
		if(cv::waitKey(40) == 27) break;
	}
	cv::destroyWindow("Recording Distorted Video");
} // function record_distorted_video()

void Fisheye::record_undistorted_video(const std::string& file_name, double fps, int fourcc) {
	// get the first frame to determine output shape
	cv::Mat frame_dist, frame_undist;
	capture_ >> frame_dist;
	this->undistort(frame_dist, frame_undist);
	int frame_width = frame_undist.cols; 
	int frame_height = frame_undist.rows;

	// create video writer and record video
	cv::VideoWriter video(file_name, fourcc, fps, cv::Size(frame_width, frame_height));
	cv::namedWindow("Recording Undistorted Video");
	while(1) {
		capture_ >> frame_dist;
		this->undistort(frame_dist, frame_undist);
		video << frame_undist;
		cv::imshow("Recording Undistorted Video", frame_undist);
		if(cv::waitKey(40) == 27) break;
	}
	cv::destroyWindow("Recording Undistorted Video");	
} // function record_undistorted_video()

void Fisheye::record_distorted_imgs(const std::string& folder_name, double fps) {
	cv::namedWindow("Recording Distorted Images");
	cv::Mat frame;
	std::string folder_n_name;
	int counter = 0;
	while(1) {
		capture_ >> frame;
		cv::imshow("Recording Distorted Images", frame);
		std::stringstream name;
		name << std::setw(4) << std::setfill('0') << counter;
		folder_n_name = folder_name + "img_" + name.str() + ".png";
		cv::imwrite(folder_n_name, frame);
		++counter;
		if(cv::waitKey(1000/int(fps)) == 27) break;
	}
	cv::destroyWindow("Recording Distorted Images");


} // function record_distorted_imgs()

void Fisheye::record_undistorted_imgs(const std::string& folder_name, double fps) {
	cv::namedWindow("Recording Undistorted Images");
	cv::Mat frame_dist, frame_undist;
	std::string folder_n_name;
	int counter = 0;
	while(1) {
		capture_ >> frame_dist;
		this->undistort(frame_dist, frame_undist);
		cv::imshow("Recording Undistorted Images", frame_undist);
		std::stringstream name;
		name << std::setw(4) << std::setfill('0') << counter;
		folder_n_name = folder_name + "img_" + name.str() + ".png";
		cv::imwrite(folder_n_name, frame_undist);
		++counter;
		if(cv::waitKey(1000/int(fps)) == 27) break;
	}
	cv::destroyWindow("Recording Undistorted Images");	
} // function record_undistorted_imgs()

void Fisheye::select_distorted_imgs(const std::string& folder_name) {
	// display video
	cv::namedWindow("Selecting Distorted Images");
	cv::Mat frame;

	// press 's' to invoke selection and save images
	std::cout << "Press s to select images" << std::endl;
	int counter = 0;
	std::string folder_n_name;
	while(1) {
		capture_ >> frame;
		cv::imshow("Selecting Distorted Images", frame);
		auto rval = cv::waitKey(40);
		if(rval == 115) {             // if 's' pressed
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
	cv::destroyWindow("Selecting Distorted Images");
} // function select_distorted_imgs()

void Fisheye::select_undistorted_imgs(const std::string& folder_name) {
	// display video
	cv::namedWindow("Selecting Unistorted Images");
	cv::Mat frame_dist, frame_undist;

	// press 's' to invoke selection and save images
	std::cout << "Press s to select images" << std::endl;
	int counter = 0;
	std::string folder_n_name;
	while(1) {
		capture_ >> frame_dist;
		this->undistort(frame_dist, frame_undist);
		cv::imshow("Selecting Undistorted Images", frame_undist);
		auto rval = cv::waitKey(40);
		if(rval == 115) {             // if 's' pressed
			std::stringstream name;
			name << std::setw(4) << std::setfill('0') << counter;
			folder_n_name = folder_name + "img_" + name.str() + ".png";
			cv::imwrite(folder_n_name, frame_undist);
			std::cout << "file img_" << name.str() << ".png saved" << std::endl;
			++counter;
		}
		else if(rval == 27) {
			break;
		}
	}
	// destroy window
	cv::destroyWindow("Selecting Undistorted Images");
} // function select_undistorted_imgs()

} // namespace vision_tools
