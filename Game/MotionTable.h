#pragma once
#include "DxLib.h"
#include "vector"

enum class  CHARACTER_MOTION
{
	//�ҋ@
	PLAYER_STAND,
	//����
	PLAYER_RUN,
	//�ꌂ��
	PLAYER_FIRSTATTACK,
	//�񌂖�
	PLAYER_SECONDATTACK,
	//�O����
	PLAYER_LASTATTACK,
	//�_�b�V���U��
	PLAYER_DASHATTACK,
	//�f�B�o�C���X�L��
	PLAYER_SKILL,
	//�f�B�o�C���X�L��(�_�b�V��)
	PLAYER_SKILLDASH,
	//���
	PLAYER_AVOID,
	//�_���[�W
	PLAYER_DAMAGE,
	//�̗�0
	PLAYER_DIE
};

//�ǂ�������ԂŃ��[�V������������
enum class MOTION_LAYER
{
	//��ɓ����Ă���
	ALWAYS,
	//������Ԃœ���
	PRESS_DOWN,
	//�g���K���͂œ���
	TRIGGER,
	//��_���[�W�œ���
	DAMAGE
};

enum class ATTACK_TYPE
{
	//�U�����Ă��Ȃ�
	NONE,
	//�ꌂ��
	NORMAL_ATTACK,
	//�񌂖�
	SCOND_ATTACK,
	//�O����
	THIRD_ATTACK,
	//�_�b�V���U��
	DASH_ATTACK
};

class MotionTableItem
{
public:
	MotionTableItem(int, float, float, float, ATTACK_TYPE, bool, bool, bool);
	~MotionTableItem();
	//�Q�b�^�[
	int			GetMotionID()		{ return mMotionID; }
	VECTOR		GetVelocity()		{ return mVelocity; }
	ATTACK_TYPE	GetTrgAttack()		{ return mTrgAttack; }
	bool		GetIsSkill()		{ return mIsSkill; }
	bool		GetIsChangeCourse() { return mIsChangeCourse; }
	bool		GetIsAvoid()		{ return mIsAvoid; }
protected:
	//ID
	int mMotionID;
	//�ړ����x
	VECTOR mVelocity;
	//�U���ł��邩
	ATTACK_TYPE mTrgAttack;
	//�X�L���𔭓��ł��邩
	bool mIsSkill;
	//�����]���ł��邩
	bool mIsChangeCourse;
	//����ł��邩
	bool mIsAvoid;
};

class MotionTable
{
public:
	enum class MOTION_ENDTYPE
	{
		LOOP,
		END,
		DIE
	};
	MotionTable();
	~MotionTable();
	void Update();
	void AddItem(MotionTableItem item);
	//�Q�b�^�[
	std::vector<MotionTableItem> GetItem()  const{ return mItem; }
	MOTION_ENDTYPE GetEndType()				const{ return mEndType; }
	MOTION_LAYER GetLayer()					const{ return mLayer; }
	//�Z�b�^�[
	void SetEndType(MOTION_ENDTYPE endtype)		 { mEndType = endtype; }
	void SetLayer(MOTION_LAYER layer)			 { mLayer = layer; }
protected:
	//�R���e�i
	std::vector<MotionTableItem> mItem;
	MOTION_ENDTYPE mEndType;
	MOTION_LAYER mLayer;
};