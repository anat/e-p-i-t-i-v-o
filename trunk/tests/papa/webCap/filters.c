#include "filters.h"

void filter_negative(IplImage *frame)
{
  unsigned char *ptr = (unsigned char *) frame->imageData;
  int i, size = frame->width * frame->height * frame->nChannels;

  for (i = 0; i < size; i += frame->nChannels)
    {
      ptr[i]   = ~ptr[i];
      ptr[i+1] = ~ptr[i+1];
      ptr[i+2] = ~ptr[i+2];
    }
}

void filter_grayscale(IplImage *frame)
{
  unsigned char *ptr = (unsigned char *) frame->imageData;
  int i, size = frame->width * frame->height * frame->nChannels;
  int grayscale;

  for (i = 0; i < size; i += frame->nChannels)
    {
      grayscale = ptr[i] + ptr[i+1] + ptr[i+2];
      grayscale /= 3;
      ptr[i] = ptr[i+1] = ptr[i+2] = grayscale;
    }
}

void apply_filter(IplImage *frame, int filter, bool apply)
{
  if (apply == true)
    {
      if (filter == FT_NEGATIVE)
	filter_negative(frame);
      else if (filter == FT_GRAYSCALE)
	filter_grayscale(frame);
      else if (filter == FT_DOWNSAMPLING)
	filter_downsampling(frame);
    }
}
