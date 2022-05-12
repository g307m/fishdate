#include "gfx.h"

#include <math.h>

// math
Point rotatePoint(Point point, Point origin, double angle) {
	double s = sin(angle);
	double c = cos(angle);

	// translate point back to origin:
	point.x -= origin.x;
	point.y -= origin.y;

	// rotate point
	double xnew = point.x * c - point.y * s;
	double ynew = point.x * s + point.y * c;

	// translate point back:
	point.x = xnew + origin.x;
	point.y = ynew + origin.y;
	return point;
}
Poly* protate(PlaydateAPI* pd, Poly* p, Point origin, double angle) {
	Point* e = pd->system->realloc(NULL, sizeof(Point)*p->n);
	Poly* w = pd->system->realloc(NULL, sizeof(Poly));
	w->n = p->n;
	w->points = e;
	for (int i = 0; i < p->n; i++)
	{
		e[i] = rotatePoint(p->points[i], origin, angle);
	}
	return w;
}

// drawing
void pdraw(PlaydateAPI *pd, Poly *p, LCDSolidColor color) {
	for (int i = 0; i < p->n; i++)
	{
		Point current = p->points[i];
		Point next;
		if (i+1 == p->n)
			next = p->points[0];
		else
			next = p->points[i+1];
		pd->graphics->drawLine(current.x, current.y, next.x, next.y, 1, color);
	}
}
