#ifndef VISION_CAMERA_HPP_
#define VISION_CAMERA_HPP_

#include <string>
#include <opencv2/opencv.hpp>

namespace vision_tools {

/**
 *  @brief A wrapper for webcams related
 *
 *  @detail This class provides basic operations on cameras, including video
 *  recording and image extractions. 
 */ 
				
class Camera {
	protected:
		cv::VideoCapture capture_;			

	public:

		/**
		 *  @brief Default constructor
		 *
		 *  @detail Open default webcam for video capture.
		 */
		
		/**
		 *  @brief Constructor from device
		 *  
		 *  @param dev_id Device ID
	 	 */
		Camera(int dev_id): capture_(dev_id) {}

		/**
		 *
		 */
		Camera(const std::string& video_file): capture_(video_file) {}
		~Camera() { capture_.release(); }
	
		/**
		 *  @brief Function to display captures on the screen
		 */	
		void display();

		/**
		 *  @brief Function to record video from a camera
		 *
		 *  @param file_name File name of the output .avi file
		 *  @param fps Frames per second for the output video, 25 by default
		 *  @param fourcc Encoding of the output video file
		 */
		void record_video(const std::string& file_name, double fps=25,
				int fourcc=CV_FOURCC('M','J','P','G'));

		/**
		 *  @brief Function to consecutively extract images from camera
		 *
		 *  @param folder_name Name of folder to store images
		 *  @param fps Frames per second to select images, 25 by default
		 */
		void record_imgs(const std::string& folder_name, double fps=25);

		/**
		 *  @brief Function to manually select images from camera
		 *
		 *  @detail Press 's'(short for 'select') to pickup an image from camera.
		 *  ESC key will invoke shutdown.
		 *
		 *  @param folder_name Name of folder to store selected images.
		 */
		void select_imgs(const std::string& folder_name);

}; // class Camera

} // namespace vision_tools

#endif // vision/camera.hpp
