#pragma once
namespace PROCON {
	extern void createWindowAfter(winClass *);
	//º‰∏Ù÷°
	extern void frame(winClass *);
	//ªÊ÷∆÷°
	extern void drawFrame(winClass *);
	extern void remove(winClass *);

	extern void event_Mousemove(winClass *w);
	extern void event_Mousedown(winClass *w);
	extern void event_Mouseup(winClass *w);
	extern void event_Mouseclick(winClass *w);
	extern void event_Mousewheel(winClass *w);
	extern void event_rMousedown(winClass *w);
	extern void event_rMouseup(winClass *w);
	extern void event_rMouseclick(winClass *w);
	extern void event_info_mouse_call(winClass*w, char * s);
	extern void loadInfo(winClass *wcls);
	extern thread t1;
	extern HANDLE eventInfo;

	//lua 
	extern BOOL loadEnd;

	extern sprite * loadSprite;
	extern void loadDrawCall(sprite *sp, winClass *app);
	extern string userKey;
	extern void userKeyCallEnd(string s, winClass * win);
}

