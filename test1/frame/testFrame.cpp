#include "../stdafx.h"
#include "../render/fileClass.h"
#include "testFrame.h"
sprite * testFrame::bg = NULL; //±³¾°²ã
sprite * testFrame::bg2;//×îÏÂ²ã
sprite * testFrame::bg3; //ÊÓÍ¼²ã


sprite * spTest = NULL; //Åö×²²âÊÔ¾«Áé
sprite * spTest2 = NULL; //Åö×²²âÊÔ¾«Áé
//fileClass * fileInfo = new fileClass("umap/frame4.umap");//ÎÄ¼þ²Ù×÷¶ÔÏó
//map_class * mpClass = new map_class(0, 0, 20, 20); //µØÍ¼´¢´æ¶ÔÏó

//ÉùÒôdx ²âÊÔ 

void testFrame::init(winClass * win) {

	//fileInfo->toStart();
	//fileInfo->write(ss2.c_str());
	//fileInfo->write("user test");
	//fileInfo->readLine(d);
	/*bg = new sprite();
	bg2 = new sprite();
	bg3 = new sprite();*/
	//mpClass->setPointVal(0, 0, 10);
	//mpClass->setPointVal(1, 0, 9);
	//mpClass->setPointVal(0, 1, 8);
	//string ss= mpClass->toString();
	//fileInfo->toIndex(0);
	//fileInfo->write(ss.c_str());
	//mpClass->getFileAttr(fileInfo);
	//mpClass->initMap(mpClass->getKeyForString("mapClass"));
	//int aa = mpClass->getPointVal(0, 1);

	//fileInfo->write(mpClass->toString().c_str());
	/*string ss = fileInfo->readLine(0);
	string ss2 = fileInfo->readLine(3);
	string ss3 = fileInfo->readLine(0);
	string ss4 = fileInfo->readLine(0);*/
	/*spTest = new sprite(win->cContent->getSoucre("source/bq.png"));
	spTest2 = new sprite(win->cContent->getSoucre("source/bq.png"));
	
	spTest->initOneFrame(250, 200);
	spTest2->initOneFrame(250, 200,1);
	spTest2->setX(300);
	spTest2->setY(300);*/
	//spTest->initPointToRect();
/*	spTest->points.push_back({ 0.0f,0.0f });
	spTest->points.push_back({ 1.0f,0.0f });
	spTest->points.push_back({ 1.0,1.0f });
	spTest->points.push_back({ 0.0,1.0f });
	spTest2->points.push_back({ 0.0f,0.0f });
	spTest2->points.push_back({ 1.0f,0.0f });
	spTest2->points.push_back({ 1.0f,1.0f });
	spTest2->points.push_back({ 0.0f,1.0f });
	spTest->renderTranPoint = TRUE;
	spTest2->renderTranPoint = TRUE;
	spTest->angle = 30;

	bg->spriteType = "drawSprite";
	bg->drawCall = drawCall3;
	bg2->spriteType = "drawSprite";
	bg2->drawCall = drawCall;
	bg3->spriteType = "drawSprite";
	bg3->drawCall = drawCall2;
	bg2->addChild(spTest);

	bg2->addChild(spTest2);*/
	win->func_Mousemove[0] = event_Mousemove;

	//ÉùÒôdx²âÊÔ
	//DirectSoundCreate8(NULL, &m_pDS, NULL);
	//m_pDS->SetCooperativeLevel(win->hWnd, DSSCL_NORMAL);
	/*dshow_sound * dsTest = new dshow_sound();
	dsTest->PLAY_LOOP = TRUE;
	dsTest->pause();
	dsTest->play("music/bg1.wma");
	dsTest->con();*/
}
/*void  testFrame::drawCall(sprite *sp, winClass *win) {
	spTest->getTransitionPoints();
	spTest2->getTransitionPoints();

	if (win->col->obb(spTest2, spTest) ==TRUE) {
		win->cContent->drawText("collsion1", 0, 0);
	}
	
}
D2D1_POINT_2F d2dPf = D2D1::Point2F(100, 100);
D2D1_POINT_2F sP = D2D1::Point2F(0, 0);
D2D1_POINT_2F cP = D2D1::Point2F(0, 400);
D2D1_POINT_2F eP = D2D1::Point2F(800, 550);
float tF = 0.0f;
BOOL isAddE = TRUE;
void testFrame::drawCall3(sprite *sp, winClass *win) {
	d2dPf.x = win->col->bezierCurve(sP.x, cP.x, eP.x, tF);
	d2dPf.y = win->col->bezierCurve(sP.y, cP.y, eP.y, tF);
	ID2D1RadialGradientBrush * radio = win->cContent->createRadioBrush(
		D2D1::ColorF(0, 0, 0, 1),
		D2D1::ColorF(255, 255, 255, 0),
		d2dPf,
		30
	);
	if (tF <= 0.0f) {
		isAddE = TRUE;
		cP = D2D1::Point2F(0, 400);
	}
	else if (tF >= 1) {
		isAddE = FALSE;
		cP = D2D1::Point2F(400, 0);
	}
	if (isAddE) {
		tF += 0.01;
	}
	else {
		tF -= 0.01;
	}
	
	
	win->cContent->fillArc(d2dPf.x, d2dPf.y, 30, 30, radio);
	radio->Release();
}
void testFrame::drawCall2(sprite *sp, winClass *win) {
	for (unsigned int q = 0; q < bg2->children.size(); q++) {
		/*sprite * bufSpr = bg2->children[q];
		for (unsigned int i = 0; i < bufSpr->transitionPoints.size(); i++) {
			win->cContent->fillArc(bufSpr->transitionPoints[i].x, bufSpr->transitionPoints[i].y, 3, 3);
		}
	}
}*/
void testFrame::show(winClass * win) {
	//win->addSprite(bg);
	//win->addSprite(bg2);
	//win->addSprite(bg3);
	
	win->nowFrame = 0;
}

void testFrame::hide(winClass *w) {
	
};

void testFrame::event_Mousemove(winClass *w) {
/*	spTest->setX(w->mouse->x);
	spTest->setY(w->mouse->y);*/
}

void testFrame::event_Mouseclick(winClass *w) {

};
void testFrame::frame(winClass * win) {
	
};
void testFrame::remove(winClass * win) {

};
void testFrame::event_Mousewheel(winClass *win) {

}