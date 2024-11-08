#pragma once
#include "appframe.h"
#include "Divine.h"
#include <string>
#include "MotionTableManager.h"
#include "AttackTableManager.h"

//�v���C���[�����S�ʂ̃N���X
class Player
{
public:
	Player();
	virtual ~Player();
	void Initialize(int handle,int weapon);
	//�C���X�^���X
	static Player* mPlInstance;
	void ActionProcess(VECTOR campos, VECTOR camtarget, SkillSlot* slot);
	//Animation:�A�j���[�V�����i�s����
	void A_Process();
	//Calcalate:�v�Z�n����
	void C_Process();
	void Process(VECTOR campos, VECTOR camtarget, SkillSlot* slot);
	//�`��
	void Render();
	//�X�L�����[�V����
	CHARACTER_MOTION SkillMotion();
	//json��p�����ʒu�ݒ�
	void SetJsonTransform();
	//���푕��
	void SetWeapon();
	//�X�L���������{�C�X
	void SkillVoice();
	//�v���C���[�X�L������
	void PlayerSkill(SkillSlot* slot,  VECTOR campos, VECTOR camtarget);
	//�v���C���[���S����
	void PlayerDie();
	//��_���[�W�㏈��
	void Invincible();
	//�_���[�W
	void Damage(VECTOR pos,int subpoint);
	//�Q�b�^�[
	static Player* GetInstance()			 { return mPlInstance; }
	VECTOR GetMove()				const	 { return mMove; }
	VECTOR GetPos()					const	 { return mPos; }
	VECTOR GetDir()					const	 { return mDir; }
	float  GetRadius()				const	 { return mRCap; }
	float  GetSeg()					const	 { return mLineSeg; }
	int	   GetLastCommand()			const	 { return mLastCommand; }
	bool   GetAvoidFlag()			const	 { return mAvoidFlag; }
	int    GetHp()					const	 { return mHp; }
	int    GetAtk()					const	 { return mAtk; }
	bool   GetGameOver()			const	 { return mGameOverFlag; }
	bool   GetInvincible()			const	 { return mNoDamage; }
	int    GetAttachIndex()			const	 { return mAttachIndex; }
	VECTOR GetWeaponPos(int i)		const	 { return mWPos[i]; }
	Divine* GetDivine()						 { return mSkill; }
	MotionTableManager* GetMotionManager()	 { return mMotionManager; }
	AttackTableManager* GetAttackManager()	 { return mAttackManager; }
	//�Z�b�^�[
	void SetPos(VECTOR any)		{ mPos = any; }
	void SetMove(VECTOR vec)	{ mMove = vec; }
	void SetGravity(float gra)	{ mGravity = gra; }
	void SetAttackFlag(bool a)	{ mIsAttack = a; }
	void SetInvincible(bool i)  { mNoDamage = i; }
	void SetStatusSkill(bool i) { mIsSkill = i; }

private:
	//�ʒu
	VECTOR mPos;
	//�p�x�A����
	VECTOR mDir;
	//�ړ���
	VECTOR mMove;
	//�J�v�Z���̒���
	float mLineSeg;
	//�����蔻��p
	VECTOR mCapsule[2];
	float mRCap;
	//���픻��ʒu
	VECTOR mWeaponVPos;
	//�d�͒l
	float mGravity;
	//�̗�
	int mHp;
	//�U����
	int mAtk;
	//���G�J�E���g
	int mInvincibleCnt;
	//�U�������ǂ���
	bool mIsAttack;
	bool mNoDamage;
	bool mIsSkill;
	bool mIsDie;
	bool mGameOverFlag;
	//����t���O
	bool mAvoidFlag;
	//�Ō�ɉ������{�^��
	int mLastCommand;
	//3D���f���`��p
	//�`�惂�f��
	int mModel;
	int mDashModel;
	//�A�^�b�`����A�j���[�V�����C���f�b�N�X
	int mAttachIndex;
	//�ȑO�̃A�^�b�`���ꂽ�A�j���[�V�����C���f�b�N�X
	float mOldIndex;
	//�V���C���f�b�N�X�̓���ւ�背�[�g
	int mRate;
	//���탂�f��
	int mWModel;
	//����ʒu
	VECTOR mWPos[2];
	//�f�B�o�C���X�L���N���X
	Divine* mSkill;
	//���[�V�����}�l�[�W���[
	MotionTableManager* mMotionManager;
	//�U���}�l�[�W���[
	AttackTableManager* mAttackManager;
	//�����[�V����
	CHARACTER_MOTION mOldMotion;
	//�V���[�V����
	CHARACTER_MOTION mMotion;

};

