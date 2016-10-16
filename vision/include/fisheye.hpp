#ifndef VISION_FISHEYE_HPP_
#define VISION_FISHEYE_HPP_

#include <opencv2/opencv.hpp>
#include <string>

namespace vision_tools {

/**
 *  @brief A wrapper for fisheye camera related.
 * 
 *  @detail This class provides basic operations on fisheye cameras, including
 *	calibration, undistort an image etc.
 *	
 *  TODO: optimize with a display_kernel() function!!!
 */				

class Fisheye {
	private:
		cv::VideoCapture capture_;      // video capture object
		cv::Mat camera_model_;          // camera model
		cv::Mat dist_coeffs_;           // distortion coefficients

		void extract_corners(int img_num, cv::Size board_size,
				const std::vector<std::string>& img_names,
				std::vector<std::vector<cv::Point2f> >& vec_vec_corners,
				int& success_img_num, int& corners_num,
				cv::Size& img_size) const;   

		void calib_(std::vector<std::vector<cv::Point2f> >& vec_vec_corners,
				cv::Size board_size, cv::Size img_size,
				int success_img_num, int corners_num,
				cv::Mat& new_model, cv::Mat& new_coeffs) const;            

	public:
		/**
		 *  @brief Constructor with device id
		 *
		 *  Capture from device, initialize camera model and 
		 *  distortion paramters to be empty cv::Mat.
		 */
		Fisheye(int dev_id): capture_(dev_id), camera_model_(cv::Mat(3,3,CV_32FC1)),
				dist_coeffs_(cv::Mat(1,4,CV_32FC1)) {}
	
		/**
		 *  @brief Constructor with video file
		 *
		 * 	Capture from video, initialize camera model and
		 * 	distortion parameters to be empty cv::Mat. 
		 *  Initialize camera 
		 */
		Fisheye(const std::string& video_file): capture_(video_file),
				camera_model_(cv::Mat(3,3,CV_32FC1)),
				dist_coeffs_(cv::Mat(1,4,CV_32FC1)) {}

		/** 
		 *  @brief Constructor with device id and known parameters 
		 *
		 *  @param dev_id Device ID
		 *  @param file_name File name of a .yaml file storing camera model and
		 *  			 distortion coefficients. The key values should be CameraModel
		 *  			 and DistCoeffs respectively
		 */
		Fisheye(int dev_id, const std::string& param_file): 
				capture_(dev_id),
				camera_model_(cv::Mat(3,3,CV_32FC1)),
				dist_coeffs_(cv::Mat(1,4,CV_32FC1)) {
			cv::FileStorage params(param_file, cv::FileStorage::READ);
			params["CameraModel"] >> camera_model_;
			params["DistCoeffs"] >> dist_coeffs_;
			params.release();
		} // function Fisheye()


		/**
		 *  @brief Constructor with video file and know paramters
		 *
		 *  @param video_file Name of video file
		 *  @param param_file File name of a .yaml file, same as above 
		 */
		Fisheye(const std::string& video_file, const std::string param_file):
				capture_(video_file),
				camera_model_(cv::Mat(3,3,CV_32FC1)),
				dist_coeffs_(cv::Mat(1,4,CV_32FC1)) {
			cv::FileStorage params(param_file, cv::FileStorage::READ);		
			params["CameraModel"] >> camera_model_;
			params["DistCoeffs"] >> dist_coeffs_;
			params.release();
		} // function Fisheye()
		

		/**
		 *  @brief Constructor with device, using explicit camera model 
		 *  and distortion coefficients
		 * 
		 *  @param dev_id Device ID
		 *  @param camera_model Camera model, cv::Mat of size 3 X 3
		 *  @param dist_coeffs Distortion coefficients, cv::Mat of size 1 X 4
		 */
		Fisheye(int dev_id, const cv::Mat& camera_model, const cv::Mat& dist_coeffs):
				capture_(dev_id),
				camera_model_(cv::Mat(3,3,CV_32FC1)), 
				dist_coeffs_(cv::Mat(1,4,CV_32FC1)) {
			camera_model.copyTo(camera_model_);
			dist_coeffs.copyTo(dist_coeffs_);
		} // function Fisheye()

