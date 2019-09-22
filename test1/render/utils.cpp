#include "../stdafx.h"

//字符转码函数
LPWSTR utils::user_stringToLPWSTR(std::string orig) {

	int lng = orig.length();
	LPWSTR d = (LPWSTR)malloc(sizeof(PWSTR)*(lng+1));
	memset(d, 0, sizeof(PWSTR)*(lng + 1));
	MultiByteToWideChar(CP_ACP, 0, orig.c_str(), lng, d, lng * sizeof(PWSTR));
	return d;
}
string utils::user_LPWSTRTostring(LPWSTR lpw) {
	int lng = lstrlenW(lpw);
	LPSTR d = (LPSTR)malloc(sizeof(PSTR)*lng);
	memset(d, 0, sizeof(PSTR)*lng);
	WideCharToMultiByte(CP_OEMCP, NULL, lpw, -1, d, sizeof(PSTR)*lng, NULL, FALSE);
	string q = d;
	return q;
}
LPCSTR utils::user_LPWSTRToLPCSTR(LPWSTR lpw) {
	string s1 = utils::user_LPWSTRTostring(lpw);
	return (s1.c_str());
}
LPWSTR utils::user_LPCSTRToLPWSTR(LPCSTR lpc) {
	string s1 = lpc;
	return utils::user_stringToLPWSTR(s1);
}
VOID utils::DebugOut(LPCTSTR str, int code) {
	CHAR sOut[256];
	sprintf_s(sOut, str, code);
	::OutputDebugString(sOut);
};
VOID utils::AlertOut(LPCTSTR str, int code) {

	MessageBox(NULL, str,"title", MB_OK);
};
long long utils::GetId() {
	static long long i = 0;
	i++;
	return i;
}
BOOL utils::console::end = FALSE;
void(*utils::console::iptEnd)(string s, winClass * win) = NULL;
HANDLE utils::console::nowEvent;
string * utils::console::bufStr = NULL;
thread utils::console::conThread;
void utils::console::log(string s) {
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

	WriteConsole(output, s.c_str(), s.length(), NULL, NULL);
}
string utils::luaStackInfo(lua_State *L) {
	int a = lua_gettop(L);
	int i = 1;
	string s2 = "";
	s2 = s2 + "stack element:\n";
	if (i <= a) {
		for (i = 1; i <= a; i++) {
			int t = lua_type(L, i);
			switch (t) {
			case LUA_TSTRING:
				s2 = s2 + lua_tostring(L, i) + "\n";
				break;
			case LUA_TBOOLEAN:
				s2 = s2 + (lua_toboolean(L, i) ? "true" : "false") + "\n";
				break;
			case LUA_TNUMBER:
				s2 = s2 + lua_tostring(L, i) + "\n";
				break;
			default: /* other values */
				s2 = s2 + lua_typename(L, t) + "\n";
				break;
			}
		}
	}
	else {
		s2 = s2 + "no element \n";
	}
	
	return s2;
};
void utils::luaError(char * s,lua_State *L) {
	int a = lua_gettop(L);
	int i = 0;
	char buf[4];
	_itoa_s(a, buf, 10);
	string s2 = "luaerror:";
	s2 = s2+s+";\nstack num: " + buf + "\n";
	s2 = s2 + utils::luaStackInfo(L);
	int ex = (int)luaL_optinteger(L, 2, 0);
	int res = lua_gc(L, LUA_GCCOUNT, ex);
	int b = lua_gc(L, LUA_GCCOUNTB, 0);
	ostringstream os;
	os << ((lua_Number)res + ((lua_Number)b / 1024));
	s2 = s2+"memory:" + os.str() + "\n";
	utils::console::log(s2);
}
void utils::luaCall(winClass *w, char *call) {
	int bRet = 0;
	lua_getglobal(w->L, call);
	lua_pcall(w->L, 0, 0, 0);
	if (bRet)
	{
		string s2 = lua_tostring(w->L, -1);
		s2 = "pcall error\n" + s2;
		utils::AlertOut(s2.c_str(), 0);
		return;
	}
};
void utils::getTable(lua_State *L, char * key) {
	lua_getglobal(L, key);
	lua_pushnil(L);
	stringstream ss;
	while (lua_next(L, 1) != 0) {
		int keyType = lua_type(L, -2);
		if (keyType == LUA_TNUMBER) {
			double value = lua_tonumber(L, -2);
			ss << "Key:" << value << "\n"<<"stack number:"<<lua_gettop(L)<<"\n";
		}
		else if (keyType == LUA_TSTRING) {
			const char*  value = lua_tostring(L, -2);
			ss << "Key:" << value << "\n" << "stack number:" << lua_gettop(L) << "\n";
		}
		else {
			ss << "Key:" << keyType << "\n" << "stack number:" << lua_gettop(L) << "\n";

			return;
		}
		int valueType = lua_type(L, -1);
		switch (valueType) {
		case LUA_TNIL:
		{
			ss << "Value: nil" << "\n";
			break;
		}
		case LUA_TBOOLEAN:
		{
			int value = lua_toboolean(L, -1);
			ss << "Value:" << value << "\n";
			break;
		}
		case LUA_TNUMBER:

		{    
			ss << "Value:" << lua_tonumber(L,-1) << "\n";
		break;
		}
		case LUA_TSTRING:
		{
			ss << "Value:" << lua_tonumber(L, -1) << "\n";
			break;
		}
		case LUA_TTABLE:
		{

			ss << "table"  << "\n";
			
			break;
		}
		default:
		{
			ss << "Invalid value type: " << valueType << "\n";
			return;
		}
		}
		lua_pop(L, 1);
	}
	utils::console::log(ss.str());

};

 void utils::console::iptCall(winClass * win) {
	while (TRUE) {
		
		WaitForSingleObject(utils::console::nowEvent, INFINITE);
		if (!utils::console::end) {
			utils::console::ipt(*utils::console::bufStr);
		}
		else {
			break;
		}
		ResetEvent(utils::console::nowEvent);
		if (utils::console::iptEnd != NULL) {
			utils::console::iptEnd(*utils::console::bufStr, win);
		}
	}
};
void utils::console::ipt2(string & s) {
	utils::console::bufStr = &s;
	SetEvent(utils::console::nowEvent);
};

