//----------------------------------------------------------------------
// @filename PlayerManager.h
// @author: Fukuma Kyohei, Nara Mitsuki
// @explanation
// �v���C���[�Ǘ��N���X
// �v���C���[���������S�ɏ�̊K�w�ň�����悤�ɂ���N���X
//----------------------------------------------------------------------
#pragma once
#include "Player.h"
class PlayerManager
{
public:
	PlayerManager();
	virtual ~PlayerManager();
	void Initialize();
	void Process();
	// �v���C���[�`��܂ށA�����f�o�b�O����`�悷��̂ł���΂܂Ƃ߂�
	void Render(); 
	// �v���C���[�N���X���玝���Ă����������K�w���グ�ă}�l�[�W���[���璼�Ɏg����悤�ɂ��Ă���
	// �Q�[���{�҂ɓ����Ă����Ƃ��A�v���C���[���o��������E����܂łɎ󂯎�������l�ŏ�����
	void P_Materialize(); 
	void P_Delete();
	void P_Initialize(int handle, int weapon);
	void P_Process(VECTOR campos, VECTOR camtarget,SkillSlot* slot);
	void P_AnimProcess();
	void P_CalcuProcess();
	void P_Damage(VECTOR pos, int subpoint);
	//�Q�b�^�[
	Player* P_Get() { return mPl; }
	VECTOR	P_GetMove()			{ return mPl->GetMove(); }
	VECTOR	P_GetPos()			{ return mPl->GetPos(); }
	VECTOR	P_GetDir()			{ return mPl->GetDir(); }
	Divine* P_GetSkill()		{ return mPl->GetDivine(); }
	int		P_GetHp()			{ return mPl->GetHp(); }
	bool	P_GetDie()			{ return mPl->GetGameOver(); }
	int		P_GetCommand()		{ return mPl->GetLastCommand(); }
	void	P_SetPos(VECTOR any){ mPl->SetPos(any); }
private:
	Player* mPl;
};

