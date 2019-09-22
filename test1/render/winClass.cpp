#include "../stdafx.h"
#include "processControl.h"


thread FUNASYNC::t1;
thread FUNASYNC::t2;
thread FUNASYNC::t3;
thread FUNASYNC::t4;
void winClass::addTimmer(timmer * t) {
	this->tTimmerArr.push_back(t);
}
void winClass::removeTimmer(timmer * t) {
	utils::vecRemove(this->tTimmerArr, t);
}
winClass::winClass(HINSTANCE hInst)
{
	this->hWnd = NULL;
	this->hInstance = hInst;
	this->szClassName = "gameWndClass";
	this->gameIsLoop = TRUE;
	eventInfo = CreateEvent(NULL, FALSE, FALSE, NULL);
	eventInfo2 = CreateEvent(NULL, FALSE, FALSE, NULL);
	removeEvent1 = CreateEvent(NULL, FALSE, FALSE, NULL);
	removeEvent2 = CreateEvent(NULL, FALSE, FALSE, NULL);
	removeEvent3 = CreateEvent(NULL, FALSE, FALSE, NULL);
	eventInfo3 = CreateEvent(NULL, FALSE, FALSE, NULL);
	eventInfo4 = CreateEvent(NULL, FALSE, FALSE, NULL);
	this->msTime = 0;
	this->oldTime = 0;
	this->newTime = 0;
	this->width=800;
	this->height = 550;
	this->col = new colVecEx();
	this->closeRect = D2D1::RectF(this->width-30,0,30,30);
	this->minRect = D2D1::RectF(this->width-60, 0, 30, 30);
	this->destopRect = { 0,0,0,0 };
	this->destopRect.left = 0;
	this->destopRect.top = 0;
	this->destopRect.right=GetSystemMetrics(SM_CXSCREEN);
	this->destopRect.bottom = GetSystemMetrics(SM_CYSCREEN);
	

		
	this->removeBool1 = TRUE;
	this->removeBool2 = TRUE;
	this->removeBool3 = TRUE;
	this->removeBool4 = TRUE;
	
}
void winClass::moveWindow(int x, int y, int w, int h) {
	MoveWindow(hWnd, x, y, w, h, TRUE);
}
winClass::winClass() {

}
void FUNASYNC::loadImgThreadCall(winClass * win, char * url, char * funcName, utils::imgInfo * info) {
	win->cContent->getSoucre(url);
	lua_getglobal(win->L, funcName);
	info->isLoad = TRUE;
	lua_call(win->L, 0, 0);
};
void winClass::loadImg(char * url, char * funcName) {
	utils::imgInfo * info = new utils::imgInfo;
	info->isLoad = FALSE;
	info->threadId = utils::GetId();

	thread * th = new thread(FUNASYNC::loadImgThreadCall,this,url,funcName,info);
	this->loadImgImgInfo.push_back(info);
	this->loadImgThread.push_back(th);

};