void utils::console::ipt(string & s) {
	HANDLE ipt = GetStdHandle(STD_INPUT_HANDLE);
	DWORD nowInt = 0;
	char buffer[1024];
	ReadConsole(ipt, buffer, 1024, &nowInt, NULL);
	
	if (nowInt != 0) {
		s = buffer;
		s = s.substr(0, nowInt);
	}
}
//传入r g b 三个分量 获取一个数值颜色值
UINT utils::getRGB(int r,int g,int b){
		int buf = r << 8;
		buf = buf + g;
		buf = buf << 8;
		buf = buf + b;
		return buf;
}



//
int utils::getFillBrushOffsetX(D2D1_RECT_F f, float w) {
	float f1 = f.right / w;
	int d1 = 0;
	if ((int)f.left > (int)f.right) {
		d1 = ((int)f.left % (int)f.right);
		d1 = (float)d1 / f.right*w;
	}
	else if (f.left != 0) {
		d1 = ((int)f.left % (int)f.right);
		d1 = (float)d1 / f.right*w;
	}
	return d1;
};
//
int utils::getFillBrushOffsetY(D2D1_RECT_F f, float w) {
	float f1 = f.bottom / w;
	int d1 = 0;
	if ((int)f.top > (int)f.bottom) {
		d1 = ((int)f.top % (int)f.bottom);
		d1 = (float)d1 / f.bottom*w;
	}
	else if (f.top != 0) {
		d1 = ((int)f.top % (int)f.bottom);
		d1 = (float)d1 / f.bottom*w;
	}
	return d1;
};
//初始化动画
void utils::initAmt(sprite * view, float frameW, float frameH, int start, int fx, int size) {
	view->spriteType = "animateSprite";
	float w = view->img->GetSize().width;
	float h = view->img->GetSize().height;
	int allWidth = w / frameW;
	int allHeight = h / frameH;
	int i = 0;

	while (view->frameArr.size())
	{
		view->frameArr.pop_back();
	}
	if (fx == 0) { //0横向 1竖直
		if (size > allWidth) {
			size = allWidth;
		}
		for (i = 0; i < size; i++) {
			view->frameArr.push_back(D2D1::RectF(i*frameW, start*frameH, frameW, frameH));
		}
	}
	else if (fx == 1) {
		if (size > allHeight) {
			size = allHeight;
		}
		for (i = 0; i < size; i++) {
			view->frameArr.push_back(D2D1::RectF(start*frameW, i*frameH, frameW, frameH));
		}
	}
}
//点是否在矩形
BOOL utils::inRect(POINT * mouse, D2D_RECT_F * rc) {

	return (mouse->x >= rc->left&&mouse->x <= rc->left + rc->right &&mouse->y > rc->top&&mouse->y <= rc->top + rc->bottom);
};
//随机数
float utils::random() {
	static int i;
	i++;
	srand(time(NULL)*i);
	return (float)(rand()% 1000 / (double)1000);
}
