#pragma once
#include "DivineTable.h"
#include "ApplicationGlobal.h"
#include <map>

//ディバインの登録、処理などをまとめるクラス
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
	//ゲッター
	std::map<int, DivineTable*> GetTable() { return mTable; }
protected:
	std::map<int, DivineTable*> mTable
};

