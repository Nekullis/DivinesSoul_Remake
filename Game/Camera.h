#pragma once
#include "appframe.h"

class Camera
{
public:
	Camera();
	virtual ~Camera();
	static Camera* cameraInstance;
	void Process(short stix, short stiy);
	//�Q�b�^�[
	static Camera* GetInstance() { return cameraInstance; }
	VECTOR GetTarget()	{ return mTarget; }
	VECTOR GetDir()		{ return mDir; }
	VECTOR GetPos()		{ return mPos; }
	//�Z�b�^�[
	void SetTarget(VECTOR vec) { mTarget = vec; }
protected:
	//GameXPad* mPad;
	//�J�����ʒu
	VECTOR mPos;
	VECTOR mDir;
	//�J���������_
	VECTOR mTarget;
	//�ŒZ�`�拗��
	float mNear;
	//�Œ��`�拗��
	float mFar;
	//�΂˒萔
	float mSpring;
	//�����萔
	float mDampFactor;
	//�ʒu�Ƒ��x
	VECTOR mCurrentPos;
	VECTOR mCurrentVelocity;
};

