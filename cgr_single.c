#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <netpbm/pbm.h>


const int MIN_SCALE=32;
const int MAX_SCALE=4096;
const int NUM_NTIDES=4;

int Scale;
bit** Plot;

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

char allowables[4] = {'A', 'T', 'C', 'G'};
point_t cornerA = {{0,1},{0,1}};
point_t cornerT = {{1,1},{0,1}};
point_t cornerC = {{0,1},{1,1}};
point_t cornerG = {{1,1},{1,1}};


_Bool is_power_of_2(int val);
coord_t reduce_coord(coord_t old_coord);
point_t reduce_point(point_t old_point);
point_t determine_midpoint(point_t pnt1, point_t pnt2);
point_t cgr(point_t in_point, char in_char);
void output_plot( void );
void plot_point( point_t point );
unsigned scale_coord( coord_t coord );


//main:
// in:
//      int argc - argument count
//      char *argv - array of arguments
// out:
//      int - exit code
//
// assumes:
//      functions: cgr, output_plot
//      global variables: Scale

int main(int argc, char *argv[]){

        if (argc < 2){fprintf(stderr, "Usage: ./cgr <N>\n");exit(1);}
        Scale = atoi(argv[1]);
        if (!is_power_of_2(Scale)){fprintf(stderr, "N must be power of 2\n");exit(1);}
        if (Scale < MIN_SCALE){fprintf(stderr, "Scale must be at least 32\n");exit(1);}
        if (Scale > MAX_SCALE){fprintf(stderr, "Scale must be at most 4096\n");exit(1);}
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
        output_plot();
	pbm_freearray(Plot, Scale);
        exit(0);
}



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



void output_plot( void ){
        pbm_writepbminit(stdout, Scale, Scale, 0);
	for (int row = 0; row < Scale; row++){
                pbm_writepbmrow(stdout, Plot[row], Scale, 0);
	}
}


//is_power_of_2:
//      checks if a number is a power of two
// in:
//      int val - an integer value
//
// out:
//      _Bool - True if val is power of 2
//
// assumes:
//      none
//

_Bool is_power_of_2(int val){
        while (((val % 2) == 0) && val > 1){
                val /= 2;
        }
        return (val == 1);
}

// reduce coord:
//      reduces coord if denominator above 64
// in:
//      coord_t old_coord - coord_t data structure to check
//
// out:
//      coord_t - new coord_t after reduction
//
// assumes:
//      coord_t data structure has attributes n and d
//

coord_t reduce_coord(coord_t old_coord){
        if (old_coord.d > 64){
                old_coord.n /= 2;
                old_coord.d /= 2;
        }
        return old_coord;
}


// reduce_point:
//      reduces both coordinates of a point
// in:
//      point_t old_point - point to check
//
// out:
//      point_t reduced point - point with reduced coords
//
// assumes:
//      point_t data structure has attributes x and y
//

point_t reduce_point(point_t old_point){
        coord_t reducedX = reduce_coord(old_point.x);
        coord_t reducedY = reduce_coord(old_point.y);
        point_t reducedPoint = {reducedX, reducedY};
        return reducedPoint;
}

// determine_midpoint:
//      determines midpoint between two points
// in:
//      point_t pnt1, point_t pnt2 - two points to find midpoint from
//
// out:
//      point_t newPoint - calculated midpoint
//
// assumes:
//      coord_t data structure contains attributes n and d
//      point_t data struction contains attributes x and y

point_t determine_midpoint(point_t pnt1, point_t pnt2){
        coord_t newX = {pnt1.x.n + (pnt2.x.n*pnt1.x.d),pnt1.x.d * 2};
        coord_t newY = {pnt1.y.n + (pnt2.y.n*pnt1.y.d),pnt1.y.d * 2};
        point_t newPoint = {newX, newY};
        newPoint = reduce_point(newPoint);
        return newPoint;
}

// cgr:
//      uses other functions to build plot
// in:
//      point_t in_point - the previously plotted point
//      char in_char - the next char in the sequence
// out:
//      point_t - the next point that was plotted
//
// assumes:
//      functions: reduce_point, determine_midpoint, plot_point
//      global variables: char[] allowables, NUM_NTIDES
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

