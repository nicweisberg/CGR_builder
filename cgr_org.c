#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

const int MIN_SCALE=16;
const int MAX_SCALE=64;
const int NUM_NTIDES=4;

struct coord_t{
unsigned long n;
unsigned long d;
};

struct point_t{
struct coord_t x;
struct coord_t y;
};

struct ntide_t{
char letter;
struct point_t vertex;
};

typedef struct coord_t coord_t;
typedef struct point_t point_t;
typedef struct ntide_t ntide_t;


int Scale;
char** Plot;
char allowables[4] = {'A', 'T', 'C', 'G'};
point_t cornerA = {{0,1},{0,1}};
point_t cornerT = {{1,1},{0,1}};
point_t cornerC = {{0,1},{1,1}};
point_t cornerG = {{1,1},{1,1}};

int main(int argc, char *argv[]);
_Bool is_power_of_2(int val);
coord_t reduce_coord(coord_t old_coord);
point_t reduce_point(point_t old_point);
void print_plot(void);
unsigned scale_coord(coord_t coord);
void plot_point(point_t point);
point_t determine_midpoint(point_t pnt1, point_t pnt2);
point_t cgr(point_t in_point, char in_char);
void initialize_plot(void);
void allocate_mem(void);



//main:
//	reads arguments and file then calls funcitons to make plot
// in:
//	int argc - argument count
//	char *argv - array of arguments
// out:
//	int - exit code
//
// assumes:
//	functions: allocate_mem, initialize_plot, cgr, print_plot
//	global variables: Scale

int main(int argc, char *argv[]){

	if (argc < 2){fprintf(stderr, "Usage: ./cgr <N>\n");exit(1);}
	Scale = atoi(argv[1]);
	if (!is_power_of_2(Scale)){fprintf(stderr, "N must be power of 2\n");exit(1);}
	if (Scale < 16){fprintf(stderr, "Scale must be at least 16\n");exit(1);}
	if (Scale > 64){fprintf(stderr, "Scale must be at most 64\n");exit(1);}
	allocate_mem();
	initialize_plot();
	point_t center = {{1,2},{1,2}};
	char c = getchar();
	point_t nextPoint = cgr(center, (char)c);
	do{
		c = getchar();
		if (c != EOF){
			nextPoint = cgr(nextPoint, (char)c);
		}
	}while (c != EOF);
	print_plot();
	exit(0);


}




// allocate_mem:
//	dynamically allocates memory for Plot
// in:
//	none
//
// out:
//	none
//
// assumes:
//	global variables: char** Plot, int Scale
//

void allocate_mem(void){

	Plot = (char**)malloc(sizeof(char*)*Scale);
        for (int i = 0; i < Scale; i++){
        	Plot[i] = (char*)malloc(sizeof(char)*Scale);
        }
}



//is_power_of_2:
//	checks if a number is a power of two
// in:
//	int val - an integer value
//
// out:
//	_Bool - True if val is power of 2
//
// assumes:
//	none
//

_Bool is_power_of_2(int val){
	while (((val % 2) == 0) && val > 1){
		val /= 2;
	}
	return (val == 1);
}



// reduce coord:
//	reduces coord if denominator above 64
// in:
//	coord_t old_coord - coord_t data structure to check
//
// out:
//	coord_t - new coord_t after reduction
//
// assumes:
//	coord_t data structure has attributes n and d
//

coord_t reduce_coord(coord_t old_coord){
	if (old_coord.d > 64){
		old_coord.n /= 2;
		old_coord.d /= 2;
	}
	return old_coord;
}


// reduce_point:
//	reduces both coordinates of a point
// in:
//	point_t old_point - point to check
//
// out:
//	point_t reduced point - point with reduced coords
//
// assumes:
//	point_t data structure has attributes x and y
//

point_t reduce_point(point_t old_point){
	coord_t reducedX = reduce_coord(old_point.x);
	coord_t reducedY = reduce_coord(old_point.y);
	point_t reducedPoint = {reducedX, reducedY};
	return reducedPoint;
}


// print_plot:
//	prints plot to console with box around it
// in:
//	none
//
// out:
//	none
//
// assumes:
//	global variables: int Scale, char** Plot
//

void print_plot(void) {

	int r, c;
	printf("C+");
	for (int i = 0; i < Scale; i++){
		printf("-");
	}
	printf("+G\n");
        for ( r=Scale-1; r >=0; r-- ) {
		printf(" |");
                for ( c=0; c < Scale; c++ ) {
                        printf( "%c", Plot[r][c] );
                }
		printf("|\n");
        }
	printf("A+");
	for (int i = 0; i < Scale; i++){
		printf("-");
	}
	printf("+T\n");
}


//scale_coord:
//	scales coordinate to fit scale of plot
// in:
//	coord_t coord - coordinate to scale
//
// out:
//	unsigned - integer value after scaled
//
// assumes:
//	global variable int Scale
//

unsigned scale_coord(coord_t coord){
	return ((coord.n * Scale)/coord.d);
}


// plot_point:
//	adds '*' to correct spot in Plot
// in:
//	point_t point - point to plot
//
// out:
//	none
//
// assumes:
//	global variable char** Plot
//	point_t data structure has attributes x and y

void plot_point(point_t point){
	int scaledX = scale_coord(point.x);
	int scaledY = scale_coord(point.y);
	Plot[scaledY][scaledX] = '*';
}

// determine_midpoint:
//	determines midpoint between two points
// in:
//	point_t pnt1, point_t pnt2 - two points to find midpoint from
//
// out:
//	point_t newPoint - calculated midpoint
//
// assumes:
//	coord_t data structure contains attributes n and d
//	point_t data struction contains attributes x and y

point_t determine_midpoint(point_t pnt1, point_t pnt2){
	coord_t newX = {pnt1.x.n + (pnt2.x.n*pnt1.x.d),pnt1.x.d * 2};
	coord_t newY = {pnt1.y.n + (pnt2.y.n*pnt1.y.d),pnt1.y.d * 2};
	point_t newPoint = {newX, newY};
	newPoint = reduce_point(newPoint);
	return newPoint;
}

// cgr:
//	uses other functions to build plot
// in:
//	point_t in_point - the previously plotted point
//	char in_char - the next char in the sequence
// out:
//	point_t - the next point that was plotted
//
// assumes:
//	functions: reduce_point, determine_midpoint, plot_point
//	global variables: char[] allowables, NUM_NTIDES
point_t cgr(point_t in_point, char in_char){
	int allowed = 0;
	point_t corner;
	in_char = toupper(in_char);
	for (int i=0; i<NUM_NTIDES; i++){
		if (in_char == allowables[i]){
			allowed = 1;
			if (in_char==65){
				corner = cornerA;
			}else if (in_char==84){
				corner = cornerT;
			}else if (in_char==67){
				corner = cornerC;
			}else{
				corner = cornerG;
			}
		}
	}
	if (allowed==1){
		in_point = reduce_point(in_point);
		point_t midpoint = determine_midpoint(in_point, corner);
		plot_point(midpoint);
		return midpoint;
	}
	return in_point;
}

// initialize_plot:
//   Assign each element of global character array Plot[][] to a space
//   character, ' '.
// In:
//   No input arguments.
// Out:
//   All characters in Plot[][] initialized.
//   No return value.
// Assumes:
//   Presence of global variables Plot and Scale.
//   Plot is of type char** and of dimension Scale X Scale.
void initialize_plot( void ) {
  int i, j;

  for( i=0; i<Scale; i++ ) {
      for( j=0; j<Scale; j++ ) {
          Plot[i][j] = ' ';
      }
  }
}
