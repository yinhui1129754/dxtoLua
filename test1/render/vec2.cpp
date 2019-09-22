#include "../stdafx.h"
#include "vec2.h"
vec2::vec2()
{
	x = 0;
	y = 0;
	this->mol = NULL;
	this->singVec = NULL;
}
vec2::vec2(utils::usePoint p) {
	x = p.x;
	y = p.y;
	this->mol = NULL;
	this->singVec = NULL;
};
vec2::vec2(float x, float y) {
	this->x = x;
	this->y = y;
	this->mol = NULL;
	this->singVec = NULL;
};
vec2::~vec2()
{
}
float vec2::getMagnitude(){
	return (float)(sqrt(pow(x, 2) + pow(y, 2)));
}
vec2  vec2::edge(vec2 v2) {
	return vec2(this->x - v2.x,this->y-v2.y);
};
vec2  vec2::perpendicular(){

	vec2  v ;
	v.x = this->y;
	v.y = 0 - this->x;
	return v;
}
vec2  vec2::normalize() {

	vec2  v;
	float m23 = 0.0f;
	m23 = (float)this->getMagnitude();
	if (m23 != 0) {
		v.x = this->x / m23;
		v.y = this->y / m23;
	}
	return v;
}
vec2  vec2::normal() {
	vec2  p = this->perpendicular();
	return p.normalize();
}