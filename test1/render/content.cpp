#include "../stdafx.h"
content::content() {

}
void content::clear() {
	
	this->m_render->Clear();
	//this->m_render->SetTransform(D2D1::Matrix3x2F::Identity());
}
IWICBitmap * content::createImgTarget(ID2D1RenderTarget ** rc,float w,float h) {
	IWICBitmap *  spWicBitmap;
	m_imgFac->CreateBitmap(w, h, GUID_WICPixelFormat32bppPBGRA,
		WICBitmapCacheOnLoad, &spWicBitmap);
	m_fac->CreateWicBitmapRenderTarget(spWicBitmap, D2D1::RenderTargetProperties(), rc);
	return spWicBitmap;
};
content::content(HWND hwnd)
{
	RECT rc;
	GetClientRect(hwnd, &rc);
	this->p_hwnd = hwnd;
	//创建绘图基础
	HRESULT hr = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_MULTI_THREADED,
		&(this->m_fac)
	);
	if (SUCCEEDED(hr)) {
	
		CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, __uuidof(this->m_imgFac), (LPVOID*)&(this->m_imgFac));
		
		
		this->m_fac->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(
				hwnd,
				D2D1::SizeU(
					rc.right - rc.left,
					rc.bottom - rc.top
				),
				D2D1_PRESENT_OPTIONS_NONE
			),
			&(this->m_render)
		);
	//	m_render->CreateCompatibleRenderTarget(&m_render);

		
		/*m_render->CreateBitmap(D2D1::SizeU(800, 800), nullptr, 0,
			D2D1::BitmapProperties(
				D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE),96.0f,96.0f
			),
			&mem_bmp2);*/
		/*m_imgFac->CreateBitmap(800, 800,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapCacheOnLoad, &mem_bmp);
		m_fac->CreateWicBitmapRenderTarget(this->mem_bmp, D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM,
				D2D1_ALPHA_MODE_PREMULTIPLIED),
			0.f, 0.f,
			D2D1_RENDER_TARGET_USAGE_GDI_COMPATIBLE),&m_render);*/
		
		D2D1_SIZE_F size = {
			0,
			0
		};

		this->m1 = D2D1::Matrix3x2F::Translation(
			size
		);
		this->bufM1 = D2D1::Matrix3x2F::Translation(
			size
		);
		//创建画线样式
		this->m_render->CreateSolidColorBrush(D2D1::ColorF(50, 100, 255, 1.0f), &(this->pen));
		//创建填充样式
		this->m_render->CreateSolidColorBrush(D2D1::ColorF(50, 100, 255, 1.0f), &(this->brush));
		//创建放射渐变


		//创建层
		this->m_render->CreateLayer(NULL, &g_pLayer);
		

		/*float deash[] = { 5.0f,1.0f,5.0f,10.0f };
		//创建边框样式
		this->m_fac->CreateStrokeStyle(D2D1::StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,
			D2D1_CAP_STYLE_FLAT,
			D2D1_CAP_STYLE_ROUND,
			D2D1_LINE_JOIN_MITER,
			10.0f,
			D2D1_DASH_STYLE_CUSTOM,
			0.0f), deash, ARRAYSIZE(deash), &(this->m_lineStyle));*/
			//创建img进程
		
		//创建字体基础
		DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory),
			reinterpret_cast<IUnknown**>(&this->m_writeFac));
		this->m_writeFac->CreateTextFormat(
			L"微软雅黑",
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			16,
			L"en-US",
			&this->m_forMat
		);



	}
	else {
		MessageBox(NULL, TEXT("错误"), TEXT(""), MB_OK);
	}
}
ID2D1RadialGradientBrush * content::createRadioBrush(D2D1_COLOR_F start, D2D1_COLOR_F end, D2D1_POINT_2F center, float distance) {
	return this->createRadioBrush(start,end,center,distance,distance);
}
ID2D1RadialGradientBrush * content::createRadioBrush(D2D1_COLOR_F start, D2D1_COLOR_F end, D2D1_POINT_2F center, float x,float y) {

	/*if (this->rodiaBrush != NULL) {
		this->rodiaBrush->Release();
		this->rodiaBrush = NULL;
	}*/
	D2D1_GRADIENT_STOP gradientStops[2];
	gradientStops[0].color = start;
	gradientStops[0].position = 0.f;
	gradientStops[1].color = end;
	gradientStops[1].position = 1.f;

	ID2D1GradientStopCollection* pGradientStops = NULL;
	m_render->CreateGradientStopCollection(
		gradientStops,
		2,
		D2D1_GAMMA_2_2,
		D2D1_EXTEND_MODE_CLAMP,
		&pGradientStops
	);

	this->m_render->CreateRadialGradientBrush(D2D1::RadialGradientBrushProperties(
		center,
		D2D1::Point2F(0, 0),
		x,
		y), pGradientStops, &this->rodiaBrush);
	SafeRelease(&pGradientStops);
	return this->rodiaBrush;
}

