#include "MathCollision.h"
#include "appframe.h"
MathCollision::MathCollision()
{

}
MathCollision::~MathCollision()
{

}
float MathCollision::DisPointAndLine(VECTOR& v1, VECTOR& v2s, VECTOR& v2e, VECTOR& mp, float& t)
{
	//v1:�_�̍��W
	//v2s:�����̎n�_�̍��W
	//v2e:�����̏I�_�̍��W
	//mp:v1���璼���ɉ����������̒[�_
	//�n�_�ƏI�_�̍��W������̂ł���͐����Ȃ̂����A����͒����Ƃ��Ĉ���
	//t:����v2(v2e-v2s)�̒�����1�Ƃ�������v2s����mp�܂ł̒����̊���

	VECTOR v2 = VSub(v2e, v2s);
	//v2:v2s����v2e�܂ł̒���
	t = 0.0f;
	float dv = VDot(v2, v2);
	if (dv > 0.0f)
	{
		t = VDot(v2, VSub(v1, v2s)) / dv;
		//VDot(v2,VSub(v1,v2s))=|v2||VSub(v1,v2s)|cos��
		//dv=v2*v2
		//t=|VSub(v1,v2s)|cos�� /|v2|
	}
	mp = VAdd(v2s, VScale(v2, t));
	return sqrt(VDot(VSub(v1, mp), VSub(v1, mp)));
}

float MathCollision::DisPointAndSegment(VECTOR& v1, VECTOR& v2s, VECTOR& v2e, VECTOR& mp, float& t)
{
	//v1:�_�̍��W
	//v2s:�����̎n�_�̍��W
	//v2e:�����̏I�_�̍��W
	//mp:v1��������ɉ����������̒[�_
	//t:����v2(v2e-v2s)�̒�����1�Ƃ�������v2s����mp�܂ł̒����̊���
	VECTOR v2 = VSub(v2e, v2s);
	float dist = DisPointAndLine(v1, v2s, v2e, mp, t);
	if (t < 0.0f)
	{
		//�_����n�_�܂ł̋������ŒZ
		mp = v2s;
		return sqrt(VDot(VSub(v1, mp), VSub(v1, mp)));
	}
	if (t > 1.0f)
	{
		//�_��������̏I�_�܂ł̋������ŒZ
		mp = v2e;
		return sqrt(VDot(VSub(v1, mp), VSub(v1, mp)));
	}
	//mp���������ɂ���
	//0 <= t <= 1
	return dist;
}

float MathCollision::DisLineAndLine(VECTOR& v1s, VECTOR& v1e, VECTOR& v1m, float& t1, VECTOR& v2s, VECTOR& v2e, VECTOR& v2m, float& t2)
{
	//v1s:�����̎n�_�̍��W
	//v1e:�����̏I�_�̍��W
	//v1m:�ŒZ���̒[�_1
	//t1:����v1(v1e-v1s)�̒�����1�Ƃ�������v1s����v1m�܂ł̒����̊���
	//v2s:�����̎n�_�̍��W
	//v2e:�����̏I�_�̍��W
	//v2m:�ŒZ���̒[�_2
	//t2:����v2(v2e-v2s)�̒�����1�Ƃ�������v2s����v2m�܂ł̒����̊���
	//�n�_�ƏI�_�̍��W������̂ł���͐����Ȃ̂����A����͒����Ƃ��Ĉ���
	VECTOR v1 = VSub(v1e, v1s);
	VECTOR v2 = VSub(v2e, v2s);
	//2���������s�̏ꍇ
	if (VDot(VCross(v1, v2), VCross(v1, v2)) < 0.000001f && VDot(VCross(v1, v2), VCross(v1, v2)) > -0.000001f);
	{
		//����1�̎n�_���璼��2�܂ł̍ŒZ�������ɋA��
		float dist = DisPointAndLine(v1s, v2s, v2e, v2m, t2);
		v1m = v1s;
		t1 = 0.0f;
		return dist;
	}
	//2���������s�łȂ��ꍇ
	//�݂��������ɂȂ�ŒZ���̒[�_v1m,v2m�����߂�
	float dov1v2 = VDot(v1, v2);
	float dov1v1 = VDot(v1, v1);
	float dov2v2 = VDot(v2, v2);
	VECTOR vp2p1 = VSub(v1s, v2s);
	t1 = (dov1v2 + VDot(v2, vp2p1) - dov2v2 * VDot(v1, vp2p1)) / (dov1v1 * dov2v2 - dov1v2 * dov1v2);
	v1m = VAdd(v1s, VScale(v1, t1));
	t2 = VDot(v2, VSub(v1m, v2s)) / dov2v2;
	v2m = VAdd(v2s, VScale(v2, t2));
	return sqrt(VDot(VSub(v2m, v1m), VSub(v2m, v1m)));
}

