#include "GameEvent.h"
#include "ApplicationGlobal.h"
GameEvent* GameEvent::_evInstance = nullptr;
GameEvent::GameEvent()
{
	_evInstance = this;
	//�N���X������
	mEnManager = new EnemyManager();
	//�G�A���탂�f��
	mHandle[0] = gGlobal.mGetModel()["EN_Osero"]._handle;
	mHandle[1] = gGlobal.mGetModel()["EN_Crab"]._handle;
	mHandle[2] = gGlobal.mGetModel()["EN_Romanoff"]._handle;
	mWeaponModel[0] = gGlobal.mGetModel()["W_Sword"]._handle;
	mWeaponModel[1] = gGlobal.mGetModel()["W_Axe"]._handle;
	//�C�x���gUI
	mHandleQuestFeld[0] = gGlobal.mGetGraph()["UI_Feld_Quest_01"]._handle;
	mHandleQuestFeld[1] = gGlobal.mGetGraph()["UI_Feld_Quest_02"]._handle;
	mHandleQuestFeld[2] = gGlobal.mGetGraph()["UI_Feld_Quest_03"]._handle;
	mHandleQuestFeld[3] = gGlobal.mGetGraph()["UI_Feld_Quest_04"]._handle;
	mHandleQuestFeld[4] = gGlobal.mGetGraph()["UI_Feld_Quest_05"]._handle;
	mHandleQuestFeld[5] = gGlobal.mGetGraph()["UI_Feld_Quest_06"]._handle;
	mHandleQuestFeld[6] = gGlobal.mGetGraph()["UI_Feld_Quest_07"]._handle;
	mHandleQuestFeld[7] = gGlobal.mGetGraph()["UI_Feld_Quest_08"]._handle;
	mHandleQuestFeld[8] = gGlobal.mGetGraph()["UI_Feld_Quest_09"]._handle;
	mHandleQuestFeld[9] = gGlobal.mGetGraph()["UI_Feld_Quest_10"]._handle;
	mHandleQuestFeld[10] = gGlobal.mGetGraph()["UI_Feld_Quest_11"]._handle;
	mHamdleQuestRomanoff[0] = gGlobal.mGetGraph()["UI_Romanoff_Quest_01"]._handle;
	mHamdleQuestRomanoff[1] = gGlobal.mGetGraph()["UI_Romanoff_Quest_02"]._handle;
	mHamdleQuestRomanoff[2] = gGlobal.mGetGraph()["UI_Romanoff_Quest_03"]._handle;
	mHamdleQuestRomanoff[3] = gGlobal.mGetGraph()["UI_Romanoff_Quest_04"]._handle;
	mHamdleQuestRomanoff[4] = gGlobal.mGetGraph()["UI_Romanoff_Quest_05"]._handle;
	mHamdleQuestRomanoff[5] = gGlobal.mGetGraph()["UI_Romanoff_Quest_06"]._handle;
	mHamdleQuestRomanoff[6] = gGlobal.mGetGraph()["UI_Romanoff_Quest_07"]._handle;
	//wave�ԍ�
	mInitNum = 0;
	mQuestNum = -1;
	mDivineEv = 0;
	//����wave
	EnemyWaveInit(mInitNum);
	//�C�x���g�p
	mStoryEv = 0;
	mWaveEv = 0;
	mHpEv = -1;
	mHpCast = 3000;
	RegisterEvent();

}
GameEvent::~GameEvent()
{

}

bool GameEvent::GameOver()
{
	if (gGlobal.mPM->P_GetDie())
	{
		int begin_game_over_time = 180;
		while (1)
		{
			begin_game_over_time--;
			if (begin_game_over_time <= 0) { break; }
		}
		if (begin_game_over_time <= 0) { return true; }
	}
	return false;
}

bool GameEvent::GameClear(EN_Romanoff* en)
{
	if (mStoryEv >= 1)
	{
		if (en->GetDeleteFlag())
		{
			int begin_game_over_time = 120;
			while (1)
			{
				begin_game_over_time--;
				if (begin_game_over_time <= 0) { break; }
			}
			if (begin_game_over_time <= 0) { return true; }
		}
	}
	return false;
}

