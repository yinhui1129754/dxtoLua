#pragma once
extern class sprite;
extern class winClass;
extern class btn_con;

namespace utils {
	namespace console {
		extern void iptCall(winClass * win);// 线程回调
		extern thread conThread; //声明线程变量
		extern HANDLE nowEvent; // 多线程输入事件控制对象
		extern void ipt2(string & s); // 触发多线程输入
		extern void log(string s); // 输出 
		extern void ipt(string & s); // 阻塞主进程
		extern string * bufStr; //输入字符串指针
		extern void (*iptEnd)(string s,winClass * win); //输入回调函数指针
		extern BOOL end; //解决关闭窗口控制台线程阻塞的bug
	}
	void luaError(char * s, lua_State *L); //抛出错误到控制台
	void luaCall(winClass *win, char *call);
	extern string luaStackInfo(lua_State *L); //输出lua虚拟栈的元素信息
	extern void getTable(lua_State *L, char * key);
	struct usePoint
	{
		float x;
		float y;
	};
	struct imgInfo {
		BOOL isLoad; //资源是否加载完成
		DWORD threadId; //线程id 自己生成的整形id
		long long pSource; //储存资源地址 32位
	};

	//移出vector模板中的元素 指针形式
	template<class T>
	bool vecRemove(vector<T *> & vc, T * sp) {
		vector<T *>::iterator s = find(vc.begin(),vc.end(),sp);
		if (s == vc.end()) {
			return false;
		}
		vc.erase(s);
		return true;
	}
	//移出vector模板中的元素 变量形式
	template<class T>
	bool vecRemove(vector<T> & vc, T sp) {
		vector<T>::iterator s = find(vc.begin(), vc.end(), sp);
		if (s == vc.end()) {
			return false;
		}
		vc.erase(s);
		return true;
	}
	//字符串转LPWSTR
	extern LPWSTR user_stringToLPWSTR(string orig);
	//LPWSTR转string
	extern string user_LPWSTRTostring(LPWSTR lpw);
	//lpwstr 转lpcstr
	extern LPCSTR user_LPWSTRToLPCSTR(LPWSTR lpw);
	//lpcstr转lpwstr
	extern LPWSTR user_LPCSTRToLPWSTR(LPCSTR lpc);
	//vs控制台输出str code可以是任意数字 通过%d输出
	extern VOID DebugOut(LPCTSTR str, int code);
	extern VOID AlertOut(LPCTSTR str, int code);
	//所有输出类型转string ;int , long , long , double , short
	template <typename T>
	string user_coutTostring(T a) {
		stringstream  ostring;
		ostring << a;
		return ostring.str();
	};
	//生成一个id 通过自增的静态变量生成不重复的id
	extern long long GetId();
	//通过位运算获取rgb值  
	extern UINT getRGB(int r, int g, int b);
	//初始化动画精灵这里可能在lua脚本下不需要用了
	extern void initAmt(sprite * sp,float frameW,float frameH, int start = 0, int fx = 0, int size = 3);
	//判断一个POINT结构是否在一个矩形的区域里面
	extern BOOL inRect(POINT * mouse, D2D_RECT_F * rc);
	//随机数产生的方法不过在lua脚本下就可以不需要
	extern float random();
	
	extern int getFillBrushOffsetX(D2D1_RECT_F f, float w);
	extern int getFillBrushOffsetY(D2D1_RECT_F f, float w);
	extern void spriteSayCall(sprite * sp, winClass * app);
	extern void initTranBtn(btn_con * btn);

	template<class T>
	struct prit_effects
	{
		vector<T *>remoevArr; //粒子移除数组
		vector<T *>arr; //粒子数组
		int num; //最大数量
		int nowTimmer;//创建间隔时间
		int allTimmer; //创建总时间
		float createW; //创建宽度
		float createH; //创建高度
		float createX; //创建X
		float createY; //创建Y
		float r;  //创建概率
	};
	template<class T>
	struct prit_effects_star
	{
		vector<T *>remoevArr; //粒子移除数组
		vector<T *>arr; //粒子数组
		int num; //最大数量
		int nowTimmer;//创建间隔时间
		int allTimmer; //创建总时间
		sprite * parent; //放入的容器精灵
		D2D1_RECT_F rc; //创建矩形区域
		ID2D1Bitmap * img;//创建的img
	};
	
	namespace NAME_PRIT {
		//粒子类型1
		template <class T>
		void create(winClass *win,
			utils::prit_effects<T> *t, //该粒子特效的结构配置项
			void(*remove)(T * pc), //粒子需要移除的时候的回调
			int type = 0, //粒子类型
			void (*before)(int,winClass *) =NULL, //粒子创建之前的回调
			void (*after)(int,winClass *,T *) =NULL) {
			if (t->nowTimmer < 0 && t->num>0) {
				t->nowTimmer = t->allTimmer;
				if (utils::random() < t->r) {
					if (before != NULL) {
						before(type, win);
					}
					t->num--;
					T * lpPc = new T();
					lpPc->view->setX(t->createX);
					lpPc->view->setY(t->createY);
					lpPc->remove = remove;
					lpPc->setWeightHeight(t->createW, t->createH);
					if (after != NULL) {
						after(type, win, lpPc);
					}
					t->arr.push_back(lpPc);
				};
			}
			else {
				t->nowTimmer--;
			}
		}
		//粒子类型2
		template<class T>
		void create_star(winClass *win,
			utils::prit_effects_star<T> *sbInfo, //该粒子特效的结构配置项
			void(*remove)(T *), //粒子需要移除的时候的回调
			int type = 0, //粒子类型
			void(*before)(int, winClass *) = NULL, //粒子创建之前的回调
			void(*after)(int, winClass *, T *) = NULL) {
			if (sbInfo->num >= 0) {
				if (sbInfo->nowTimmer <= 0) {
					sbInfo->nowTimmer = sbInfo->allTimmer;
					if (before) {
						before(type, win);
					}
					sprite * sp = new sprite(sbInfo->img);
					T * t = new  T(sp, &sbInfo->rc, remove);
					sbInfo->arr.push_back(t);
					if (after) {
						after(type, win, t);
					}
					sbInfo->parent->addChild(sp);
					sbInfo->num--;
				}
				else {
					sbInfo->nowTimmer--;
				}
			}
		}
	}
	//一个常用的移除对象的模板
	template <class key>
	void removeCall1(vector<key * >&karr, vector<key * >&karr2) {
		for (size_t i = 0; i < karr.size(); i++) {
			key * d = karr[i];
			utils::vecRemove(karr2, d);
			utils::vecRemove(karr, d);
			delete d;
			d = NULL;
			i--;
		}
	}
	//一个常用的移除对象的模板 对父级
	template<class key>
	void removeCall2(vector<key * >&karr, vector<key * >&karr2) {
		for (size_t i = 0; i < karr.size(); i++) {
			key * d = karr[i];
			d->view->parent->removeChild(d->view);
			utils::vecRemove(karr2, d);
			utils::vecRemove(karr, d);
			delete d;
			d = NULL;
			i--;
		}
	}
	//一个常用的移除对象的模板 带回调的移除函数
	template<class key>
	void removeCall3(vector<key * >&karr, vector<key * >&karr2,int type=0,void (*removeCall)(int)=NULL) {
		for (size_t i = 0; i < karr.size(); i++) {
			key * d = karr[i];
			utils::vecRemove(karr2, d);
			utils::vecRemove(karr, d);
			delete d;
			d = NULL;
			i--;
			if (removeCall != NULL) {
				removeCall(type);
			}
		}
	}

}