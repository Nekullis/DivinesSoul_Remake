//----------------------------------------------------------------------
// @filename AttackTableManager.h
// @author: Fukuma Kyohei
// @explanation
// �U�����̊Ǘ��N���X
// �U���Ɉ����A�C�e���̏����Ɋւ���N���X
//----------------------------------------------------------------------
#pragma once
#include"MotionTableManager.h"
#include "AttackTable.h"

//�U�����̏����܂Ƃ߂�N���X
class AttackTableManager
{
public:
	AttackTableManager();
	~AttackTableManager();
	static AttackTableManager* mAtkManagerInstance;
	void Process();
	//�O���t�@�C���ōU�����擾
	void LoadAttackData(const std::string& filename, ATTACK_TYPE type, std::string voicename, std::string sename);
	//�w�肵���U���^�C�v���R���e�i�ɒǉ�
	void AddTable(ATTACK_TYPE type, AttackTable* table);
	//�U�����ύX
	void AttackChange(ATTACK_TYPE type);
	//�Q�b�^�[
	static AttackTableManager*	GetInstance()		  { return mAtkManagerInstance; }
	std::map<int, AttackTable*> GetAttackList()		  { return mAttackList; }
	AttackTable*				GetTable()			  { return mTable; }
	ATTACK_TYPE					GetType()		const { return mType; }
	bool						GetIsTrg()		const { return mIsTrg; }
	bool						GetIsChange()	const { return mIsChange; }
	int							GetAttackCount()const { return mAttackCnt; }
	int							GetMaxCount()	const { return mCountMax; }
protected:
	//�R���e�i
	std::map<int, AttackTable*> mAttackList;
	//�e�[�u��
	AttackTable* mTable;
	//�^�C�v
	ATTACK_TYPE mType;
	//�g���K���͒���
	bool mIsTrg;
	//�ύX�ł��邩
	bool mIsChange;
	//���[�V�����J�E���g
	int mAttackCnt;
	//�ő�J�E���g
	int mCountMax;

};

