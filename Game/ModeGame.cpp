#pragma once
#include "ApplicationMain.h"
#include "ModeGame.h"
#include "ModeGameClear.h"
#include "ModeGameover.h"
#include "ModeEnding.h"
#include "ModeFade.h"

bool ModeGame::Initialize() {
	if (!base::Initialize()) { return false; }
	//各クラス初期化
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
	 //読み込み完了しているか？
	if (sndItem && sndItem->IsLoad()) {
		// 再生中か？
		if (sndItem->IsPlay() == false) {
			// 再生する
			sndItem->Play();
		}
	}

	//各オブジェクト更新処理
	base::Process();
	mMapEntity->Process();
	mActionCol->Process(gGlobal.mPM->P_Get(), mEvent->GetEnemyManager());
	gGlobal.mPM->P_Process(mCam->GetPos(), mCam->GetTarget(), mSlot);
	mCam->Process(gGlobal.gPad->GetXLx(), gGlobal.gPad->GetXLy());
	Effect::GetInstance()->Update();
	mEvent->Process();
	mSystem->Process(mEvent->GetEnemyManager(),mSlot,gGlobal.mPM->P_GetCommand());
	mSlot->Process();

	//ゲームがクリアされた場合
	if (mEvent->GetEvent() >= 1)
	{
		if (EN_Romanoff::GetInstance()->GetDeleteFlag())
		{
			sndItem->Stop();
			// このモードを削除予約
			ModeServer::GetInstance()->Del(this);
			// 次のモードを登録
			ModeServer::GetInstance()->Add(new ModeEnding(), 1, "Ending");
		}
	}
	
	//プレイヤーの体力が0の場合
	if (gGlobal.mPM->P_GetDie())
	{
		sndItem->Stop();
		// このモードを削除予約
		ModeServer::GetInstance()->Del(this);
		// 次のモードを登録
		ModeServer::GetInstance()->Add(new ModeGameover(), 1, "gameover");
	}
	return true;
}

bool ModeGame::Render() {
	base::Render();

	// 3D基本設定
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);

	//オブジェクト描画
	mMapEntity->Render();
	gGlobal.mPM->Render();
	mEvent->Render();
	mGameUI->Draw(mSlot->GetSlot());
	mSlot->Render();
	return true;
}

