//----------------------------------------------------------------------
// @filename MotionTableManager.h
// @author: Fukuma Kyohei
// @explanation
// ���[�V�����Ǘ��N���X
// ���[�V�����̒ǉ��A�ύX���Ǘ�����N���X
//----------------------------------------------------------------------
#pragma once
#include "MotionTable.h"
#include <map>
#include <string>
#include <utility>
class MotionTableManager
{
public:
	MotionTableManager();
	virtual ~MotionTableManager();
	static MotionTableManager* mMotTableInstance;
	void Process();
	//�O���t�@�C������f�[�^�擾
	void LoadTable(const std::string& filename, CHARACTER_MOTION motion, MotionTable::MOTION_ENDTYPE endtype, MOTION_LAYER layer);
	//���[�V�����e�[�u���ǉ�
	void AddTable(CHARACTER_MOTION motionID,MotionTable* table);
	//���[�V�����ύX
	void ChangeMotion(CHARACTER_MOTION motion);
	//�Q�b�^�[
	static MotionTableManager*	GetInstance()			{ return mMotTableInstance; }
	int							GetMotionCnt() const	{ return mMotionCnt; }
	int							GetMaxCnt()	   const	{ return mCountMax; }
	MotionTable*				GetTable()				{ return mTable; }
	CHARACTER_MOTION			GetMotion()				{ return mMotion; }
	std::map<int, std::pair<MotionTable::MOTION_ENDTYPE, MotionTable*>> GetMotionList() { return mMotionList; }
protected:
	//�e�[�u���R���e�i
	std::map<int, std::pair<MotionTable::MOTION_ENDTYPE, MotionTable*>> mMotionList;
	MotionTable* mTable;
	CHARACTER_MOTION mMotion;
	MOTION_LAYER mLayer;
	//���[�V�����J�E���g
	int mMotionCnt;
	//�ő�J�E���g
	int mCountMax;
};

