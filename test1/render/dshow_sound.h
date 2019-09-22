#pragma once
#include "../stdafx.h"
enum DX_SHOW_ERROR_CODE {
	U_DX_SHOW_NO_ERROR = -1, //没有错
	U_DX_SHOW_ERROR_CREATEBUILD = 0, //创建出错
	U_DX_SHOW_ERROR_CREATECONTROL = 1, //创建滤波器接口出错
	U_DX_SHOW_ERROR_CREATEEVENT = 2, //创建事件对象出错
	U_DX_SHOW_ERROR_READERFILE = 3, //线程播放声音出错
	U_DX_SHOW_ERROR_CREATESEEKING = 4, //创建位置控制对象错误
};

class dshow_sound
{

	
public:
	dshow_sound();
	~dshow_sound();
	BOOL PLAY_LOOP;
	HRESULT hr; // com对象返回的hresult对象
	IPin*pPin =NULL;
	IGraphBuilder *pGraph = NULL; //接口获取对象
	IMediaControl *pControl = NULL; //声音滤波器对象
	IMediaEvent   *pEvent = NULL; //事件接口
	IMediaSeeking *pConSeek = NULL;//控制声音滤波器对象进度的一个接口
	IBaseFilter * pBaseFilter;
	DX_SHOW_ERROR_CODE ERROR_CODE; //错误code

	string path; //文件path
	void createComObject(REFIID riid, void ** buf, DX_SHOW_ERROR_CODE code); //创建接口对象
	static HRESULT GetPin(IBaseFilter * pFilter, PIN_DIRECTION dirrequired, int iNum, IPin **ppPin); //获取
	static IPin * GetOutPin(IBaseFilter * pFilter, int nPin); //获取输出pin
	void playEnd(); //一次播放结束的回调
	void play(string path,int type=0);//播放函数
	void play(const char * path); //播放函数
	void pause(); //暂停函数
	thread pTh;//暂停线程
	thread cTh;//继续线程

	void con();//继续函数
	static void threadCall(dshow_sound *); //线程回调
	static void pThreadCall(dshow_sound *); //线程回调
	static void cThreadCall(dshow_sound *); //线程回调
	long evCode; //事件code
	BOOL isRenderData; //是否已经装载数据
	BOOL isPause; //是否处于暂停状态
	BOOL pauseThreadIn; //是否处于暂停线程
	BOOL conThreadIn; //是否处于继续线程
	int pauseNum;
	int conNum;
	HANDLE cpEvent; //暂停事件
	HANDLE ccEvent; //继续事件
	HANDLE pcEvent; //播放事件
	thread th; //线程变量
};

