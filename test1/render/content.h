
#pragma once
class content
{
public:
	content(HWND h_wnd);
	content();
	~content();
	//设置线样式
	void strokeStyle(UINT32 hex, FLOAT alpha);
	void setLineStyle(float model);
	//创建放射渐变画刷
	ID2D1RadialGradientBrush * createRadioBrush(D2D1_COLOR_F start, D2D1_COLOR_F end, D2D1_POINT_2F center,float distance);
	ID2D1RadialGradientBrush * createRadioBrush(D2D1_COLOR_F start, D2D1_COLOR_F end, D2D1_POINT_2F center, float x, float y);
	//创建放射渐变画刷
	ID2D1RadialGradientBrush * createShadowBrush(D2D1_COLOR_F end, float blow, D2D1_POINT_2F center, float x, float y);
	ID2D1LinearGradientBrush * createLinearBrush(D2D1_COLOR_F start, D2D1_COLOR_F end, D2D1_POINT_2F pstart, D2D1_POINT_2F pend);
	//创建画刷
	ID2D1SolidColorBrush * createSolidBrush(D2D1_COLOR_F c);
	
	//线条绘制
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
	//绘制
	void stroke();
	//填充
	void fill();
	//设置填充样式
	void fillStyle(UINT32 hex, FLOAT alpha);
	//绘制线端
	void drawLine(float x, float y, float x2, float y2);
	//清除窗口
	void clear();
	//开始绘制
	void beginDraw();
	//结束绘制
	void closeDraw();
	//填充矩形
	void fillRect(float x, float y, float width, float height);
	void fillRect(float x, float y, float width, float height, ID2D1Brush * brsh);
	void fillArc(float x, float y, float xWidth, float yWidth);
	void fillArc(float x, float y, float xWidth, float yWidth, ID2D1Brush * brsh);
	//填充圆角矩形
	void fillRoundRect(float x, float y, float width, float height, float radioX, float radioY);
	void fillRoundRect(float x, float y, float width, float height, float radioX, float radioY, ID2D1Brush * brsh);
	//绘制园
	void drawArc(float x, float y, float xWidth, float yWidth);
	//绘制矩形
	void drawRect(float x, float y, float width, float height);
	//绘制圆角矩形
	void drawRoundRect(float x, float y, float width, float height,float radioX,float radioY);
	//绘制图形1
	void drawImage(CHAR * url, float x, float y);
	void drawImage(CHAR * url, float x, float y, float width, float height);
	void drawImage(CHAR * url, float x, float y, float zoom);
	void drawImage(CHAR * url, float x, float y, float width, float height, float srcX, float srcY, float srcWidth, float srcHeight);
	void drawImage(WCHAR * url, float x, float y, float width, float height);
	//绘制图形2
	void drawImage(ID2D1Bitmap * img, float x, float y);
	void drawImage(ID2D1Bitmap * img, float x, float y, float width, float height);
	void drawImage(ID2D1Bitmap * img, float x, float y, float zoom);
	void drawImage(ID2D1Bitmap * img, float x, float y, float width, float height, float srcX, float srcY, float srcWidth, float srcHeight);
	void drawImage(ID2D1Bitmap * img, float x, float y, float width, float height, D2D1_RECT_F * frame);
	//填充图形
	void fillImage(CHAR * url, float x, float y, float width, float height, float srcX = 0, float srcY = 0, float xZoom = 1, float yZoom = 1, float angle = 0);
	void fillImage(ID2D1Bitmap * img, float x, float y, float width, float height, float srcX = 0, float srcY = 0, float xZoom = 1, float yZoom = 1, float angle = 0);
	//获取资源
	ID2D1Bitmap * content::getSoucre(WCHAR * url);
	ID2D1Bitmap * content::getSoucre(CHAR * url);
	//变换
	void rotate(float angle, float x = 0, float y = 0);
	//缩放变换
	void scale(float zoom, float x = 0, float y = 0);
	//扭曲变换
	void skew(float angleX, float angleY, float x = 0, float y = 0);
	//位移变换
	void trisition(float x, float y);
	//保存变换
	void save();
	//重回变换
	void restore();
	//绘制文字
	void drawText(LPCSTR  txt, float x, float y);
	void drawText(string  txt, float x, float y);
	void drawText(LPCSTR  txt, float x, float y, float w, float h);
	void drawText(string  txt, float x, float y, float w, float h);
	void drawText(LPCSTR  txt, float x, float y, float w, float h, IDWriteTextFormat * mat);
	void getTextInfo(LPWSTR  txt, D2D1_SIZE_F& size);
	//创建字体
	IDWriteTextFormat * createFont(float size, LPWSTR fontFamily=L"微软雅黑");
	//获取文本的长度和宽度啊
	void getTextInfo(string  txt, D2D1_SIZE_F& size);
	void getTextInfo(LPWSTR  txt, D2D1_SIZE_F& size, IDWriteTextFormat * mat);
	void getTextInfo(string  txt, D2D1_SIZE_F& size, IDWriteTextFormat * mat);
	void getTextInfo(string txt, D2D1_SIZE_F& size, IDWriteTextFormat * mat, float maxWidth);
	//图层
	void pushLayer(D2D1_LAYER_PARAMETERS k = D2D1::LayerParameters());
	void popLayer();
	IWICBitmap * createImgTarget(ID2D1RenderTarget ** rc, float w, float h);
	D2D1_COLOR_F getColorBrush();
public:
	float lineWidth = 1;
	float lineStyle = 0;//0 实线 1虚线
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

