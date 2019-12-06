#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <netpbm/pbm.h>


#ifndef AUXILLARYHEADER
#define AUXILLARYHEADER

//constants

extern const int NUM_NTIDES;

//data structures

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

//prototypes

_Bool is_power_of_2(int val);
coord_t reduce_coord(coord_t old_coord);
point_t reduce_point(point_t old_point);
point_t determine_midpoint(point_t pnt1, point_t pnt2);
point_t cgr(point_t in_point, char in_char);

#endif //ended auxillary file
