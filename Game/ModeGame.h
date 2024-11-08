#pragma once
#include "actioncollision.h"
#include "appframe.h"
#include "Camera.h"
#include "Effect.h"
#include "Enemy.h"
#include "GameUI.h"
#include "MapEntity.h"
#include "ObjectManager.h"
#include "SkillSlot.h"
#include "GameEvent.h"
#include "GameSystem.h"
#include <string>

// モード
class ModeGame : public ModeBase
{
	typedef ModeBase base;
	typedef ApplicationGlobal::stage stage;
public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();
protected:
	//使う各オブジェクト
	Camera*				mCam;
	GameEvent*			mEvent;
	GameSystem*			mSystem;
	MapEntity*			mMapEntity;
	EN_Osero*			mEnemy;
	EN_Crab*			mCrab;
	ActionCollision*	mActionCol;
	Effect*				mEffect;
	SkillSlot*			mSlot;
	GameUI*				mGameUI;
};

