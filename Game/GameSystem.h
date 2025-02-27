#pragma once
#include "EnemyManager.h"
#include "SkillSlot.h"
constexpr auto CHANGE_SKILL_COMBO = 30;
class GameSystem
{
public:
	GameSystem();
	virtual ~GameSystem();
	//インスタンス
	static GameSystem* _sysInstance;
	bool Process(EnemyManager* en, SkillSlot* slot, int lasttrg);
	bool Render();
public:
	//撃破数に関するプロセス
	void KOProcess(EnemyManager* en, SkillSlot* slot, int lasttrg);
	void DrawConbo();
	//ゲッター
	static GameSystem* GetInstance(){ return _sysInstance; }
protected:
	//撃破数
	int mKo;
	//スロット回転開始フラグ
	bool mKoSlot;
};

