#include "enemy.h"
Enemy::Enemy(int model, int weapon,VECTOR vpos, VECTOR vdir)
{
	mModel = MV1DuplicateModel(model);
	mWeaponModel = MV1DuplicateModel(weapon);
	//�����l��ݒ�
	mPos = vpos;
	mDir = vdir;
	mMove = VGet(0, 0, 0);
	MV1SetPosition(mModel, mPos);
	MV1SetRotationXYZ(mModel, mDir);
	//����J�v�Z�����̗v�f��������
	mCapsule[0] = mPos;
	mCapsule[1] = VAdd(mPos, VGet(0, 150, 0));
	mRadius = 0;
	mLineSeg = 0;
	mWeaponPos[0] = VGet(0, 0, 0);
	mWeaponPos[1] = VGet(0, 0, 0);
	mWeaponSize = 0;
	//�̗�
	mHp = 0;
	mAtk = 0;
	mDie = false;
	mDeleteFlag = false;
	//�J�E���g������
	mActionCnt = 0;
	mInvincibleCnt = 0;
	mNextFrame = 1;
	mTimeCnt = 0;
	//�U�����ł͂Ȃ��̂�false��
	mIsAttack = false;
	//�_���[�W���󂯂Ă��Ȃ��̂�
	mDamage = false;
	mNoDamage = false;
	//�Đ����Ԃ̏�����
	mPlayTime = 0.0f;
	//���Đ����Ԃ̏�����
	mTotalTime = 0;
	//�A�^�b�`����A�j���[�V�����ԍ��̏�����
	mAttachIndex = -1;
	mType = ENEMYTYPE::NOCHARA;
}
Enemy::~Enemy()
{
	MV1DeleteModel(mModel);
}

bool Enemy::Process(VECTOR pl_pos)
{
	return true;
}
bool Enemy::Render()
{
	return true;
}
bool Enemy::Debug()
{
	return true;
}
bool Enemy::Delete()
{
	MV1DeleteModel(mModel);
	return true;
}

bool Enemy::Damage(VECTOR pl_pos, int subpoint,int nextframe)
{
	return true;
}

bool Enemy::Suction(VECTOR pl_pos, int nextframe)
{
	SoundItemBase* snditem_se = gGlobal.mSndServer.Get("SE_Damage");
	if (snditem_se && snditem_se->IsLoad())
	{
		// �Đ������H
		if (snditem_se->IsPlay() == false)
		{
			// �Đ�����
			snditem_se->Play();
		}
	}
	ChangeStatus(STATUS::DAMAGE);
	VECTOR v = VSub(mPos, pl_pos);
	v = VScale(VNorm(v), -5);
	mPos = VAdd(mPos, v);
	mNextFrame = nextframe;
	mNoDamage = true;
	return true;
}

void Enemy::ChangeStatus(STATUS en_status)
{

}
