#pragma once
#include "appframe.h"
#include "ApplicationGlobal.h"
#include "EnumInfo.h"
#include "Player.h"
class GameUI
{
public:
	GameUI();
	virtual ~GameUI();
	void Process();
	//�X�L���������̃C���^�[�o���̉���
	void IntervalDraw(std::array<kindDivine, 3> slot);
	//�`��
	void Draw(std::array<kindDivine, 3> slot);
protected:
	//�v���C���[HP�o�[
	int mUiPlHp;
	//�v���C���[HP�o�[�t���[��
	int mUiPlHpBarFrame;
	//�{�XHP�o�[
	int mUiEnHp;
	//�{�XHP�o�[�t���[��
	int mUiEnHpBarFrame;
	//�X�L���K�`���A�C�R��
	int mUiSkillIcon[7];
	//�X�L���A�C�R��
	std::unordered_map<kindDivine, int> mUiDIcon;
	//����A�C�R��
	int mUiWeaponIcon[3];
	//�A�C�R���t���[��
	int mUiIconFrame[4];
};

