#pragma once

namespace testFrame {

	extern sprite * bg;
	extern sprite * bg2;
	extern sprite * bg3;


	
	extern void init(winClass *);
	extern void frame(winClass *);
	extern void remove(winClass *);
	
	extern void event_Mousemove(winClass *w);
	extern void event_Mouseclick(winClass *w);

	extern void hide(winClass *w );
	extern void show(winClass *w);
	/*extern void drawCall(sprite * sp, winClass *w);
	extern void drawCall2(sprite * sp, winClass *w);
	extern void drawCall3(sprite *sp, winClass *win);*/
	extern void event_Mousewheel(winClass *w);
}

