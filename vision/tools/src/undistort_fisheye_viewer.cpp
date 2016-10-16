#include <cstdlib>
#include <iostream>
#include <string>
#include "highgui.h"
#include "cv.h"

using namespace std;
using namespace cv;


int main(int argc, char** argv)
{
	cvNamedWindow("video", CV_WINDOW_AUTOSIZE);
	CvCapture* capture; 
	if(argc == 1) {
		capture = cvCaptureFromCAM(1);
	}
	else {
		capture = cvCreateFileCapture(argv[1]);
	}
	assert(capture != NULL); 

	// load camera model and distortion
	Mat camera_model = Mat(3,3,CV_32FC1);
	Mat distortion = Mat(1,4,CV_32FC1);

	FileStorage params("../params/fisheye_params.yaml", FileStorage::READ);
	params["CameraModel"] >> camera_model;
	params["DistCoeffs"] >> distortion;
	params.release();

	IplImage* frame;
 	Mat undistorted_frame;
	while(cvWaitKey(33) != 27) {
		frame = cvQueryFrame(capture);
		if(!frame) break;
		fisheye::undistortImage(Mat(frame), undistorted_frame, camera_model, distortion, camera_model);
		IplImage ipl_show = undistorted_frame; 
		cvShowImage("video", &ipl_show);
	}

	cvReleaseCapture(&capture);
	cvDestroyWindow("video");
}
