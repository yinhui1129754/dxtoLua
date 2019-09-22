#pragma once
extern class winClass;
class sprite
{
public:
	sprite();
	sprite(char * url, content * cc);
	sprite(ID2D1Bitmap * img,  float width = -1.0f, float height = -1.0f, string spriteType = "default");
	sprite(ID2D1Bitmap * img,float x,float y, float width = -1.0f, float height = -1.0f);

	~sprite();
	void init();
	void initOneFrame(float w, float h,int f=0);
public:
	float x,y, width,height,g_x,g_y; //x y w h
	BOOL visible = true;
	ID2D1Bitmap * img=NULL; //imgָ��
	string  status = "sprite"; //�ṹ����
	
	//�任

	float angle;
	utils::usePoint zoom = { 0.5,0.5 };
	utils::usePoint pivot = {0.5,0.5};

	//��������
	string spriteType = "default";
	D2D1_RECT_F * frame =NULL;
	void initFrame();
	void initFrame(float left, float top, float right, float bottom);
public:
		void initG_x();
		void initG_y();
		void setX(float x);
		void setY(float y);
		float getWidth();
		float getHeight();


		//����id���
		void setId(string id);
		sprite *  getChildById(string id);
		string id = "";
		int addChild(sprite * child);
		int addChild(sprite * child, BOOL bl);
		int removeChild(sprite * child);
		//���û��Զ���ָ��Ķ���
		long long userData;
		//���Ƿ��پ�����
		BOOL inRect(POINT * pt);

		//����ʾ��������
		vector <sprite * >children;
		sprite * parent = NULL;

		//�Զ�����չ����
		oMap<string, int> use_int;
		oMap<string, string>use_str;
		
		//���ƻص�����
		vector<void(*)(winClass *)> drawCallList;

public:
	void render(winClass *);
	//animateSprite
	vector<D2D1_RECT_F>frameArr;//֡����
	unsigned int nowFrame = 0;//��ǰ֡
	float speedTime = 0;//����
	float speedNowTime = 0;//����
	int loop = -1;
	void(*amtEnd)(sprite *);
	//fillSprite
	float fillSrcX = 0;
	float fillSrcY = 0;
	//drawSprite

	void(*drawCall)(sprite *sp, winClass *app);
	long long drawCallArgu = 0;
	//������ײ��
public:
	vector<utils::usePoint> points;
	vector<utils::usePoint> transitionPoints;
	vector<vec2> vecArr;
	//��ȡȫ�������
	utils::usePoint getGlobalPoint(utils::usePoint);
	BOOL renderTranPoint;
	//��ȡ�任��
	void getTransitionPoints();
	void getOneVec();
	void addPoint(utils::usePoint p);
	void initPointToRect();
};

