#ifndef VISION_FISHEYE_HPP_
#define VISION_FISHEYE_HPP_

#include <opencv2/opencv.hpp>
#include <string>

namespace vision_tools {

/**
 *  @brief A wrapper for fisheye camera related.
 */				

class Fisheye {
	private:
		cv::Mat camera_model_;          // camera model
		cv::Mat dist_coeffs_;           // distortion coefficients

		void extract_corners() const;   // TODO: unfinished
		void calib_() const;            // TODO: unfinished

	public:
		/**
		 *  @brief Default constructor
		 *
		 *  Initialize camera model and distortion paramters to be empty cv::Mat.
		 */
		Fisheye(): camera_model_(cv::Mat(3,3,CV_32FC1)),
				dist_coeffs_(cv::Mat(1,4,CV_32FC1)) {}

		/** 
		 *  @brief Constructor using yaml file for initilization
		 *
		 *  @param file_name File name of a .yaml file storing camera model and
		 *  			 distortion coefficients. The key values should be CameraModel
		 *  			 and DistCoeffs respectively
		 */
		Fisheye(std::string file_name): camera_model_(cv::Mat(3,3,CV_32FC1)),
				dist_coeffs_(cv::Mat(1,4,CV_32FC1)) {
			cv::FileStorage param_file(file_name, cv::FileStorage::READ);
			param_file["CameraModel"] >> camera_model_;
			param_file["DistCoeffs"] >> dist_coeffs_;
			param_file.release();
		}

		/**
		 *  @brief Constructor using explicit camera model and distortion coefficients
		 *
		 */
		Fisheye(const cv::Mat& camera_model, const cv::Mat& dist_coeffs):
				camera_model_(cv::Mat(3,3,CV_32FC1)), dist_coeffs_(cv::Mat(1,4,CV_32FC1)) {
			camera_model.copyTo(camera_model_);
			dist_coeffs.copyTo(dist_coeffs_);
		}

		~Fisheye() {}

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
		 *  @brief Function to calibrate a fisheye camera
		 *  
		 *  @param sample_folder Name of folder that stores chessboard images for calibration
		 */
		void calibrate(std::string sample_folder, 
				cv::Size board_size, std::string outfile_name);

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
			cv::fisheye::undistort(src, dst, camera_model_, dist_coeffs_, camera_model_);	
		}


}; // class Fisheye
} // namespace vision_tools
#endif // fisheye.hpp
