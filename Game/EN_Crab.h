//----------------------------------------------------------------------
// @filename EN_Crab.h
// @author: Fukuma Kyohei
// @explanation
// �G�h���N���X
// �J�u�g�K�j�^�̓G�̏����N���X
//----------------------------------------------------------------------
#pragma once
#include "Enemy.h"
class EN_Crab : public Enemy
{
	using base = Enemy;
public:
	EN_Crab(int model, int weapon, VECTOR vpos, VECTOR vdir);
	virtual ~EN_Crab();
	bool C_Process(VECTOR pl_pos);
	bool Process(VECTOR pl_pos) override;
	bool Render() override;
	bool Debug() override;
	bool Delete() override;
	//�����蔻��N���X�Ɏg���_���[�W�֐�
	bool Damage(VECTOR pl_pos,int subpoint, int nextframe)override;
	bool Suction(VECTOR pl_pos, int nextframe)override;
	//�X�e�[�^�X�ύX
	void ChangeStatus(STATUS en_status)override;
protected:
	//crab�̃f�[�^
	ACTIONDATA mData;
	//�s���̃f�[�^
	STATUS mStatus;
};