float MathCollision::DisSegAndSeg(VECTOR& v1s, VECTOR& v1e, VECTOR& v1m, float& t1, VECTOR& v2s, VECTOR& v2e, VECTOR& v2m, float& t2)
{
	//�͂ݏo���Ȃ��悤�ɃN�����v����֐�������Ă���
	auto clamp0to1 = [](float& f)
		{
			if (f < 0.0f) { f = 0.0f; }
			else if (f > 1.0f) { f = 1.0f; }
		};
	//v1s:�����̎n�_�̍��W
	//v1e:�����̏I�_�̍��W
	//v1m:�ŒZ���̒[�_1
	//t1:����v1(v1e-v1s)�̒�����1�Ƃ�������v1s����v1m�܂ł̒����̊���
	//v2s:�����̎n�_�̍��W
	//v2e:�����̏I�_�̍��W
	//v2m:�ŒZ���̒[�_2
	//t2:����v2(v2e-v2s)�̒�����1�Ƃ�������v2s����v2m�܂ł̒����̊���
	VECTOR v1 = VSub(v1e, v1s);
	VECTOR v2 = VSub(v2e, v2s);
	float dist = 0.0f;
	//��U2�����Ԃ̍ŒZ���������߂�
	dist = DisLineAndLine(v1s, v1e, v1m, t1, v2s, v2e, v2m, t2);
	if (0.0f <= t1 && t1 <= 1.0f && 0.0f <= t2 && t2 <= 1.0f)
	{
		//v1m,v2m�������Ƃ��������ɂ�����
		return dist;
	}
	//�����A�܂��͂ǂ��炩���Ȃ����ߎ���
	clamp0to1(t2);
	v2m = VAdd(v2s, VScale(v2, t2));
	//vb = v2m;
	dist = DisPointAndSegment(v2m, v1s, v1e, v1m, t1);
	if (0.0f <= t1 && t1 <= 1.0f)
	{
		//v2m���������ɂ�����
		return dist;
	}
	//v1m���������ɂȂ��̂Ŏ���
	clamp0to1(t1);
	v1m = VAdd(v1s, VScale(v1, t1));
	//va = v1m;
	dist = DisPointAndSegment(v1m, v2s, v2e, v2m, t2);
	if (0.0f <= t2 && t2 <= 1.0f)
	{
		//v2m���������ɂ�����
		return dist;
	}
	//v2m���������ɂȂ��̂Ŏ���
	//�����܂łȂ�������v1m����v2m�܂ł��ŒZ
	return sqrt(VDot(VSub(v2m, v1m), VSub(v2m, v1m)));
}

float MathCollision::DisPointAndOBB(VECTOR v1p, VECTOR v2p, VECTOR v2d, float w2, float h2, float d2)
{
	float dis = 0;
	VECTOR vec = VGet(0, 0, 0);
	//for���Ŏg����悤�Ɋe�傫����z��ɑ��
	float getlen[3] = { w2,h2,d2 };
	for (auto i = 0; i < 3; i++)
	{
		float l = getlen[i];
		//�e�傫����0���傫���Ȃ瑱�s
		if (l <= 0) { continue; }
		//�_��OBB�̈ʒu�̍����ƕ����x�N�g��������ς��v�Z���A�e�傫���Ŋ���
		float s = VDot(VSub(v1p, v2p), v2d) / l;
		//��Βl�ɕϊ�
		s = std::fabs(s);
		if (s > 1)
		{//��Βl��1���傫���Ȃ�͂ݏo���������̃x�N�g���Z�o
			vec = VAdd(vec, VScale(v2d, (1 - s) * l));
		}
	}
	dis = VSize(vec);
	return dis;
}

bool MathCollision::CollisionPointAndFan(VECTOR v1, VECTOR v2, float rad)
{
	//���ς̌v�Z
	v1 = VNorm(v1);
	v2 = VNorm(v2);
	float dot = VDot(v1, v2);
	//���ς̌v�Z���o�O��Ȃ��悤��
	if (dot < 0.0000001 && dot > -0.0000001) { return false; }
	if (dot > Math::DegToRad(rad))
	{
		return true;
	}
	return false;
}
