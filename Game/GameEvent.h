#pragma once
#include "EnemyManager.h"
#include "JsonUtility.h"
#include "EN_Romanoff.h"
//�萔
constexpr auto MAX_EVENT_NUM = 18;
constexpr auto MAX_SPAWN_WAVE = 6;
class GameEvent
{
public:
	struct EVENT
	{	
		//�摜�n���h��
		int handleUI;
		//�C�x���g�J�E���g
		int eventCnt;
		//�C�x���g�J�E���g�ő�l
		int maxEventCnt;
		//�C�x���g������
		bool isOccur;
		//�{�C�X�L�[
		std::string voiceCode;
	};
	GameEvent();
	virtual ~GameEvent();
	//�C���X�^���X
	static GameEvent* _evInstance;
	void Process();
	void Render();
	bool GameOver();
	bool GameClear(EN_Romanoff* en);
	//�C�x���g�o�^
	void RegisterEvent();
	//�C�x���g����
	void OccurEvent(int i);
	//wavw�X�V
	void EnemyWaveInit(int i);
	//�C�x���g�����Ɋւ��鏈��
	void OccurProcess();
	//wave�Ɋւ��鏈��
	void WaveProcess();
	//wave�Ɋւ���C�x���g�ԍ�
	bool WaveNum(int i);
	//�X�g�[���[�Ɋւ���C�x���g�ԍ�
	bool StoryNum(int i);
	//�f�B�o�C���Ɋւ���C�x���g�ԍ�
	bool DivineNum(int i);
	//�C�x���g�Ɋւ��鏈��
	void EventProcess();
	//�{�X�X�e�[�W�̓G����
	void CastEnemy(int i);
	//�����Ɋւ��鏈��
	void CastProcess();
	//UI�̕\��(UI�N���X�Ɏg��)
	void DrawQuest();
	void DrawWave();
	void DrawEventUI();
	//�Q�b�^�[
	static GameEvent*	GetInstance()			{ return _evInstance; }
	EnemyManager*		GetEnemyManager()		{ return mEnManager; }
	int					GetEvent()				{ return mStoryEv; }
	int					GetDivineEvent()		{ return mDivineEv; }
	//�Z�b�^�[
	void				SetEvent(int i)			{ mStoryEv += i; }
	void				SetDivineEvent(int i)	{ mDivineEv += i; }
protected:
	//�N�G�X�g�摜�n���h��
	int mHandleQuestFeld[11];
	int mHamdleQuestRomanoff[7];
	//�ԍ�
	int mInitNum;
	int mQuestNum;
	//���f���n���h��
	int mHandle[3];
	//���탂�f���n���h��
	int mWeaponModel[2];
	//�{�X�̗͔̑�r�p�ϐ�
	int mHpCast;
	//�C�x���g�J�E���g
	int mStoryEv;
	int mWaveEv;
	int mHpEv;
	int mDivineEv;
	//�G�}�l�[�W���[
	EnemyManager* mEnManager;
	EVENT mEvent[MAX_EVENT_NUM];

};

