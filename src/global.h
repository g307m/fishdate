#ifndef GLOBAL_H
#define GLOBAL_H
#include "gfx.h"

Point hook_org = {45,5};

Point hook_pts[] = {
	{40,00},
	{50,00},
	{60,10},
	{60,20},
	{50,20},
	{50,50},
	{40,60},
	{30,60},
	{15,40},
	{30,40},
	{35,50},
	{40,40},
	{40,20},
	{30,20},
	{30,10}
};

Poly hook_poly = {
	sizeof(hook_pts)/sizeof(Point),
	hook_pts
};

#endif
