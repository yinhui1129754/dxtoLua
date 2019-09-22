#include "../stdafx.h"
#include "frame1.h"
#include "frame3.h"
#include "frame4.h"
#include "../system/system.h"
#include "../class/star_bg.h"
#include "../class/btn_con.h"
#include "../class/textBox.h"
#include "../class/dialog_con.h"
#include "../class/uppart_bg.h"
#include "../class/bird_user.h"
#include "../class/spriteSay_con.h"
sprite * frame4::bg; //最下层
sprite * frame4::bg2;//第二层
sprite * frame4::bg3; //第三层
int frame4::STATUS  = 0; //场景状态
mci_sound * frame4::bgSound = NULL;//背景音乐
dialog_con * frame4::dialogA = NULL; //对话框
oMap<string, ID2D1Bitmap *> frame4::imgInfo; //图片信息
oMap<string, sprite *> frame4::spriteInfo; //精灵信息


void frame4::init(winClass * win) {
	
}
void frame4::event_Mousedown(winClass * w) {
	
};
void frame4::event_Mouseup(winClass * w) {

};
void frame4::event_Mousewheel(winClass *w) {
	
};
void frame4::show(winClass * win) {
	
}

void frame4::hide(winClass *w) {
	
};

void frame4::frame(winClass * win) {

};



void frame4::remove(winClass * win) {
	
};



void frame4::reload() {


}
void frame4::event_Mousemove(winClass *w) {
	
}
void frame4::event_Mouseclick(winClass *w) {

};