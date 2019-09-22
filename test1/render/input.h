//ͷ�ļ�
#include<Dinput.h>

//���ļ�
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

	//����ѭ��
	char g_pKeyStateBuffer[256] = { 0 };
	//�豸�������
	LPDIRECTINPUT8 g_pDirectInput = NULL;
	//�����������
	LPDIRECTINPUTDEVICE8 g_pKeyboardDevice = NULL;
	//�¼�ѭ��
	void loop(winClass *);

	//��ʼ��
	BOOL init(IDirectInputDevice8* pDIDevice, void* pBuffer, DWORD longlSize);
	

	//����data��Ϣ
	DIPROPDWORD dip;
	//�������̻ص�
	void addCall(int , void(*)(input*));
	//�Ƴ����̻ص�
	void removeCall(void(*)(input*));

	void keyUp();
	//����code����
	vector<int>charArr;
	//code�Ļص�����
	vector<void(*)(input*)> callArr;

	BOOL isDown;
	BOOL isUp;
	BOOL centerBool;
};