void GameEvent::RegisterEvent()
{	//�C�x���g�\���̂̍쐬
	EVENT ev[MAX_EVENT_NUM] =
	{
		{mHandleQuestFeld[0],	  0, 150, false, "VO_Fe_Quest_01"},
		{mHandleQuestFeld[1],	  0, 300, false, "VO_Fe_Quest_02"},
		{mHandleQuestFeld[2],	  0, 180, false, "VO_Fe_Quest_03"},
		{mHandleQuestFeld[3],	  0, 300, false, "VO_Fe_Quest_04"},
		{mHandleQuestFeld[4],	  0, 480, false, "VO_Fe_Quest_05"},
		{mHandleQuestFeld[5],	  0, 180, false, "VO_Fe_Quest_06"},
		{mHandleQuestFeld[6],	  0, 300, false, "VO_Fe_Quest_07"},
		{mHandleQuestFeld[7],	  0, 360, false, "VO_Fe_Quest_08"},
		{mHandleQuestFeld[8],	  0, 300, false, "VO_Fe_Quest_09"},
		{mHandleQuestFeld[9],	  0, 120, false, "VO_Fe_Quest_10"},
		{mHandleQuestFeld[10],	  0, 120, false, "VO_Fe_Quest_11"},
		{mHamdleQuestRomanoff[0], 0, 300, false, "VO_Ro_Quest_01"},
		{mHamdleQuestRomanoff[1], 0, 480, false, "VO_Ro_Quest_02"},
		{mHamdleQuestRomanoff[2], 0, 480, false, "VO_Ro_Quest_03"},
		{mHamdleQuestRomanoff[3], 0, 480, false, "VO_Ro_Quest_04"},
		{mHamdleQuestRomanoff[4], 0, 480, false, "VO_Ro_Quest_05"},
		{mHamdleQuestRomanoff[5], 0, 600, false, "VO_Ro_Quest_06"},
		{mHamdleQuestRomanoff[6], 0, 900, false, "VO_Ro_Quest_07"},
	};
	for (int i = 0; i < MAX_EVENT_NUM; i++)
	{	//�����o�ϐ��Ɉړ�
		mEvent[i] = std::move(ev[i]);
	}
}

bool GameEvent::WaveNum(int i)
{	//wave�Ɋւ���C�x���g�ԍ�
	if (i == 2 || i == 3 || i == 4 || i == 5 || i == 6)
	{
		return true;
	}
	return false;
}

bool GameEvent::StoryNum(int i)
{	//�X�g�[���[�Ɋւ���C�x���g�ԍ�
	if (i == 7 || i == 8 || i == 11 || i == 12 || i == 13 || i == 14)
	{
		return true;
	}
	return false;
}

bool GameEvent::DivineNum(int i)
{	//�f�B�o�C���Ɋւ���C�x���g�ԍ�
	if (i == 0 || i == 1)
	{
		return true;
	}
	return false;
}

void GameEvent::OccurEvent(int i)
{	//�C�x���g����
	//�ԍ��̑��
	mQuestNum = i;
	//�C�x���g�������Ȃ̂�true��
	mEvent[mQuestNum].isOccur = true;
	//���̔ԍ��̃{�C�X����
	SoundItemBase* snditem_voice = gGlobal.mSndServer.Get(mEvent[mQuestNum].voiceCode);
	//���ʒ���
	snditem_voice->SetVolume(255);
	if (mEvent[mQuestNum].eventCnt <= 10)
	{
		if (snditem_voice && snditem_voice->IsLoad())
		{	// �Đ����łȂ��Ȃ�
			if (snditem_voice->IsPlay() == false)
			{	// �Đ�����
				snditem_voice->Play();
			}
		}
	}
}

void GameEvent::OccurProcess()
{	//�ԍ��������l�łȂ�
	if (mQuestNum != -1)
	{	//�C�x���g�������Ȃ炻�̔ԍ��̃C�x���g�J�E���g�����Z
		if (mEvent[mQuestNum].isOccur) { mEvent[mQuestNum].eventCnt++; }
		//�C�x���g�J�E���g���K��l�܂ŒB����
		if (mEvent[mQuestNum].eventCnt >= mEvent[mQuestNum].maxEventCnt)
		{	//�����I�������̂�false��
			mEvent[mQuestNum].isOccur = false;
			//�J�E���g���Z�b�g
			mEvent[mQuestNum].eventCnt = 0;
			//�ԍ�����
			int old_num = mQuestNum;
			//�ԍ�������
			mQuestNum = -1;
			//�e�C�x���g�J�E���g�̉��Z
			if (WaveNum(old_num))
			{
				mWaveEv++;
			}
			if (StoryNum(old_num))
			{
				mStoryEv++;
			}
			if (DivineNum(old_num))
			{
				mDivineEv++;
			}
		}
	}
}

