// stdafx.h: 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 项目特定的包含文件
//

#pragma once

#include "targetver.h"
// Windows 头文件: 
#include <windows.h>

#include <functional>
// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
//C++运行库
#include <iostream>
#include <thread>
#include <sstream>
#define M_PI       3.14159265358979323846   // pi
#include <cmath>
#include <time.h>
// TODO:  在此处引用程序需要的其他头文件
#include <d2d1_3.h>

#include <d2d1helper.h>
#include <d2d1_3helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <vector>
#include <future>
#include <Digitalv.h>
#include <dshow.h>
#pragma comment (lib,"Strmiids.lib")
#pragma comment (lib,"Quartz.lib")
#pragma comment(lib,"d2d1.lib")
#pragma comment (lib, "dwrite.lib")
/*文件操作类*/
#include <fstream>
//消息提示宏
#define _REMIND_ME0(a) #a
#define _REMIND_ME1(a) __FILE__ "(" _REMIND_ME0(a) ") : "
#define REMIND_ME(a) message(_REMIND_ME1(__LINE__)a)

using namespace std;
template<class Interface>
inline void SafeRelease(
	Interface **ppInterfaceToRelease
)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();

		(*ppInterfaceToRelease) = NULL;
	}
}
//定义声音类出错进行提示 如果没有定义就不提示
#define U_DX_SHOW_MESSAGETOOLTIP
extern "C"
{
	#include "lua/lua.h"  
	#include "lua/lauxlib.h"  
	#include "lua/lualib.h"  
}
// 在此处引用程序需要的其他标头
#include "render/oMap.h"
//工具类
#include "render/utils.h"


//渲染类
#include "render/content.h"
//计时器类
#include "render/timmer.h"
//核心winclass类
#include "render/winClass.h"
//键盘输入类
#include "render/input.h"
//向量
#include "render/vec2.h"
//升级碰撞算法
#include "render/colVecEx.h"
//精灵类
#include "render/sprite.h"
//声音类
//#include "render/mci_sound.h"
#include "render/dshow_sound.h"
