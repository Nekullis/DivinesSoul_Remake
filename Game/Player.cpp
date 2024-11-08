#include "Player.h"
#include "ApplicationGlobal.h"
#include "Camera.h"

Player* Player::mPlInstance = nullptr;
Player::Player() 
{
	mPlInstance = this;
	//�ʒu
	mPos = VGet(0.0f, 0.0f, 0.0f);
	//�p�x
	mDir = VGet(0.0f, 1.0f, 0.0f);
	SetJsonTransform();
	//�ړ�
	mMove = VGet(0.0f, 0.0f, 0.0f);
	//�J�v�Z���̒���
	mLineSeg = 170.0f;
	//�J�v�Z�����a
	mRCap = 30.0f;
	//�J�v�Z�����_(��)
	mCapsule[0] = VGet(mPos.x + 0.0f, mPos.y + 50.0f, mPos.z + 0.0f);
	//�J�v�Z�����_(��)
	mCapsule[1] = VGet(mPos.x + 0.0f, mPos.y - 50.0f, mPos.z + 0.0f);
	//���f���`��
	mModel = 0;
	//�A�^�b�`����A�j���[�V�����ԍ�
	mAttachIndex = -1;
	//�d�͏�����
	mGravity = -15.0f;
	//�U������
	mIsAttack = false;
	//���G����
	mNoDamage = false;
	//�X�L����������
	mIsSkill = false;
	//����ł��邩
	mIsDie = false;
	//�Q�[���I�[�o�[�t���O
	mGameOverFlag = false;
	//�Ō�ɉ������{�^��
	mLastCommand = -1;
	//����ʒu
	mWPos[0] = VGet(0, 0, 0);
	mWPos[1] = VGet(0, 0, 0);
	mSkill = new Divine();
	//�e�p�����[�^����
	mHp = 255;
	mAtk = 0;

	mOldMotion = CHARACTER_MOTION::PLAYER_STAND;
	mMotion = CHARACTER_MOTION::PLAYER_STAND;
	mMotionManager = new MotionTableManager();
	mMotionManager->LoadTable("res/csv/player/Motion/Motion_Table_STAND.csv",		CHARACTER_MOTION::PLAYER_STAND,			MotionTable::MOTION_ENDTYPE::LOOP,	MOTION_LAYER::ALWAYS);
	mMotionManager->LoadTable("res/csv/player/Motion/Motion_Table_RUN.csv",			CHARACTER_MOTION::PLAYER_RUN,			MotionTable::MOTION_ENDTYPE::LOOP,	MOTION_LAYER::PRESS_DOWN);
	mMotionManager->LoadTable("res/csv/player/Motion/Motion_Table_FIRSTATTACK.csv",	CHARACTER_MOTION::PLAYER_FIRSTATTACK,	MotionTable::MOTION_ENDTYPE::END,	MOTION_LAYER::TRIGGER);
	mMotionManager->LoadTable("res/csv/player/Motion/Motion_Table_SECONDATTACK.csv",CHARACTER_MOTION::PLAYER_SECONDATTACK,	MotionTable::MOTION_ENDTYPE::END,	MOTION_LAYER::TRIGGER);
	mMotionManager->LoadTable("res/csv/player/Motion/Motion_Table_LASTATTACK.csv",	CHARACTER_MOTION::PLAYER_LASTATTACK,	MotionTable::MOTION_ENDTYPE::END,	MOTION_LAYER::TRIGGER);
	mMotionManager->LoadTable("res/csv/player/Motion/Motion_Table_DASHATTACK.csv",	CHARACTER_MOTION::PLAYER_DASHATTACK,	MotionTable::MOTION_ENDTYPE::END,	MOTION_LAYER::TRIGGER);
	mMotionManager->LoadTable("res/csv/player/Motion/Motion_Table_SKILL.csv",		CHARACTER_MOTION::PLAYER_SKILL,			MotionTable::MOTION_ENDTYPE::END,	MOTION_LAYER::TRIGGER);
	mMotionManager->LoadTable("res/csv/player/Motion/Motion_Table_SKILLDASH.csv",	CHARACTER_MOTION::PLAYER_SKILLDASH,		MotionTable::MOTION_ENDTYPE::LOOP,	MOTION_LAYER::TRIGGER);
	mMotionManager->LoadTable("res/csv/player/Motion/Motion_Table_DAMAGE.csv",		CHARACTER_MOTION::PLAYER_DAMAGE,		MotionTable::MOTION_ENDTYPE::END,	MOTION_LAYER::DAMAGE);
	mMotionManager->LoadTable("res/csv/player/Motion/Motion_Table_DIE.csv",			CHARACTER_MOTION::PLAYER_DIE,			MotionTable::MOTION_ENDTYPE::DIE,	MOTION_LAYER::TRIGGER);
	mMotionManager->LoadTable("res/csv/player/Motion/Motion_Table_AVOID.csv",		CHARACTER_MOTION::PLAYER_AVOID,			MotionTable::MOTION_ENDTYPE::END,	MOTION_LAYER::TRIGGER);
	mMotionManager->ChangeMotion(mMotion);

	mAttackManager = new AttackTableManager();
	mAttackManager->LoadAttackData("res/csv/player/AttackData/Attack_Data_NONE.csv",			ATTACK_TYPE::NONE,"","");
	mAttackManager->LoadAttackData("res/csv/player/AttackData/Attack_Data_NORMALATTACK.csv",	ATTACK_TYPE::NORMAL_ATTACK, "VO_Fe_Attack01", "SE_Attack01");
	mAttackManager->LoadAttackData("res/csv/player/AttackData/Attack_Data_SCONDATTACK.csv",		ATTACK_TYPE::SCOND_ATTACK,  "VO_Fe_Attack02", "SE_Attack02");
	mAttackManager->LoadAttackData("res/csv/player/AttackData/Attack_Data_THIRDATTACK.csv",		ATTACK_TYPE::THIRD_ATTACK,  "VO_Fe_Attack03", "SE_Attack03");
	mAttackManager->LoadAttackData("res/csv/player/AttackData/Attack_Data_DASHATTACK.csv",		ATTACK_TYPE::DASH_ATTACK,	"VO_Fe_Attack03", "SE_Attack01");
	mAttackManager->AttackChange(ATTACK_TYPE::NONE);
}

