#include "AttackTable.h"

AttackTableItem::AttackTableItem(int ID, bool istrg, bool ischange, bool iscol)
{
	//����������擾
	mAttackID = ID;
	mIsTrgButton = istrg;
	mIsChangeAttack = ischange;
	mIsColAttack = iscol;
}

AttackTableItem::~AttackTableItem()
{

}
