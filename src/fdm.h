#ifndef FDM_H
#define FDM_H

#include <math.h>

#define PI 3.14159265

static inline double degrad(double x) {
	return fmod(x,360.0)*(PI/180.0);
}

#endif