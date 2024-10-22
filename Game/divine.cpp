#include "Divine.h"
#include"ApplicationGlobal.h"
Divine* Divine::_divineInstance = nullptr;
Divine::Divine()
{
	_divineInstance = this;
	mPos = VGet(0,0,100);
	mHitFlag = false;
	SKILL skill[8] =
	{//	�X�L����, �ʒu, �����蔻��p�T�C�Y, �Ĕ����t���[��, �Ĕ����܂ł̃J�E���g, ����p�J�E���g, �����t���O, ��������, ������������, ����J�n����, �G�t�F�N�g������
		{SKILLNAME::BREATH,	  VGet(0,0,0),   0.0f, 320, 0, 0,  30, true, false, 150.0f, 12.0f,  50.0f, new Effect("res/effekseer/bless/bless.efkefc",			   100.0f), "SE_Breath"},
		{SKILLNAME::CIRCLE,	  VGet(0,0,0), 150.0f, 550, 0, 0,   5, true, false, 500.0f, 24.0f, 450.0f, new Effect("res/effekseer/circle/circle.efkefc",				30.0f), "SE_Circle"},
		{SKILLNAME::LASER,	  VGet(0,0,0), 200.0f, 400, 0, 0,   5, true, false, 240.0f, 27.0f, 70.0f,  new Effect("res/effekseer/laser/Laser.efkefc",				30.0f), "SE_Laser"},
		{SKILLNAME::SLASH,	  VGet(0,0,0), 300.0f, 300, 0, 0,  30, true, false,  96.0f, 12.0f,  30.0f, new Effect("res/effekseer/slash/slash2.efkefc",				80.0f), "SE_Slash"},
		{SKILLNAME::EXPLOSION,VGet(0,0,0), 480.0f, 400, 0, 0, 100, true, false, 150.0f, 10.0f,  15.0f, new Effect("res/effekseer/explosion/explosion_new3.efkefc",	50.0f), "SE_Explosion"},
		//{SKILLNAME::LOCKON,	   	VGet(0,0,0),   0.0f, 480, 0, 0,  40, true, false, 150.0f,  0.0f,   0.0f, new Effect("res/effekseer/lockon/lockon.efkefc", 15.0f),	"SE_Lockon"},
		{SKILLNAME::DASH,	  VGet(0,0,0), 100.0f, 180, 0, 0,  10, true, false,  60.0f, 15.0f,  60.0f, new Effect("res/effekseer/dash/dash.efkefc",					50.0f), "SE_DashAttack"},
		{SKILLNAME::VACUUM,	  VGet(0,0,0),   0.0f, 600, 0, 0,   0, true, false, 350.0f, 30.0f, 120.0f, new Effect("res/effekseer/vacuum/vacuum.efkefc",				50.0f), "SE_Vacuum"},
		{SKILLNAME::SONIC,	  VGet(0,0,0), 400.0f, 240, 0, 0,  20, true, false,  75.0f,  5.0f,  50.0f, new Effect("res/effekseer/sonicwave/sonicwave.efkefc",		50.0f), "SE_Sonic"}
	};
	for (int i = 0; i < MAX_SKILL_NUM; i++)
	{
		mSkill[i] = std::move(skill[i]);
	}
}

Divine::~Divine()
{

}

void Divine::Invocation(int type, kindDivine skillname)
{
	int i = static_cast<int>(skillname);
	if (mSkill[i].invocationFlag)
	{
		//���������ǂ�����true��
		mSkill[i].isPlaying = true;
		//�X�L�������\���ǂ�����false��
		mSkill[i].invocationFlag = false;
	}
}

void Divine::Reset()
{
	for (int i = 0; i < MAX_SKILL_NUM; i++)
	{
		if (mSkill[i].isPlaying)
		{
			//���������ǂ�����true��
			mSkill[i].isPlaying = false;
			//�X�L�������\���ǂ�����false��
			mSkill[i].invocationFlag = false;
			mSkill[i].effect->Stop();
		}
		mSkill[i].colCnt = 0;
	}
	
}

bool Divine::Calcalate(VECTOR pos, float roty)
{
	MATRIX matrix = MGetRotY(roty);
	VECTOR _all_skill_calc_pos[MAX_SKILL_NUM] =
	{
		VGet(0,0,0),
		VGet(0,100,0),
		VGet(0,100,400 - (24 * mSkill[2].colCnt)),
		VGet(0,0,0),
		VGet(0,100,-630),
		//VGet(0,0,0),
		VGet(0,0,0),
		VGet(0,100,-50),
		VGet(0,0,0)
	};
	for (auto i = 0; i < MAX_SKILL_NUM; i++)
	{
		if (mSkill[i].isPlaying)
		{
			if (mSkill[i].colCnt > mSkill[i].startColFrame &&
				mSkill[i].colCnt <= mSkill[i].endColFrame)
			{
				mSkill[i].vPos = VAdd(pos, VTransform(_all_skill_calc_pos[i], matrix));
			}
		}
	}
	return true;
}

