#include "GameUI.h"
#include "GameEvent.h"
#include "EN_Romanoff.h"
#include "GameSystem.h"
GameUI::GameUI()
{
	mUiPlHp = gGlobal.mRS->mGetGraph()["UI_playerhp"]._handle;
	mUiPlHpBarFrame = gGlobal.mRS->mGetGraph()["UI_playerhp_bar"]._handle;
	mUiEnHp = gGlobal.mRS->mGetGraph()["UI_enemyhp"]._handle;
	mUiEnHpBarFrame = gGlobal.mRS->mGetGraph()["UI_enemyhp_bar"]._handle;
	mUiIconFrame[0] = gGlobal.mRS->mGetGraph()["UI_icon_frame_01"]._handle;
	mUiIconFrame[1] = gGlobal.mRS->mGetGraph()["UI_icon_frame_02"]._handle;
	mUiIconFrame[2] = gGlobal.mRS->mGetGraph()["UI_icon_frame_03"]._handle;
	mUiIconFrame[3] = gGlobal.mRS->mGetGraph()["UI_icon_frame_04"]._handle;
	mUiDIcon[kindDivine::BLEATH] = gGlobal.mRS->mGetGraph()["UI_skill_bleath"]._handle;
	mUiDIcon[kindDivine::LASER] = gGlobal.mRS->mGetGraph()["UI_skill_lasar"]._handle;
	mUiDIcon[kindDivine::CIRCLE] = gGlobal.mRS->mGetGraph()["UI_skill_sircle"]._handle;
	mUiDIcon[kindDivine::SLASH] = gGlobal.mRS->mGetGraph()["UI_skill_slash"]._handle;
	mUiDIcon[kindDivine::DASH] = gGlobal.mRS->mGetGraph()["UI_skill_dashattack"]._handle;
	mUiDIcon[kindDivine::SONIC_WAVE] = gGlobal.mRS->mGetGraph()["UI_skill_sonic"]._handle;
	mUiDIcon[kindDivine::EXPLOSION] = gGlobal.mRS->mGetGraph()["UI_skill_explosion"]._handle;
	mUiDIcon[kindDivine::VACCUM] = gGlobal.mRS->mGetGraph()["UI_skill_vacuum"]._handle;
	mUiWeaponIcon[0] = gGlobal.mRS->mGetGraph()["UI_weapon_sword"]._handle;
	mUiWeaponIcon[1] = gGlobal.mRS->mGetGraph()["UI_weapon_lockon"]._handle;
	mUiWeaponIcon[2] = gGlobal.mRS->mGetGraph()["UI_weapon_lockon"]._handle;
	
}

GameUI::~GameUI()
{
	
}

void GameUI::Process()
{

}

void GameUI::IntervalDraw(std::array<kindDivine, 3> slot)
{
	//�C���^�[�o���摜�̃n���h������
	int cg = gGlobal.mRS->mGetGraph()["UI_skill_interval"]._handle;
	//for���Ŏg�����߂�std::tuple�ŕ`��ʒu��������
	std::tuple<int, int, int> pos[3] =
	{
		{1650,1730,880},
		{1560,1640,970},
		{1650,1730,1060}
	};
	//enum��int�ɕϊ�
	int i[3] =
	{
		static_cast<int>(slot[0]),
		static_cast<int>(slot[1]),
		static_cast<int>(slot[2]),
	};
	//�X���b�g�̕������J��Ԃ�
	for (int j = 0; j < 3; j++)
	{
		//�X�L���̍Ĕ����܂ł̃J�E���g���C���^�[�o���J�E���g�Ƃ���
		float interval = static_cast<float>(gGlobal.mPM->P_GetSkill()->GetSkill(i[j]).divineCnt);
		//�X�L���Ĕ����t���[���𑍃C���^�[�o���J�E���g�Ƃ���
		float max_interval = gGlobal.mPM->P_GetSkill()->GetSkill(i[j]).reInvocationFrame;
		//���������߂�̂�������͋t�̊������g��
		float ratio = 1 - interval / max_interval;
		//�X�L�������t���O��false�Ȃ�
		if (!gGlobal.mPM->P_GetSkill()->GetSkill(i[j]).invocationFlag)
		{
			//�摜�̋�`�`��
			DrawExtendGraph(std::get<0>(pos[j]), std::get<2>(pos[j]) - 80 * ratio, std::get<1>(pos[j]), std::get<2>(pos[j]), cg, false);
		}
	}
}

void GameUI::Draw(std::array<kindDivine, 3> slot)
{
	//HP�o�[�t���[���`��
	DrawGraph(0, 900, mUiPlHpBarFrame, TRUE);
	//HP�o�[�`��
	for (int i = 0; i < gGlobal.mPM->P_GetHp(); i++)
	{
		DrawGraph(55 + i * 2.15, 915, mUiPlHp, TRUE);
	}
	//�{�X�̗͕`��
	if (GameEvent::GetInstance()->GetEvent() >= 1)
	{
		for (int i = 0; i < EN_Romanoff::GetInstance()->GetHp(); i++)
		{
			DrawGraph(460 + i * 0.23, 60, mUiEnHp, TRUE);
		}
		DrawGraph(450, 50, mUiEnHpBarFrame, TRUE);
	}
	//�eUI�`��
	GameEvent::GetInstance()->DrawEventUI();
	GameSystem::GetInstance()->DrawConbo();
	//�t���[���̕`��
	DrawGraph(1640, 790, mUiIconFrame[1], TRUE);
	DrawGraph(1550, 880, mUiIconFrame[0], TRUE);
	DrawGraph(1640, 970, mUiIconFrame[2], TRUE);
	DrawGraph(1730, 880, mUiIconFrame[3], TRUE);
	//�A�C�R���̕`��
	DrawGraph(1650, 800, mUiDIcon[slot[0]], TRUE);
	DrawGraph(1560, 890, mUiDIcon[slot[1]], TRUE);
	DrawGraph(1650, 980, mUiDIcon[slot[2]], TRUE);
	DrawGraph(1740, 890, mUiWeaponIcon[0], TRUE);
	//�A�C�R���̍Ďg�p���Ԃ̉���
	IntervalDraw(slot);
	
	
}