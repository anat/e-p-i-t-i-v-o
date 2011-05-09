#include "filters.h"
#include <stdio.h>
#include <unistd.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>

# define WIN_TITLE   "WebCap"

void error_msg(char *msg, bool quit)
{
  write(STDERR_FILENO, msg, strlen(msg));
  if (quit == true)
    exit(EXIT_SUCCESS);
}

void display_capture_infos(IplImage *frame)
{
  printf("Capture information:\n");
  printf("  Channels numbers : %d.\n", frame->nChannels);
  printf("  Definition :       %d*%d.\n", frame->width, frame->height);
  printf("  Channel depth :    %d.\n", frame->depth);
  printf("  Origin :           %d.\n", frame->origin);
  printf("  ImageData :        %p.\n", frame->imageData);
}

int main()
{
  CvCapture* capture;
  IplImage* frame;
  char c;
  bool negative = false, grayscale = false;

  if(!(capture = cvCaptureFromCAM(CV_CAP_ANY)))
    error_msg("Error: cannot start capture.\n", true);
  
  cvNamedWindow(WIN_TITLE, CV_WINDOW_AUTOSIZE);
  
  frame = cvQueryFrame(capture);
  display_capture_infos(frame);

  while(true)
    {
      if (!(frame = cvQueryFrame(capture)))
	error_msg("Error: cannot grab frame.\n", true);

      apply_filter(frame, FT_NEGATIVE, negative);
      apply_filter(frame, FT_GRAYSCALE, grayscale);

      cvShowImage(WIN_TITLE, frame);
      
      if ((c = cvWaitKey(10)) == 27) /* Esc */
	break;
      else if(c == 'n')
	negative = (negative == true) ? false : true;
      else if(c == 'i')
	grayscale = (grayscale == true) ? false : true;
    }

  cvReleaseCapture(&capture);
  cvDestroyWindow(WIN_TITLE);
  return 0;
}
