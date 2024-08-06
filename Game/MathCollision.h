#pragma once
#include"dxlib.h"
#include<cmath>
class MathCollision
{
public:
	MathCollision();
	virtual ~MathCollision();
	//�_�ƒ����̍ŒZ����
	static float DisPointAndLine(VECTOR& v1, VECTOR& v2s, VECTOR& v2e, VECTOR& mp, float& t);
	//�_�Ɛ����̍ŒZ����
	static float DisPointAndSegment(VECTOR& v1, VECTOR& v2s, VECTOR& v2e, VECTOR& mp, float& t);
	//�����ƒ����̍ŒZ����
	static float DisLineAndLine(VECTOR& v1s, VECTOR& v1e, VECTOR& v1m, float& t1, VECTOR& v2s, VECTOR& v2e, VECTOR& v2m, float& t2);
	//�����Ɛ����̍ŒZ����
	static float DisSegAndSeg(VECTOR& v1s, VECTOR& v1e, VECTOR& v1m, float& t1, VECTOR& v2s, VECTOR& v2e, VECTOR& v2m, float& t2);
	//�_��OBB�̍ŒZ����
	static float DisPointAndOBB(VECTOR v1p, VECTOR v2p, VECTOR v2d, float w2, float h2, float d2);
	//�_�Ɛ�`�̓����蔻��
	//v1:�����x�N�g��, v2:�����x�N�g��, rad;�p�x
	static bool CollisionPointAndFan(VECTOR v1, VECTOR v2, float rad);
};

