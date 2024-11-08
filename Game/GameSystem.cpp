#include "GameSystem.h"
GameSystem* GameSystem::_sysInstance = nullptr;
GameSystem::GameSystem()
{
	_sysInstance = this;
	mKoSlot = false;
	mKo = 0;
}

GameSystem::~GameSystem()
{

}

void GameSystem::KOProcess(EnemyManager* en, SkillSlot* slot, int lasttrg)
{
	//コンボ数取得
	mKo = en->GetCombo();
	//コンボ数が規定数に達した
	if (mKo >= CHANGE_SKILL_COMBO)
	{
		mKoSlot = true;
		//コンボ数リセット
		en->SetCombo(0);
	}
	if (mKoSlot)
	{
		int trg = lasttrg;
		SoundItemBase* snditem_se = gGlobal.mSndServer.Get("SE_Slot_Start");
		snditem_se->Play();
		slot->SlotSpin(trg);
		if (!slot->GetIsSpin())
		{
			mKoSlot = false;
		}
	}
}

bool GameSystem::Process(EnemyManager* en, SkillSlot* slot, int lasttrg)
{
	KOProcess(en,slot,lasttrg);
	return true;
}

void GameSystem::DrawConbo()
{
	int x = 1600;
	int ko = mKo;
	int loop_cnt = 0;
	while (1)
	{
		int cg = gGlobal.mRS->mGetDivGraph()["combo_number"].handle[ko % 10];
		DrawGraph(x, 600, cg, true);
		ko /= 10;
		x -= 60;
		loop_cnt++;
		if (loop_cnt >= 2) { break; }
	}
	int ko_slash = gGlobal.mRS->mGetGraph()["KO_slash"]._handle;
	DrawGraph(1640, 630, ko_slash, true);
	int max_ko[2] =
	{
		gGlobal.mRS->mGetDivGraph()["combo_number"].handle[CHANGE_SKILL_COMBO % 10],
		gGlobal.mRS->mGetDivGraph()["combo_number"].handle[CHANGE_SKILL_COMBO / 10]
	};
	for (int i = 0; i < 2; i++)
	{
		DrawGraph(1730 - (60 * i), 660, max_ko[i], true);
	}
	int ko_hundle = gGlobal.mRS->mGetGraph()["KO"]._handle;
	DrawGraph(1790, 700, ko_hundle, true);
}

bool GameSystem::Render()
{
	DrawConbo();
	return true;
}


