#include "AttackTable.h"

AttackTable::AttackTable()
{
	//�A�C�e���R���e�i������
	mItem.clear();
}

AttackTable::~AttackTable()
{
	//�A�C�e���R���e�i���v�f�폜
	mItem.clear();
}

void AttackTable::Update()
{
}

void AttackTable::AddItem(AttackTableItem item)
{
	//�R���e�i�ɒǉ�
	mItem.push_back(item);
}
