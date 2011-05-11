#ifndef FILTERS_H_
# define FILTERS_H_

# include <opencv/cv.h>
# include <opencv/highgui.h>

typedef char bool;
# define false 0
# define true  1

# define FT_NONE         0
# define FT_NEGATIVE     1
# define FT_GRAYSCALE    2
# define FT_DOWNSAMPLING 3

void apply_filter(IplImage *frame, int filter, bool apply);
void filter_negative(IplImage *frame);
void filter_grayscale(IplImage *frame);
void filter_downsampling(IplImage *frame);

#endif
