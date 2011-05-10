#include <cv.h>
#include <highgui.h>
#include <cstdlib>
#include <string>
#include <vector>


int main (int /*argc*/, char** /*argv*/)
{ 
	// necessaire pour ecrire l'img
	const std::string 		imgCaptureFilename = "capture.jpeg";
	//const vector<int> 	imgCaptureParams = new vector<int>();

	// open the default camera
	cv::VideoCapture cap(0);
	if(!cap.isOpened())
		return EXIT_FAILURE;

	cv::namedWindow("My simple capture", 1);
	for(;;)
	{
		cv::Mat frame;

		// get a new frame from camera
		cap >> frame; 
		
		cv::imshow("My simple capture", frame);

		if(cv::waitKey(30) >= 0)
		{
			cv::imwrite(imgCaptureFilename, frame/*, imgCaptureParams*/);
			break;
		}
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return EXIT_SUCCESS;
}
