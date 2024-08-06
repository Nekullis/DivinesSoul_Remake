#include "EN_Crab.h"
EN_Crab::EN_Crab(int model, int weapon, VECTOR vpos, VECTOR vdir) : base(model, weapon, vpos, vdir)
{
	//�����l��ݒ�
	MV1SetPosition(mModel, mPos);
	//�ړ���
	mMove = VGet(0, 0, 0);
	//�̗�
	mHp = 60;
	//�U����
	mAtk = 5;
	//����J�v�Z�����̗v�f��������
	//�J�v�Z���̔��a
	mRadius = 43;
	//�����̒���
	mLineSeg = 170;
	//�J�v�Z���̈ʒu
	mCapsule[0] = mPos;
	mCapsule[1] = VAdd(mPos, VGet(0, mLineSeg, 0));
	//�X�e�[�^�X��ҋ@��Ԃ�
	ChangeStatus(STATUS::WAIT);
	mType = ENEMYTYPE::CRAB;
}
EN_Crab::~EN_Crab()
{
	MV1DeleteModel(mModel);
}

void EN_Crab::ChangeStatus(STATUS en_status)
{
	//�X�e�[�^�X�̑��
	mData.status = en_status;
	//�J�E���g���Z�b�g
	mActionCnt = 0;
	mTimeCnt = 0;
	//�e��Ԃ̑����[�V�����t���[���ƒT���͈͂̑��
	switch (mData.status)
	{
	//�ҋ@
	case STATUS::WAIT:
		mData.motionTotalFrame = 0;
		mData.searchArea = 2000;
		break;
	//�U��
	case STATUS::ATTACK:
		mData.motionTotalFrame = 0;
		mData.searchArea = 100;
		break;
	//�x�e
	case STATUS::REST:
		mData.motionTotalFrame = 60;
		mData.searchArea = 100;
		break;
	//���S
	case STATUS::DIE:
		mData.motionTotalFrame = 60;
		mData.searchArea = 100;
		break;
	}
}
bool EN_Crab::C_Process(VECTOR pl_pos)
{
	//�J�E���g�̉��Z
	mActionCnt++;
	mTimeCnt++;
	//�X�e�[�^�X���f�[�^���̕ύX���ꂽ�X�e�[�^�X��
	mStatus = mData.status;
	//�����蔻��J�v�Z���̈ʒu��ύX
	mCapsule[0] = mPos;
	mCapsule[1] = VAdd(mPos, VGet(0, mLineSeg, 0));
	//���[�J���ϐ��̏�����
	VECTOR v = VGet(0, 0, 0);
	float len = 0;
	//�ړ����x
	float speed = 0;
	//��Ԃɂ���ď�����ύX�@
	switch (mStatus)
	{
		//�ҋ@
	case STATUS::WAIT:
		//�ړ����Ȃ����ߑ��x��0��
		speed = 0;
		//�v���C���[�ƓG�̈ʒu�̍������o��
		v = VSub(mPos, pl_pos);
		//�x�N�g���̃T�C�Y���v�Z
		len = VSize(v);
		//�G����v���C���[�̋������T���͈͓�
		if (len * len <= mData.searchArea * mData.searchArea)
		{
			//�X�e�[�^�X���U����
			ChangeStatus(STATUS::ATTACK);
		}
		break;
		//�U��
	case STATUS::ATTACK:
		//�U�����Ȃ̂Ńt���O��true��
		mIsAttack = true;
		//���[�J���ϐ�
		VECTOR vec_pl_pos = VGet(0, 0, 0);
		VECTOR vector = VGet(0, 0, 0);
		//�ړ����x��ݒ�
		speed = 2;
		//0.5�b�ɂP�񏈗�
		if (mTimeCnt >= 30)
		{
			//���g�̈ʒu�ƃv���C���[�̃x�N�g�����쐬
			vec_pl_pos = VSub(mPos, pl_pos);
			//�����x�N�g���ƃv���C���[�Ƃ̈ʒu�x�N�g���̍����x�N�g�����o���Ă���2���̃x�N�g�����o��
			vector = VScale(VSub(mDir, vec_pl_pos), 0.2);
			//�����x�N�g���ƕ����x�N�g�����������邱�Ƃňړ������̃x�N�g�����ł���
			vector = VAdd(vector, mDir);
			//�����x�N�g���̐��K�����A�����x�N�g����
			mDir = VNorm(vector);
			//�J�E���g���Z�b�g
			mTimeCnt = 0;
		}
		//�����x�N�g���ɃX�s�[�h�����������̂��ړ��x�N�g���Ƃ���
		mMove = VScale(mDir, speed);
		//�ʒu�x�N�g���Ɉړ��x�N�g�������Z
		mPos = VAdd(mPos, mMove);
		break;
	case STATUS::REST:
		if (mActionCnt > mData.motionTotalFrame)
		{
			//�X�e�[�^�X���U����
			ChangeStatus(STATUS::ATTACK);
		}
		break;
	case STATUS::DAMAGE:
		//�J�E���g�����t���[���ɒB����
		if (mActionCnt >= mData.motionTotalFrame)
		{
			//�X�e�[�^�X�𑖍s��
			ChangeStatus(STATUS::RUN);
		}
		break;
	case STATUS::DIE:
		mIsAttack = false;
		mDie = true;
		Delete();
		break;
	}
	if (mNoDamage) { mInvincibleCnt++; }
	if (mInvincibleCnt >= mNextFrame)
	{
		mNoDamage = false;
		mInvincibleCnt = 0;
	}
	//���܂�Ȃ��悤�Ɉʒu�𒲐�
	if (mPos.y <= 0 || mPos.y >= 0)
	{
		mPos.y = 0;
	}
	if (mDie)
	{
		float rate = 1;
		mStatus = STATUS::DIE;
		for (rate; rate >= 0; rate -= 0.05)
		{
			MV1SetOpacityRate(mModel, rate);
		}
		if (rate < 0)
		{
			Delete();
			mDeleteFlag = true;
		}

	}
	else { mPlayTime = 0; }
	//���f���̈ʒu��ݒ�
	MV1SetPosition(mModel, mPos);
	//���f���̌�����ݒ�
	//�p�x�����߂�̂������W�n���Ⴄ�̂ŕύX
	float angle = atan2(-mDir.x, -mDir.z);
	MV1SetRotationXYZ(mModel, VGet(0,angle,0));
	return true;
}
bool EN_Crab::Damage(VECTOR pl_pos, int subpoint, int nextframe)
{
	SoundItemBase* snditem_se = gGlobal.mSndServer.Get("SE_Damage");
	snditem_se->SetVolume(200);
	if (snditem_se && snditem_se->IsLoad())
	{
		// �Đ������H
		if (snditem_se->IsPlay() == false)
		{
			// �Đ�����
			snditem_se->Play();
		}
	}
	VECTOR v = VSub(mPos, pl_pos);
	mHp = mHp - subpoint;
	if (mHp <= 0)
	{
		v = VScale(VNorm(v), 100);
		//�X�e�[�^�X�����S��
		ChangeStatus(STATUS::DIE);
	}
	else if (mHp > 0)
	{
		v = VScale(VNorm(v), 200);
	}
	mPos = VAdd(mPos, v);
	mNextFrame = nextframe;
	return true;
}

bool EN_Crab::Suction(VECTOR pl_pos, int nextframe)
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

	VECTOR v = VSub(mPos, pl_pos);
	v = VScale(VNorm(v), -5);
	mPos = VAdd(mPos, v);
	mNextFrame = nextframe;
	mNoDamage = true;
	return true;
}

bool EN_Crab::Process(VECTOR pl_pos)
{
	C_Process(pl_pos);
	return true;
}

bool EN_Crab::Render()
{
	MV1SetAttachAnimTime(mModel, mAttachIndex, mPlayTime);
	MV1DrawModel(mModel);
	return true;
}

bool EN_Crab::Debug()
{
	base::Debug();
	return true;
}

bool EN_Crab::Delete()
{
	base::Delete();
	return true;
}