void GameEvent::EnemyWaveInit(int i)
{
	//�L�[
	std::string wave[6] =
	{
		"Enemy_Wave1",
		"Enemy_Wave2",
		"Enemy_Wave3",
		"Enemy_Wave4",
		"Enemy_Wave5",
		"Enemy_Wave8",
	};
	//�ʒu
	VECTOR pos = VGet(0, 0, 0);
	//�p�x
	VECTOR dir = VGet(0, 0, 0);
	//json�̏�����
	JsonUtility* jUtil;
	jUtil = new JsonUtility();
	//json�̃C���|�[�g
	nlohmann::json enemy_pos = jUtil->Import("res/Json/Enemy_pos.json").at(wave[i]);
	//�C���|�[�g���ꂽ�G�̈ʒu�̕��J��Ԃ�
	for (auto& data : enemy_pos)
	{
		std::string name;
		//���O�̎擾
		data.at("objectName").get_to(name);
		//���W���e�v�f�Ŏ擾
		data.at("translate").at("x").get_to(pos.x);
		data.at("translate").at("z").get_to(pos.y);
		data.at("translate").at("y").get_to(pos.z);
		data.at("rotate").at("x").get_to(dir.x);
		data.at("rotate").at("z").get_to(dir.y);
		data.at("rotate").at("y").get_to(dir.z);
		dir.x = Math::DegToRad(dir.x);	// ��]��degree��radian��
		dir.y = Math::DegToRad(dir.y);
		dir.z = Math::DegToRad(dir.z);
		//UE5�ł͍��W�n���Ⴄ�̂ŕϊ�����
		pos.z *= -1;
		//�擾�������O�ŃX�|�[��������G��ς���
		if (name == "EN_Osero")
		{	//osero�̃X�|�[��
			mEnManager->Spawn(new EN_Osero(mHandle[0], mWeaponModel[0], pos, dir));
		}
		else if (name == "EN_Crab")
		{	//crab�̃X�|�[��
			mEnManager->Spawn(new EN_Crab(mHandle[1], -1, pos, dir));
		}
		else if (name == "EN_Romanoff")
		{	//romanoff�̃X�|�[��
			mEnManager->Spawn(new EN_Romanoff(mHandle[2], mWeaponModel[1], pos, dir));
		}
	}
}

void GameEvent::WaveProcess()
{
	//�X�|�[�����邽�߂̓G���i�[���Ă���R���e�i���擾
	std::list<Enemy*> list = mEnManager->GetEnemyList();
	//�}�l�[�W���[�̃v���Z�X�����s
	mEnManager->Process(gGlobal.mPM->P_GetPos());
	//�G�̐���0�ɂȂ���
	if (list.size() <= 0)
	{
		//wave�ԍ����X�V
		mInitNum++;
		if (mStoryEv == 0)
		{
			mWaveEv++;
		}
		//wavw�ԍ���wave�ω��\����
		if (mInitNum < MAX_SPAWN_WAVE)
		{	//wave���X�V����
			EnemyWaveInit(mInitNum);
		}
	}
}

void GameEvent::EventProcess()
{
	OccurProcess();
	//wave�Ɋւ���C�x���g�ԍ�
	switch (mWaveEv)
	{
	case 0:
		OccurEvent(2);
		break;
	case 2:
		OccurEvent(3);
		break;
	case 4:
		OccurEvent(4);
		break;
	case 6:
		OccurEvent(5);
		break;
	case 8:
		OccurEvent(6);
		break;
	}
	//�X�g�[���[�Ɋւ���C�x���g�ԍ�
	switch (mStoryEv)
	{
	case 1:
		OccurEvent(11);
		break;
	case 2:
		OccurEvent(7);
		break;
	case 4:
		OccurEvent(12);
		break;
	case 5:
		OccurEvent(13);
		break;
	case 6:
		OccurEvent(8);
		break;
	case 7:
		OccurEvent(14);
		break;
	}
	//�f�B�o�C���Ɋւ���C�x���g�ԍ�
	switch (mDivineEv)
	{
	case 1:
		OccurEvent(0);
		break;
	case 2:
		OccurEvent(1);
		break;
	}

}

