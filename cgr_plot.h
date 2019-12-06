#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <netpbm/pbm.h>

#include "cgr_aux.h"

#ifndef PLOTHEADER
#define PLOTHEADER

// external storage specifiers

extern bit** Plot;

// prototypes

void output_plot(int testing);
void plot_point( point_t point );
unsigned scale_coord( coord_t coord );

#endif //end of plot header
