#include "../stdafx.h"
#include "colVecEx.h"
//#include "frame0.h"

colVecEx::colVecEx()
{
	//����Ԥ����

}


colVecEx::~colVecEx()
{

}
float colVecEx::bezierCurve(float p0, float p1, float p2, float t) {
	return (1 - t)*(1 - t)*p0 + 2 * t*(1 - t)*p1 + t*t*p2;
}




void colVecEx::polarCoordinates(const utils::usePoint &p, float angle, float distance, utils::usePoint &cp) {
	float l_o = angle*M_PI / 180.0f;
	cp.x = p.x + cos(l_o)*distance;
	cp.y = p.y + sin(l_o)*distance;
};

/**
* ����֮��ĽǶ�
* {point1}����ԭ��
* {point2}�����point1Ϊԭ�����һ����  
* ����ĵ����ֱ�Ӵ����ǵľ���ȫ������
*/
float colVecEx::pointAngleInfo(const utils::usePoint point1, const utils::usePoint point2) {
	float x = abs(point1.x - point2.x);
	float y = abs(point1.y - point2.y);
	float z = sqrt(pow(x, 2) + pow(y, 2));
	float cos = y / z;
	float radina = acos(cos);//�÷����Ǻ����󻡶�
	float angle = floor(180.0f / (M_PI / radina));//������ת���ɽǶ�
	if (point2.x > point1.x&&point2.y > point1.y) {//����ڵ�������
		angle = 180.0f - angle;
	}

	if (point2.x == point1.x&&point2.y == point1.y) {//�����y�Ḻ������
		angle = 180.0f;
	}

	if (point2.x > point1.x&&point2.y == point1.y) {//�����x����������
		angle = 90.0f;
	}

	if (point2.x < point1.x&&point2.y > point1.y) {//����ڵ�������
		angle = 180.0f + angle;
	}

	if (point2.x < point1.x&&point2.y == point1.y ) {//�����x�Ḻ����
		angle = 270.0f;
	}

	if (point2.x < point1.x&&point2.y < point1.y) {//����ڵڶ�����
		angle = 360.0f - angle;
	}
	return angle;
}


/**
* ������ײ��ʽ aabb һ�������κ���һ���������Ƿ���ײ
* {sp} ���ľ������
* {sp2} ���ľ������2
*/
bool colVecEx::aabb(sprite *sp, sprite *sp2) {
	sprite l_sp1 = *sp;
	sprite l_sp2 = *sp2;
	if (l_sp1.x < l_sp2.x + l_sp2.width &&
		l_sp1.x + l_sp1.width > l_sp2.x &&
		l_sp1.y < l_sp2.y + l_sp2.height &&
		l_sp1.height + l_sp1.y > l_sp2.y) {
		return true;
	}
	else {
		return false;
	}
};
BOOL colVecEx::overlaps() {
	return (this->project.x > this->project2.y && this->project2.x > this->project.y);
}
void colVecEx::getProject(vec2 v, vector<utils::usePoint> allPoint, int type) {
	vector<float> scalars;
	vec2 v2;
	for (unsigned int i = 0; i < allPoint.size(); i++) {
		v2.x = allPoint[i].x;
		v2.y = allPoint[i].y;
		scalars.push_back(v2.dot(&v));
	}
	if (type == 0) {
		this->project.y = minVec(scalars);
		this->project.x = maxVec(scalars);
	}
	else if (type == 1) {
		this->project2.y = minVec(scalars);
		this->project2.x = maxVec(scalars);
	}
};
BOOL colVecEx::obb(sprite * sp1, sprite *sp2) {
	sp1->getTransitionPoints();
	sp2->getTransitionPoints();
	sp1->getOneVec();
	sp2->getOneVec();
	vector<vec2> allVec;
	allVec.insert(allVec.end(), sp1->vecArr.begin(), sp1->vecArr.end());
	allVec.insert(allVec.end(), sp2->vecArr.begin(), sp2->vecArr.end());
	unsigned int len = allVec.size();
	
	for (unsigned int i = 0; i < len; i++) {
		vec2 axis = allVec[i];
		this->getProject(axis, sp1->transitionPoints, 0);
		this->getProject(axis, sp2->transitionPoints, 1);
		if (!this->overlaps()) {
			return FALSE;
		}
	}
	return TRUE;
}