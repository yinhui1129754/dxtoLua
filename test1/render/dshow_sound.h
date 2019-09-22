#pragma once
#include "../stdafx.h"
enum DX_SHOW_ERROR_CODE {
	U_DX_SHOW_NO_ERROR = -1, //û�д�
	U_DX_SHOW_ERROR_CREATEBUILD = 0, //��������
	U_DX_SHOW_ERROR_CREATECONTROL = 1, //�����˲����ӿڳ���
	U_DX_SHOW_ERROR_CREATEEVENT = 2, //�����¼��������
	U_DX_SHOW_ERROR_READERFILE = 3, //�̲߳�����������
	U_DX_SHOW_ERROR_CREATESEEKING = 4, //����λ�ÿ��ƶ������
};

class dshow_sound
{

	
public:
	dshow_sound();
	~dshow_sound();
	BOOL PLAY_LOOP;
	HRESULT hr; // com���󷵻ص�hresult����
	IPin*pPin =NULL;
	IGraphBuilder *pGraph = NULL; //�ӿڻ�ȡ����
	IMediaControl *pControl = NULL; //�����˲�������
	IMediaEvent   *pEvent = NULL; //�¼��ӿ�
	IMediaSeeking *pConSeek = NULL;//���������˲���������ȵ�һ���ӿ�
	IBaseFilter * pBaseFilter;
	DX_SHOW_ERROR_CODE ERROR_CODE; //����code

	string path; //�ļ�path
	void createComObject(REFIID riid, void ** buf, DX_SHOW_ERROR_CODE code); //�����ӿڶ���
	static HRESULT GetPin(IBaseFilter * pFilter, PIN_DIRECTION dirrequired, int iNum, IPin **ppPin); //��ȡ
	static IPin * GetOutPin(IBaseFilter * pFilter, int nPin); //��ȡ���pin
	void playEnd(); //һ�β��Ž����Ļص�
	void play(string path,int type=0);//���ź���
	void play(const char * path); //���ź���
	void pause(); //��ͣ����
	thread pTh;//��ͣ�߳�
	thread cTh;//�����߳�

	void con();//��������
	static void threadCall(dshow_sound *); //�̻߳ص�
	static void pThreadCall(dshow_sound *); //�̻߳ص�
	static void cThreadCall(dshow_sound *); //�̻߳ص�
	long evCode; //�¼�code
	BOOL isRenderData; //�Ƿ��Ѿ�װ������
	BOOL isPause; //�Ƿ�����ͣ״̬
	BOOL pauseThreadIn; //�Ƿ�����ͣ�߳�
	BOOL conThreadIn; //�Ƿ��ڼ����߳�
	int pauseNum;
	int conNum;
	HANDLE cpEvent; //��ͣ�¼�
	HANDLE ccEvent; //�����¼�
	HANDLE pcEvent; //�����¼�
	thread th; //�̱߳���
};

