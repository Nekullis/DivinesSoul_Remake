#include "EN_Romanoff.h"
#include "GameEvent.h"
EN_Romanoff* EN_Romanoff::_bossInstance = nullptr;
EN_Romanoff::EN_Romanoff(int model, int weapon, VECTOR vpos, VECTOR vdir) :base(model, weapon, vpos, vdir)
{
	_bossInstance = this;
	//�����l��ݒ�
	MV1SetPosition(mModel, mPos);
	//�̗�
	mHp = 4000;
	//�U����
	mAtk = 20;
	//����ł��邩
	mDie = false;
	//����J�v�Z�����̗v�f��������
	//�J�v�Z���̔��a
	mRadius = 45;
	//�����̒���
	mLineSeg = 191;
	//�J�v�Z���̈ʒu
	mCapsule[0] = mPos;
	mCapsule[1] = VAdd(mPos, VGet(0, mLineSeg, 0));
	//�A�^�b�`����A�j���[�V�����ԍ��̏�����
	mAttachIndex = MV1AttachAnim(mModel, 6, -1, FALSE);
	mName = "romanoff_stand";
	//���Đ����Ԃ̏�����
	mTotalTime = gGlobal.mRS->mGetAttach()[mName]._attach_time;
	//����T�C�Y
	mWeaponSize = 50;
	mDamageCnt = 5;
	//�X�e�[�^�X�𖢔�����
	ChangeStatus(STATUS::NODISCOVERY);
	mType = ENEMYTYPE::ROMANOFF;
}

EN_Romanoff::~EN_Romanoff()
{
	MV1DeleteModel(mModel);
	MV1DetachAnim(mModel, mAttachIndex);
}

void EN_Romanoff::ChangeStatus(STATUS en_status)
{
	//�X�e�[�^�X�̑��
	mData.status = en_status;
	//�J�E���g���Z�b�g
	mActionCnt = 0;
	mTimeCnt = 0;
	switch (mData.status)
	{
	case STATUS::DAMAGE:
		mData.motionTotalFrame = 42;
	}
}

