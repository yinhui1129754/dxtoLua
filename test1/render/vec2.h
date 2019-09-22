#pragma once
class vec2
{
public:
	//���캯��
	vec2();
	vec2(utils::usePoint);
	vec2(float x, float y);
	~vec2();
	//��������
	float x;
	float y;
	vec2 * singVec;
	vec2 * mol;
	//ȡĪ
	float getMagnitude();
	//������
	void add(vec2 * v2) {
		this->x += v2->x;
		this->y += v2->y;
	};
	//������
	void subtract(vec2 * v2) {
		this->x -= v2->x;
		this->y -= v2->y;
	};
	//���
	float dot(vec2 * v2) {
		return this->x *v2->x + this->y *v2->y;
	};
	//����Ϊһ���߶�
	vec2 edge(vec2 v2);
	//��ֱͶӰ��
	vec2  perpendicular();
	//��ȡ��λ����
	vec2  normalize();
	//ͶӰ�ᵥλ����
	vec2  normal();
};

