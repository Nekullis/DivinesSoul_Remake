#pragma once
#include "ApplicationMain.h"
#include "ModeGame.h"
#include "ModeGameClear.h"
#include "ModeGameover.h"
#include "ModeEnding.h"
#include "ModeFade.h"

bool ModeGame::Initialize() {
	if (!base::Initialize()) { return false; }
	//ŠeƒNƒ‰ƒX‰Šú‰»
	gGlobal.mStageNum = ApplicationGlobal::stage::stage1;
	mMapEntity =	new MapEntity();
	mActionCol =	new ActionCollision();
	mSlot =			new SkillSlot();
	gGlobal.mPM->P_Materialize();
	mGameUI =		new GameUI();
	mEvent =		new GameEvent();
	mSystem =		new GameSystem();
	gGlobal.mPM->P_Initialize(gGlobal.mGetModel()["Feld"]._handle, gGlobal.mGetModel()["W_Sword"]._handle);
	mCam =			new Camera();
	return true;
}

bool ModeGame::Terminate() {
	delete mCam;
	gGlobal.mPM->P_Delete();
	delete mEvent;
	delete mMapEntity;
	delete mGameUI;
	gGlobal.mStageNum = ApplicationGlobal::stage::none;
	base::Terminate();
	return true;
}

bool ModeGame::Process() {
	std::string bgmName;
	if (mEvent->GetEvent() < 1)
	{
		bgmName = "BGM_Quest01";
	}
	else if (mEvent->GetEvent() >= 1)
	{
		bgmName = "BGM_Boss";
	}
	SoundItemBase* sndItem = gGlobal.mSndServer.Get(bgmName);
	sndItem->SetVolume(75);
	 //“Ç‚İ‚İŠ®—¹‚µ‚Ä‚¢‚é‚©H
	if (sndItem && sndItem->IsLoad()) {
		// Ä¶’†‚©H
		if (sndItem->IsPlay() == false) {
			// Ä¶‚·‚é
			sndItem->Play();
		}
	}
	base::Process();
	mMapEntity->Process();
	mActionCol->Process(gGlobal.mPM->P_Get(), mEvent->GetEnemyManager());
	gGlobal.mPM->P_Process(mCam->GetPos(), mCam->GetTarget(), mSlot);
	mCam->Process(gGlobal.gPad->GetXLx(), gGlobal.gPad->GetXLy());
	Effect::GetInstance()->Update();
	mEvent->Process();
	mSystem->Process(mEvent->GetEnemyManager(),mSlot,gGlobal.mPM->P_GetCommand());
	mSlot->Process();
	if (mEvent->GetEvent() >= 1)
	{
		if (EN_Romanoff::GetInstance()->GetDeleteFlag())
		{
			sndItem->Stop();
			// ‚±‚Ìƒ‚[ƒh‚ğíœ—\–ñ
			ModeServer::GetInstance()->Del(this);
			// Ÿ‚Ìƒ‚[ƒh‚ğ“o˜^
			ModeServer::GetInstance()->Add(new ModeEnding(), 1, "Ending");
		}
	}
	
	if (gGlobal.mPM->P_GetDie())
	{
		sndItem->Stop();
		// ‚±‚Ìƒ‚[ƒh‚ğíœ—\–ñ
		ModeServer::GetInstance()->Del(this);
		// Ÿ‚Ìƒ‚[ƒh‚ğ“o˜^
		ModeServer::GetInstance()->Add(new ModeGameover(), 1, "gameover");
	}
	return true;
}

bool ModeGame::Render() {
	base::Render();
	// 3DŠî–{İ’è
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);
	mMapEntity->Render();
	gGlobal.mPM->Render();
	mEvent->Render();
	mGameUI->Draw(mSlot->GetSlot());
	mSlot->Render();
	return true;
}

