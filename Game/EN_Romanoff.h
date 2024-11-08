#pragma once
#include "Enemy.h"
class EN_Romanoff :public Enemy
{
	using base = Enemy;
public:
	enum class ANIMATION :int
	{
		WAIT,
		RUN,
		FIRSTATTACK,
		SECONDATTACK,
		SKILL,
		DAMAGE,
		DIE
	};
public:
	EN_Romanoff(int model, int weapon, VECTOR vpos, VECTOR vdir);
	virtual ~EN_Romanoff();
	static EN_Romanoff* _bossInstance;
	bool Process(VECTOR pl_pos) override;
	bool Render() override;
	bool Debug() override;
	bool Delete() override;
public:
	//�A�j���[�V�����v���Z�X
	bool A_Process();
	//�v�Z�n�v���Z�X
	bool C_Process(VECTOR pl_pos);
	void DiscoveryProcess(VECTOR pl_pos);
	void WaitProcess();
	void AttackProcess();
	void AssaultProcess(VECTOR pl_pos);
	void DamageProcess();
	void DieProcess();
	void RunProcess(VECTOR pl_pos);
	void SetWeapon();
	void Move(float speed,VECTOR pl_pos);
	void Invincible(int nextframe);
	VECTOR AttackPos();
	bool Attack();
	bool Assult();
	//�����蔻��N���X�Ɏg���_���[�W�֐�
	bool Damage(VECTOR pl_pos, int subpoint, int nextframe)override;
	bool Suction(VECTOR pl_pos, int nextframe)override;
	//�X�e�[�^�X�ύX
	void ChangeStatus(STATUS en_status)override;
	static EN_Romanoff* GetInstance() { return _bossInstance; }
protected:
	//romanoff�̏��
	STATUS mStatus;
	//�s���̃f�[�^
	ACTIONDATA mData;
	//�A�j���[�V����
	ANIMATION  mAnimation;
	//���A�j���[�V����
	ANIMATION  mOldAnimation;
	//�_���[�W�J�E���g
	int mDamageCnt;
};

