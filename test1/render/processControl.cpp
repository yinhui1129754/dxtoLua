
#include "../stdafx.h"
#include "processControl.h"
#include "../system/system.h"
#include "../frame/testFrame.h"
#include "../system/ulua_prototype.h"
HANDLE PROCON::eventInfo;
thread PROCON::t1;
sprite * PROCON::loadSprite = NULL;
string sssss = "灰灰世界";
D2D_SIZE_F ssssssize;
BOOL PROCON::loadEnd = FALSE;
string PROCON::userKey;
void PROCON::loadInfo(winClass *wcls) {
	//加载非常重要的系统资源
	wcls->systemInterface["close"] = wcls->cContent->getSoucre(L"source/system/close.png");
	wcls->systemInterface["minbtn"] = wcls->cContent->getSoucre(L"source/system/sx.png");
	wcls->isClose = TRUE;
	wcls->isMin = TRUE;
	//加载界面资源
	systemInfo::initSource(wcls);
	//显示场景资源
	testFrame::init(wcls);
	

	Sleep(1000);
	SetEvent(PROCON::eventInfo);
	WaitForSingleObject(PROCON::eventInfo, INFINITE);
	wcls->removeSprite(loadSprite);
	
	//log
	utils::console::ipt2(userKey);
	testFrame::show(wcls);
	loadEnd = TRUE;
	//FreeConsole();
};
void PROCON::userKeyCallEnd(string s, winClass * win) {
	if (!win->isShowConsole) {
		return;
	}
	int error = luaL_loadbuffer(win->L, s.c_str(), s.length(), "line") ||
		lua_pcall(win->L, 0, 0, 0);
	if (error) {
		string s2 = lua_tostring(win->L, -1);
		s2 = s2 + " code:" + s;
		utils::luaError((char *)s2.c_str(), win->L);
		lua_pop(win->L, 1);  /* pop error message from the stack */
	}
	userKey = "";
	utils::console::ipt2(userKey);
};
void PROCON::createWindowAfter(winClass * wcls) {
	//wcls->showConsole();
	loadSprite = new sprite();
	loadSprite->spriteType = "drawSprite";
	loadSprite->drawCall = loadDrawCall;
	wcls->nowFrame = 0;
	wcls->addSprite(loadSprite);
	//1.创建Lua状态
	wcls->L = luaL_newstate();
	if (wcls->L == NULL)
	{
		return;
	}
	/* 载入Lua基本库 */
	ulua_prototype::registerCall(wcls->L, wcls);
	luaL_openlibs(wcls->L);
	lua_checkstack(wcls->L, 1000);
	/* 载入自定义函数库*/
	int bRet = luaL_loadfile(wcls->L, "script/main.lua");

	PROCON::eventInfo = CreateEvent(NULL, FALSE, FALSE, NULL);
	/*
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	WriteConsole(output, "hello world", sizeof("hello world"), NULL, NULL);
	HANDLE input = GetStdHandle(STD_INPUT_HANDLE);
	char  test[2];
	DWORD uInt;
	ReadConsole(input, test, 2, &uInt, NULL);
	ResetEvent(PROCON::eventInfo);*/
	PROCON::t1 = thread(PROCON::loadInfo, wcls);//加载资源线程
	utils::console::nowEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	//ResetEvent(utils::console::nowEvent);
	//ResetEvent(utils::console::nowEvent);
	utils::console::end = FALSE;
	utils::console::conThread = thread(utils::console::iptCall, wcls);
	utils::console::iptEnd = userKeyCallEnd;
	if (bRet)
	{
		utils::AlertOut("load file error",0);
		return;
	}
	bRet = lua_pcall(wcls->L, 0, 0, 0);
	if (bRet)
	{
		string s2 = lua_tostring(wcls->L, -1);
		s2 ="pcall error\n"+ s2;
		utils::AlertOut(s2.c_str(), 0);
		return;
	}
	
	//utils::getTable(wcls->L, "tableTest");
	//testFrame::init(wcls);
	//testFrame::show(wcls);
}
void PROCON::drawFrame(winClass * w) {
	std::lock_guard<std::mutex> lock(w->g_L);
	if (loadEnd) {
		/*int bRet = 0;
		lua_getglobal(w->L, "drawFrame");
		bRet = lua_pcall(w->L, 0, 0, 0);
		if (bRet)
		{
			string s2 = lua_tostring(w->L, -1);
			s2 = "pcall error\n" + s2;
			utils::AlertOut(s2.c_str(), 0);
			return;
		}*/
		
		utils::luaCall(w, "drawFrame");
		//lua_call(w->L, 0, 0);
	}
	
};
void PROCON::loadDrawCall(sprite *sp, winClass *app) {
	app->cContent->fillStyle(0x000000,1.0);
	app->cContent->fillRect(0, 0, app->cWidth, app->cHeight);
	app->cContent->strokeStyle(0xffffff, 1.0);
	app->cContent->getTextInfo(sssss, ssssssize);
	app->cContent->drawText(sssss, app->cWidth/2- ssssssize.width/2, app->cHeight/2-10- ssssssize.height / 2);
};
void PROCON::frame(winClass * w) {
	/*if (w->func_frame[w->nowFrame] != NULL) {
		w->func_frame[w->nowFrame](w);
	};*/
	std::lock_guard<std::mutex> lock(w->g_L);
	if (loadEnd) {
		utils::luaCall(w, "frame");
		/*lua_getglobal(w->L, "frame");
		lua_call(w->L, 0, 0);*/
	}
	/*HWND hwnd = GetConsoleWindow();
	RECT rc;
	GetClientRect(hwnd, &rc);
	InvalidateRect(hwnd, &rc, TRUE);*/
};
void PROCON::remove(winClass *w) {
	if (w->func_remove[w->nowFrame] != NULL) {
		w->func_remove[w->nowFrame](w);
	}
}

