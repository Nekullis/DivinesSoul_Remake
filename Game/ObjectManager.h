//----------------------------------------------------------------------
// @filename ObjetManager.h
// @author: Fukuma Kyohei, Nara Mitsuki
// @explanation
// �I�u�W�F�N�g�Ǘ��N���X
// �I�u�W�F�N�g�̔z�u�A�������Ǘ�����N���X
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