		/**
		 *  @brief Constructor with video file, using explicit camera 
		 *  model and distortion coefficients
		 *
		 *  @param video_file Name of video file
		 *  @param camera_model Camera model, cv::Mat of size 3 X 3
		 *  @param dist_coeffs Distortion coefficients, cv::Mat of size 1 X 4
		 */
		Fisheye(const std::string& video_file, const cv::Mat& camera_model,
				const cv::Mat dist_coeffs):
				capture_(video_file),
				camera_model_(cv::Mat(3,3,CV_32FC1)), 
				dist_coeffs_(cv::Mat(1,4,CV_32FC1)) {
			camera_model.copyTo(camera_model_);
			dist_coeffs.copyTo(dist_coeffs_);
		} // function Fisheye()

		~Fisheye() { capture_.release(); }

		/**
		 *  @brief Function to get camera model
		 */
		cv::Mat camera_model() const { 
			cv::Mat m;
			camera_model_.copyTo(m); 
			return m;
		}

		/**
		 *  @brief Function to get distortion coefficients
		 */
		cv::Mat dist_coeffs() const {
			cv::Mat m;
			dist_coeffs_.copyTo(m);			
			return m;
		}	

		/**
		 *  @brief Function to display distorted images
		 */
		void display_distorted();

		/**
		 *  @brief Function to display undistorted video
		 */
		void display_undistorted();

		/**
		 *  @brief Function to record distorted video from a camera
		 *
		 *  @param file_name File name of the output .avi file
		 *  @param fps Frames per second for the output video, 25 by default
		 *  @param fourcc Encoding of the output video file
		 */
		void record_distorted_video(const std::string& file_name, double fps=25,
				int fourcc=CV_FOURCC('M','J','P','G'));

		/**
		 *  @brief Function to record undistorted video from a camera
		 */
		void record_undistorted_video(const std::string& file_name, double fps=25,
				int fourcc=CV_FOURCC('M','J','P','G'));

		/**
		 *  @brief Function to consecutively extract distorted images from camera
		 *
		 *  @param folder_name Name of folder to store images
		 *  @param fps Frames per second to select images, 25 by default
		 */
		void record_distorted_imgs(const std::string& folder_name, double fps=25);

		/**
		 *  @brief Function to consecutively extract undistorted images from camera
		 */ 
		void record_undistorted_imgs(const std::string& folder_name, double fps=25);

		/**
		 *  @brief Function to manually select images from camera
		 *
		 *  @detail Press 's'(short for 'select') to pickup an image from camera
		 *  ESC key will invoke shutdown
		 *
		 *  @param folder_name Name of folder to store selected images.
		 */
		void select_distorted_imgs(const std::string& folder_name);

		/**
		 *  @brief Function to manually select images from camera
		 */
		void select_undistorted_imgs(const std::string& folder_name);

		/**
		 *  @brief Function to calibrate a fisheye camera
		 * 
		 * 	@param img_num Number of images to achieve calibration
		 * 	@param board_size Size of calibration board (CROSSINGS_per_ROW, CROSSINGS_per_COL)
		 * 	@param img_names Names of images for calibration
		 * 	@param outfile_name Name of output parameter file, in .yaml format
		 */
		void calibrate(int img_num, cv::Size board_size, const std::vector<std::string>& img_names,
					const std::string& outfile_name);

		/**
		 *  @brief Funtion to reset camera model and distortion paramters
		 *
		 *  This function is usually used after calibration so that the parameters could
		 *  be introduced.
		 *
		 *  @param camera_model New camera model
		 *  @param dist_coeffs New distortion coefficients
		 */
		void reset(const cv::Mat& camera_model, const cv::Mat& dist_coeffs) {
			camera_model.copyTo(camera_model_);	
			dist_coeffs.copyTo(dist_coeffs_);
		}

		/**
		 *  @brief Function to undistort an image using specified camera models and distortion
		 *  coefficients
		 *  
		 *  @param src Distorted input image
		 *  @param dst Undistorted output image
		 */		
		void undistort(const cv::Mat& src, cv::Mat& dst) const {
			cv::fisheye::undistortImage(src, dst, camera_model_, dist_coeffs_, camera_model_);	
		}


}; // class Fisheye
} // namespace vision_tools
#endif // vision/fisheye.hpp