bool EN_Romanoff::A_Process()
{
	//1�t���[���O�̃X�e�[�^�X�ƈႤ�̂Ȃ珈��
	if (mOldAnimation != mAnimation)
	{
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(mModel, mAttachIndex);
		//�X�e�[�^�X�ɂ���ăA�^�b�`����A�j���[�V�����̕ύX
		switch (mAnimation)
		{
		//�ҋ@
		case ANIMATION::WAIT:
			//�L�[����v�����邽�߂ɕ��������
			mName = "romanoff_stand";
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		//�_���[�W
		case ANIMATION::DAMAGE:
			//�L�[����v�����邽�߂ɕ��������
			mName = "romanoff_damage";
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		//�U��
		case ANIMATION::FIRSTATTACK:
			//�L�[����v�����邽�߂ɕ��������
			mName = "romanoff_attack1";
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		case ANIMATION::SECONDATTACK:
			//�L�[����v�����邽�߂ɕ��������
			mName = "romanoff_attack2";
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		//���s
		case ANIMATION::RUN:
			//�L�[����v�����邽�߂ɕ��������
			mName = "romanoff_run";
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		//���s
		case ANIMATION::DIE:
			//�L�[����v�����邽�߂ɕ��������
			mName = "romanoff_die";
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
	mOldAnimation = mAnimation;
	return true;
}

void EN_Romanoff::DiscoveryProcess(VECTOR pl_pos)
{
	float dis_discovery = 2000.0f;
	mAnimation = ANIMATION::WAIT;
	//�v���C���[�ƓG�̈ʒu�̍������o��
	VECTOR v = VSub(mPos, pl_pos);
	//�x�N�g���̃T�C�Y���v�Z
	float len = VSize(v);
	if (len <= dis_discovery)
	{
		ChangeStatus(STATUS::WAIT);
		GameEvent::GetInstance()->SetEvent(1);
	}

}

void EN_Romanoff::WaitProcess()
{
	int action_num = rand() % 10;
	mAnimation = ANIMATION::WAIT;
	mActionCnt++;
	if (mActionCnt >= 70)
	{
		if (action_num < 7)
		{
			//�X�e�[�^�X�𑖍s��
			ChangeStatus(STATUS::RUN);
		}
		else if (action_num >= 7)
		{
			//�X�e�[�^�X��ˌ���
			ChangeStatus(STATUS::ASSAULT);
		}
		
	}
}

void EN_Romanoff::Move(float speed, VECTOR pl_pos)
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

void EN_Romanoff::RunProcess(VECTOR pl_pos)
{
	//�A�j���[�V�����𑖍s��
	mAnimation = ANIMATION::RUN;
	//�X�s�[�h��ݒ�
	float speed = 8.3;
	//�J�E���g���Z
	mActionCnt++;
	//�ړ�����
	Move(speed, pl_pos);
	//�v���C���[�ƓG�̈ʒu�̍������o��
	VECTOR v = VSub(mPos, pl_pos);
	//�x�N�g���̃T�C�Y���v�Z
	float len = VSize(v);
	//�J�E���g���K�萔�A�������̓x�N�g���T�C�Y���K��ȓ�
	if (len <= 100)
	{
		//�X�e�[�^�X���U���ɕύX
		ChangeStatus(STATUS::ATTACK);
	}
	else if (mActionCnt >= 360 && len >= 100)
	{
		//�X�e�[�^�X���U���ɕύX
		ChangeStatus(STATUS::ASSAULT);
	}

}

VECTOR EN_Romanoff::AttackPos()
{
	VECTOR vec = { 0 };
	int frame_index = MV1SearchFrame(mModel, "Character1_Hips");
	//�ʒu�����[�J������O���[�o���ɕϊ�����}�g���b�N�X���쐬
	MATRIX matrix = MV1GetFrameLocalWorldMatrix(mModel, frame_index);
	vec = VTransform(VGet(0, 0, 0), matrix);
	return VGet(vec.x, 0, vec.z);
}

bool EN_Romanoff::Attack()
{
	if (mActionCnt >= 25 && mActionCnt <= 35 ||
		mActionCnt >= 45 && mActionCnt <= 70)
	{
		return true;
	}
	return false;
}

void EN_Romanoff::AttackProcess()
{
	mActionCnt++;
	std::string se_voice = "VO_Ro_Attack";
	SoundItemBase* snditem_voice = gGlobal.mSndServer.Get(se_voice);
	if (Attack())
	{
		//_vPos = AttackPos();
		mIsAttack = true;
	}
	else
	{
		mIsAttack = false;
	}
	if (mActionCnt >= 0 && mActionCnt < 40)
	{
		mAnimation = ANIMATION::FIRSTATTACK;
		if (snditem_voice && snditem_voice->IsLoad())
		{
			// �Đ������H
			if (snditem_voice->IsPlay() == false)
			{
				// �Đ�����
				snditem_voice->Play();
			}
		}
	}
	else if (mActionCnt >= 40 && mActionCnt < 112)
	{
		mAnimation = ANIMATION::SECONDATTACK;
	}
	else if (mActionCnt == 112)
	{
		ChangeStatus(STATUS::WAIT);
	}
}

bool EN_Romanoff::Assult()
{
	if (mActionCnt >= 85 && mActionCnt <= 95)
	{
		return true;
	}
	return false;
}

void EN_Romanoff::AssaultProcess(VECTOR pl_pos)
{
	//�X�s�[�h��ݒ�
	float speed = 30.0;
	float finish_frame = 125;
	float assult_start_frame = 40;
	float dis_assult = 100;
	std::string voice[3] =
	{
		"VO_Ro_Divine1",
		"VO_Ro_DIvine2",
		"VO_Ro_DIvine3"
	};
	SoundItemBase* snditem_voice = gGlobal.mSndServer.Get(voice[rand() % 3]);
	//�J�E���g���Z
	mActionCnt++;
	//�v���C���[�ƓG�̈ʒu�̍������o��
	VECTOR v = VSub(mPos, pl_pos);
	//�x�N�g���̃T�C�Y���v�Z
	float len = VSize(v);
	if (mActionCnt == 1)
	{
		snditem_voice->Play();
	}
	if (mActionCnt < assult_start_frame)
	{
		//�A�j���[�V�����𑖍s��
		Move(speed, pl_pos);
		mAnimation = ANIMATION::RUN;
	}
	else if (mActionCnt == assult_start_frame)
	{
		mAnimation = ANIMATION::FIRSTATTACK;
	}
	else if (mActionCnt == finish_frame)
	{
		ChangeStatus(STATUS::WAIT);
	}
	
	if (Assult())
	{
		//_vPos = AttackPos();
		mIsAttack = true;
	}
	if (mActionCnt < 85 || mActionCnt > 95)
	{
		mIsAttack = false;
	}

}


void EN_Romanoff::DieProcess()
{
	std::string se_voice = "VO_Ro_Blow";
	SoundItemBase* snditem_voice = gGlobal.mSndServer.Get(se_voice);
	mAnimation = ANIMATION::DIE;
	if (snditem_voice && snditem_voice->IsLoad())
	{
		// �Đ������H
		if (snditem_voice->IsPlay() == false)
		{
			// �Đ�����
			snditem_voice->Play();
		}
	}
	mDie = true;
}

void EN_Romanoff::DamageProcess()
{
	mActionCnt++;
	mAnimation = ANIMATION::DAMAGE;
	//�J�E���g�����t���[���ɒB����
	if (mActionCnt >= mData.motionTotalFrame)
	{
		//�X�e�[�^�X�𑖍s��
		ChangeStatus(STATUS::WAIT);
	}

}

bool EN_Romanoff::Damage(VECTOR pl_pos, int subpoint, int nextframe)
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
	mDamageCnt--;
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
		v = VScale(VNorm(v), 50);
		//�X�e�[�^�X���_���[�W��
		if (mDamageCnt <= 0)
		{
			ChangeStatus(STATUS::DAMAGE);
			mDamageCnt = 5;
		}
	}
	mPos = VAdd(mPos, v);
	mNextFrame = nextframe;
	mNoDamage = true;
	return true;
}

