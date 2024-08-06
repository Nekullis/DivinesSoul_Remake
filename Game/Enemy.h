#pragma once
#include"dxlib.h"
#include"MathCollision.h"
#include"string"
#include"ApplicationGlobal.h"
class Enemy
{
public:
	enum ENEMYTYPE
	{
		NOCHARA,
		OSERO,
		CRAB,
		ROMANOFF
	};
	enum STATUS
	{
		//������
		NODISCOVERY,
		//�ҋ@
		WAIT,
		//�x�e
		REST,
		//�U��
		ATTACK,
		//�ˌ�
		ASSAULT,
		//�_���[�W
		DAMAGE,
		//���s
		RUN,
		//�x��
		CAUTION,
		//���S
		DIE,
	};
	struct ACTIONDATA
	{
		//�X�e�[�^�X
		STATUS status;
		//���[�V�����̃g�[�^���t���[��
		float motionTotalFrame;
		//�T���͈�
		float searchArea;
	};
public:
	Enemy(int model, int weapon, VECTOR vpos, VECTOR vdir);
	virtual ~Enemy();
	virtual bool Process(VECTOR pl_pos);
	virtual bool Render();
	virtual bool Debug();
	virtual bool Delete();
	virtual bool Damage(VECTOR pl_pos, int subpoint,int nextframe);
	virtual bool Suction(VECTOR pl_pos,  int nextframe);
	//�X�e�[�^�X�ύX
	virtual void ChangeStatus(STATUS en_status);
	//�Q�b�^�[
	VECTOR	GetPos()			{ return mPos; }
	VECTOR	GetDir()			{ return mDir; }
	float	GetRadius()			{ return mRadius; }
	float	GetSeg()			{ return mLineSeg; }
	bool	GetAttackFlag()		{ return mIsAttack; }
	VECTOR	GetWeaponPos(int i)	{ return mWeaponPos[i]; }
	float	GetWeaponSize()		{ return mWeaponSize; }
	bool	GetInvincible()		{ return mNoDamage; }
	int		GetHp()				{ return mHp; }
	int		GetATK()			{ return mAtk; }
	bool	GetDeleteFlag()		{ return mDeleteFlag; }
	ENEMYTYPE GetEnemyType()	{ return mType; }
	//�Z�b�^�[
	void  SetPos(VECTOR i)		{ mPos = VAdd(mPos, i); }
	void  SetDir(VECTOR i)		{ mDir = i; }
	void  SetAttackFlag(bool i)	{ mIsAttack = i; }
	void  SetStatus(STATUS status) { ChangeStatus(status); }
protected:
	ENEMYTYPE mType;
	//�ʒu
	VECTOR mPos;
	//����
	VECTOR mDir;
	//�ړ���
	VECTOR mMove;
	//�J�v�Z���p
	VECTOR mCapsule[2];
	//���a
	float mRadius;
	//�����̒���
	float mLineSeg;
	//�̗�
	int mHp;
	//�U����
	int mAtk;
	//�J�E���g
	int mActionCnt;
	//����
	int mTimeCnt;
	//���G����
	int mInvincibleCnt;
	//������܂ł̃J�E���g
	int mNextFrame;
	//�U������
	bool mIsAttack;
	//�_���[�W���󂯂�
	bool mDamage;
	//���G����
	bool mNoDamage;
	//�̗͂�0���ǂ���
	bool mDie;
	//��������t���O
	bool mDeleteFlag;
	//���f��
	int mModel;
	std::string mName;
	//�A�^�b�`����A�j���[�V�����C���f�b�N�X
	int mAttachIndex;
	//�A�j���[�V�����̃g�[�^������
	float mTotalTime;
	//�A�j���[�V��������
	float mPlayTime;
	//���탂�f��
	int mWeaponModel;
	//����ʒu
	VECTOR mWeaponPos[2];
	//����T�C�Y
	float mWeaponSize;


};