ID2D1RadialGradientBrush * content::createShadowBrush(D2D1_COLOR_F end,float blow,D2D1_POINT_2F center, float x, float y) {
	/*if (this->rodiaBrush2 != NULL) {
		return this->rodiaBrush2;
	}*/
	D2D1_GRADIENT_STOP gradientStops[2];
	float xAll = x + 2 * blow;
	float yAll = y + 2 * blow;
	gradientStops[0].color = end;
	gradientStops[0].position = (x/xAll+y/yAll)/2;
	gradientStops[1].color = D2D1::ColorF(end.r,end.g,end.b,0);
	gradientStops[1].position = 1.0f;

	ID2D1GradientStopCollection * pGradientStops = NULL;
	m_render->CreateGradientStopCollection(
		gradientStops,
		2,
		D2D1_GAMMA_2_2,
		D2D1_EXTEND_MODE_CLAMP,
		&pGradientStops
	);
	/*rodiaBrush2->SetRadiusX(xAll);
	rodiaBrush2->SetRadiusY(yAll);
	rodiaBrush2->SetCenter(center);*/
	//rodiaBrush2->GetGradientStopCollection()
	HRESULT hok=this->m_render->CreateRadialGradientBrush(D2D1::RadialGradientBrushProperties(
		center,
		D2D1::Point2F(0, 0),
		xAll,
		yAll), pGradientStops, &this->rodiaBrush2);
	if (hok == S_OK) {
		return this->rodiaBrush2;
	}
	else {
		return NULL;
	}
	
}
ID2D1SolidColorBrush * content::createSolidBrush(D2D1_COLOR_F c) {
	this->m_render->CreateSolidColorBrush(c, &(this->solidBrush));
	return this->solidBrush;
};
ID2D1LinearGradientBrush * content::createLinearBrush(D2D1_COLOR_F start, D2D1_COLOR_F end, D2D1_POINT_2F pstart, D2D1_POINT_2F pend) {
	D2D1_GRADIENT_STOP gradientStops[2];
	gradientStops[0].color = start;
	gradientStops[0].position = 0.f;
	gradientStops[1].color = end;
	gradientStops[1].position = 1.f;
	ID2D1GradientStopCollection* pGradientStops = NULL;
	m_render->CreateGradientStopCollection(
		gradientStops,
		2,
		D2D1_GAMMA_2_2,
		D2D1_EXTEND_MODE_CLAMP,
		&pGradientStops
	);

	this->m_render->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties(
		pstart,
		pend), pGradientStops,&this->lineBrush);
	SafeRelease(&pGradientStops);
	return this->lineBrush;
}
void content::stroke() {
	//	this->m_render->DrawLine()
	this->m_render->DrawGeometry(this->m_path, this->pen, this->lineWidth, this->m_lineStyle);
};
void content::pushLayer(D2D1_LAYER_PARAMETERS k) {
	m_render->PushLayer(
		k,
		g_pLayer
	);
}
void content::popLayer() {
	m_render->PopLayer();
}
void content::fill() {
	this->m_render->FillGeometry(this->m_path, this->brush);
}
void content::releasePath() {
	SafeRelease(&(this->m_slink));
	SafeRelease(&(this->m_path));
}
void content::strokeStyle(UINT32 hex, FLOAT alpha) {
	this->pen->SetColor(D2D1::ColorF(hex, alpha));
}
void content::setLineStyle(float model) {
	this->lineStyle = model;
	SafeRelease(&(this->m_lineStyle));
	if (this->lineStyle == 1) {
		float deash[] = { 5.0f,1.0f,5.0f,10.0f };
		//创建边框样式
		this->m_fac->CreateStrokeStyle(D2D1::StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,
			D2D1_CAP_STYLE_FLAT,
			D2D1_CAP_STYLE_ROUND,
			D2D1_LINE_JOIN_MITER,
			10.0f,
			D2D1_DASH_STYLE_CUSTOM,
			0.0f), deash, ARRAYSIZE(deash), &(this->m_lineStyle));
	}
}
void content::initPath(D2D1_FILL_MODE mode) {
	this->releasePath();
	this->m_fac->CreatePathGeometry(&(this->m_path));
	HRESULT hr = this->m_path->Open(&(this->m_slink));
	m_slink->SetFillMode(mode);
}
void content::beginPath(float x, float y) {
	this->m_slink->BeginFigure(
		D2D1::Point2F(x, y),
		D2D1_FIGURE_BEGIN_FILLED
	);
}

