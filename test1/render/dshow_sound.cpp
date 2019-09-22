
#include "dshow_sound.h"

dshow_sound::dshow_sound()
{
//	this->pGraph = argupGraph;
	hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
		IID_IGraphBuilder, (void **)&pGraph);
	if (FAILED(hr))
	{


#ifdef U_DX_SHOW_MESSAGETOOLTIP
	MessageBox(NULL, "错误!创建接口对象错误", "提示哦！", MB_OK);
#endif // DEBUG
		ERROR_CODE = U_DX_SHOW_ERROR_CREATEBUILD;
	}
	else {
		ERROR_CODE = U_DX_SHOW_NO_ERROR;
	}
	createComObject(IID_IMediaControl, (void **)&pControl, U_DX_SHOW_ERROR_CREATECONTROL);
	createComObject(IID_IMediaEvent, (void **)&pEvent, U_DX_SHOW_ERROR_CREATEEVENT);
	PLAY_LOOP = TRUE;
	isRenderData = FALSE;
	isPause = FALSE;
	pauseThreadIn = FALSE;
	conThreadIn = FALSE;
	cpEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	ccEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	pcEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (!pTh.joinable()) {
		pTh = thread(dshow_sound::pThreadCall, this);
	}
	if (!cTh.joinable()) {
		cTh = thread(dshow_sound::cThreadCall, this);
	}
	if (!th.joinable()) {
		th = thread(dshow_sound::threadCall, this);
	}
}
void dshow_sound::createComObject(REFIID riid, void ** buf, DX_SHOW_ERROR_CODE code) {
	hr = pGraph->QueryInterface(riid, buf);//获取滤波器接口
	if (FAILED(hr)) {
#ifdef U_DX_SHOW_MESSAGETOOLTIP
		MessageBox(NULL, "错误!创建设备对象出错", "提示哦！", MB_OK);
#endif // DEBUG

		ERROR_CODE = code;
	}
	else {
		ERROR_CODE = U_DX_SHOW_NO_ERROR;
	}
};
void dshow_sound::play(const char * path) {
	this->path = path;
	this->play(this->path);
};
void dshow_sound::pause() {
	pauseThreadIn = TRUE;
	conThreadIn = FALSE;
	this->pauseNum = 0;
	isPause = TRUE;
	SetEvent(this->cpEvent);
}
void dshow_sound::con() {
	pauseThreadIn = FALSE;
	conThreadIn = TRUE;
	isPause = FALSE;
	this->conNum = 0;
	SetEvent(this->ccEvent);
}
void dshow_sound::play(string path, int type) {
	if (this->path != path) {
		this->path = path; 
	}

	//ts->hr = ts->pGraph->RenderFile(lpw, NULL);
	//ts->pControl->QueryInterface(IID_IMediaSeeking, (void **)ts->pConSeek);
	if (isRenderData) {

	}
	else {
		LPWSTR lpw = utils::user_stringToLPWSTR(path);
		hr = pGraph->AddSourceFilter(lpw, L"source", &pBaseFilter);
		pPin = GetOutPin(pBaseFilter, 0);
		pControl->QueryInterface(IID_IMediaSeeking, (void **)&pConSeek);
		pGraph->Render(pPin);
		isRenderData = TRUE;
		free(lpw);
	}
	if(!type) {
		//th = thread(dshow_sound::threadCall, this);
		SetEvent(pcEvent);
	}
};
HRESULT dshow_sound::GetPin(IBaseFilter * pFilter, PIN_DIRECTION dirrequired, int iNum, IPin **ppPin) {
	IEnumPins * pEnum;
	*ppPin = NULL;

	HRESULT hr = pFilter->EnumPins(&pEnum);//hrererer!!!!!!!!!!!!

	if (FAILED(hr))
		return hr;

	ULONG ulFound;
	IPin *pPin;
	hr = E_FAIL;

	while (S_OK == pEnum->Next(1, &pPin, &ulFound))
	{
		PIN_DIRECTION pindir = (PIN_DIRECTION)3;

		pPin->QueryDirection(&pindir);
		if (pindir == dirrequired)
		{
			if (iNum == 0)
			{
				*ppPin = pPin;  // Return the pin's interface
				hr = S_OK;      // Found requested pin, so clear error
				break;
			}
			iNum--;
		}

		pPin->Release();
	}

	return hr;
};
IPin * dshow_sound::GetOutPin(IBaseFilter * pFilter, int nPin) {
	IPin * pComPin = 0;
	dshow_sound::GetPin(pFilter, PINDIR_OUTPUT, nPin, &pComPin);
	return pComPin;
};
void dshow_sound::playEnd() {
	//th = thread(dshow_sound::threadCall, this);
}
void dshow_sound::pThreadCall(dshow_sound *ts) {
	while (true) {
		WaitForSingleObject(ts->cpEvent, INFINITE);
		ResetEvent(ts->cpEvent);
		ts->pauseThreadIn = TRUE;
		while (ts->pauseThreadIn) {
			ts->hr = ts->pControl->Pause();
			if (SUCCEEDED(ts->hr)) {
				ts->pauseThreadIn = FALSE;
				break;
			}
			ts->pauseNum++;
			if (ts->pauseNum >= 50) {
				ts->pauseThreadIn = FALSE;
				break;
			}
			Sleep(10);
		}
	}

};
void dshow_sound::cThreadCall(dshow_sound *ts) {
	while (true) {
		WaitForSingleObject(ts->ccEvent, INFINITE);
		ResetEvent(ts->ccEvent);
		ts->conThreadIn = TRUE;
		while (ts->conThreadIn) {
			ts->play(ts->path);
		
			ts->pauseNum++;
			if (ts->pauseNum >= 50) {

				ts->conThreadIn = FALSE;
				break;
			}
			Sleep(10);
		}
	}

};
void dshow_sound::threadCall(dshow_sound * ts) {

	

	//ts->pBaseFilter->QueryInterface(IID_IMediaSeeking, (void **)ts->pConSeek);
	//ts->createComObject(IID_IMediaSeeking, (void **)ts->pConSeek, U_DX_SHOW_ERROR_CREATESEEKING);
	if (SUCCEEDED(ts->hr))
	{
		while (TRUE) {
			WaitForSingleObject(ts->pcEvent,INFINITE);
			
			if (!ts->isPause) {
				long long before = 0;
				ts->pConSeek->SetTimeFormat(&TIME_FORMAT_MEDIA_TIME);
				ts->pConSeek->SetPositions(&before, AM_SEEKING_AbsolutePositioning, 0, AM_SEEKING_NoPositioning);
				ts->pControl->Run();
				ts->pEvent->RestoreDefaultHandling(ts->evCode);
				ts->pEvent->WaitForCompletion(INFINITE, &ts->evCode);
				if (!ts->PLAY_LOOP) {
					SetEvent(ts->pcEvent);
				}
				else {
					ts->playEnd();
				}
			}
			else {
				ResetEvent(ts->pcEvent);
			}
			
			/*while (TRUE && (!ts->isPause)) {
				
				//ts->pBaseFilter->Run(0);
				
				ts->pEvent->WaitForCompletion(INFINITE, &ts->evCode);
			}*/
		}
	
		
		//ts->pConSeek->SetPositions(0, AM_SEEKING_AbsolutePositioning, &end, AM_SEEKING_ReturnTime);
		ts->ERROR_CODE = U_DX_SHOW_NO_ERROR;
	}
	else {
		ts->ERROR_CODE = U_DX_SHOW_ERROR_READERFILE;
	}
};
dshow_sound::~dshow_sound()
{
	if (pEvent != NULL) {
		pEvent->Release();
	}
	if (pControl != NULL) {
		pControl->Release();
	}
}
