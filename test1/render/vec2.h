#pragma once
class vec2
{
public:
	//构造函数
	vec2();
	vec2(utils::usePoint);
	vec2(float x, float y);
	~vec2();
	//向量坐标
	float x;
	float y;
	vec2 * singVec;
	vec2 * mol;
	//取莫
	float getMagnitude();
	//向量加
	void add(vec2 * v2) {
		this->x += v2->x;
		this->y += v2->y;
	};
	//向量减
	void subtract(vec2 * v2) {
		this->x -= v2->x;
		this->y -= v2->y;
	};
	//点乘
	float dot(vec2 * v2) {
		return this->x *v2->x + this->y *v2->y;
	};
	//两点为一个线段
	vec2 edge(vec2 v2);
	//垂直投影轴
	vec2  perpendicular();
	//获取单位向量
	vec2  normalize();
	//投影轴单位向量
	vec2  normal();
};

