#include "../stdafx.h"
#include "ulua_prototype.h"
//输出调试函数
winClass * ulua_prototype::win = NULL;

static int ulua_prototype::addMouseEvent(lua_State *L) {
	int bufInt = lua_gettop(L);
	if (bufInt != 2) {
		utils::luaError("addMouseEvent", L);
		return 0;
	}
	string eventName = lua_tostring(L, 1);
	string eventCall = lua_tostring(L, 2);
	win->eventTable[eventName].push_back(eventCall);
};
static int ulua_prototype::log(lua_State * L) {
	string s = lua_tostring(L,1);
	utils::console::log(s);
	utils::DebugOut(s.c_str(), 0);
	return 0;
};
static int ulua_prototype::getStackNum(lua_State * L) {
	int i = lua_gettop(L);
	lua_pushinteger(L,i);
	return 1;
};
static int ulua_prototype::luaStackInfo(lua_State *L) {
	string s =utils::luaStackInfo(L);
	utils::console::log(s);
	return 0;
};
static int ulua_prototype::fillStyle(lua_State *L) {
	int bufInt = lua_gettop(L);
	if (bufInt != 2) {
		utils::luaError("fillStyle", L);
		return 0;
	}
	win->cContent->fillStyle(lua_tonumber(L, 1), lua_tonumber(L, 2));
	return 0;
};
static int ulua_prototype::strokeStyle(lua_State * L) {
	int bufInt = lua_gettop(L);
	if (bufInt != 2) {
		utils::luaError("strokeStyle", L);
		return 0;
	}
	win->cContent->strokeStyle(lua_tonumber(L, 1), lua_tonumber(L, 2));
	return 0;
};
static int ulua_prototype::fillRect(lua_State * L) {
	int bufInt = lua_gettop(L);	
	if (bufInt != 4) {
		utils::luaError("fillRect",L);
		return 0;
	}
	win->cContent->fillRect(lua_tonumber(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4));
	return 0;
}
static int  ulua_prototype::drawLine(lua_State * L) {
	int bufInt = lua_gettop(L);
	if (bufInt != 4) {
		utils::luaError("drawLine", L);
		return 0;
	}
	win->cContent->drawLine(lua_tonumber(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4));
	return 0;
}
static int  ulua_prototype::fillArc(lua_State * L) {
	int bufInt = lua_gettop(L);
	if (bufInt != 4) {
		utils::luaError("fillArc", L);
		return 0;
	}
	win->cContent->fillArc(lua_tonumber(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4));
	return 0;
}
static int  ulua_prototype::fillRoundRect(lua_State * L) {
	int bufInt = lua_gettop(L);
	if (bufInt != 6) {
		utils::luaError("fillRoundRect", L);
		return 0;
	}
	win->cContent->fillRoundRect(lua_tonumber(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4),
		lua_tonumber(L, 5),
		lua_tonumber(L, 6));

	return 0;
};
static int ulua_prototype::drawImg(lua_State * L) {
	int bufInt = lua_gettop(L);
	if (bufInt != 3 && bufInt != 5 && bufInt != 4 && bufInt != 9) {
		utils::luaError("drawImg", L);
		return 0;
	}
	CHAR * str = (char *)lua_tostring(L, 1);
	double x = lua_tonumber(L, 2);
	double y = lua_tonumber(L, 3);
	switch (bufInt) {
	case 3:
		win->cContent->drawImage(str, x, y);
		break;
	case 4:
		win->cContent->drawImage(str, x, y,lua_tonumber(L,4));
		break;
	case 5:
		win->cContent->drawImage(str, x, y, lua_tonumber(L, 4), lua_tonumber(L, 5));
		break;
	case 9:
		win->cContent->drawImage(
			str, x, y, 
			lua_tonumber(L, 4), 
			lua_tonumber(L, 5),
			lua_tonumber(L, 6), 
			lua_tonumber(L, 7),
			lua_tonumber(L, 8), 
			lua_tonumber(L, 9));
		break;
	}
	return 0;
};
static int ulua_prototype::drawStr(lua_State *L) {
	int bufInt = lua_gettop(L);
	if (bufInt != 3 && bufInt != 5) {
		utils::luaError("drawStr", L);
		return 0;
	}
	CHAR * str = (char *)lua_tostring(L, 1);
	double x = lua_tonumber(L, 2);
	double y = lua_tonumber(L, 3);
	switch (bufInt)
	{
	case 3:
		win->cContent->drawText(str, x, y);
		break;
	case 5:
		win->cContent->drawText(str, x, y,lua_tonumber(L,4),lua_tonumber(L,5));
		break;
	}
	return 0;
};
static int  ulua_prototype::drawArc(lua_State * L) {
	int bufInt = lua_gettop(L);
	if (bufInt != 4) {
		utils::luaError("drawArc", L);
		return 0;
	}
	win->cContent->drawArc(lua_tonumber(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4));
	return 0;
};
static int  ulua_prototype::drawRect(lua_State * L) {
	int bufInt = lua_gettop(L);
	if (bufInt != 4) {
		utils::luaError("drawRect", L);
		return 0;
	}
	win->cContent->drawRect(lua_tonumber(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4));
	return 0;
};
static int  ulua_prototype::drawRoundRect(lua_State * L) {
	int bufInt = lua_gettop(L);
	if (bufInt != 6) {
		utils::luaError("drawRoundRect", L);
		return 0;
	}
	win->cContent->drawRoundRect(lua_tonumber(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4),
		lua_tonumber(L, 5),
		lua_tonumber(L, 6));
	return 0;
};
static int  ulua_prototype::save(lua_State * L) {
	win->cContent->save();
		return 0;
}
static int  ulua_prototype::restore(lua_State * L) {
	win->cContent->restore();
	return 0;
}
static int  ulua_prototype::rotate(lua_State * L) {
	int bufInt = lua_gettop(L);
	if (bufInt != 3) {
		utils::luaError("rotate", L);
		return 0;
	}
	win->cContent->rotate(lua_tonumber(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 3));
	return 0;
};
static int  ulua_prototype::scale(lua_State * L) {
	int bufInt = lua_gettop(L);
	if (bufInt != 3) {
		utils::luaError("scale", L);
		return 0;
	}
	win->cContent->scale(lua_tonumber(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 3));
	return 0;
};
static int  ulua_prototype::skew(lua_State * L) {
	int bufInt = lua_gettop(L);
	if (bufInt != 4) {
		utils::luaError("skew", L);
		return 0;
	}
	win->cContent->skew(lua_tonumber(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 3),
		lua_tonumber(L, 4));
	return 0;
};
static int ulua_prototype::loadImg(lua_State * L) {
	int bufInt = lua_gettop(L);
	if (bufInt != 2) {
		utils::luaError("loadImg", L);
		return 0;
	}
	win->loadImg((char *)lua_tostring(L, 1), (char *)lua_tostring(L, 2));
	return 0;
};