Player::~Player()
{
	delete mSkill;
	delete mMotionManager;
	delete mAttackManager;
	MV1DetachAnim(mModel, mAttachIndex);
}

void Player::SetJsonTransform()
{
	JsonUtility* jUtil;
	jUtil = new JsonUtility();
	nlohmann::json player_pos = jUtil->Import("res/Json/Player_pos.json").at("Player Start");
	for (auto& data : player_pos)
	{
		data.at("translate").at("x").get_to(mPos.x);
		data.at("translate").at("z").get_to(mPos.y);
		data.at("translate").at("y").get_to(mPos.z);
		// ���W�̕ϊ�
		mPos.z *= -1.f;
		data.at("rotate").at("x").get_to(mDir.x);
		data.at("rotate").at("z").get_to(mDir.y);
		data.at("rotate").at("y").get_to(mDir.z);
		// ��]��degree��radian��
		mDir.x = Math::DegToRad(mDir.x);
		mDir.y = Math::DegToRad(mDir.y);
		mDir.z = Math::DegToRad(mDir.z);
	}
}

void Player::Initialize(int handle, int weapon)
{
	// ���f���f�[�^�̃��[�h�i�e�N�X�`�����ǂݍ��܂��j	
	mModel = handle;
	mDashModel = MV1LoadModel("res/Model/Character/Player/A_DashAttack.mv1");
	// 3D���f����1�Ԗڂ̃A�j���[�V�������A�^�b�`����
	mAttachIndex = MV1AttachAnim(mModel, 0, -1, FALSE);
	//���탂�f���̃��[�h
	mWModel = weapon;
	mOldIndex = -1;
	mRate = 1.f;
}

