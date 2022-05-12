#include <stdio.h>
#include <stdlib.h>

#include <pd_api.h>

#include "fdm.h"
#include "gfx.h"
#include "fd_strings.h"

static int update(void* userdata);
const char* fontpath = "/System/Fonts/Asheville-Sans-14-Bold.pft";
LCDFont* font = NULL;
int cnt = 0;

#ifdef _WINDLL
__declspec(dllexport)
#endif
int eventHandler(PlaydateAPI* pd, PDSystemEvent event, uint32_t arg)
{
	(void)arg; // arg is currently only used for event = kEventKeyPressed

	if ( event == kEventInit )
	{
		const char* err;
		font = pd->graphics->loadFont(fontpath, &err);
		
		if ( font == NULL )
			pd->system->error("%s:%i Couldn't load font %s: %s", __FILE__, __LINE__, fontpath, err);

		// Note: If you set an update callback in the kEventInit handler, the system assumes the game is pure C and doesn't run any Lua code in the game
		pd->system->setUpdateCallback(update, pd);
	} else if (event==kEventKeyPressed) {
		cnt = 1;
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

static int update(void* userdata)
{
	PlaydateAPI* pd = userdata;
	
	pd->graphics->clear(kColorWhite);
	pd->graphics->setFont(font);

	Poly* mod = protate(pd, &q, org, degrad(rot));
	pdraw(pd, mod, kColorBlack);
	pd->system->realloc(mod, 0);
	rot += 1;

	pd->system->drawFPS(0,0);

	return 1;
}

