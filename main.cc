/*
 *  GrabVideo.c
 *
 *  Created by Dev Priya on 11/09/09.
 *  Copyright 2010 Robosense. All rights reserved.
 *
 */
 
 
#include "cvextra.h"
#include <iostream>

using namespace std;

int main (int argc, char** argv)
{
	double threshold = atof(argv[1]);

	// OpenCV data structure for handle to the cam
	CvCapture* vidObj;
 
	// This captures from the default cam
	vidObj = cvCaptureFromCAM(0);
 
	while (!cvGrabFrame(vidObj)) {
		// Just wait while first frame is grabbed
	}
 
	// Creating structures to hold the captured and processed frames
	IplImage *grabbedImg; //, *grayImg;
	
	// Class to handle RGB pixels
	RgbImage imgA;

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

	// Will hold the corners of the square
	CvPoint a, b;
	// The colour we are looking for
	Colour theColour(130,35,24);
	
	cout<<"Scanning for hue: "<<hue(theColour.r, theColour.g, theColour.b)<<" Threshold: "<<threshold<<endl;

  	// Loop until Esc key is pressed
	while (1) {
 	//for (int i = 0; i<10; i++) {
		// This function is used to grab the frame from camera + retrieve the image from it
		grabbedImg = cvQueryFrame(vidObj);
 		
		// Convert to RGB wrapper
		imgA = grabbedImg;

		//find_colour(a,b,imgA,theColour, threshold);

		//cvRectangle(grabbedImg, a, b, cvScalar(255,255,255), 1);
		//cvRectangle(grabbedImg, cvPoint(100,100), cvPoint(200,200), cvScalar(255,255,255), 1);
		
		for (int r = 0; r < imgA.h(); r++)
		{
			for (int c = 0;c<imgA.w(); c++)
			{
				if (fabs(hue((int)imgA[r][c].r,(int)imgA[r][c].g,(int)imgA[r][c].b) - hue(theColour.r, theColour.g, theColour.b)) < threshold )
				{
					cvLine(grabbedImg, cvPoint(c,r), cvPoint(c,r), cvScalar(255,255,255), 1);
				}
			}
		}

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