void Player::A_Process()
{
	std::string mname;
	if (mOldMotion != mMotionManager->GetMotion())
	{
		//MV1DetachAnim(mModel, mAttachIndex);
		mOldIndex = mAttachIndex;
		mRate = 1.f;
		switch (mMotion)
		{
		case CHARACTER_MOTION::PLAYER_STAND:
			// �ҋ@��Ԃ̃A�j���[�V�������A�^�b�`����
			mname = "player_stand";
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mname]._attach_index, -1, FALSE);
			break;
		case CHARACTER_MOTION::PLAYER_RUN:
			// ����A�j���[�V�������A�^�b�`����
			mname = "player_run";
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mname]._attach_index, -1, FALSE);
			break;
		case CHARACTER_MOTION::PLAYER_FIRSTATTACK:
			//�c�a�胂�[�V�������A�^�b�`����
			mname = "player_attack1";
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mname]._attach_index, -1, FALSE);
			break;
		case CHARACTER_MOTION::PLAYER_SECONDATTACK:
			//���a�胂�[�V�������A�^�b�`����
			mname = "player_attack2";
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mname]._attach_index, -1, FALSE);
			break;
		case CHARACTER_MOTION::PLAYER_LASTATTACK:
			//��]�a�胂�[�V�������A�^�b�`����
			mname = "player_attack3";
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mname]._attach_index, -1, FALSE);
			break;
		case CHARACTER_MOTION::PLAYER_DASHATTACK:
			//�_�b�V���U�����[�V�������A�^�b�`����
			//mname = "player_avoid";
			mAttachIndex = MV1AttachAnim(mModel, 0, mDashModel, true);
			break;
		case CHARACTER_MOTION::PLAYER_SKILL:
			//�f�B�o�C���X�L�����g�p���郂�[�V�������A�^�b�`����
			mname = "player_skill";
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mname]._attach_index, -1, FALSE);
			break;
		case CHARACTER_MOTION::PLAYER_SKILLDASH:
			//�f�B�o�C���X�L�����g�p���郂�[�V�������A�^�b�`����
			mname = "player_run";
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mname]._attach_index, -1, FALSE);
			break;
		case CHARACTER_MOTION::PLAYER_AVOID:
			//������[�V�������A�^�b�`����
			mname = "player_avoid";
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mname]._attach_index, -1, FALSE);
			break;
		case CHARACTER_MOTION::PLAYER_DAMAGE:
			//�_���[�W���[�V�������A�^�b�`����
			mname = "player_damage";
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mname]._attach_index, -1, FALSE);
			break;
		case CHARACTER_MOTION::PLAYER_DIE:
			//���S���[�V�������A�^�b�`����
			mname = "player_blow";
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mname]._attach_index, -1, FALSE);
			break;
		}
		//���[�V�����X�e�[�^�X�ύX
		mMotionManager->ChangeMotion(mMotion);
	}
	if (mOldIndex != -1)
	{
		mRate -= 0.1;
		MV1SetAttachAnimBlendRate(mModel, mOldIndex, mRate);
		MV1SetAttachAnimBlendRate(mModel, mAttachIndex, 1.f - mRate);
		if (mRate <= 0.0f)
		{
			mOldIndex = -1;
			mRate = 0.f;
			MV1DetachAnim(mModel, mOldIndex);
		}
	}
	//�����[�V�����X�V
	mOldMotion = mMotion;
	// �Đ����Ԃ��Z�b�g����
	int motioncnt = mMotionManager->GetMotionCnt();
	MV1SetAttachAnimTime(mModel, mAttachIndex, motioncnt);
}

void Player::SetWeapon()
{
	//�v���C���[�̃��f�����畐��𑕔�����t���[����T��
	int frame_index = MV1SearchFrame(mModel, "joint_sword");
	//�ʒu�����[�J������O���[�o���ɕϊ�����}�g���b�N�X���쐬
	MATRIX weapon_matrix = MV1GetFrameLocalWorldMatrix(mModel, frame_index);
	mWPos[0] = VTransform(VGet(0, 0, 0), weapon_matrix);
	mWPos[1] = VTransform(VGet(0, 100, 0), weapon_matrix);
	//����̈ʒu����̃t���[���ɐݒ�
	MV1SetMatrix(mWModel, weapon_matrix);
}

