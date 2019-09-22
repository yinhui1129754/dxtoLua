
#pragma once
class content
{
public:
	content(HWND h_wnd);
	content();
	~content();
	//��������ʽ
	void strokeStyle(UINT32 hex, FLOAT alpha);
	void setLineStyle(float model);
	//�������佥�仭ˢ
	ID2D1RadialGradientBrush * createRadioBrush(D2D1_COLOR_F start, D2D1_COLOR_F end, D2D1_POINT_2F center,float distance);
	ID2D1RadialGradientBrush * createRadioBrush(D2D1_COLOR_F start, D2D1_COLOR_F end, D2D1_POINT_2F center, float x, float y);
	//�������佥�仭ˢ
	ID2D1RadialGradientBrush * createShadowBrush(D2D1_COLOR_F end, float blow, D2D1_POINT_2F center, float x, float y);
	ID2D1LinearGradientBrush * createLinearBrush(D2D1_COLOR_F start, D2D1_COLOR_F end, D2D1_POINT_2F pstart, D2D1_POINT_2F pend);
	//������ˢ
	ID2D1SolidColorBrush * createSolidBrush(D2D1_COLOR_F c);
	
	//��������
	/*app.content->initPath();
	app.content->beginPath(0, 0);
	app.content->addPofloat(100, xxx);
	app.content->addPofloat(80+xxx, xxx+20);
	app.content->closePath();
	app.content->stroke();
	app.content->releasePath();*/
	void initPath(D2D1_FILL_MODE mode = D2D1_FILL_MODE_ALTERNATE);
	void releasePath();
	void beginPath(float x, float y);
	void addPofloat(float x, float y);
	void addPofloat(D2D1_POINT_2F  pofloat);
	void addBezier(D2D1_POINT_2F start, D2D1_POINT_2F center, D2D1_POINT_2F end);
	void addArc(float x, float y, float xSize, float ySize, float angle, D2D1_SWEEP_DIRECTION angleFx = D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE, D2D1_ARC_SIZE size = D2D1_ARC_SIZE_SMALL);
	void closePath(D2D1_FIGURE_END type = D2D1_FIGURE_END_OPEN);
	//����
	void stroke();
	//���
	void fill();
	//���������ʽ
	void fillStyle(UINT32 hex, FLOAT alpha);
	//�����߶�
	void drawLine(float x, float y, float x2, float y2);
	//�������
	void clear();
	//��ʼ����
	void beginDraw();
	//��������
	void closeDraw();
	//������
	void fillRect(float x, float y, float width, float height);
	void fillRect(float x, float y, float width, float height, ID2D1Brush * brsh);
	void fillArc(float x, float y, float xWidth, float yWidth);
	void fillArc(float x, float y, float xWidth, float yWidth, ID2D1Brush * brsh);
	//���Բ�Ǿ���
	void fillRoundRect(float x, float y, float width, float height, float radioX, float radioY);
	void fillRoundRect(float x, float y, float width, float height, float radioX, float radioY, ID2D1Brush * brsh);
	//����԰
	void drawArc(float x, float y, float xWidth, float yWidth);
	//���ƾ���
	void drawRect(float x, float y, float width, float height);
	//����Բ�Ǿ���
	void drawRoundRect(float x, float y, float width, float height,float radioX,float radioY);
	//����ͼ��1
	void drawImage(CHAR * url, float x, float y);
	void drawImage(CHAR * url, float x, float y, float width, float height);
	void drawImage(CHAR * url, float x, float y, float zoom);
	void drawImage(CHAR * url, float x, float y, float width, float height, float srcX, float srcY, float srcWidth, float srcHeight);
	void drawImage(WCHAR * url, float x, float y, float width, float height);
	//����ͼ��2
	void drawImage(ID2D1Bitmap * img, float x, float y);
	void drawImage(ID2D1Bitmap * img, float x, float y, float width, float height);
	void drawImage(ID2D1Bitmap * img, float x, float y, float zoom);
	void drawImage(ID2D1Bitmap * img, float x, float y, float width, float height, float srcX, float srcY, float srcWidth, float srcHeight);
	void drawImage(ID2D1Bitmap * img, float x, float y, float width, float height, D2D1_RECT_F * frame);
	//���ͼ��
	void fillImage(CHAR * url, float x, float y, float width, float height, float srcX = 0, float srcY = 0, float xZoom = 1, float yZoom = 1, float angle = 0);
	void fillImage(ID2D1Bitmap * img, float x, float y, float width, float height, float srcX = 0, float srcY = 0, float xZoom = 1, float yZoom = 1, float angle = 0);
	//��ȡ��Դ
	ID2D1Bitmap * content::getSoucre(WCHAR * url);
	ID2D1Bitmap * content::getSoucre(CHAR * url);
	//�任
	void rotate(float angle, float x = 0, float y = 0);
	//���ű任
	void scale(float zoom, float x = 0, float y = 0);
	//Ť���任
	void skew(float angleX, float angleY, float x = 0, float y = 0);
	//λ�Ʊ任
	void trisition(float x, float y);
	//����任
	void save();
	//�ػر任
	void restore();
	//��������
	void drawText(LPCSTR  txt, float x, float y);
	void drawText(string  txt, float x, float y);
	void drawText(LPCSTR  txt, float x, float y, float w, float h);
	void drawText(string  txt, float x, float y, float w, float h);
	void drawText(LPCSTR  txt, float x, float y, float w, float h, IDWriteTextFormat * mat);
	void getTextInfo(LPWSTR  txt, D2D1_SIZE_F& size);
	//��������
	IDWriteTextFormat * createFont(float size, LPWSTR fontFamily=L"΢���ź�");
	//��ȡ�ı��ĳ��ȺͿ�Ȱ�
	void getTextInfo(string  txt, D2D1_SIZE_F& size);
	void getTextInfo(LPWSTR  txt, D2D1_SIZE_F& size, IDWriteTextFormat * mat);
	void getTextInfo(string  txt, D2D1_SIZE_F& size, IDWriteTextFormat * mat);
	void getTextInfo(string txt, D2D1_SIZE_F& size, IDWriteTextFormat * mat, float maxWidth);
	//ͼ��
	void pushLayer(D2D1_LAYER_PARAMETERS k = D2D1::LayerParameters());
	void popLayer();
	IWICBitmap * createImgTarget(ID2D1RenderTarget ** rc, float w, float h);
	D2D1_COLOR_F getColorBrush();
public:
	float lineWidth = 1;
	float lineStyle = 0;//0 ʵ�� 1����
	IWICImagingFactory * m_imgFac;
	HWND p_hwnd;
	string status = "content";
	D2D1_MATRIX_3X2_F m1;
	D2D1_MATRIX_3X2_F bufM1;
	ID2D1HwndRenderTarget * m_render = NULL;

	D2D1_TAG buf1;
	D2D1_TAG buf2;
	ID2D1RadialGradientBrush * rodiaBrush = NULL;
	ID2D1RadialGradientBrush * rodiaBrush2 = NULL;
	ID2D1LinearGradientBrush * lineBrush = NULL;
	ID2D1SolidColorBrush *solidBrush = NULL;
	ID2D1Layer* g_pLayer = NULL;
private:
	ID2D1Factory * m_fac;
	
	ID2D1SolidColorBrush * pen = NULL;
	ID2D1SolidColorBrush *brush = NULL;

	ID2D1BitmapBrush * bitmapBrush;

	ID2D1StrokeStyle * m_lineStyle = NULL;
	vector <wstring> imgName;
	vector <ID2D1Bitmap *> imgSource;
	IDWriteFactory * m_writeFac = NULL;
	IDWriteTextFormat * m_forMat = NULL;
	ID2D1PathGeometry * m_path = NULL;
	ID2D1GeometrySink *m_slink = NULL;
	

};

