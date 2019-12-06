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

int Scale;
const int MIN_SCALE = 32;
const int MAX_SCALE = 4096;


//main:
//	reads arguments and file then calls funcitons to make plot
// in:
//	int argc - argument count
//	char *argv - array of arguments
// out:
//	int - exit code
//
// assumes:
//	functions: cgr, output_plot, pm_init, pbm_freearray
//	global variables: Scale, MAX_SCALE, MIN_SCALE

int main(int argc, char *argv[]){


	if (argc < 2){fprintf(stderr, "Usage: ./cgr <N>\n");exit(1);}
	Scale = atoi(argv[1]);
	if (!is_power_of_2(Scale)){fprintf(stderr, "N must be power of 2\n");exit(1);}
	if (Scale < MIN_SCALE){fprintf(stderr, "Scale must be at least 32\n");exit(1);}
	if (Scale > MAX_SCALE){fprintf(stderr, "Scale must be at most 4096\n");exit(1);}
	int testing = 0;
	if (argc==3){testing = 1;}

	pm_init("cgr", 0);
	Plot = pbm_allocarray(Scale, Scale);
	point_t center = {{1,2},{1,2}};
	char c = getchar();
	point_t nextPoint = cgr(center, (char)c);
	do{
		c = getchar();
		if (c != EOF){
			nextPoint = cgr(nextPoint, (char)c);
		}
	}while (c != EOF);
	output_plot(testing);
	pbm_freearray(Plot, Scale);
	exit(0);


}