CHARACTER_MOTION Player::SkillMotion()
{
	CHARACTER_MOTION motion;
	for (int i = 0; i < MAX_SKILL_NUM; i++)
	{
		int cnt = mSkill->GetSkill(i).divineCnt;
		if (cnt > 0 && cnt <= 38)
		{
			switch (mSkill->GetSkill(i).skillName)
			{
			case Divine::SKILLNAME::BREATH:
			case Divine::SKILLNAME::CIRCLE:
			case Divine::SKILLNAME::EXPLOSION:
			case Divine::SKILLNAME::LASER:
			case Divine::SKILLNAME::SLASH:
			case Divine::SKILLNAME::SONIC:
			case Divine::SKILLNAME::VACUUM:
				motion = CHARACTER_MOTION::PLAYER_SKILL;
				break;
			case Divine::SKILLNAME::DASH:
				motion = CHARACTER_MOTION::PLAYER_SKILLDASH;
				break;
			}
		}
		else if (cnt > 38) { motion = CHARACTER_MOTION::PLAYER_STAND; }
	}
	return motion;
}

void Player::SkillVoice()
{
	//�L�[�p�ϐ�������
	std::string voice;
	//�e�X�L���ɂ���Đݒ�
	for (int i = 0; i < MAX_SKILL_NUM; i++)
	{
		switch (mSkill->GetSkill(i).skillName)
		{
		//�u���X
		case Divine::SKILLNAME::BREATH:
			voice = "VO_Fe_Breath";
			break;
		//�T�[�N��
		case Divine::SKILLNAME::CIRCLE:
			voice = "VO_Fe_Circle";
			break;
		//�G�N�X�v���[�W����
		case Divine::SKILLNAME::EXPLOSION:
			voice = "VO_Fe_Explosion";
			break;
		//���[�U�[
		case Divine::SKILLNAME::LASER:
			voice = "VO_Fe_Laser";
			break;
		//�X���b�V��
		case Divine::SKILLNAME::SLASH:
			voice = "VO_Fe_Slash";
			break;
		//�_�b�V��
		case Divine::SKILLNAME::DASH:
			voice = "VO_Fe_Avoid";
			break;
		//�\�j�b�N�E�F�[�u
		case Divine::SKILLNAME::SONIC:
			voice = "VO_Fe_Slash";
			break;
		//�o�L���[��
		case Divine::SKILLNAME::VACUUM:
			voice = "VO_Fe_Attack03";
			break;
		}
		if (mSkill->GetSkill(i).divineCnt > 0 && mSkill->GetSkill(i).divineCnt < 10)
		{
			SoundItemBase* snditem_voice = gGlobal.mSndServer.Get(voice);
			if (snditem_voice && snditem_voice->IsLoad())
			{
				//�Đ����łȂ��Ȃ�
				if (!snditem_voice->IsPlay())
				{
					//�Đ�����
					snditem_voice->Play();
				}
			}
		}
	}
}

