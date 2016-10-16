#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "highgui.h"
#include "cv.h"

using namespace std;
using namespace cv;


int main(int argc, char** argv)
{
	Mat camera_model = Mat(3,3,CV_32FC1);
	Mat distortion = Mat(1,4,CV_32FC1);

	FileStorage params("../params/params.yaml", FileStorage::READ);
	params["CameraModel"] >> camera_model;
	params["DistCoeffs"] >> distortion;
	params.release();

	CvCapture* capture;
	if(argc == 2) {
		// extract camera
		capture = cvCaptureFromCAM(1);
	}
	else {
		// extract video files
		capture = cvCreateFileCapture(argv[2]);
	}

	IplImage* frame;
	frame = cvQueryFrame(capture);
	Mat undistort_image = Mat(frame).clone();

	vector<int> compression;
	compression.push_back(CV_IMWRITE_PNG_COMPRESSION);
	compression.push_back(0);

	int i = 0;
	while(cvWaitKey(1) != 27) {
		frame = cvQueryFrame(capture);	
		if(!frame) break;
		cvShowImage("capture", frame);
		if(i%5 == 0) {
			stringstream img_name;
			img_name << setw(4) << setfill('0') << i/5 << ".png";
			string name = argv[1]+img_name.str();
			fisheye::undistortImage(Mat(frame), undistort_image, camera_model, distortion, camera_model);
			imwrite(name, undistort_image, compression);
		}
		++i;
	}

	cvReleaseCapture(&capture);
	undistort_image.release();

	return 0;
}
