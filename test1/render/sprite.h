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
	ID2D1Bitmap * img=NULL; //img指针
	string  status = "sprite"; //结构名称
	
	//变换

	float angle;
	utils::usePoint zoom = { 0.5,0.5 };
	utils::usePoint pivot = {0.5,0.5};

	//精灵类型
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


		//设置id相关
		void setId(string id);
		sprite *  getChildById(string id);
		string id = "";
		int addChild(sprite * child);
		int addChild(sprite * child, BOOL bl);
		int removeChild(sprite * child);
		//给用户自定义指针的东西
		long long userData;
		//点是否再矩形中
		BOOL inRect(POINT * pt);

		//子显示对象数组
		vector <sprite * >children;
		sprite * parent = NULL;

		//自定义扩展属性
		oMap<string, int> use_int;
		oMap<string, string>use_str;
		
		//绘制回调函数
		vector<void(*)(winClass *)> drawCallList;

public:
	void render(winClass *);
	//animateSprite
	vector<D2D1_RECT_F>frameArr;//帧数组
	unsigned int nowFrame = 0;//当前帧
	float speedTime = 0;//毫秒
	float speedNowTime = 0;//毫秒
	int loop = -1;
	void(*amtEnd)(sprite *);
	//fillSprite
	float fillSrcX = 0;
	float fillSrcY = 0;
	//drawSprite

	void(*drawCall)(sprite *sp, winClass *app);
	long long drawCallArgu = 0;
	//向量碰撞点
public:
	vector<utils::usePoint> points;
	vector<utils::usePoint> transitionPoints;
	vector<vec2> vecArr;
	//获取全局坐标点
	utils::usePoint getGlobalPoint(utils::usePoint);
	BOOL renderTranPoint;
	//获取变换点
	void getTransitionPoints();
	void getOneVec();
	void addPoint(utils::usePoint p);
	void initPointToRect();
};