void Player::PlayerSkill(SkillSlot* slot, VECTOR campos, VECTOR camtarget)
{
	//�X���b�g�̔z��擾
	std::array<kindDivine, 3> _slot = slot->GetSlot();
	//X�{�^����������
	if (gGlobal.gPad->GetXTrg(XINPUT_BUTTON_X))
	{
		//�X���b�g1�̃X�L������
		mSkill->Invocation(1, _slot[1]);
		//�ŏI�����{�^����1��
		mLastCommand = 1;
	}
	//Y�{�^����������
	if (gGlobal.gPad->GetXTrg(XINPUT_BUTTON_Y))
	{
		//�X���b�g0�̃X�L������
		mSkill->Invocation(1, _slot[0]);
		//�ŏI�����{�^����0��
		mLastCommand = 0;
	}
	//A�{�^����������
	if (gGlobal.gPad->GetXTrg(XINPUT_BUTTON_A))
	{
		//�X���b�g2�̃X�L������
		mSkill->Invocation(1, _slot[2]);
		//�ŏI�����{�^����2��
		mLastCommand = 2;
	}
	// ��������Y����]���Z�o
	VECTOR vRot = { 0,0,0 };
	vRot.y = atan2(mDir.x * -1, mDir.z * -1);
	mDir.y = vRot.y;
	//���f���̉�]�l�����f���ɑ��
	MV1SetRotationXYZ(mModel, vRot);
	mSkill->Process(mPos, mDir.y);
	//�{�C�X�ݒ�
	SkillVoice();
	//�e�X�L��
	for (int i = 0; i < MAX_SKILL_NUM; i++)
	{
		if (mSkill->GetSkill(i).divineCnt > 0 && mSkill->GetSkill(i).divineCnt < 54)
		{
			//����̃J�E���g�����[�V�������Œ�
			mMotion = SkillMotion();
		}
	}
	
}

void Player::Damage(VECTOR pos,int subpoint)
{
	//�_���[�W�{�C�X�ݒ�
	std::string se_code_damage[3] =
	{
		"VO_Fe_Damage1",
		"VO_Fe_Damage2",
		"VO_Fe_Damage3",
	};
	//���S�{�C�X�ݒ�
	std::string se_code_die[2] =
	{
		"VO_Fe_Blow1",
		"VO_Fe_Blow2"
	};
	SoundItemBase* snditem_voice= gGlobal.mSndServer.Get("");
	//�̗͌���
	mHp = mHp - subpoint;
	//�̗͂�0��菭�Ȃ�
	if (mHp <= 0)
	{
		//���[�V���������S��
		mMotion = CHARACTER_MOTION::PLAYER_DIE;
		//�{�C�X��o�^
		snditem_voice = gGlobal.mSndServer.Get(se_code_die[rand() % 2]);
	}
	//�̗͂�0��葽��
	if (mHp > 0)
	{
		//�U����ԂłȂ��̂Ȃ�
		if (mAttackManager->GetType() == ATTACK_TYPE::NONE)
		{
			//���[�V�������_���[�W��
			mMotion = CHARACTER_MOTION::PLAYER_DAMAGE;
			//�{�C�X��o�^
			snditem_voice = gGlobal.mSndServer.Get(se_code_damage[rand() % 3]);
		}
	}
	
	if (snditem_voice && snditem_voice->IsLoad())
	{
		//���ʐݒ�
		snditem_voice->SetVolume(255);
		// �Đ������H
		if (snditem_voice->IsPlay() == false)
		{
			// �Đ�����
			snditem_voice->Play();
		}
	}
	////�G�ƃv���C���[�ʒu�̍������߂�
	VECTOR v = VSub(mPos, pos);
	////���K��������x�N�g����50�{��
	v = VScale(VNorm(v),50);
	//�ړ��l�Ƀx�N�g�������Z
	mMove = VAdd(mMove, v);
	//�ʒu�Ɉړ��l�����Z
	mPos = VAdd(mPos, mMove);
	//�X�L��������Ԃ����Z�b�g
	mSkill->Reset();
}

void Player::PlayerDie()
{
	mNoDamage = true;
	mIsDie = true;
}

void Player::Invincible()
{
	//���S��ԂłȂ�
	if (!mIsDie)
	{
		if (mNoDamage) { mInvincibleCnt++; }
		if (mInvincibleCnt > 0 && mInvincibleCnt <= 42)
		{
			mMotion = CHARACTER_MOTION::PLAYER_DAMAGE;
		}
		if (mInvincibleCnt > 80)
		{
			mNoDamage = false;
			mInvincibleCnt = 0;
		}
	}
}