void content::closePath(D2D1_FIGURE_END type) {
	this->m_slink->EndFigure(type);
	this->m_slink->Close();
}

void content::addPofloat(float x, float y) {
	this->m_slink->AddLine(D2D1::Point2F(x, y));
};
void content::addPofloat(D2D1_POINT_2F  pofloat) {
	this->m_slink->AddLine(pofloat);
}

void content::addBezier(D2D1_POINT_2F start, D2D1_POINT_2F center, D2D1_POINT_2F end) {
	this->m_slink->AddBezier(D2D1::BezierSegment(start, center, end));
};
void content::addArc(float x, float y, float xSize, float ySize, float angle, D2D1_SWEEP_DIRECTION angleFx, D2D1_ARC_SIZE size) {
	this->m_slink->AddArc(D2D1::ArcSegment(
		D2D1::Point2F(x, y),
		D2D1::SizeF(xSize, ySize),
		angle,
		angleFx,
		size
	));
};
void content::fillStyle(UINT32 hex, FLOAT alpha) {
	this->brush->SetColor(D2D1::ColorF(hex, alpha));
};
void content::beginDraw() {
	
	this->m_render->BeginDraw();
	
}
void content::closeDraw() {
	this->m_render->EndDraw();
}
void content::fillRect(float x, float y, float width, float height) {
	this->fillRect(x,y,width,height,this->brush);
}
void content::fillRect(float x, float y, float width, float height, ID2D1Brush * brsh) {
	this->m_render->FillRectangle(D2D1::RectF(x, y, x + width, y + height), brsh);
};
void content::drawRect(float x, float y, float width, float height) {
	this->initPath();
	this->beginPath(x, y);
	this->addPofloat(x + width, y);
	this->addPofloat(x + width, y + height);
	this->addPofloat(x, y + height);
	this->closePath(D2D1_FIGURE_END_CLOSED);
	this->stroke();
	this->releasePath();
}
void content::drawRoundRect(float x, float y, float width, float height, float radioX, float radioY) {
	this->m_render->DrawRoundedRectangle(
		D2D1::RoundedRect(D2D1::RectF(x, y, x + width, y + height), radioX, radioY),
		this->pen, this->lineWidth, this->m_lineStyle
	);
}
void content::fillRoundRect(float x, float y, float width, float height, float radioX, float radioY) {
	this->fillRoundRect(x, y, width, height, radioX, radioY, this->brush);
}
D2D1_COLOR_F content::getColorBrush() {
	return this->brush->GetColor();
}
void content::fillRoundRect(float x, float y, float width, float height, float radioX, float radioY, ID2D1Brush * brsh) {
	this->m_render->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x, y, x + width, y + height), radioX, radioY), brsh);
}

void content::drawArc(float x, float y, float xWidth, float yWidth) {
	D2D1_ELLIPSE circle1 = D2D1::Ellipse(
		D2D1::Point2F(x, y),
		xWidth,
		yWidth
	);
	ID2D1EllipseGeometry * l_ellipse = NULL;
	this->m_fac->CreateEllipseGeometry(
		circle1,
		&l_ellipse
	);
	this->m_render->DrawGeometry(l_ellipse, this->pen, this->lineWidth, this->m_lineStyle);
	SafeRelease(&l_ellipse);
};

