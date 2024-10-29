#include "AttackTable.h"

AttackTableItem::AttackTableItem(int ID, bool istrg, bool ischange, bool iscol, bool isse, bool isvoice)
{
	mAttackID		= ID;
	mIsTrgButton	= istrg;
	mIsChangeAttack = ischange;
	mIsColAttack	= iscol;
	mIsPlaySE		= isse;
	mIsPlayVoice	= isvoice;
}

AttackTableItem::~AttackTableItem()
{

}
