#pragma once
extern class sprite;
class colVecEx
{
public:
	colVecEx();//构造函数
	~colVecEx();//析构函数
	bool colVecEx::aabb(sprite *sp, sprite *sp2);//检查模式aabb 非向量模式
	void colVecEx::polarCoordinates(const utils::usePoint &p,float angle,float distance,utils::usePoint &cp);//极坐标位移
	float colVecEx::pointAngleInfo(const utils::usePoint point1, const utils::usePoint point2);//获取两点之间的角度
	float colVecEx::bezierCurve(float p0, float p1, float p2, float t); //贝塞尔曲线
	BOOL obb(sprite * sp1, sprite *sp2);//obb碰撞模式
private:
	utils::usePoint project;
	utils::usePoint project2;
	BOOL overlaps();
	void getProject(vec2 v,vector<utils::usePoint> allPoint,int type);
	template <typename T>
	T minVec(vector<T> arr) {
		if (!arr.size()) {
			return 0;
		}
		T min = arr[0]?arr[0]:0;
		for (unsigned int i = 0; i < arr.size(); i++) {
			if (arr[i] < min) {
				min = arr[i];
			}
		}
		return min;
	}
	template <typename T>
	T maxVec(vector<T> arr) {
		if (!arr.size()) {
			return 0;
		}
		T max = arr[0] ? arr[0] : 0;
		for (unsigned int i = 0; i < arr.size(); i++) {
			if (arr[i] > max) {
				max = arr[i];
			}
		}
		return max;
	}
};

