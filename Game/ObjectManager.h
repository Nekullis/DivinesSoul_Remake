#pragma once
#include "MapEntity.h"
// �I�u�W�F�N�g�̔z�u�A�������L�q�i��ɒn�`�E�M�~�b�N�֘A�A�G�t�F�N�g���H�j
// �v���C���[��G�Ȃǂ̃L�����͕ʃN���X��

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