bool Divine::Process(VECTOR pos, float roty)
{
	Calcalate(pos, roty);
	//�X�L���̈ʒu
	VECTOR all_skill_pos[MAX_SKILL_NUM] =
	{
		VGet(0,0,0),
		VGet(0,0,0),
		VGet(0,100,-200),
		VGet(0,0,0),
		VGet(0,0,-630),
		//VGet(0,0,0),
		VGet(0,100,-100),
		VGet(0,100,-50),
		VGet(0,0,0)
	};
	//y����]�̂��߂̃}�g���N�X�쐬
	MATRIX matrix = MGetRotY(roty);
	float all_skill_dir[MAX_SKILL_NUM] =
	{
		90.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f
	};
	for (int i = 0; i < MAX_SKILL_NUM; i++)
	{
		//�X�L�������\�łȂ��̂Ȃ�J�E���g�𑝂₷
		if (!mSkill[i].invocationFlag)
		{
			mSkill[i].divineCnt++;
		}
		//�J�E���g������̃t���[���ɒB����
		if(mSkill[i].colCnt >= mSkill[i].startColFrame + 10)
		{
			//�Đ��\�t���O��false��
			mSkill[i].effect->SetUseFlag(false);
		}
		//�J�E���g�������\�t���[���܂ŒB�����Ȃ�
		if (mSkill[i].divineCnt >= mSkill[i].reInvocationFrame)
		{
			//�G�t�F�N�g�Đ��\�t���O��true��
			mSkill[i].effect->SetUseFlag(true);
			//�X�L�������t���O��true��
			mSkill[i].invocationFlag = true;
			//�J�E���g���Z�b�g
			mSkill[i].divineCnt = 0;
		}
		//�Đ����łȂ���΃R���e�B�j���[
		if (!mSkill[i].isPlaying) continue;
		else{ mSkill[i].colCnt++;}
		//�G�t�F�N�g�Đ����Ȃ�
		if (mSkill[i].effect->GetPlayFlag())
		{
			//�����̒P�ʂ����W�A���ɕύX
			all_skill_dir[i] = Math::DegToRad(all_skill_dir[i]);
			//������ύX����
			mSkill[i].effect->SetDir(VGet(0,roty+all_skill_dir[i], 0));
			//�ʒu��ύX
			mSkill[i].effect->SetPos(VAdd(pos, VTransform(all_skill_pos[i], matrix)));
			//�v���Z�X����
			mSkill[i].effect->Process();
		}
		//�G�t�F�N�g�̍Đ�
		if (mSkill[i].colCnt == mSkill[i].startColFrame)
		{
			mSkill[i].effect->Play();
			//������Đ�����Ȃ��悤�ɏ�����t����
			if (mSkill[i].colCnt <= mSkill[i].startColFrame + 1)
			{
				SoundItemBase* snditem_se = gGlobal.mSndServer.Get(mSkill[i].seCode);
				if (snditem_se && snditem_se->IsLoad())
				{	// �Đ������H
					if (snditem_se->IsPlay() == false)
					{	// �Đ�����
						snditem_se->Play();
					}
				}
			}
		}
		//����J�E���g�����������Ԃɓ��B����
		if (mSkill[i].colCnt >= mSkill[i].invocationFrame)
		{
			//�������Ă��Ȃ��̂�false
			mSkill[i].isPlaying = false;
			//�J�E���g���Z�b�g
			mSkill[i].colCnt = 0;
		}
	}
	return true;
}

bool Divine::Render()
{
	//�G�t�F�N�g�̕`��
	for (int i = 0; i < MAX_SKILL_NUM; i++)
	{
		if (mSkill[i].effect->GetPlayFlag())
		{
			mSkill[i].effect->Draw();
		}
	}
	
	return true;
}
bool Divine::Debug()
{
	DrawFormatString(300, 0, GetColor(0, 0, 255), "Cnt =%d", mSkill[3].divineCnt);
	DrawFormatString(300, 20, GetColor(0, 0, 255), "Cnt =%d", mSkill[4].divineCnt);
	return true;
}