//window 函数
static int ulua_prototype::hideconsole(lua_State *L) {

	win->hideConsole();
	return 0;
};
static int ulua_prototype::showconsole(lua_State *L) {

	win->showConsole();
	return 0;
};
static int ulua_prototype::setwidth(lua_State *L) {
	int bufInt = lua_gettop(L);
	if (bufInt != 1) {
		utils::luaError("setwidth", L);
		return 0;
	}
	win->setWidth(lua_tonumber(L, 1));
	return 0;
};
static int ulua_prototype::setheight(lua_State *L) {
	int bufInt = lua_gettop(L);
	if (bufInt != 1) {
		utils::luaError("setheight", L);
		return 0;
	}
	win->setHeight(lua_tonumber(L, 1));
	return 0;
};
static int ulua_prototype::getwidth(lua_State *L) {
	int w = win->getWidth();
	lua_pushnumber(L, w);
	return 1;
};
static int ulua_prototype::getheight(lua_State *L) {
	int h = win->getHeight();
	lua_pushnumber(L, h);
	return 1;
};
//自定义函数库
static const luaL_Reg ulua_prototype::mylibs_funcs[] = {
{"fillStyle", ulua_prototype::fillStyle},
{"strokeStyle",ulua_prototype::strokeStyle},
{"fillRect", ulua_prototype::fillRect},
{"drawLine",ulua_prototype::drawLine},
{"fillArc",ulua_prototype::fillArc},
{"fillRoundRect",ulua_prototype::fillRoundRect},
{"drawArc",ulua_prototype::drawArc},
{"drawRect",ulua_prototype::drawRect},
{"drawRoundRect",ulua_prototype::drawRoundRect},
{"save",ulua_prototype::save},
{"restore",ulua_prototype::restore},
{"rotate",ulua_prototype::rotate},
{"scale",ulua_prototype::scale},
{"skew",ulua_prototype::skew},
{"drawImg",ulua_prototype::drawImg},
{"drawStr",ulua_prototype::drawStr},
{ NULL, NULL }
};
static const luaL_Reg ulua_prototype::windowlibs_funcs[] = {
	 {"showconsole", ulua_prototype::showconsole},
	 {"hideconsole", ulua_prototype::hideconsole},
	 { "getwidth", ulua_prototype::getwidth },
	 { "getheight", ulua_prototype::getheight },
	 { "setheight", ulua_prototype::setheight },
	 { "setwidth", ulua_prototype::setwidth },
	{ NULL, NULL }
};
//注册的库
static const luaL_Reg ulua_prototype::lua_reg_libs[] = {
	 { "draw", ulua_prototype::regDraw }, //这里为自定义的模块名字mylib
	 { "window", ulua_prototype::regWindow },
		{ NULL, NULL }
};


//注册函数
static int ulua_prototype::regDraw(lua_State * L) {
	luaL_newlib(L, mylibs_funcs); //将所有函数放到一个table中
	
	return 1; //将这个table压到stack里
};
static int ulua_prototype::regWindow(lua_State * L) {
	luaL_newlib(L, windowlibs_funcs);//将所有函数放到一个table中
	return 1; //将这个table压到stack里
};
//注册
void ulua_prototype::registerCall(lua_State * L, winClass * win) {
	ulua_prototype::win = win;
	lua_register(L, "log", log);
	lua_register(L, "getStackNum", getStackNum);
	lua_register(L, "luaStackInfo", ulua_prototype::luaStackInfo);
	lua_register(L, "loadImg", ulua_prototype::loadImg);
	lua_register(L, "addMouseEvent", ulua_prototype::addMouseEvent);
	/*lua_register(L, "draw_fillRect", fillRect);
	lua_register(L, "draw_fillStyle", fillStyle);*/
	const luaL_Reg* lua_reg = lua_reg_libs;
	 for (; lua_reg->func; ++lua_reg) {
		 luaL_requiref(L, lua_reg->name, lua_reg->func, 1);
		     lua_pop(L, 1);
		
	}

};
