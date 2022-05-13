#include <stdio.h>
#include <stdlib.h>

#include <pd_api.h>

#include "fdm.h"
#include "gfx.h"
#include "global.h"
#include "fd_strings.h"

static int update(void* userdata);
const char* fontpath = "/System/Fonts/Asheville-Sans-14-Bold.pft";
LCDFont* font = NULL;
uint32_t cnt = 0;
char number[12] = {0};

#ifdef _WINDLL
__declspec(dllexport)
#endif
int eventHandler(PlaydateAPI* pd, PDSystemEvent event, uint32_t arg)
{
	const char* err;
	switch (event) {
		case kEventInit:
		font = pd->graphics->loadFont(fontpath, &err);
		
		if ( font == NULL )
			pd->system->error("%s:%i Couldn't load font %s: %s", __FILE__, __LINE__, fontpath, err);
		pd->system->setUpdateCallback(update, pd);
		break;
		default:
		break;
	}
	return 0;
}

int rot = 0;

PDButtons current = 0;
PDButtons pushed = 0;
PDButtons released = 0;

double vrate = 0;

static int update(void* userdata)
{
	PlaydateAPI* pd = userdata;

	// move shape
	pd->system->getButtonState(&current, &pushed, &released);
	if (!pd->system->isCrankDocked()) {
		vrate += pd->system->getCrankChange() / 4;
		if (fabs(vrate) < 0.01) {
			vrate = 0;
		}
	} else {
		vrate = 0;
	}

	if (vrate != 0) {
		vrate /= 1.1;
	}

	ptranslate(&hook_poly, (Point){0,vrate});
	hook_org.y+=vrate;
	if (current & kButtonLeft ) {ptranslate(&hook_poly, (Point){-5,0});hook_org.x-=5;}
	if (current & kButtonRight) {ptranslate(&hook_poly, (Point){5, 0});hook_org.x+=5;}

	pd->graphics->clear(kColorWhite);
	pd->graphics->setFont(font);
	Poly* mod = protate(pd, &hook_poly, hook_org, degrad(current & kButtonRight?15:(current & kButtonLeft?-15:0)));
	pdraw(pd, mod, kColorBlack);
	pd->system->realloc(mod->points, 0);
	pd->system->realloc(mod, 0);

	pd->system->drawFPS(0,0);
	pd->graphics->drawText(number, 12, kASCIIEncoding, 0,30);

	return 1;
}
