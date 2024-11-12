//----------------------------------------------------------------------
// @filename GameSystem.h
// @author: Fukuma Kyohei
// @explanation
// �Q�[�������ʃV�X�e���N���X
// �K�`���̉�]�̂��߂̃R���{���ȂǃQ�[�����ł̋��ʃM�~�b�N�������s���N���X
//----------------------------------------------------------------------
#pragma once
#include "EnemyManager.h"
#include "SkillSlot.h"
constexpr auto CHANGE_SKILL_COMBO = 30;
class GameSystem
{
public:
	GameSystem();
	virtual ~GameSystem();
	//�C���X�^���X
	static GameSystem* _sysInstance;
	bool Process(EnemyManager* en, SkillSlot* slot, int lasttrg);
	bool Render();
public:
	//���j���Ɋւ���v���Z�X
	void KOProcess(EnemyManager* en, SkillSlot* slot, int lasttrg);
	void DrawConbo();
	//�Q�b�^�[
	static GameSystem* GetInstance(){ return _sysInstance; }
protected:
	//���j��
	int mKo;
	//�X���b�g��]�J�n�t���O
	bool mKoSlot;
};

