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
	//インターバル画像のハンドルを代入
	int cg = gGlobal.mRS->mGetGraph()["UI_skill_interval"]._handle;
	//for文で使うためにstd::tupleで描画位置を初期化
	std::tuple<int, int, int> pos[3] =
	{
		{1650,1730,880},
		{1560,1640,970},
		{1650,1730,1060}
	};
	//enumをintに変換
	int i[3] =
	{
		static_cast<int>(slot[0]),
		static_cast<int>(slot[1]),
		static_cast<int>(slot[2]),
	};
	//スロットの分だけ繰り返す
	for (int j = 0; j < 3; j++)
	{
		//スキルの再発動までのカウントをインターバルカウントとする
		float interval = static_cast<float>(gGlobal.mPM->P_GetSkill()->GetSkill(i[j]).divineCnt);
		//スキル再発動フレームを総インターバルカウントとする
		float max_interval = gGlobal.mPM->P_GetSkill()->GetSkill(i[j]).reInvocationFrame;
		//割合を求めるのだが今回は逆の割合を使う
		float ratio = 1 - interval / max_interval;
		//スキル発動フラグがfalseなら
		if (!gGlobal.mPM->P_GetSkill()->GetSkill(i[j]).invocationFlag)
		{
			//画像の矩形描画
			DrawExtendGraph(std::get<0>(pos[j]), std::get<2>(pos[j]) - 80 * ratio, std::get<1>(pos[j]), std::get<2>(pos[j]), cg, false);
		}
	}
}

void GameUI::Draw(std::array<kindDivine, 3> slot)
{
	//HPバーフレーム描画
	DrawGraph(0, 900, mUiPlHpBarFrame, TRUE);
	//HPバー描画
	for (int i = 0; i < gGlobal.mPM->P_GetHp(); i++)
	{
		DrawGraph(55 + i * 2.15, 915, mUiPlHp, TRUE);
	}
	//ボス体力描画
	if (GameEvent::GetInstance()->GetEvent() >= 1)
	{
		for (int i = 0; i < EN_Romanoff::GetInstance()->GetHp(); i++)
		{
			DrawGraph(460 + i * 0.23, 60, mUiEnHp, TRUE);
		}
		DrawGraph(450, 50, mUiEnHpBarFrame, TRUE);
	}
	//各UI描画
	GameEvent::GetInstance()->DrawEventUI();
	GameSystem::GetInstance()->DrawConbo();
	//フレームの描画
	DrawGraph(1640, 790, mUiIconFrame[1], TRUE);
	DrawGraph(1550, 880, mUiIconFrame[0], TRUE);
	DrawGraph(1640, 970, mUiIconFrame[2], TRUE);
	DrawGraph(1730, 880, mUiIconFrame[3], TRUE);
	//アイコンの描画
	DrawGraph(1650, 800, mUiDIcon[slot[0]], TRUE);
	DrawGraph(1560, 890, mUiDIcon[slot[1]], TRUE);
	DrawGraph(1650, 980, mUiDIcon[slot[2]], TRUE);
	DrawGraph(1740, 890, mUiWeaponIcon[0], TRUE);
	//アイコンの再使用時間の可視化
	IntervalDraw(slot);
	
	
}