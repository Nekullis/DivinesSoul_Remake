#include "AttackTable.h"

AttackTableItem::AttackTableItem(int ID, bool istrg, bool ischange, bool iscol)
{
	mAttackID = ID;
	mIsTrgButton = istrg;
	mIsChangeAttack = ischange;
	mIsColAttack = iscol;
}

AttackTableItem::~AttackTableItem()
{

}
