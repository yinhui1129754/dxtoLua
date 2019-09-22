#pragma once
extern class mci_sound;
extern class btn_con;
extern class textBox;
extern class dialog_con;
extern class uppart_bg;
extern class bird_user;
extern class spriteSay_con;
namespace frame4 {

	extern sprite * bg;
	extern sprite * bg2;
	extern sprite * bg3;

	extern int STATUS;
	extern void init(winClass *);
	extern void frame(winClass *);
	extern void remove(winClass *);
	extern mci_sound * bgSound;

	extern oMap<string, ID2D1Bitmap *> imgInfo;
	extern void event_Mousemove(winClass *w);
	extern void event_Mouseclick(winClass *w);
	extern void event_Mousewheel(winClass *w);
	extern void event_Mousedown(winClass * w);
	extern void event_Mouseup(winClass * w);
	extern void reload();
	extern dialog_con * dialogA;
	extern oMap<string, sprite *> spriteInfo;
	extern void hide(winClass *w );
	extern void show(winClass *w);

}