void PROCON::event_info_mouse_call(winClass*w, char * s) {
	string ss = s;
	vector<string> eventArr = w->eventTable[ss];

	if (eventArr.size()) {
		for (int i = 0; i < eventArr.size(); i++) {
			lua_getglobal(w->L, eventArr[i].c_str());
			lua_pushnumber(w->L, w->mouse->x);
			lua_pushnumber(w->L, w->mouse->y);
			int bRet = 0;
			bRet = lua_pcall(w->L, 2, 0, 0);
			if (bRet)
			{
				string s2 = lua_tostring(w->L, -1);
				s2 = "pcall error\n" + s2;
				utils::AlertOut(s2.c_str(), 0);
				return;
			}
		}
	}
};
void PROCON::event_Mousemove(winClass *w) {
	event_info_mouse_call(w, "mousemove");
	/*if (w->func_Mousemove[w->nowFrame] != NULL) {
		w->func_Mousemove[w->nowFrame](w);
	};*/
	
}
void PROCON::event_Mousedown(winClass *w) {
	event_info_mouse_call(w, "mousedown");
	/*if (w->func_Mousedown[w->nowFrame] != NULL) {
		w->func_Mousedown[w->nowFrame](w);
	};*/
};
void PROCON::event_Mouseup(winClass *w) {
	event_info_mouse_call(w, "mouseup");
	/*if (w->func_Mouseup[w->nowFrame] != NULL) {
		w->func_Mouseup[w->nowFrame](w);
	};*/
};
void PROCON::event_Mouseclick(winClass * w) {
	event_info_mouse_call(w, "click");
	/*if (w->func_Mouseclick[w->nowFrame] != NULL) {
		w->func_Mouseclick[w->nowFrame](w);
	};*/
}
void PROCON::event_rMousedown(winClass *w) {
	event_info_mouse_call(w, "rMousedown");
	/*if (w->func_rMousedown[w->nowFrame] != NULL) {
		w->func_rMousedown[w->nowFrame](w);
	};*/
};
void PROCON::event_rMouseup(winClass *w) {
	event_info_mouse_call(w, "rMouseup");
	/*if (w->func_rMouseup[w->nowFrame] != NULL) {
		w->func_rMouseup[w->nowFrame](w);
	};*/
};
void PROCON::event_rMouseclick(winClass * w) {
	event_info_mouse_call(w, "rClick");
	/*if (w->func_rMouseclick[w->nowFrame] != NULL) {
		w->func_rMouseclick[w->nowFrame](w);
	};*/
}
void PROCON::event_Mousewheel(winClass *w) {
	event_info_mouse_call(w, "mousewheel");
	/*if (w->func_Mousewheel[w->nowFrame] != NULL) {
		w->func_Mousewheel[w->nowFrame](w);
	};*/
};