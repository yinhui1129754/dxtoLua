#pragma once
extern class sprite;
class colVecEx
{
public:
	colVecEx();//���캯��
	~colVecEx();//��������
	bool colVecEx::aabb(sprite *sp, sprite *sp2);//���ģʽaabb ������ģʽ
	void colVecEx::polarCoordinates(const utils::usePoint &p,float angle,float distance,utils::usePoint &cp);//������λ��
	float colVecEx::pointAngleInfo(const utils::usePoint point1, const utils::usePoint point2);//��ȡ����֮��ĽǶ�
	float colVecEx::bezierCurve(float p0, float p1, float p2, float t); //����������
	BOOL obb(sprite * sp1, sprite *sp2);//obb��ײģʽ
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

