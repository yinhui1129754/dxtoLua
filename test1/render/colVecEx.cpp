#include "../stdafx.h"
#include "colVecEx.h"
//#include "frame0.h"

colVecEx::colVecEx()
{
	//分配预留点

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
* 两点之间的角度
* {point1}检测的原点
* {point2}相对于point1为原点的另一个点  
* 这里的点可以直接传我们的精灵全局坐标
*/
float colVecEx::pointAngleInfo(const utils::usePoint point1, const utils::usePoint point2) {
	float x = abs(point1.x - point2.x);
	float y = abs(point1.y - point2.y);
	float z = sqrt(pow(x, 2) + pow(y, 2));
	float cos = y / z;
	float radina = acos(cos);//用反三角函数求弧度
	float angle = floor(180.0f / (M_PI / radina));//将弧度转换成角度
	if (point2.x > point1.x&&point2.y > point1.y) {//鼠标在第四象限
		angle = 180.0f - angle;
	}

	if (point2.x == point1.x&&point2.y == point1.y) {//鼠标在y轴负方向上
		angle = 180.0f;
	}

	if (point2.x > point1.x&&point2.y == point1.y) {//鼠标在x轴正方向上
		angle = 90.0f;
	}

	if (point2.x < point1.x&&point2.y > point1.y) {//鼠标在第三象限
		angle = 180.0f + angle;
	}

	if (point2.x < point1.x&&point2.y == point1.y ) {//鼠标在x轴负方向
		angle = 270.0f;
	}

	if (point2.x < point1.x&&point2.y < point1.y) {//鼠标在第二象限
		angle = 360.0f - angle;
	}
	return angle;
}


/**
* 矩形碰撞方式 aabb 一个正方形和另一个正方形是否碰撞
* {sp} 检测的精灵对象
* {sp2} 检测的精灵对象2
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