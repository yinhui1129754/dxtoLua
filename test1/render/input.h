//头文件
#include<Dinput.h>

//库文件
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#pragma once
extern class winClass;
class input
{
public:
	input();
	input(HWND);
	~input();
	string status = "input";

	//键盘循环
	char g_pKeyStateBuffer[256] = { 0 };
	//设备输入对象
	LPDIRECTINPUT8 g_pDirectInput = NULL;
	//键盘输入对象
	LPDIRECTINPUTDEVICE8 g_pKeyboardDevice = NULL;
	//事件循环
	void loop(winClass *);

	//初始化
	BOOL init(IDirectInputDevice8* pDIDevice, void* pBuffer, DWORD longlSize);
	

	//键盘data信息
	DIPROPDWORD dip;
	//新增键盘回调
	void addCall(int , void(*)(input*));
	//移除键盘回调
	void removeCall(void(*)(input*));

	void keyUp();
	//键盘code缓存
	vector<int>charArr;
	//code的回调函数
	vector<void(*)(input*)> callArr;

	BOOL isDown;
	BOOL isUp;
	BOOL centerBool;
};

