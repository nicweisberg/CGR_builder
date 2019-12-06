#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <netpbm/pbm.h>

#include "cgr.h"
#include "cgr_plot.h"
#include "cgr_aux.h"

// definitions

bit** Plot;

//scale_coord:
//      scales coordinate to fit scale of plot
// in:
//      coord_t coord - coordinate to scale
//
// out:
//      unsigned - integer value after scaled
//
// assumes:
//      global variable int Scale
//

unsigned scale_coord(coord_t coord){
        return ((coord.n * Scale)/coord.d);
}

// plot_point:
//      sets Plot[row][col] to black
// in:
//      point_t point - point to plot
//
// out:
//      none
//
// assumes:
//      global variable bit** Plot
//      point_t data structure has attributes x and y

void plot_point(point_t point){
        int scaledX = scale_coord(point.x);
        int scaledY = scale_coord(point.y);
        Plot[scaledY][scaledX] = PBM_BLACK;
}


// output_plot:
//	writes values from plot array into PBM file
// in:
//	int testing - print to acscii or pbm
// out:
//	void
//assumes:
//	global variables: bit** Plot, int Scale
//	functions: pbm_writepbminit(File*, int, int, int), pbm_writepbmrow(File*, bit*, int, int)
void output_plot(int testing){
	pbm_writepbminit(stdout, Scale, Scale, testing);
	for (int row = 0; row < Scale; row++){
		pbm_writepbmrow(stdout, Plot[row], Scale, testing);
	}
}


