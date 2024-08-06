#include "AttackTable.h"

AttackTable::AttackTable()
{
	//アイテムコンテナ初期化
	mItem.clear();
}

AttackTable::~AttackTable()
{
	//アイテムコンテナ内要素削除
	mItem.clear();
}

void AttackTable::Update()
{
}

void AttackTable::AddItem(AttackTableItem item)
{
	//コンテナに追加
	mItem.push_back(item);
}