void Player::ActionProcess(VECTOR campos, VECTOR camtarget, SkillSlot* slot)
{
	//�ړ����������߂�
	mMove = { 0,0,0 };
	//���[�V�����J�E���g�擾
	int motion_cnt = mMotionManager->GetMotionCnt();
	//�U���J�E���g�擾
	int attack_cnt = mAttackManager->GetAttackCount();
	//�J�E���g�ő�l�擾
	int motioncnt_max = mMotionManager->GetMaxCnt();
	//���[�V�������ƂɃX�L�������\�t���O�擾
	bool skill = mMotionManager->GetTable()->GetItem()[motion_cnt].GetIsSkill();
	//���[�V�������Ƃɉ���\�t���O�擾
	bool avoid = mMotionManager->GetTable()->GetItem()[motion_cnt].GetIsAvoid();
	//�e���[�V�����ʏ���
	switch (mMotionManager->GetMotion())
	{
	//�ҋ@
	case CHARACTER_MOTION::PLAYER_STAND:
		if (mAttackManager->GetIsChange()) { mMotion = CHARACTER_MOTION::PLAYER_FIRSTATTACK; }
		break;
	//����
	case CHARACTER_MOTION::PLAYER_RUN:
		if (mAttackManager->GetIsChange()) { mMotion = CHARACTER_MOTION::PLAYER_DASHATTACK; }
		break;
	//�A���U��1����
	case CHARACTER_MOTION::PLAYER_FIRSTATTACK:
		if (mAttackManager->GetIsChange()) { mMotion = CHARACTER_MOTION::PLAYER_SECONDATTACK; }
		break;
	//�A���U��2����
	case CHARACTER_MOTION::PLAYER_SECONDATTACK:
		if (mAttackManager->GetIsChange()) { mMotion = CHARACTER_MOTION::PLAYER_LASTATTACK; }
		break;
	//�A���U��3����
	case CHARACTER_MOTION::PLAYER_LASTATTACK:
		break;
	//�_�b�V���U��
	case CHARACTER_MOTION::PLAYER_DASHATTACK:
		if (mAttackManager->GetIsChange()) { mMotion = CHARACTER_MOTION::PLAYER_SECONDATTACK; }
		break;
	//�X�L������
	case CHARACTER_MOTION::PLAYER_SKILL:
		break;
	//�X�L������(�_�b�V��)
	case CHARACTER_MOTION::PLAYER_SKILLDASH:
		break;
	//���
	case CHARACTER_MOTION::PLAYER_AVOID:
		if (motion_cnt >= motioncnt_max - 1) { mAvoidFlag = false; }
		break;
	//�_���[�W
	case CHARACTER_MOTION::PLAYER_DAMAGE:
		break;
	//���S
	case CHARACTER_MOTION::PLAYER_DIE:
		if (motion_cnt >= motioncnt_max-1)
		{

			mGameOverFlag = true;
		}
		break;
	}
	//�U�����̐���se���Đ�����
	if (mAttackManager->GetType() != ATTACK_TYPE::NONE)
	{
		if (attack_cnt == 1)
		{
			//���[�V�����e�[�u������Đ��p�̐���se�̃L�[���擾����
			SoundItemBase* snditem_voice = gGlobal.mSndServer.Get(mAttackManager->GetTable()->GetVoiceName());
			SoundItemBase* snditem_se = gGlobal.mSndServer.Get(mAttackManager->GetTable()->GetSeName());
			//���ʐݒ�
			snditem_voice->SetVolume(255);
			snditem_se->SetVolume(255);
			// �Đ����łȂ��Ȃ�
			if (snditem_voice->IsPlay() == false)
			{
				// �Đ�����
				snditem_voice->Play();
			}
			// �Đ����łȂ��Ȃ�
			if (snditem_se->IsPlay() == false)
			{
				// �Đ�����
				snditem_se->Play();
			}
		}
	}
	//�J�E���g���K��l�ɒB����
	if (motion_cnt >= motioncnt_max - 1)
	{
		//���[�v�����Ȃ����[�V�����̏ꍇ�A�ҋ@��Ԃ�
		if (mMotionManager->GetTable()->GetEndType() == MotionTable::MOTION_ENDTYPE::END) 
		{ 
			mMotion = CHARACTER_MOTION::PLAYER_STAND; 
		}
	}
	//�X�L�������\�Ȃ�X�L���Ɋւ���v���Z�X���񂹂�悤��
	if (skill) { PlayerSkill(slot, campos, camtarget); }
	//����g���K�{�^���������ꂽ
	if (gGlobal.gPad->GetXLt())
	{
		//����\�̏�ԂȂ�
		if(avoid)
		{
			//����t���O��true��
			mAvoidFlag = true;
			//���[�V������ύX
			mMotion = CHARACTER_MOTION::PLAYER_AVOID;
		}
	}
	//�L�����ړ�(�J�����ݒ�ɍ��킹��)
	float dir = atan2(-gGlobal.gPad->GetXLy(), -gGlobal.gPad->GetXLx());
	//�J�����̌����Ă���p�x���擾
	float com_dir_y = Camera::GetInstance()->GetDir().y;
	MATRIX matrix = MGetRotY(com_dir_y);
	//���鑬�x�̐ݒ�
	float mvspeed = mMotionManager->GetTable()->GetItem()[motion_cnt].GetVelocity().z;
	float len = 0.f;
	//�A�i���O�p�b�h���X���Ă���Ƃ��݈̂ړ��l�����Z
	if (gGlobal.gPad->IsInputStickLeft())
	{
		len = mvspeed;
	}
	mMove.x = len * cos(dir);
	mMove.z = len * sin(dir);
	//v�̕��ړ�
	mMove = VTransform(mMove, matrix);
	mPos = VAdd(mPos, mMove);
	mPos.y += mGravity;
	//�ړ��ʂ����̂܂܃L�����̌����ɂ���
	int layer = static_cast<int>(mMotionManager->GetMotionList().at(static_cast<int>(mMotion)).second->GetLayer());
	if (layer <= static_cast<int>(MOTION_LAYER::PRESS_DOWN))
	{
		// �ړ����Ă��Ȃ����͖������邽��
		if (gGlobal.gPad->IsInputStickLeft())
		{
			//�v���C���[�̃��[�V�������uRUN�v�ɕύX
			if (mMotion != CHARACTER_MOTION::PLAYER_SKILLDASH) { mMotion = CHARACTER_MOTION::PLAYER_RUN; }
		}
		else
		{
			// �v���C���[�̃��[�V�������uSTAND�v�ɕύX
			mMotion = CHARACTER_MOTION::PLAYER_STAND;
		}
	}
	bool ischangecourse = mMotionManager->GetTable()->GetItem()[motion_cnt].GetIsChangeCourse();
	//�����]���t���O��true�Ȃ�
	if (ischangecourse)
	{
		//�ړ��ʂ�0�łȂ��Ȃ���Z
		if (VSize(mMove) != 0){ mDir = mMove; }
	}
	//y���W�Œ�
	if (mPos.y <= 0) { mPos.y = 0; }
	//�����ݒ�
	VECTOR vrot = { 0,0,0 };
	vrot.y = atan2(mDir.x * -1, mDir.z * -1);
	mDir.y = vrot.y;
	//���f���ʒu�X�V
	MV1SetPosition(mModel, mPos);
	//���f����]�X�V
	MV1SetRotationXYZ(mModel, vrot);
	Invincible();
	//����ݒ�
	SetWeapon();
	//�����蔻��p��������
	C_Process();
}

void Player::C_Process() 
{
	//����J�v�Z���̍X�V
	mCapsule[0] = mPos;
	mCapsule[1] = VAdd(mPos, VGet(0, mLineSeg, 0));
}

void Player::Process(VECTOR campos, VECTOR camtarget, SkillSlot* slot)
{
	//���������S��
	ActionProcess(campos, camtarget, slot);
	//�A�j���[�V��������
	A_Process();
	//�}�l�[�W���[�t���[��������
	mMotionManager->Process();
	mAttackManager->Process();
}

void Player::Render() 
{
	mSkill->Render();
	// ���f����`�悷��
	MV1DrawModel(mModel);
	MV1DrawModel(mWModel);
}