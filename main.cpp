/*
 *  main.c
 *
 *  Sends Webcam data over a network
 *
 *
 */

//#include <opencv/cv.h>
//#include <opencv/highgui.h>
//#include <iostream>
#include "cvextra.h"

#include <cstdlib>
#include <cstring>
#include <boost/asio.hpp>

using boost::asio::ip::udp;
using namespace std;

enum { max_length = 1024 };


int main (int argc, char* argv[])
{
	try
    {
        if (argc != 3)
        {
            std::cerr << "Usage: blocking_udp_echo_client <host> <port>\n";
            return 1;
        }

        /***********************
         * Set Up OpenCV Stuff
         ***********************/

	    // OpenCV data structure for handle to the cam
	    CvCapture* vidObj;
 
	    // This captures from the default cam
	    vidObj = cvCaptureFromCAM(0);
 
	    while (!cvGrabFrame(vidObj)) {
		    // Just wait while first frame is grabbed
	    }
 
	    // Creating structures to hold the captured and processed frames
	    IplImage *grabbedImg, *grayImg;

	    // Retrieve the captured frame
	    grabbedImg = cvRetrieveFrame(vidObj);
	    // Allocate memory for the image structure which will hold the processed frame
	    grayImg = cvCreateImage(cvSize(grabbedImg->width, grabbedImg->height), IPL_DEPTH_8U, 1);
 
        // Define an object that makes it easy to access pixels
        BwImage frame;
        frame = grayImg;
        unsigned char line[frame.w()];

	    // Create a Window to show the captured stream
	    cvNamedWindow("CapturedImage", CV_WINDOW_AUTOSIZE); 
	    cvMoveWindow("CapturedImage", 00, 100);
 
	    // Create a Window to show the processed stream
	    cvNamedWindow("ModifiedImage", CV_WINDOW_AUTOSIZE);
	    cvMoveWindow("ModifiedImage", 640, 100);


        /*************************
         * Set Up Network Stuff
         *************************/
        boost::asio::io_service io_service;
        udp::socket s(io_service, udp::endpoint(udp::v4(), 0));
        udp::resolver resolver(io_service);
        udp::resolver::query query(udp::v4(), argv[1], argv[2]);
        udp::resolver::iterator iterator = resolver.resolve(query);


  	    // Loop until Esc key is pressed
	    while (1) 
        {
		    // This function is used to grab the frame from camera + retrieve the image from it
		    grabbedImg = cvQueryFrame(vidObj);

		    // Display the captured frame in first Window
		    //cvShowImage("CapturedImage", grabbedImg);
 
		    // Convert the captured frame to Grayscale
		    cvCvtColor(grabbedImg, grayImg, CV_RGB2GRAY);

            // Convert the opencv frame to our own class for easy access
            frame = grayImg;

            // Prepare frame data to be sent

            // Send frame data
            s.send_to(boost::asio::buffer("BEGIN FRAME", 11), *iterator);

            for (int r = 0; r < frame.h(); r++)
            {
                for (int c = 0; c< frame.w(); c++)
                {
                    line[c] = frame[r][c];
                }
                s.send_to(boost::asio::buffer(line, frame.w()), *iterator);
            }

            s.send_to(boost::asio::buffer("END FRAME", 9), *iterator);

		    // Display the processed frame in second Window
		    //cvShowImage("ModifiedImage", grayImg);
            // no need to show this...

		    // Exit on esc key
		    if( cvWaitKey( 100 ) == 27 ) 
                break;
	    }

    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
	    
    cvWaitKey(0);
 
	return 0;
}


