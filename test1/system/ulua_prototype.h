#pragma once

namespace ulua_prototype {
	extern winClass * win;
	static int log(lua_State * L); //���
	static int getStackNum(lua_State * L); //��ȡlua����ջ�е�Ԫ�ظ���
	static int luaStackInfo(lua_State *L);
	static int addMouseEvent(lua_State *L);
	//����ģ���
	extern  const luaL_Reg mylibs_funcs[];
	extern  const luaL_Reg windowlibs_funcs[];
	extern  const luaL_Reg lua_reg_libs[];
	
	//������������
	static int loadImg(lua_State * L);

	static int regDraw(lua_State* L);
	static int regWindow(lua_State* L);
	//�滭ģ��
	static int fillRect(lua_State * L);
	static int fillStyle(lua_State *L);
	static int  fillArc(lua_State * L);
	static int  fillRoundRect(lua_State * L);
	static int  drawArc(lua_State * L);
	static int  drawRect(lua_State * L);
	static int  drawRoundRect(lua_State * L);
	static int drawLine(lua_State * L);
	static int save(lua_State * L);
	static int restore(lua_State * L);
	static int  rotate(lua_State * L);
	static int  scale(lua_State * L);
	static int  skew(lua_State * L);
	static int strokeStyle(lua_State * L);
	static int drawImg(lua_State * L);
	static int drawStr(lua_State *L);

	extern void registerCall(lua_State * L, winClass * win); //ע�ắ��
	


	//���ڲ�������
	static int hideconsole(lua_State *L);
	static int showconsole(lua_State *L);
	static int setwidth(lua_State *L);
	static int setheight(lua_State *L);
	static int getwidth(lua_State *L);
	static int getheight(lua_State *L);
}
