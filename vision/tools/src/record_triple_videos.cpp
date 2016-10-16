#include "cv.h"  
#include "cxcore.h"  
#include "highgui.h"  
#include <iostream>  
  
using namespace std;  
int main(int argc, char** argv)  
{
	 if(argc == 1) {
		  cerr << "Usage: ./recordVideo outfile_left outfile_straight outfile_right" << endl;
			cerr << "Please specify folder and video name!" << endl;
			return 0;
	 }	
   CvCapture* capture_left = cvCaptureFromCAM(0);
   CvCapture* capture_straight = cvCaptureFromCAM(2);
   CvCapture* capture_right = cvCaptureFromCAM(3);

   CvVideoWriter* video_left=NULL;  
   CvVideoWriter* video_straight=NULL;  
   CvVideoWriter* video_right=NULL;  

   IplImage* frame_left=NULL;  
   IplImage* frame_straight=NULL;  
   IplImage* frame_right=NULL;  

	 int nl, ns, nr;  
   if(!capture_left || !capture_straight || !capture_right) 
   {  
      cout<<"Can not open the camera."<<endl;  
      return -1;  
   }  
   else  
   {  
      frame_left=cvQueryFrame(capture_left);  
      frame_straight=cvQueryFrame(capture_straight);  
      frame_right=cvQueryFrame(capture_right);  


			video_left=cvCreateVideoWriter(argv[1], CV_FOURCC('X', 'V', 'I', 'D'), 25,  
			cvSize(frame_left->width,frame_left->height)); 
			video_straight=cvCreateVideoWriter(argv[2], CV_FOURCC('X', 'V', 'I', 'D'), 25,  
      cvSize(frame_straight->width,frame_straight->height)); 
			video_right=cvCreateVideoWriter(argv[3], CV_FOURCC('X', 'V', 'I', 'D'), 25,  
      cvSize(frame_right->width,frame_right->height)); 


			if(video_left && video_straight && video_right) 
      {  
         cout<<"VideoWriter has been created."<<endl;  
      }  
  
      cvNamedWindow("Camera Video Left",1); 
      cvNamedWindow("Camera Video Straight",1); 
      cvNamedWindow("Camera Video Right",1); 
      int i = 0;  
      while(1)   
      {  
         frame_left=cvQueryFrame(capture_left); 
         frame_straight=cvQueryFrame(capture_straight); 
         frame_right=cvQueryFrame(capture_right); 
         if(!frame_left || !frame_straight || !frame_right)  
         {  
            cout<<"Can not get frame from the capture."<<endl;  
            break;  
         }  
         nl=cvWriteFrame(video_left,frame_left); 
         ns=cvWriteFrame(video_straight,frame_straight); 
         nr=cvWriteFrame(video_right,frame_right); 
         cvShowImage("Camera Video Left",frame_left); 
         cvShowImage("Camera Video Straight",frame_straight); 
         cvShowImage("Camera Video Right",frame_right); 
         i++;  
         if(cvWaitKey(100)==27)   
            break; 
      }  
  
      cvReleaseVideoWriter(&video_left);  
      cvReleaseVideoWriter(&video_straight);  
      cvReleaseVideoWriter(&video_right);  
      cvReleaseCapture(&capture_left);  
      cvReleaseCapture(&capture_straight);  
      cvReleaseCapture(&capture_right);  
      cvDestroyWindow("Camera Video Left");  
      cvDestroyWindow("Camera Video Straight");  
      cvDestroyWindow("Camera Video Right");  
   }  
   return 0;  
} 
