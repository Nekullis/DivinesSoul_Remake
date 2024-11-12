//----------------------------------------------------------------------
// @filename ObjetManager.h
// @author: Fukuma Kyohei, Nara Mitsuki
// @explanation
// オブジェクト管理クラス
// オブジェクトの配置、挙動を管理するクラス
//----------------------------------------------------------------------
#pragma once
#include "MapEntity.h"

class ObjectManager{
	typedef ApplicationGlobal::stage stage;
public:
	ObjectManager();
	virtual ~ObjectManager();

	void Initialize(stage global);
	void Process();
	void Render();
protected:
	MapEntity* mEntity;
};