void content::fillArc(float x, float y, float xWidth, float yWidth) {
	this->fillArc(x, y, xWidth, yWidth, this->brush);
};
void content::fillArc(float x, float y, float xWidth, float yWidth, ID2D1Brush * brsh) {
	D2D1_ELLIPSE circle1 = D2D1::Ellipse(
		D2D1::Point2F(x, y),
		xWidth,
		yWidth
	);
	ID2D1EllipseGeometry * l_ellipse = NULL;
	this->m_fac->CreateEllipseGeometry(
		circle1,
		&l_ellipse
	);
	this->m_render->FillGeometry(l_ellipse, brsh);
	SafeRelease(&l_ellipse);
};
void content::rotate(float angle, float x, float y) {
	this->m1 = this->m1* D2D1::Matrix3x2F::Rotation(
		angle,
		D2D1::Point2F(x, y));
	this->m_render->SetTransform(
		this->m1
	);
};
void content::scale(float zoom, float x, float y) {
	RECT rc;
	GetClientRect(this->p_hwnd, &rc);
	D2D1_SIZE_F size = {
			zoom,
			zoom
	};
	this->m1 = this->m1*D2D1::Matrix3x2F::Scale(
		size,
		D2D1::Point2F(x, y)
	);
	this->m_render->SetTransform(this->m1);
};
void content::skew(float angleX, float angleY, float x, float y) {
	this->m1 = this->m1*D2D1::Matrix3x2F::Skew(angleX, angleY, D2D1::Point2(x, y));
	this->m_render->SetTransform(
		this->m1
	);
};
void content::trisition(float x, float y) {
	if (x != 0) {

	}
	D2D1_SIZE_F size = {
		x,
		y
	};
	this->m1 = this->m1 * D2D1::Matrix3x2F::Translation(
		size
	);
	this->m_render->SetTransform(this->m1);
};
void content::save() {
	this->bufM1 = this->m1;
}
void content::restore() {
	this->m1 = this->bufM1;
	this->m_render->SetTransform(this->bufM1);
}
void content::getTextInfo(LPWSTR  txt, D2D1_SIZE_F& size) {
	this->getTextInfo(txt, size, this->m_forMat);
}
void content::getTextInfo(LPWSTR  txt, D2D1_SIZE_F& size,IDWriteTextFormat * mat) {
	IDWriteTextLayout* pTextLayout = NULL;
	this->m_writeFac->CreateTextLayout(txt, wcslen(txt), mat, 0.0f, 0.0f, &pTextLayout);

	//获取文本尺寸
	FLOAT fontSize;
	pTextLayout->GetFontSize(0, &fontSize);
	pTextLayout->SetMaxWidth(wcslen(txt)*fontSize*1.5);

	DWRITE_TEXT_METRICS textMetrics;
	pTextLayout->GetMetrics(&textMetrics);
	size = D2D1::SizeF(ceil(textMetrics.widthIncludingTrailingWhitespace), ceil(textMetrics.height));
	SafeRelease(&pTextLayout);
}
void content::getTextInfo(string txt, D2D1_SIZE_F& size, IDWriteTextFormat * mat, float maxWidth) {
	IDWriteTextLayout* pTextLayout = NULL;
	WCHAR * txt2 = utils::user_stringToLPWSTR(txt);
	this->m_writeFac->CreateTextLayout(txt2, wcslen(txt2), mat, 0.0f, 0.0f, &pTextLayout);

	// 获取文本尺寸  
	FLOAT fontSize;
	pTextLayout->GetFontSize(0, &fontSize);
	pTextLayout->SetMaxWidth(maxWidth);
	DWRITE_TEXT_METRICS textMetrics;
	pTextLayout->GetMetrics(&textMetrics);
	size = D2D1::SizeF(ceil(textMetrics.widthIncludingTrailingWhitespace), ceil(textMetrics.height));
	SafeRelease(&pTextLayout);
	free(txt2);
};
void content::getTextInfo(string  txt, D2D1_SIZE_F& size) {
	LPWSTR a =utils::user_stringToLPWSTR(txt);
	this->getTextInfo(txt, size, this->m_forMat);
	free(a);
};
void content::getTextInfo(string  txt, D2D1_SIZE_F& size, IDWriteTextFormat * mat) {
	LPWSTR a = utils::user_stringToLPWSTR(txt);
	this->getTextInfo(a, size, mat);
	free(a);
};
ID2D1Bitmap * content::getSoucre(WCHAR * url) {
	//vector<WCHAR *>::iterator it;
	//wcscmp()
	int index = -1;
	wstring ws1 = url;
	for (int i = 0; i < this->imgName.size(); i++) {
		wstring ws2 = this->imgName[i];
		if (ws2.compare(ws1)==0) {
			index = i;
			break;
		}
	}
	if (index != -1) {
		return this->imgSource[index];
	}
	else {
		ID2D1Bitmap * g_bitmap = NULL;
		IWICBitmapDecoder * bitmapdecoder = NULL;
		this->m_imgFac->CreateDecoderFromFilename(url, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &bitmapdecoder);
		IWICBitmapFrameDecode  *pframe = NULL;
		bitmapdecoder->GetFrame(0, &pframe);
		IWICFormatConverter * fmtcovter = NULL;
		this->m_imgFac->CreateFormatConverter(&fmtcovter);
		fmtcovter->Initialize(pframe, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);
		this->m_render->CreateBitmapFromWicBitmap(fmtcovter, NULL, &g_bitmap);
		fmtcovter->Release();
		pframe->Release();
		bitmapdecoder->Release();
		this->imgName.push_back(ws1);
		this->imgSource.push_back(g_bitmap);
		return g_bitmap;
	}
	/*it = find(this->imgName.begin(), this->imgName.end(), url);
	if (it != this->imgName.end()) {
		return (this->imgSource[distance(this->imgName.begin(), it)]);
	}
	else {
		
	};*/
}
ID2D1Bitmap * content::getSoucre(CHAR * url) {
	LPWSTR url2 = utils::user_LPCSTRToLPWSTR(url);
	
	ID2D1Bitmap * g_bitmap =this->getSoucre(url2);
	free(url2);
	return g_bitmap;
	//return NULL;
}
void content::drawImage(CHAR * url, float x, float y) {
	LPWSTR url2=utils::user_LPCSTRToLPWSTR(url);
	ID2D1Bitmap * g_bitmap = this->getSoucre(url2);
	D2D1_SIZE_F size = g_bitmap->GetSize();
	D2D_RECT_F imgr = { x,y,x + size.width,y + size.height };
	this->m_render->DrawBitmap(g_bitmap, imgr);
	free(url2);
}
void content::fillImage(CHAR * url, float x, float y, float width, float height, float srcX, float srcY, float xZoom, float yZoom, float angle) {
	LPWSTR url2 = utils::user_LPCSTRToLPWSTR(url);
	ID2D1Bitmap * img = this->getSoucre(url2);
	this->fillImage(img, x, y, width, height, srcX, srcY, xZoom, yZoom, angle);
	free(url2);
}
void content::fillImage(ID2D1Bitmap * img, float x, float y, float width, float height, float srcX, float srcY, float xZoom, float yZoom, float angle) {
	this->m_render->CreateBitmapBrush(
		img,
		&this->bitmapBrush
	);
	this->bitmapBrush->SetExtendModeX(D2D1_EXTEND_MODE_WRAP);
	this->bitmapBrush->SetExtendModeY(D2D1_EXTEND_MODE_WRAP);
	D2D1_MATRIX_3X2_F rotation = D2D1::Matrix3x2F::Rotation(
		angle,
		D2D1::Point2F(0, 0)
	);
	this->bitmapBrush->SetTransform(D2D1::Matrix3x2F::Translation(D2D1::Size(srcX, srcY))*D2D1::Matrix3x2F::Scale(D2D1::Size(xZoom, yZoom))*rotation);
	this->m_render->FillRectangle(D2D1::RectF(x, y, x + width, y + height), this->bitmapBrush);
	SafeRelease(&this->bitmapBrush);
}
void content::drawImage(ID2D1Bitmap * img, float x, float y) {
	D2D1_SIZE_F size = img->GetSize();
	D2D_RECT_F imgr = { x,y,x + size.width,y + size.height };
	this->m_render->DrawBitmap(img, imgr);
}
void content::drawImage(CHAR * url, float x, float y, float width, float height) {
	LPWSTR url2 = utils::user_LPCSTRToLPWSTR(url);
	ID2D1Bitmap * g_bitmap = this->getSoucre(url2);
	D2D_RECT_F imgr = { x,y,x + width,y + height };
	this->m_render->DrawBitmap(g_bitmap, imgr);
	free(url2);
	//,1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,NULL
}
void content::drawImage(WCHAR * url, float x, float y, float width, float height) {

	ID2D1Bitmap * g_bitmap = this->getSoucre(url);
	D2D_RECT_F imgr = { x,y,x + width,y + height };
	this->m_render->DrawBitmap(g_bitmap, imgr);
	//, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, NULL
}
void content::drawImage(ID2D1Bitmap * img, float x, float y, float width, float height) {
	D2D1_SIZE_F size = img->GetSize();
	D2D_RECT_F imgr = { x,y,x + width,y + height };
	this->m_render->DrawBitmap(img, imgr);
}
void content::drawImage(CHAR * url, float x, float y, float width, float height, float srcX, float srcY, float srcWidth, float srcHeight) {
	LPWSTR url2 = utils::user_LPCSTRToLPWSTR(url);
	ID2D1Bitmap * g_bitmap = this->getSoucre(url2);
	D2D_RECT_F imgr = { x,y,x + width,y + height };
	D2D_RECT_F srcImg = { srcX,srcY,srcX + srcWidth,srcY + srcHeight };
	this->m_render->DrawBitmap(g_bitmap, imgr, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &srcImg);
	free(url2);
}
void content::drawImage(ID2D1Bitmap * img, float x, float y, float width, float height, float srcX, float srcY, float srcWidth, float srcHeight) {
	D2D_RECT_F imgr = { x,y,x + width,y + height };
	D2D_RECT_F srcImg = { srcX,srcY,srcX + srcWidth,srcY + srcHeight };
	this->m_render->DrawBitmap(img, imgr, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &srcImg);
}
void content::drawImage(ID2D1Bitmap * img, float x, float y, float width, float height, D2D1_RECT_F * frame) {
	
	D2D_RECT_F imgr = { x,y,x + width,y + height };
	D2D_RECT_F srcImg = { frame->left,frame->top,frame->right + frame->left,frame->top + frame->bottom };
	this->m_render->DrawBitmap(img, imgr, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &srcImg);
};
void content::drawImage(CHAR * url, float x, float y, float zoom) {
	this->drawImage(url, x, y, zoom, zoom);
}
void content::drawImage(ID2D1Bitmap * img, float x, float y, float zoom) {
	this->drawImage(img, x, y, zoom, zoom);
}