winClass::~winClass()
{
	if (this->hWnd != NULL && ::IsWindow(this->hWnd)) // C++对象被销毁之前，销毁窗口对象
	{
		::DestroyWindow(this->hWnd);  // Tell system to destroy hWnd and Send WM_DESTROY to wndproc
	}
}
void winClass::Create() {
		//注册窗口类
		WNDCLASSEX wcex;
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW| CS_DROPSHADOW;
		wcex.lpfnWndProc = winClass::WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = this->hInstance;
		wcex.hIcon = NULL;
		wcex.hCursor = ::LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = szClassName;
		wcex.hIconSm = NULL;

		::RegisterClassEx(&wcex);
	// 创建窗口
	if (this->hWnd == NULL)
	{
		hWnd = ::CreateWindowEx(NULL,szClassName,
			"最无聊的游戏",
			WS_POPUP| WS_VISIBLE,
			this->x, this->y, this->width, this->height,
			NULL,
			NULL,
			hInstance,
			(LPVOID)this
		);
		if (hWnd == NULL)
		{
			char msg[100];
			::wsprintf(msg, "CreateWindow()失败:%ld", ::GetLastError());
			::MessageBox(NULL, msg, "错误", MB_OK);
			return;
		}
		else {
		
			ShowWindow(hWnd,SW_SHOW);
			UpdateWindow(hWnd);
			this->cContent = new content(this->hWnd);
			FUNASYNC::t1= thread(FUNASYNC::timmerLoop, this);
			FUNASYNC::t2 = thread(FUNASYNC::removeCall, this);
			FUNASYNC::t3 = thread(FUNASYNC::inputLoop, this);
			FUNASYNC::t4 = thread(FUNASYNC::frameCall, this);
			RECT rc;
			this->nowFrame = 1;
			GetClientRect(hWnd, &rc);
			this->cWidth = rc.right - rc.left;
			this->cHeight = rc.bottom - rc.top;
			PROCON::createWindowAfter(this);
		}
		
	}

}
void FUNASYNC::frameCall(winClass * w) {
	while (w->gameIsLoop) {
		//死循环多线程方便操作
		WaitForSingleObject(w->eventInfo4, INFINITE);
		ResetEvent(w->eventInfo4);
		ResetEvent(w->removeEvent3);
		w->removeBool1 =FALSE;
		PROCON::frame(w);
		w->removeBool1 = TRUE;
		SetEvent(w->removeEvent3);
	}
}
void FUNASYNC::timmerLoop(winClass * w) {
	while (w->gameIsLoop) {
		//死循环多线程方便操作
		WaitForSingleObject(w->eventInfo, INFINITE);
		ResetEvent(w->eventInfo);
		ResetEvent(w->removeEvent1);
		w->removeBool2 = FALSE;
		for (int i = 0; i < w->tTimmerArr.size(); i++) {
			w->tTimmerArr[i]->loop(w);
		}
		w->removeBool2 = TRUE;
		SetEvent(w->removeEvent1);
	}
	
}
void FUNASYNC::inputLoop(winClass * w) {
	while (w->gameIsLoop) {
		//死循环多线程方便操作
		WaitForSingleObject(w->eventInfo3, INFINITE);
		ResetEvent(w->eventInfo3);
		ResetEvent(w->removeEvent2);
		w->removeBool3 = FALSE;
		for (int i = 0; i < w->iInputArr.size(); i++) {
			w->iInputArr[i]->loop(w);
		}
		w->removeBool3 = TRUE;
		SetEvent(w->removeEvent2);
	}
}
void FUNASYNC::removeCall(winClass * w) {
	while (w->gameIsLoop) {
		WaitForSingleObject(w->eventInfo2, INFINITE);
		WaitForSingleObject(w->removeEvent1, INFINITE);
		//移除精灵的同步对象
		WaitForSingleObject(w->removeEvent2, INFINITE);
		WaitForSingleObject(w->removeEvent3, INFINITE);
		ResetEvent(w->eventInfo2);
		ResetEvent(w->removeEvent1);
		ResetEvent(w->removeEvent2);
		ResetEvent(w->removeEvent3);
		for (unsigned int i = 0; i < w->loadImgImgInfo.size(); i++) {
			if (w->loadImgImgInfo[i]->isLoad) {
				thread * bufThread = w->loadImgThread[i];
				utils::vecRemove(w->loadImgThread, bufThread);
				bufThread->join();
				delete bufThread;
				bufThread = NULL;
				utils::imgInfo  * bufImgInfo = w->loadImgImgInfo[i];
				utils::vecRemove(w->loadImgImgInfo, w->loadImgImgInfo[i]);
				delete bufImgInfo;
				bufImgInfo = NULL;
			}
		}
		//移除操作
		if (w->removeBool1&&w->removeBool2&&w->removeBool3&&w->removeBool4) {
			PROCON::remove(w);
		}
		
	}
}
/*显示控制台*/
void winClass::showConsole() {

	AllocConsole();
	HWND hwnd = GetConsoleWindow();
	RECT rc;
	GetWindowRect(this->hWnd, &rc);
	MoveWindow(this->hWnd, rc.left, rc.top - 150, this->width, this->height + 300, TRUE);
	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_CAPTION);
	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_MAXIMIZEBOX);
	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_MINIMIZEBOX);
	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_SIZEBOX);
	SetParent(hwnd, this->hWnd);

	this->cContent->m_render->Resize(D2D1::SizeU(this->width, this->height + 300));

	MoveWindow(hwnd, 0, this->height, this->width, 300, true);
	isShowConsole = TRUE;
	string s = "lua console \nauthor: huihuishijie\ndate: 2019-09-03 \nversion: 1.0.0\n";
	utils::console::log(s);
}
/*隐藏控制台*/
void winClass::hideConsole() {
	FreeConsole();
	HWND hwnd = GetConsoleWindow();
	RECT rc;
	GetWindowRect(this->hWnd, &rc);
	MoveWindow(this->hWnd, rc.left, rc.top+150, this->width, this->height, TRUE);
	this->cContent->m_render->Resize(D2D1::SizeU(this->width, this->height));
	isShowConsole = FALSE;
}
/*设置窗口宽度*/
void winClass::setWidth(float w) {
	this->width = w;
	float height = this->height;
	if (this->isShowConsole) {
		height = height + 300;
		HWND hwnd = GetConsoleWindow();
		MoveWindow(hwnd, 0, this->height, this->width, 300, true);
	}
	RECT clientRc;
	GetWindowRect(GetDesktopWindow(), &clientRc);
	RECT rc;
	GetWindowRect(this->hWnd, &rc);
	int clientWidth = clientRc.right - clientRc.left;
	MoveWindow(this->hWnd, (clientWidth-w)/2, rc.top, this->width, height, TRUE);
	this->cContent->m_render->Resize(D2D1::SizeU(this->width, height));
	this->closeRect = D2D1::RectF(this->width - 30, 0, 30, 30);
	this->minRect = D2D1::RectF(this->width - 60, 0, 30, 30);
};
/*设置窗口高度*/
void winClass::setHeight(float h) {
	this->height = h;
	float height = h ;
	if (this->isShowConsole) {
		height = h + 300;
		HWND hwnd = GetConsoleWindow();
		MoveWindow(hwnd, 0, this->height, this->width, 300, true);
	}
	RECT clientRc;
	GetWindowRect(GetDesktopWindow(), &clientRc);
	RECT rc;
	GetWindowRect(this->hWnd, &rc);
	int clientHeight = clientRc.bottom - clientRc.top;
	MoveWindow(this->hWnd, (clientHeight - h) / 2, rc.top, this->width, height, TRUE);
	this->cContent->m_render->Resize(D2D1::SizeU(this->width, height));
	this->closeRect = D2D1::RectF(this->width - 30, 0, 30, 30);
	this->minRect = D2D1::RectF(this->width - 60, 0, 30, 30);
};
int winClass::getWidth() {
	return this->width;
}
int winClass::getHeight() {
	int h = this->height;
	if (this->isShowConsole) {
		h = h + 300;
	}
	return h;
}
/*设置鼠标图标*/
void winClass::setCursor(LPSTR i) {
	this->pointer = i;
	SetClassLong(this->hWnd, GCL_HCURSOR, (LONG)LoadCursor(NULL,i));
}
void winClass::loop() {
	MSG msg;
	// 主消息循环:
	while (TRUE)
	{
		
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) {
				this->gameIsLoop = FALSE;
				//线程同步 关闭进程
				SetEvent(this->removeEvent1);
				SetEvent(this->eventInfo);
				SetEvent(this->eventInfo2);
				SetEvent(this->eventInfo3);
				SetEvent(this->removeEvent2);
				SetEvent(this->eventInfo4);
				SetEvent(this->removeEvent3);
				
				FUNASYNC::t1.join();
				FUNASYNC::t2.join();
				FUNASYNC::t3.join();
				FUNASYNC::t4.join();
				PROCON::t1.join();
			
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		
		size_t i;
		
		

		this->removeBool4 = FALSE;
		this->cContent->beginDraw();

		//计时
		if (this->newTime - this->oldTime < 5) {
			Sleep(2);
		}
		if (this->newTime > this->oldTime) {
			this->msTime = this->newTime - this->oldTime;
		}
		this->oldTime = this->newTime;
		this->newTime = GetTickCount();

		if (this->isRender) {
			this->removeBool4 = TRUE;
			SetEvent(this->eventInfo4);
			SetEvent(this->eventInfo2);
			SetEvent(this->eventInfo);
			SetEvent(this->eventInfo3);
			continue;
		}
		this->cContent->clear();
		for (i = 0; i < this->sSpriteArr.size(); i++) {
			this->sSpriteArr[i]->render(this);
		}
		PROCON::drawFrame(this);
		if (this->isMin) {
			if (this->hoverMin) {
				this->cContent->fillStyle(0xffffff, 0.3);
				this->cContent->fillRect(minRect.left, minRect.top, minRect.right, minRect.bottom);
			}
			this->cContent->drawImage(this->systemInterface["minbtn"], minRect.left, minRect.top, minRect.right, minRect.bottom);
		}
		if (this->isClose || this->isMin) {
			if (this->hoverClose) {
				this->cContent->fillStyle(0xff0000, 0.7);
				this->cContent->fillRect(closeRect.left, closeRect.top, closeRect.right, closeRect.bottom);
			}
			this->cContent->drawImage(this->systemInterface["close"], closeRect.left, closeRect.top, closeRect.right, closeRect.bottom);

		}
		this->removeBool4 = TRUE;
		SetEvent(this->eventInfo4);
		SetEvent(this->eventInfo2);
		SetEvent(this->eventInfo);
		SetEvent(this->eventInfo3);
		this->cContent->closeDraw();
	
		

	}
};
int winClass::HandleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {


	return 0;
};
BOOL winClass::isMoveFun() {
	if (utils::inRect(this->mouse, &this->minRect) && this->isMin) {
		return FALSE;
	}
	if (utils::inRect(this->mouse, &this->closeRect) && (this->isClose || this->isMin)) {
		return FALSE;
	}
	for (size_t i = 0; i < nodrop_vrc[this->nowFrame].size(); i++) {
		if (utils::inRect(this->mouse, &(nodrop_vrc[this->nowFrame][i]))) {
			return FALSE;
		}
	}
	return TRUE;
}
LRESULT CALLBACK winClass::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	winClass* pObj = NULL;
	RECT topRect;
	GetWindowRect(hWnd, &topRect);
	LRESULT result;
	
	if (message == WM_CREATE)	// 在此消息收到时，把窗口对象句柄赋给C++对象成员，同时把C++对象地址赋给窗口对象成员
	{
		pObj = (winClass*)(((LPCREATESTRUCT)lParam)->lpCreateParams);
		pObj->hWnd = hWnd;	                                         // 在此处获取HWND，此时CreateWindow()尚未返回。
		::SetWindowLong(hWnd, GWL_USERDATA, (LONG)pObj);             // 通过USERDATA把HWND和C++对象关联起来
		DWORD dwStyle = GetClassLong(hWnd, GCL_STYLE);
		SetClassLong(hWnd, GCL_STYLE, dwStyle | CS_DROPSHADOW);
		pObj->moveWindow((pObj->destopRect.right - pObj->width) / 2, (pObj->destopRect.bottom - pObj->height) / 2, pObj->width, pObj->height);
		SystemParametersInfo(SPI_SETDROPSHADOW, 0, (PVOID)true, SPIF_UPDATEINIFILE);
	}
	pObj = (winClass*)::GetWindowLong(hWnd, GWL_USERDATA);
	switch (message)
	{
	case WM_SIZE:
	{
		int nWidth = LOWORD(lParam); // width of client area
		int nHeight = HIWORD(lParam); // height of client area
		if (nWidth != pObj->getWidth()) {
			pObj->setWidth(pObj->width);
		}
		if (nHeight != pObj->getHeight()) {
			pObj->setHeight(pObj->height);
		}
		return DefWindowProc(hWnd, message, wParam, lParam);
		
	}
	case WM_CREATE:
		pObj->HandleMessage(hWnd, message, wParam, lParam);

		break;
	case WM_DESTROY:
		if (pObj != NULL)  // 此时，窗口对象已经销毁，通过设置hWnd=NULL，来通知C++对象
		{
			pObj->hWnd = NULL;
			
		}
		PostQuitMessage(0);
		break;
	case WM_ERASEBKGND:
		break;
	case WM_MOUSEMOVE:
		pObj->mouse->x = LOWORD(lParam);
		pObj->mouse->y = HIWORD(lParam);
		if (pObj->isMin) {
			if (utils::inRect(pObj->mouse, &pObj->minRect)) {
				pObj->setCursor(IDC_HAND);
				pObj->hoverClose = FALSE;
				pObj->hoverMin = TRUE;
				break;
			}
			else {
				pObj->hoverMin = FALSE;
				pObj->setCursor(IDC_ARROW);
			}
		}
		if (pObj->isClose || pObj->isMin) {
			if (utils::inRect(pObj->mouse, &pObj->closeRect)) {
				pObj->setCursor(IDC_HAND);

				pObj->hoverClose = TRUE;
				break;
			}
			else {
				pObj->setCursor(IDC_ARROW);
				pObj->hoverClose = FALSE;
			}
		}
		PROCON::event_Mousemove(pObj);
		break;
	case WM_LBUTTONDOWN:
		
		pObj->lClickTime = GetTickCount();
		pObj->lClickNowTime = pObj->lClickTime;
		PROCON::event_Mousedown(pObj);
		if (pObj->mouse->y < 30) {
			
			pObj->public_ismove = TRUE;
			pObj->startMouse.left = pObj->mouse->x+ topRect.left;
			pObj->startMouse.top = pObj->mouse->y+ topRect.top;
			pObj->startMouse.right = topRect.left;
			pObj->startMouse.bottom = topRect.top;
			if (pObj->isMoveFun()) {
				PostMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(pObj->startMouse.left, pObj->startMouse.top));
			}
		
		}
		break;
	
	case WM_SYSCOMMAND:

		if (SC_MINIMIZE == wParam) {
			pObj->isRender = TRUE;
			return DefWindowProc(hWnd, message, wParam, lParam);
			 
		}
		pObj->isRender = FALSE;
		return DefWindowProc(hWnd, message, wParam, lParam);
	case WM_LBUTTONUP:
		PROCON::event_Mouseup(pObj);
		pObj->lClickNowTime = GetTickCount();
		if (pObj->lClickNowTime - pObj->lClickTime < 300) {
			PROCON::event_Mouseclick(pObj);
			if (utils::inRect(pObj->mouse, &pObj->minRect)&& pObj->isMin) {
				SendMessage(hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
			}
			if (utils::inRect(pObj->mouse, &pObj->closeRect)&&(pObj->isClose||pObj->isMin)) {
				SendMessage(hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
			}
		}

		break;
	case WM_RBUTTONDOWN:
		pObj->rClickTime = GetTickCount();
		pObj->rClickNowTime = pObj->rClickTime;
		PROCON::event_rMousedown(pObj);
		break;
	case WM_RBUTTONUP:
		PROCON::event_rMouseup(pObj);
		pObj->rClickNowTime = GetTickCount();
		if (pObj->rClickNowTime - pObj->rClickTime < 300) {
			PROCON::event_rMouseclick(pObj);
		}
		break;
	case WM_CLOSE:
		utils::console::end = TRUE;
		SetEvent(utils::console::nowEvent);
		PostMessage(GetConsoleWindow(), WM_CHAR, 13, 0);
		utils::console::conThread.join();
		PostMessage(hWnd, WM_QUIT, 0, 0);
		break;
	case WM_MOUSEWHEEL:
		pObj->wheel->x=(short)HIWORD(wParam); //滚动方向信息
		pObj->wheel->y = LOWORD(wParam); //按键信息
		PROCON::event_Mousewheel(pObj);
		break;

		
	default:
		pObj = (winClass*)::GetWindowLong(hWnd, GWL_USERDATA);
		if (pObj != NULL)
		{
			if (pObj->HandleMessage(hWnd, message, wParam, lParam) == 0) // 调用子类的消息处理虚函数
			{
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		
		}
		else
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	}
	return 0;
}
void winClass::addInput(input * d) {
	this->iInputArr.push_back(d);
}
void winClass::removeInput(input * d) {
	utils::vecRemove(this->iInputArr, d);
}
void winClass::addSprite(sprite * d) {
	this->sSpriteArr.push_back(d);
}
void winClass::removeSprite(sprite  * d) {
	utils::vecRemove(this->sSpriteArr, d);
}