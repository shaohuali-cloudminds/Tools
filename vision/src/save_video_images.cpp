#include <cstdlib>
#include <iostream>
#include <string>
#include "highgui.h"
#include "cv.h"

using namespace std;
using namespace cv;


/**
 *	Usage: ./saveVideoImages output_folder skip file_name 
 *
 *	file_name: name of video file to be loaded, 0 for using camera as input
 *	output_folder: name of folder to save output images
 *	skip: number of skip frames, 0 as default
 */
int main(int argc, char** argv)
{
	if(argc < 3) {
		cerr << "Usage: ./saveVideoImages file_name output_folder skip " << endl;
		return 0;
	}
	int num_skip = atoi(argv[2]);

	cvNamedWindow("capture", CV_WINDOW_AUTOSIZE);
	CvCapture* capture; 
	string mode = argv[1];
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
  
	int i = 1;
	while (cvWaitKey(33) != 27)
	{
		pframe = cvQueryFrame(capture);
		if (!pframe)
			break;
		cvShowImage("capture", pframe);

		if(i % num_skip == 0) {
			 stringstream img_name;
			 img_name << setw(4) << setfill('0') << i/num_skip << ".png"; 
			 string name = argv[1]+img_name.str();
			 cvSaveImage(name.c_str(), pframe);
		}
		++i;
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow("capture");
}