void GameEvent::CastEnemy(int i)
{
	std::string cast[3] =
	{
		"Boss_Cast_Wave1",
		"Boss_Cast_Wave2",
		"Boss_Cast_Wave3",
	};
	//�ʒu
	VECTOR pos = VGet(0, 0, 0);
	//�p�x
	VECTOR dir = VGet(0, 0, 0);
	//json�̏�����
	JsonUtility* jUtil;
	jUtil = new JsonUtility();
	//json�̃C���|�[�g
	nlohmann::json enemy_pos = jUtil->Import("res/Json/Boss_Cast_Enemy.json").at(cast[i]);
	//�C���|�[�g���ꂽ�G�̈ʒu�̕��J��Ԃ�
	for (auto& data : enemy_pos)
	{
		std::string name;
		//���O�̎擾
		data.at("objectName").get_to(name);
		//���W���e�v�f�Ŏ擾
		data.at("translate").at("x").get_to(pos.x);
		data.at("translate").at("z").get_to(pos.y);
		data.at("translate").at("y").get_to(pos.z);
		data.at("rotate").at("x").get_to(dir.x);
		data.at("rotate").at("z").get_to(dir.y);
		data.at("rotate").at("y").get_to(dir.z);
		dir.x = Math::DegToRad(dir.x);	// ��]��degree��radian��
		dir.y = Math::DegToRad(dir.y);
		dir.z = Math::DegToRad(dir.z);
		//UE5�ł͍��W�n���Ⴄ�̂ŕϊ�����
		pos.z *= -1;
		//�擾�������O�ŃX�|�[��������G��ς���
		if (name == "EN_Osero")
		{	//osero�̃X�|�[��
			mEnManager->Spawn(new EN_Osero(mHandle[0], mWeaponModel[0], pos, dir));
		}
		else if (name == "EN_Crab")
		{	//crab�̃X�|�[��
			mEnManager->Spawn(new EN_Crab(mHandle[1], -1, pos, dir));
		}
	}
}

void GameEvent::CastProcess()
{
	//�X�g�[���[�Ɋւ���C�x���g�ԍ���0�ȏ�
	if (mStoryEv >= 1)
	{	//�{�X�̗͔̑�r�p�ϐ����K��l�ȏ�
		if (mHpCast >= 1000)
		{	//�{�X�̗̑͂���r�ϐ��l��菬����
			if (EN_Romanoff::GetInstance()->GetHp() <= mHpCast)
			{	//hp�C�x���g���Z
				mHpEv++;
				//�G�̏���
				CastEnemy(mHpEv);
				//�̗͔�r�ϐ����K��l
				if (mHpCast == 2000)
				{	//�X�g�[���[�C�x���g���Z
					mStoryEv++;
				}
				//��r�p�ϐ�������
				mHpCast -= 1000;
			}
		}
	}

}

void GameEvent::Process()
{
	//�G�����Ɋւ��鏈��
	CastProcess();
	//�C�x���g�Ɋւ��鏈��
	EventProcess();
	//�E�F�[�u�Ɋւ��鏈��
	WaveProcess();
}

void GameEvent::DrawQuest()
{
	if (mQuestNum != -1)
	{	//�C�x���g�������Ȃ�
		if (mEvent[mQuestNum].isOccur)
		{	//�摜�\��
			DrawGraph(0, 0, mEvent[mQuestNum].handleUI, TRUE);
		}
	}
}

void GameEvent::DrawWave()
{	//wave�̕����`�ʗp�n���h��
	int cg_wave = gGlobal.mRS->mGetGraph()["UI_wave"]._handle;
	//��wave���`�ʗp�n���h��
	int cg_wave_num = gGlobal.mRS->mGetDivGraph()["wave_number"].handle[mInitNum + 1];
	int cg_wave_slash = gGlobal.mRS->mGetGraph()["wave_slash"]._handle;
	///�ő�wave���`�ʗp�n���h��
	int cg_wave_max = gGlobal.mRS->mGetDivGraph()["wave_number"].handle[MAX_SPAWN_WAVE];
	DrawGraph(30, 196, cg_wave, true);
	DrawGraph(55, 270, cg_wave_num, true);
	DrawGraph(100, 300, cg_wave_slash, true);
	DrawGraph(130, 330, cg_wave_max, true);
}

void GameEvent::DrawEventUI()
{
	DrawQuest();
	DrawWave();
}

void GameEvent::Render()
{
	//�G�̕`��
	mEnManager->Render();

}