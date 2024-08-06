#include "Camera.h"
#include "Player.h"
#include "ApplicationGlobal.h"
#include <cmath>

Camera* Camera::cameraInstance = nullptr;
Camera::Camera()
{
	cameraInstance = this;
	//�����_������
	mTarget = { 0 };
	//�ʒu������
	mPos = Player::GetInstance()->GetPos();
	mDir = { 0 };
	//�ŒZ�`�拗��������
	mNear = 20;
	//�Œ��`�拗��������
	mFar = 50000;
	//�΂˒萔
	mSpring = 0.1;
	//�����萔
	mDampFactor = 0.8;
	mCurrentPos = mPos;
	mCurrentVelocity = { 0 };
}

Camera::~Camera()
{
}

void Camera::Process(short stix, short stiy)
{
	//�p�b�h���͂Ŋp�x����
	if (gGlobal.gPad->GetXRx() < 0) { mDir.y -= 0.05; }
	if (gGlobal.gPad->GetXRx() > 0) { mDir.y += 0.05; }
	//�����_�ݒ�
	VECTOR target;
	VECTOR plpos = Player::GetInstance()->GetPos();
	//�J�����ʒu���v���[���[�ʒu�ɋ��^���W�n����ω��������W�n�𑫂������W�ɂ���
	VECTOR pos = VAdd(plpos , Math::ConvertToCartesian(mDir, 700));
	//�㓪����菭�����߂̈ʒu�ɂ���
	pos.y += 300;
	target = plpos; 
	mPos = pos;
	//�΂˗͌v�Z
	VECTOR springforce = VScale(VSub(mCurrentPos,pos), - mSpring);
	//�����͌v�Z
	VECTOR dampforce = VScale(mCurrentVelocity, -mDampFactor);
	//�����͂��v�Z���Ă���
	VECTOR force = VAdd(springforce,dampforce);
	VECTOR accseler = force;
	//���x�X�V
	mCurrentVelocity = VAdd(mCurrentVelocity,accseler);
	//�ʒu�X�V
	mCurrentPos = VAdd(mCurrentPos,mCurrentVelocity);
	mPos = mCurrentPos;
	//�J�����`�ʂ̍ŒZ�����A�Œ�������ݒ肷��
	SetCameraNearFar(mNear, mFar);
	//�J�����̈ʒu�ƒ����_�𔽉f����
	SetCameraPositionAndTarget_UpVecY(mCurrentPos, target);
}
