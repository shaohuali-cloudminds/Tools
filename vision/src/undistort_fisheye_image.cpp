#include <cstdlib>
#include <iostream>
#include <string>
#include "highgui.h"
#include "cv.h"

using namespace std;
using namespace cv;


int main(int argc, char** argv)
{
	Mat camera_model = Mat(3,3,CV_32FC1);
	Mat distortion = Mat(1,4,CV_32FC1);

	FileStorage params("../params/fisheye_params.yaml", FileStorage::READ);
	params["CameraModel"] >> camera_model;
	params["DistCoeffs"] >> distortion;
	params.release();

	Mat original_image = imread("../data/images/select0003.png");
	Mat undistort_image = original_image.clone(); 

	fisheye::undistortImage(original_image, undistort_image, camera_model, distortion, camera_model);

	imshow("Original Image", original_image);
	imshow("Undistorted Image", undistort_image);
	
	waitKey(0);
	original_image.release();
	undistort_image.release();
}
