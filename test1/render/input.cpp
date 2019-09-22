#include "../stdafx.h"



input::input() {

}
input::input(HWND hwnd)
{
	HRESULT hr;
	hr=DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (LPVOID *)&g_pDirectInput, NULL);
	if (FAILED(hr)) {
		MessageBox(NULL, "fail create input", "error", MB_OK);
	}
	hr=g_pDirectInput->CreateDevice(GUID_SysKeyboard, &g_pKeyboardDevice, NULL);
	if (FAILED(hr)) {
		MessageBox(NULL, "fail create device", "error", MB_OK);
	}
	hr=g_pKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);

	if (FAILED(hr))
	{
		MessageBox(NULL, "fail set format", "error", MB_OK);
	}
	hr=g_pKeyboardDevice->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	if (hr == DIERR_UNSUPPORTED)
	{
		MessageBox(NULL, "不支持设置的协作等级", "erro", 0);
		
	}
	if (FAILED(hr))
	{
		MessageBox(NULL, "设置协作等级失败", "erro",0);
		
	}
	this->isDown = FALSE;
	dip.diph.dwSize = sizeof(DIPROPDWORD);
	dip.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dip.diph.dwObj = 0;
	dip.diph.dwHow = DIPH_DEVICE;
	dip.dwData = 16;
	hr = g_pKeyboardDevice->SetProperty(DIPROP_BUFFERSIZE, &dip.diph);
	if (FAILED(hr))
	{
		return ;
	}
	g_pKeyboardDevice->Acquire();
	/*ZeroMemory(g_pKeyStateBuffer, sizeof(g_pKeyStateBuffer));
	init(g_pKeyboardDevice, (LPVOID)g_pKeyStateBuffer, sizeof(g_pKeyStateBuffer));*/



}

BOOL input::init(IDirectInputDevice8* pDIDevice, void* pBuffer, DWORD longlSize) {
	HRESULT hr;
	while (true)
	{
		pDIDevice->Poll();    //轮询设备
		pDIDevice->Acquire();
		if (SUCCEEDED(hr = pDIDevice->GetDeviceState(longlSize, pBuffer))) break;
		if (hr != DIERR_INPUTLOST || hr != DIERR_NOTACQUIRED) return false;
		if (FAILED(pDIDevice->Acquire())) return false;
	}

	return TRUE;

}
input::~input()
{

	g_pKeyboardDevice->Unacquire();
	g_pKeyboardDevice->Release();
}

void input::loop(winClass * wn) {
	g_pKeyboardDevice->Poll();
	g_pKeyboardDevice->Acquire();
	g_pKeyboardDevice->GetDeviceState(sizeof(g_pKeyStateBuffer), (LPVOID)g_pKeyStateBuffer);
	  isUp = FALSE;
	 centerBool = FALSE;
	if (this->isDown == TRUE) {
		isUp = TRUE;
	}
	for (int i = 0; i < this->charArr.size(); i++) {
		if ((g_pKeyStateBuffer[this->charArr[i]] & 0x80)) {
			this->callArr[i](this);
			this->isDown = TRUE;
			centerBool = TRUE;
		};
	}
	if (centerBool == FALSE) {
		this->isDown = FALSE;
	}
	if (this->isUp == TRUE&&this->isDown==FALSE) {
		this->keyUp();
	}
	
}
void input::keyUp() {

}
void input::addCall( int c, void (* call)(input*)) {
	this->charArr.push_back(c);
	this->callArr.push_back(call);
};
void input::removeCall(void(*call)(input*)) {
	int bufI = -1;
	for (int i = 0; i < this->callArr.size(); i++) {
		if (call == this->callArr[i]) {
			bufI = i;
			break;
		}
	}
	if (bufI == -1) {
		return;
	}
	vector<void(*)(input*)>::iterator s = find(callArr.begin(), callArr.end(), call);
	vector<int>::iterator s2 = find(charArr.begin(), charArr.end(), charArr[bufI]);
	callArr.erase(s);
	charArr.erase(s2);
	return;
};