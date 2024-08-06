#pragma once
#include "Enemy.h"
#include"cmath"
class EN_Osero : public Enemy
{
	using base = Enemy;
public:
	EN_Osero(int model,int weapon,VECTOR vpos, VECTOR vdir);
	virtual ~EN_Osero();
	//�A�j���[�V�����v���Z�X
	bool A_Process();
	//�v�Z�n�v���Z�X
	bool C_Process(VECTOR pl_pos);
	bool Process(VECTOR pl_pos) override;
	bool Render() override;
	bool Debug() override;
	bool Delete() override;
public:
	void WaitProcess(VECTOR pl_pos);
	void RunProcess(VECTOR pl_pos);
	void CautionProcess(VECTOR pl_pos);
	void AttackProcess();
	void DamageProcess();
	void DieProcess();
	
	void SetWeapon();
	void Move(float speed, VECTOR pl_pos);
	void Invincible(int nextframe);
	VECTOR AttackPos();
	//�����蔻��N���X�Ɏg���_���[�W�֐�
	bool Damage(VECTOR pl_pos, int subpoint, int nextframe)override;
	bool Suction(VECTOR pl_pos, int nextframe)override;
	//�X�e�[�^�X�ύX
	void ChangeStatus(STATUS en_status)override;
protected:
	//osero�̏��
	STATUS mStatus;
	STATUS mOldStatus;
	//�s���̃f�[�^
	ACTIONDATA mData;
	
};

