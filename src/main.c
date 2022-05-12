#include <stdio.h>
#include <stdlib.h>

#include <pd_api.h>

#include "fdm.h"
#include "gfx.h"
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

		// Note: If you set an update callback in the kEventInit handler, the system assumes the game is pure C and doesn't run any Lua code in the game
		pd->system->setUpdateCallback(update, pd);
		break;
		default:
		break;
	}
	return 0;
}

Point org = {150,150};

Point pts[] = {
	{100,100},
	{100,200},
	{200,200},
	{200,100}
};

Poly q = {
	4,
	pts
};
int rot = 0;

PDButtons current = 0;
PDButtons pushed = 0;
PDButtons released = 0;

static int update(void* userdata)
{
	PlaydateAPI* pd = userdata;

	// move shape
	pd->system->getButtonState(&current, &pushed, &released);
	if (current & kButtonLeft ) {ptranslate(&q, (Point){-5,0});org.x-=5;}
	if (current & kButtonRight) {ptranslate(&q, (Point){5, 0});org.x+=5;}
	if (current & kButtonUp   ) {ptranslate(&q, (Point){0,-5});org.y-=5;}
	if (current & kButtonDown ) {ptranslate(&q, (Point){0, 5});org.y+=5;}

	pd->graphics->clear(kColorWhite);
	pd->graphics->setFont(font);
	Poly* mod = protate(pd, &q, org, degrad(pd->system->getCrankAngle()));
	pdraw(pd, mod, kColorBlack);
	pd->system->realloc(mod->points, NULL);
	pd->system->realloc(mod, NULL);

	pd->system->drawFPS(0,0);
	pd->graphics->drawText(number, 12, kASCIIEncoding, 0,30);

	return 1;
}
