#ifndef GFX_H
#define GFX_H

#include <pd_api.h>

typedef struct {
	double x;
	double y;
} Point;

typedef struct {
	int n;
	Point* points;
} Poly;

// math
Point rotatePoint(Point point, Point origin, double angle);
// returns a new poly, mainly for drawing a repesentation of the original,
// to avoid distortion such as drifting and weird scaling.
Poly* protate(PlaydateAPI* pd, Poly* p, Point origin, double angle);
void ptranslate(Poly* p, Point translation);

// draw
void pdraw(PlaydateAPI* pd, Poly* p, LCDSolidColor color);

#endif
