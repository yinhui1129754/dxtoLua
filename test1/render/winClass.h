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
	// ��Ϣ������Ҫ����Ĭ�ϴ�������Ҫ����0��ֹͣ����Ϣ���������򷵻�1
	virtual int HandleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
	// ԭʼ���ڹ���
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	// ��������
	void Create();
	void loop();
	void moveWindow(int x, int y, int w, int h);
	int width, height, x, y;
	int cWidth ,cHeight;
	void setCursor(LPSTR i= IDC_ARROW);
	LPSTR pointer;
	//�������
	oMap<string, ID2D1Bitmap *>systemInterface;
	D2D1_RECT_F closeRect;
	D2D1_RECT_F minRect;

	BOOL isMin = FALSE;
	BOOL isClose = FALSE;
	BOOL hoverClose = FALSE;
	BOOL hoverMin = FALSE;
	BOOL public_ismove = FALSE;
	RECT  startMouse = { 0 ,0,0,0 };
	RECT destopRect; //����ߴ�
	BOOL isRender = FALSE;

public:
	//����̨���
	BOOL isShowConsole;
	void winClass::showConsole();//����console����
	void winClass::hideConsole();//����console����
	void setWidth(float w);
	void setHeight(float w);
	int getWidth();
	int getHeight();
public:
	//��Ⱦ���
	content * cContent;

public:
	//timmer���
	vector<timmer *> tTimmerArr;

	void addTimmer(timmer *);

	void removeTimmer(timmer *);
public:
	//input���
	vector<input *> iInputArr;

	void addInput(input *);

	void removeInput(input *);


public:
	//���߳����
	HANDLE eventInfo; //�����߳�
	HANDLE eventInfo2; //�Ƴ��߳�
	HANDLE eventInfo3; //�����߳�
	HANDLE eventInfo4; //frame �߳�
	HANDLE removeEvent1;
	HANDLE removeEvent2;
	HANDLE removeEvent3;
	BOOL removeBool1 = FALSE;
	BOOL removeBool2 = FALSE;
	BOOL removeBool3 = FALSE;
	BOOL removeBool4 = FALSE;
	BOOL gameIsLoop;

	//���̼߳���ͼƬ 
	vector <thread *> loadImgThread;
	vector <utils::imgInfo *> loadImgImgInfo; //
	
	void loadImg(char * url, char * funcName);
public: 
	//ÿһ֮֡��ļ������
	DWORD msTime;
	DWORD newTime;
	DWORD oldTime;
	//click�¼�
	DWORD lClickTime;
	DWORD lClickNowTime;
	//click�¼�
	DWORD rClickTime;
	DWORD rClickNowTime;
	//lua ����ջ
	lua_State * L = luaL_newstate();
	mutex g_L;
	//��ǰ����
	DWORD nowFrame;
	POINT * mouse = new POINT();
	POINT * wheel = new POINT();
	//�Ƿ�����϶�
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
	//�¼���������
	oMap<string,vector<string>> eventTable;
public:
	//����
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
