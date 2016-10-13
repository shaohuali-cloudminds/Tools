#include "cv.h"  
#include "cxcore.h"  
#include "highgui.h"  
#include <iostream>  
  
using namespace std;  
int main(int argc, char** argv)  
{
	 if(argc == 1) {
		  cerr << "Usage: ./recordVideo output_file_name" << endl;
			cerr << "Please specify folder and video name!" << endl;
			return 0;
	 }	
   CvCapture* capture=cvCaptureFromCAM(-1);  
//   CvVideoWriter* video=NULL;  
   IplImage* frame=NULL;  
   int n;  
   if(!capture) 
   {  
      cout<<"Can not open the camera."<<endl;  
      return -1;  
   }  
   else  
   {  
      frame=cvQueryFrame(capture);  
//      video=cvCreateVideoWriter(argv[1], CV_FOURCC('X', 'V', 'I', 'D'), 25,  
//      cvSize(frame->width,frame->height)); 
//      if(video) 
//      {  
//         cout<<"VideoWriter has created."<<endl;  
//      }  
  
      cvNamedWindow("Camera Video",1); 
      int i = 0;
				
      while(1)   
      {  
         frame=cvQueryFrame(capture); 

   	     IplImage* dst_persp;
  	 		 dst_persp = cvCreateImage( cvSize(640,480), 8, 3 );   // undistorted perspective and panoramic image
  	 		 CvMat* mapx_persp = cvCreateMat(dst_persp->height, dst_persp->width, CV_32FC1);
  	     CvMat* mapy_persp = cvCreateMat(dst_persp->height, dst_persp->width, CV_32FC1);

				 cvRemap(frame, dst_persp, mapx_persp, mapy_persp, CV_INTER_LINEAR+CV_WARP_FILL_OUTLIERS, cvScalarAll(0));

         if(!frame)  
         {  
            cout<<"Can not get frame from the capture."<<endl;  
            break;  
         }  
//         n=cvWriteFrame(video,frame); 
         cvShowImage("Camera Video",frame); 
         i++;  
         if(cvWaitKey(2)>0)   
            break; 
      }  
  
//      cvReleaseVideoWriter(&video);  
      cvReleaseCapture(&capture);  
      cvDestroyWindow("Camera Video");  
   }  
   return 0;  
} 
