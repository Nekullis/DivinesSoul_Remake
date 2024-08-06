#pragma once
#include "DivineTable.h"
#include "ApplicationGlobal.h"
#include <map>

//�f�B�o�C���̓o�^�A�����Ȃǂ��܂Ƃ߂�N���X
class DivineManager
{
public:
	DivineManager();
	~DivineManager();
	void Process();
	void Render();
	void AddTable(DivineTable* table);
	void LoadDivine(DIVINENAME name);
	void Invocation(kindDivine divine);
	void Reset();
	//�Q�b�^�[
	std::map<int, DivineTable*> GetTable() { return mTable; }
protected:
	std::map<int, DivineTable*> mTable
};