bool EN_Romanoff::Suction(VECTOR pl_pos, int nextframe)
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

void EN_Romanoff::SetWeapon()
{
	//�v���C���[�̃��f�����畐��𑕔�����t���[����T��
	int frame_index = MV1SearchFrame(mModel, "joint_axe");
	//�ʒu�����[�J������O���[�o���ɕϊ�����}�g���b�N�X���쐬
	MATRIX weapon_matrix = MV1GetFrameLocalWorldMatrix(mModel, frame_index);
	MATRIX weapon_dir_matrix = MGetRotY(1.75);
	weapon_matrix = MMult(weapon_dir_matrix,weapon_matrix);
	//����ʒu�̐ݒ�
	mWeaponPos[0] = VTransform(VGet(0, 0, 0), weapon_matrix);
	mWeaponPos[1] = VTransform(VGet(0, 150, 0), weapon_matrix);
	//����̈ʒu����̃t���[���ɐݒ�
	MV1SetMatrix(mWeaponModel, weapon_matrix);
}

void EN_Romanoff::Invincible(int nextframe)
{
	//���G���Ԓ��̂݃J�E���g�𑝂₷
	if (mNoDamage) { mInvincibleCnt++; }
	//�J�E���g���K�萔�ɒB����
	if (mInvincibleCnt >= nextframe)
	{
		//���G�t���O��false��
		mNoDamage = false;
		//�J�E���g���Z�b�g
		mInvincibleCnt = 0;
	}
}

bool EN_Romanoff::C_Process(VECTOR pl_pos)
{
	mStatus = mData.status;
	//�J�E���g�̉��Z
	mTimeCnt++;
	//�����蔻��J�v�Z���̈ʒu��ύX
	mCapsule[0] = mPos;
	mCapsule[1] = VAdd(mPos, VGet(0, mLineSeg, 0));
	//��Ԃɂ���ď�����ύX
	switch (mStatus)
	{
	case STATUS::NODISCOVERY:
		DiscoveryProcess(pl_pos);
		break;
	//�ҋ@
	case STATUS::WAIT:
		WaitProcess();
		break;
	//���s
	case STATUS::RUN:
		RunProcess(pl_pos);
		break;
	//�_���[�W
	case STATUS::DAMAGE:
		DamageProcess();
		break;
	//�U��
	case STATUS::ATTACK:
		AttackProcess();
		break;
	//�ˌ�
	case STATUS::ASSAULT:
		AssaultProcess(pl_pos);
		break;
	//���S
	case STATUS::DIE:
		DieProcess();
		break;
	}
	//���܂�Ȃ��悤�Ɉʒu�𒲐�
	if (mPos.y <= 0|| mPos.y >= 0)
	{
		mPos.y = 0;
	}
	Invincible(mNextFrame);
	SetWeapon();
	//�p�x�����߂�̂������W�n���Ⴄ�̂ŕύX
	float angle = atan2(-mDir.x, -mDir.z);
	//���f���̌�����ݒ�
	MV1SetRotationXYZ(mModel, VGet(0, angle, 0));
	MV1SetPosition(mModel, mPos);
	return true;
}

bool EN_Romanoff::Process(VECTOR pl_pos)
{
	C_Process(pl_pos);
	A_Process();
	return true;
}

bool EN_Romanoff::Render()
{
	MV1SetAttachAnimTime(mModel, mAttachIndex, mPlayTime);
	MV1DrawModel(mModel);
	MV1DrawModel(mWeaponModel);
	return true;
}

bool EN_Romanoff::Debug()
{
	return true;
}

bool EN_Romanoff::Delete()
{
	return true;
}








