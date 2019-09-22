#pragma once
extern class sprite;
extern class winClass;
extern class btn_con;

namespace utils {
	namespace console {
		extern void iptCall(winClass * win);// �̻߳ص�
		extern thread conThread; //�����̱߳���
		extern HANDLE nowEvent; // ���߳������¼����ƶ���
		extern void ipt2(string & s); // �������߳�����
		extern void log(string s); // ��� 
		extern void ipt(string & s); // ����������
		extern string * bufStr; //�����ַ���ָ��
		extern void (*iptEnd)(string s,winClass * win); //����ص�����ָ��
		extern BOOL end; //����رմ��ڿ���̨�߳�������bug
	}
	void luaError(char * s, lua_State *L); //�׳����󵽿���̨
	void luaCall(winClass *win, char *call);
	extern string luaStackInfo(lua_State *L); //���lua����ջ��Ԫ����Ϣ
	extern void getTable(lua_State *L, char * key);
	struct usePoint
	{
		float x;
		float y;
	};
	struct imgInfo {
		BOOL isLoad; //��Դ�Ƿ�������
		DWORD threadId; //�߳�id �Լ����ɵ�����id
		long long pSource; //������Դ��ַ 32λ
	};

	//�Ƴ�vectorģ���е�Ԫ�� ָ����ʽ
	template<class T>
	bool vecRemove(vector<T *> & vc, T * sp) {
		vector<T *>::iterator s = find(vc.begin(),vc.end(),sp);
		if (s == vc.end()) {
			return false;
		}
		vc.erase(s);
		return true;
	}
	//�Ƴ�vectorģ���е�Ԫ�� ������ʽ
	template<class T>
	bool vecRemove(vector<T> & vc, T sp) {
		vector<T>::iterator s = find(vc.begin(), vc.end(), sp);
		if (s == vc.end()) {
			return false;
		}
		vc.erase(s);
		return true;
	}
	//�ַ���תLPWSTR
	extern LPWSTR user_stringToLPWSTR(string orig);
	//LPWSTRתstring
	extern string user_LPWSTRTostring(LPWSTR lpw);
	//lpwstr תlpcstr
	extern LPCSTR user_LPWSTRToLPCSTR(LPWSTR lpw);
	//lpcstrתlpwstr
	extern LPWSTR user_LPCSTRToLPWSTR(LPCSTR lpc);
	//vs����̨���str code�������������� ͨ��%d���
	extern VOID DebugOut(LPCTSTR str, int code);
	extern VOID AlertOut(LPCTSTR str, int code);
	//�����������תstring ;int , long , long , double , short
	template <typename T>
	string user_coutTostring(T a) {
		stringstream  ostring;
		ostring << a;
		return ostring.str();
	};
	//����һ��id ͨ�������ľ�̬�������ɲ��ظ���id
	extern long long GetId();
	//ͨ��λ�����ȡrgbֵ  
	extern UINT getRGB(int r, int g, int b);
	//��ʼ�������������������lua�ű��²���Ҫ����
	extern void initAmt(sprite * sp,float frameW,float frameH, int start = 0, int fx = 0, int size = 3);
	//�ж�һ��POINT�ṹ�Ƿ���һ�����ε���������
	extern BOOL inRect(POINT * mouse, D2D_RECT_F * rc);
	//����������ķ���������lua�ű��¾Ϳ��Բ���Ҫ
	extern float random();
	
	extern int getFillBrushOffsetX(D2D1_RECT_F f, float w);
	extern int getFillBrushOffsetY(D2D1_RECT_F f, float w);
	extern void spriteSayCall(sprite * sp, winClass * app);
	extern void initTranBtn(btn_con * btn);

	template<class T>
	struct prit_effects
	{
		vector<T *>remoevArr; //�����Ƴ�����
		vector<T *>arr; //��������
		int num; //�������
		int nowTimmer;//�������ʱ��
		int allTimmer; //������ʱ��
		float createW; //�������
		float createH; //�����߶�
		float createX; //����X
		float createY; //����Y
		float r;  //��������
	};
	template<class T>
	struct prit_effects_star
	{
		vector<T *>remoevArr; //�����Ƴ�����
		vector<T *>arr; //��������
		int num; //�������
		int nowTimmer;//�������ʱ��
		int allTimmer; //������ʱ��
		sprite * parent; //�������������
		D2D1_RECT_F rc; //������������
		ID2D1Bitmap * img;//������img
	};
	
	namespace NAME_PRIT {
		//��������1
		template <class T>
		void create(winClass *win,
			utils::prit_effects<T> *t, //��������Ч�Ľṹ������
			void(*remove)(T * pc), //������Ҫ�Ƴ���ʱ��Ļص�
			int type = 0, //��������
			void (*before)(int,winClass *) =NULL, //���Ӵ���֮ǰ�Ļص�
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
		//��������2
		template<class T>
		void create_star(winClass *win,
			utils::prit_effects_star<T> *sbInfo, //��������Ч�Ľṹ������
			void(*remove)(T *), //������Ҫ�Ƴ���ʱ��Ļص�
			int type = 0, //��������
			void(*before)(int, winClass *) = NULL, //���Ӵ���֮ǰ�Ļص�
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
	//һ�����õ��Ƴ������ģ��
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
	//һ�����õ��Ƴ������ģ�� �Ը���
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
	//һ�����õ��Ƴ������ģ�� ���ص����Ƴ�����
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