void content::drawLine(float x, float y, float x2, float y2) {

	if (this->lineStyle == 0) {
		this->m_render->DrawLine(
			D2D1::Point2(x, y),
			D2D1::Point2(x2, y2),
			(this->pen),
			this->lineWidth
		);
	}
	else {
		this->m_render->DrawLine(
			D2D1::Point2(x, y),
			D2D1::Point2(x2, y2),
			(this->pen),
			this->lineWidth,
			this->m_lineStyle
		);
	}
}
void content::drawText(LPCSTR  txt, float x, float y) {
	this->drawText(txt,x, y, 100, 100);
}
void content::drawText(string  txt, float x, float y) {
	this->drawText(txt.c_str(), x, y);
}
void content::drawText(LPCSTR  txt, float x, float y, float w, float h) {

	LPWSTR url2 = utils::user_LPCSTRToLPWSTR(txt);
	D2D1_RECT_F layoutRect = D2D1::RectF(x, y, x + w, y + h);

	this->m_render->DrawText(url2, wcslen(url2), this->m_forMat, layoutRect, this->pen);
	free(url2);
}
void content::drawText(LPCSTR  txt, float x, float y, float w, float h, IDWriteTextFormat * mat) {

	LPWSTR url2 = utils::user_LPCSTRToLPWSTR(txt);
	D2D1_RECT_F layoutRect = D2D1::RectF(x, y, x + w, y + h);

	this->m_render->DrawText(url2, wcslen(url2), mat, layoutRect, this->pen);
	free(url2);
}
IDWriteTextFormat * content::createFont(float size, LPWSTR fontFamily) {
	IDWriteTextFormat * u = NULL;
	this->m_writeFac->CreateTextFormat(
		fontFamily,
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		size,
		L"en-US",
		&u
	);
	return u;
};
void content::drawText(string  txt, float x, float y, float w, float h) {
	this->drawText(txt.c_str(), x, y,w,h);
}
content::~content()
{
	SafeRelease(&(this->m_fac));
	SafeRelease(&(this->m_render));
	SafeRelease(&(this->m_render));
	SafeRelease(&(this->brush));
	SafeRelease(&(this->pen));
	SafeRelease(&(this->bitmapBrush));
	SafeRelease(&(this->m_lineStyle));
	SafeRelease(&(this->m_writeFac));
	SafeRelease(&(this->m_forMat));
	SafeRelease(&(this->m_slink));
	SafeRelease(&(this->m_path));
	for (float i = 0; i < imgSource.size(); i++) {
		SafeRelease(&(imgSource[i]));
	}
}
