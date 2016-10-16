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
	if(argc == 1) {
		cerr << "Please specify output file name" << endl;
		cerr << "Usage ./recordFisheye file_name" << endl;
	}

	CvCapture* capture; 
	capture = cvCaptureFromCAM(1);

	assert(capture != NULL); 

	// load camera model and distortion
	Mat camera_model = Mat(3,3,CV_32FC1);
	Mat distortion = Mat(1,4,CV_32FC1);

	FileStorage params("../params/fisheye_params.yaml", FileStorage::READ);
	params["CameraModel"] >> camera_model;
	params["DistCoeffs"] >> distortion;
	params.release();

	IplImage* frame = NULL;
	CvVideoWriter* video = NULL;
 	Mat undistorted_frame;
	int n;
	while(1){
		frame = cvQueryFrame(capture);
		if(!frame) break;
		fisheye::undistortImage(Mat(frame), undistorted_frame, camera_model, distortion, camera_model);
		IplImage ipl_show = undistorted_frame; 
		video=cvCreateVideoWriter(argv[1], CV_FOURCC('X', 'V', 'I', 'D'), 25,
				cvSize(ipl_show.width, ipl_show.height));
		cvShowImage("video", &ipl_show);
		n = cvWriteFrame(video, &ipl_show);
		if(cvWaitKey(2) > 0) {
			break;
		}
	}

	cvReleaseCapture(&capture);
	cvReleaseVideoWriter(&video);
	cvDestroyWindow("video");

}
