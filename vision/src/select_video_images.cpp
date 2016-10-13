#include <cstdlib>
#include <iostream>
#include <string>
#include "highgui.h"
#include "cv.h"

using namespace std;
using namespace cv;


/**
 *	Usage: ./selectVideoImages output_folder file_name_prefix mode
 *
 *	file_name: name of video file to be loaded, 0 for using camera as input
 *	output_folder: name of folder to save output images
 *	file_name_prefix: prefix of output file name
 *	mode: non for devide input, otherwise for input video name
 */
int main(int argc, char** argv)
{
	if(argc < 3) {
		cerr << "Usage: ./selectVideoImages output_folder file_name_prefix mode" << endl;
		return -1;
	}	

	cvNamedWindow("video", CV_WINDOW_AUTOSIZE);
	CvCapture* capture; 
	if (argc == 3)
	{
		capture = cvCaptureFromCAM(1);
	}                            
	else
	{
		capture = cvCreateFileCapture(argv[3]);
	}
	assert(capture != NULL); 
	

	IplImage* pframe;
	Mat mframe;
 
	int i = 0;
	while(i < 25) {                       // store 25 images
		while(cvWaitKey(33) != 27) {
			pframe = cvQueryFrame(capture);
			if(!pframe) break;
			cvShowImage("video", pframe);
		}
	 	stringstream img_name;
		img_name << setw(4) << setfill('0') << i << ".png"; 
		string folder_name = argv[1];
		string prefix_name = argv[2];
	 	string name = folder_name+prefix_name+img_name.str();
	 	cvSaveImage(name.c_str(), pframe);
		cout << i+1 << " image(s) saved" << endl; 
		++i;
	}

	cvReleaseCapture(&capture);
	cvDestroyWindow("video");
}
