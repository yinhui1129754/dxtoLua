#pragma once
extern class input;
extern class sprite;
extern class colVecEx;
class winClass
{
public:
	winClass();
	winClass(HINSTANCE hInst);
	~winClass();
public:
	char * szClassName;
	string status = "winClass";
	HWND hWnd;   
	HINSTANCE hInstance;
public:
	// 消息处理。需要后续默认处理则需要返回0；停止该消息后续处理，则返回1
	virtual int HandleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
	// 原始窗口过程
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	// 创建窗口
	void Create();
	void loop();
	void moveWindow(int x, int y, int w, int h);
	int width, height, x, y;
	int cWidth ,cHeight;
	void setCursor(LPSTR i= IDC_ARROW);
	LPSTR pointer;
	//界面相关
	oMap<string, ID2D1Bitmap *>systemInterface;
	D2D1_RECT_F closeRect;
	D2D1_RECT_F minRect;

	BOOL isMin = FALSE;
	BOOL isClose = FALSE;
	BOOL hoverClose = FALSE;
	BOOL hoverMin = FALSE;
	BOOL public_ismove = FALSE;
	RECT  startMouse = { 0 ,0,0,0 };
	RECT destopRect; //桌面尺寸
	BOOL isRender = FALSE;

public:
	//控制台相关
	BOOL isShowConsole;
	void winClass::showConsole();//创建console窗口
	void winClass::hideConsole();//隐藏console窗口
	void setWidth(float w);
	void setHeight(float w);
	int getWidth();
	int getHeight();
public:
	//渲染相关
	content * cContent;

public:
	//timmer相关
	vector<timmer *> tTimmerArr;

	void addTimmer(timmer *);

	void removeTimmer(timmer *);
public:
	//input相关
	vector<input *> iInputArr;

	void addInput(input *);

	void removeInput(input *);


public:
	//多线程相关
	HANDLE eventInfo; //输入线程
	HANDLE eventInfo2; //移除线程
	HANDLE eventInfo3; //输入线程
	HANDLE eventInfo4; //frame 线程
	HANDLE removeEvent1;
	HANDLE removeEvent2;
	HANDLE removeEvent3;
	BOOL removeBool1 = FALSE;
	BOOL removeBool2 = FALSE;
	BOOL removeBool3 = FALSE;
	BOOL removeBool4 = FALSE;
	BOOL gameIsLoop;

	//多线程加载图片 
	vector <thread *> loadImgThread;
	vector <utils::imgInfo *> loadImgImgInfo; //
	
	void loadImg(char * url, char * funcName);
public: 
	//每一帧之间的间隔属性
	DWORD msTime;
	DWORD newTime;
	DWORD oldTime;
	//click事件
	DWORD lClickTime;
	DWORD lClickNowTime;
	//click事件
	DWORD rClickTime;
	DWORD rClickNowTime;
	//lua 虚拟栈
	lua_State * L = luaL_newstate();
	mutex g_L;
	//当前场景
	DWORD nowFrame;
	POINT * mouse = new POINT();
	POINT * wheel = new POINT();
	//是否可以拖动
	BOOL isMoveFun();
	vector<D2D1_RECT_F> vrc;
	oMap<int, vector<D2D1_RECT_F>>nodrop_vrc;
	oMap<int, void(*)(winClass*)> func_Mousemove;
	oMap<int, void(*)(winClass*)> func_Mousedown;
	oMap<int, void(*)(winClass*)> func_Mouseup;
	oMap<int, void(*)(winClass*)> func_Mouseclick;
	oMap<int, void(*)(winClass*)> func_Mousewheel;
	oMap<int, void(*)(winClass*)> func_rMousedown;
	oMap<int, void(*)(winClass*)> func_rMouseup;
	oMap<int, void(*)(winClass*)> func_rMouseclick;
	oMap<int, void(*)(winClass*)> func_frame;
	oMap<int, void(*)(winClass*)> func_remove;
	//事件储存数组
	oMap<string,vector<string>> eventTable;
public:
	//精灵
	vector<sprite *> sSpriteArr;
	void addSprite(sprite *);
	void removeSprite(sprite *);
public:
	colVecEx * col;
};
namespace FUNASYNC {
	extern void timmerLoop(winClass * w);
	extern void inputLoop(winClass * w);
	extern void removeCall(winClass * w);
	extern void frameCall(winClass * w);
	extern thread t1;
	extern thread t2;
	extern thread t3;
	extern thread t4;
	extern void loadImgThreadCall(winClass * win,char * url, char * funcName, utils::imgInfo * info);
}
