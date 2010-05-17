/*
 *  main.c
 *
 *  TODO Discription
 *
 *
 */

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>

using namespace std;

int main (int argc, char** argv)
{
	//double threshold = atof(argv[1]);

	// OpenCV data structure for handle to the cam
	CvCapture* vidObj;
 
	// This captures from the default cam
	vidObj = cvCaptureFromCAM(0);
 
	while (!cvGrabFrame(vidObj)) {
		// Just wait while first frame is grabbed
	}
 
	// Creating structures to hold the captured and processed frames
	IplImage *grabbedImg; //, *grayImg;

	// Retrieve the captured frame
	grabbedImg = cvRetrieveFrame(vidObj);
	// Allocate memory for the image structure which will hold the processed frame
	//grayImg = cvCreateImage(cvSize(grabbedImg->width, grabbedImg->height), IPL_DEPTH_8U, 1);
 
	// Create a Window to show the captured stream
	cvNamedWindow("CapturedImage", CV_WINDOW_AUTOSIZE); 
	cvMoveWindow("CapturedImage", 00, 100);
 
	// Create a Window to show the processed stream
	//cvNamedWindow("ModifiedImage", CV_WINDOW_AUTOSIZE);
	//cvMoveWindow("ModifiedImage", 640, 100);


  	// Loop until Esc key is pressed
	while (1) 
    {
		// This function is used to grab the frame from camera + retrieve the image from it
		grabbedImg = cvQueryFrame(vidObj);

		// Display the captured frame in first Window
		cvShowImage("CapturedImage", grabbedImg);
 
		// Convert the captured frame to Grayscale
		//cvCvtColor(grabbedImg, grayImg, CV_RGB2GRAY);
 
		// Display the processed frame in second Window
		//cvShowImage("ModifiedImage", grayImg);
 
		// Exit on esc key
		if( cvWaitKey( 100 ) == 27 ) 
			break;
	}
 
	cvWaitKey(0);
 
	return -1;
}
