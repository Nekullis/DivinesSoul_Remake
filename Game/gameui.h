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
	//スキル発動時のインターバルの可視化
	void IntervalDraw(std::array<kindDivine, 3> slot);
	//描画
	void Draw(std::array<kindDivine, 3> slot);
protected:
	//プレイヤーHPバー
	int mUiPlHp;
	//プレイヤーHPバーフレーム
	int mUiPlHpBarFrame;
	//ボスHPバー
	int mUiEnHp;
	//ボスHPバーフレーム
	int mUiEnHpBarFrame;
	//スキルガチャアイコン
	int mUiSkillIcon[7];
	//スキルアイコン
	std::unordered_map<kindDivine, int> mUiDIcon;
	//武器アイコン
	int mUiWeaponIcon[3];
	//アイコンフレーム
	int mUiIconFrame[4];
};

