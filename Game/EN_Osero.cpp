#include "EN_Osero.h"
EN_Osero::EN_Osero(int model, int weapon, VECTOR vpos, VECTOR vdir) : base(model, weapon, vpos, vdir)
{
	//�����l��ݒ�
	MV1SetPosition(mModel, mPos);
	//�̗�
	mHp = 50;
	//�U����
	mAtk = 8;
	//����ł��邩
	mDie = false;
	//�J�v�Z���̔��a
	mRadius = 35;
	//�����̒���
	mLineSeg = 191;
	//�J�v�Z���̈ʒu
	mCapsule[0] = mPos;
	mCapsule[1] = VAdd(mPos, VGet(0, mLineSeg, 0));
	//�A�^�b�`����A�j���[�V�����ԍ��̏�����
	mAttachIndex = MV1AttachAnim(mModel, 6, -1, FALSE);
	//���Đ����Ԃ̏�����
	mTotalTime = gGlobal.mRS->mGetAttach()["osero_stand"]._attach_time;
	//����T�C�Y
	mWeaponSize = 30;
	//�X�e�[�^�X��ҋ@��Ԃ�
	ChangeStatus(STATUS::WAIT);
	mType = ENEMYTYPE::OSERO;
}
EN_Osero::~EN_Osero()
{
	MV1DeleteModel(mModel);
	MV1DetachAnim(mModel, mAttachIndex);
}
void EN_Osero::ChangeStatus(STATUS en_status)
{
	mActionCnt = 0;
	mTimeCnt = 0;
	//�X�e�[�^�X�̑��
	mStatus = en_status;
	//�e��Ԃ̑����[�V�����t���[���ƒT���͈͂̑��
	switch (mStatus)
	{
	//�ҋ@
	case WAIT:
		mData.motionTotalFrame = 0;
		mData.searchArea = 1000;
		break;
	//�_���[�W
	case DAMAGE:
		mData.motionTotalFrame = 42;
		mData.searchArea = 0;
		break;
	//�x��
	case CAUTION:
		mData.motionTotalFrame = 0;
		mData.searchArea = 0;
		break;
	//�U��
	case ATTACK:
		mData.motionTotalFrame = 38;
		mData.searchArea = 200;
		break;
	//���s
	case RUN:
		mData.motionTotalFrame = 31;
		mData.searchArea = 200;
		break;
	}
}
bool EN_Osero::A_Process()
{
	//std::string mName;
	std::string name[2] =
	{
		"osero_walk_left",
		"osero_walk_right",
	};
	//1�t���[���O�̃X�e�[�^�X�ƈႤ�̂Ȃ珈��
	if (mOldStatus != mStatus)
	{
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(mModel, mAttachIndex);
		//�X�e�[�^�X�ɂ���ăA�^�b�`����A�j���[�V�����̕ύX
		switch (mStatus)
		{
		//�ҋ@
		case STATUS::WAIT:
			//�L�[����v�����邽�߂ɕ��������
			mName = "osero_stand";
			mAttachIndex = MV1AttachAnim(mModel,gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		//�_���[�W
		case STATUS::DAMAGE:
			//�L�[����v�����邽�߂ɕ��������
			mName = "osero_damage";
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		//�x��
		case STATUS::CAUTION:
			//�L�[����v�����邽�߂ɕ��������
			mName = name[rand() % 2];
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		//�U��
		case STATUS::ATTACK:
			//�L�[����v�����邽�߂ɕ��������
			mName = "osero_attack1";
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		//���s
		case STATUS::RUN:
			//�L�[����v�����邽�߂ɕ��������
			mName = "osero_run";
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
			//���s
		case STATUS::DIE:
			//�L�[����v�����邽�߂ɕ��������
			mName = "osero_die";
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		}
		// �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
		mTotalTime = gGlobal.mRS->mGetAttach()[mName]._attach_time;
		mPlayTime = 0.0f;
	}
	
	// �Đ����Ԃ�i�߂�
	mPlayTime += 1.0f;
	// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
	if (mPlayTime >= mTotalTime)
	{
		if (mDie)
		{
			mPlayTime = mTotalTime;
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
	}
	//�ꎞ�I�ȃX�e�[�^�X�̕ύX
	mOldStatus = mStatus;
	return true;
}
void EN_Osero::WaitProcess(VECTOR pl_pos)
{
	//�v���C���[�ƓG�̈ʒu�̍������o��
	VECTOR v = VSub(mPos, pl_pos);
	//�x�N�g���̃T�C�Y���v�Z
	float len = VSize(v);
	//�G����v���C���[�̋������T���͈͓�
	if (len * len <= mData.searchArea * mData.searchArea)
	{
		//�X�e�[�^�X�𑖍s��
		ChangeStatus(STATUS::RUN);
	}
}


void EN_Osero::Move(float speed, VECTOR pl_pos)
{
	//���[�J���ϐ���ݒ�
	VECTOR vec_pl_pos = VGet(0, 0, 0);
	VECTOR vector = VGet(0, 0, 0);
	//���g�̈ʒu�ƃv���C���[�̃x�N�g�����쐬
	vec_pl_pos = VSub(pl_pos, mPos);
	//�x�N�g���𐳋K��
	VECTOR vunit = VNorm(vec_pl_pos);
	//���K�������x�N�g����
	vector = vunit;
	//������ݒ肷�邽�߂ɑ��
	mDir = vec_pl_pos;
	//�����x�N�g���ɃX�s�[�h�����������̂��ړ��x�N�g���Ƃ���
	mMove = VScale(vector, speed);
	//�ʒu�x�N�g���Ɉړ��x�N�g�������Z
	mPos = VAdd(mPos, mMove);
}

void EN_Osero::RunProcess(VECTOR pl_pos)
{
	float speed = 10;
	Move(speed, pl_pos);
	//�v���C���[�ƓG�̈ʒu�̍������o��
	VECTOR v = VSub(mPos, pl_pos);
	//�x�N�g���̃T�C�Y���v�Z
	float len = VSize(v);
	//�G����v���C���[�̋������T���͈͓�
	if (len * len <= mData.searchArea * mData.searchArea)
	{
		//�X�e�[�^�X���x����
		ChangeStatus(STATUS::CAUTION);
	}
	if (len >= 2100)
	{
		//�X�e�[�^�X��ҋ@��
		ChangeStatus(STATUS::WAIT);
	}

}
void EN_Osero::CautionProcess(VECTOR pl_pos)
{
	mActionCnt++;
	float attack_frame = 70 * (rand() % 10 + 1);
	if (mName == "osero_walk_left")
	{
		mPos.x += 0.1;
	}
	if (mName == "osero_walk_right")
	{
		mPos.x -= 0.1;
	}
	//�v���C���[�ƓG�̈ʒu�̍������o��
	VECTOR v = VSub(pl_pos, mPos);
	//�x�N�g���̃T�C�Y���v�Z
	float len = VSize(v);
	//�v���C���[�ƓG�̔���J�v�Z���̍��v
	float add_radius = mData.searchArea + 30;
	MATRIX m = MGetRotY(mDir.y);
	VECTOR vec = VGet(m.m[2][0], m.m[2][1], m.m[2][2]);
	//vec = VScale(vec, -1);
	//�v���C���[���G�̍��G�͈͂ɓ�����
	if (MathCollision::CollisionPointAndFan(vec, v, 50))
	{
		//�J�E���g���U���܂ł̃t���[���ɒB����
		if (mActionCnt >= attack_frame)
		{
			//�X�e�[�^�X���U����
			ChangeStatus(STATUS::ATTACK);
		}
	}
	if (len >= 300)
	{
		//�X�e�[�^�X�𑖍s��
		ChangeStatus(STATUS::RUN);
	}
}
void EN_Osero::AttackProcess()
{
	mActionCnt++;
	//�U�����Ȃ̂Ńt���O��true��
	mIsAttack = true;
	//�J�E���g�������[�V�����t���[���ɒB����
	if (mActionCnt >= mData.motionTotalFrame)
	{
		//�U�����I������̂Ńt���O��false��
		mIsAttack = false;
		//�X�e�[�^�X�𑖍s��
		ChangeStatus(STATUS::RUN);
	}
}

void EN_Osero::DamageProcess()
{
	mActionCnt++;
	//�J�E���g�����t���[���ɒB����
	if (mActionCnt >= mData.motionTotalFrame)
	{
		//�X�e�[�^�X�𑖍s��
		ChangeStatus(STATUS::RUN);
	}
}

void EN_Osero::DieProcess()
{
	mDie = true;
	mIsAttack = false;
}
void EN_Osero::SetWeapon()
{
	//�v���C���[�̃��f�����畐��𑕔�����t���[����T��
	int frame_index = MV1SearchFrame(mModel, "joint_sword");
	//�ʒu�����[�J������O���[�o���ɕϊ�����}�g���b�N�X���쐬
	MATRIX weapon_matrix = MV1GetFrameLocalWorldMatrix(mModel, frame_index);
	mWeaponPos[0] = VTransform(VGet(0, 0, 0), weapon_matrix);
	mWeaponPos[1] = VTransform(VGet(0, 100, 0), weapon_matrix);
	//����̈ʒu����̃t���[���ɐݒ�
	MV1SetMatrix(mWeaponModel, weapon_matrix);
}

void EN_Osero::Invincible(int nextframe)
{
	////���G���Ԓ��̂݃J�E���g�𑝂₷
	//if (mNoDamage) { mInvincibleCnt++; }
	//if (mInvincibleCnt >= mNextFrame)
	//{
	//	mNoDamage = false;
	//	mInvincibleCnt = 0;
	//}
}
VECTOR EN_Osero::AttackPos()
{
	return VECTOR();
}
bool EN_Osero::C_Process(VECTOR pl_pos)
{
	
	//�J�E���g�̉��Z
	mTimeCnt++;
	//�����蔻��J�v�Z���̈ʒu��ύX
	mCapsule[0] = mPos;
	mCapsule[1] = VAdd(mPos, VGet(0, mLineSeg, 0));
	//��Ԃɂ���ď�����ύX
	switch (mStatus)
	{
	//�ҋ@
	case STATUS::WAIT:
		WaitProcess(pl_pos);
		break;
	//���s
	case STATUS::RUN:
		RunProcess(pl_pos);
		break;
	//�_���[�W
	case STATUS::DAMAGE:
		DamageProcess();
		break;
	//�x��
	case STATUS::CAUTION:
		CautionProcess(pl_pos);
		break;
	//�U��
	case STATUS::ATTACK:
		AttackProcess();
		break;
	//���S
	case STATUS::DIE:
		DieProcess();
		break;
	}
	//���܂�Ȃ��悤�Ɉʒu�𒲐�
	mPos.y -= 10;
	if (mPos.y <= 0)
	{
		mPos.y = 0;
	}
	//���G���Ԓ��̂݃J�E���g�𑝂₷
	Invincible(mNextFrame);
	SetWeapon();
	//���f���̈ʒu��ݒ�
	MV1SetPosition(mModel, mPos);
	//�p�x�����߂�̂������W�n���Ⴄ�̂ŕύX
	float angle = atan2(-mDir.x, -mDir.z);
	//���f���̌�����ݒ�
	MV1SetRotationXYZ(mModel, VGet(0,angle,0));
	return true;
}

bool EN_Osero::Process(VECTOR pl_pos)
{
	A_Process();
	C_Process(pl_pos);
	return true;
}

bool EN_Osero::Damage(VECTOR pl_pos,int subpoint, int nextframe)
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
		v = VScale(VNorm(v), 85);
		ChangeStatus(STATUS::DAMAGE);
	}
	mPos = VAdd(mPos, v);
	/*mNextFrame = nextframe;
	mNoDamage = true;*/
	return true;
}

bool EN_Osero::Suction(VECTOR pl_pos, int nextframe)
{
	Enemy::Suction(pl_pos,nextframe);
	return true;
}

bool EN_Osero::Render()
{
	MV1SetAttachAnimTime(mModel, mAttachIndex, mPlayTime);
	MV1SetRotationXYZ(mWeaponModel, VGet(0, 0.5, 0));
	MV1DrawModel(mModel);
	MV1DrawModel(mWeaponModel);
	return true;
}
bool EN_Osero::Debug()
{
	base::Debug();
	DrawFormatString(0, 200, GetColor(255, 255, 255), "cnt=%d", mActionCnt);
	DrawFormatString(0, 200, GetColor(255, 255, 255), "time=%d", mPlayTime);
	return true;
}
bool EN_Osero::Delete()
{
	base::Delete();
	return true;
}
