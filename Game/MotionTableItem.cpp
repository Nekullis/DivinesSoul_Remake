#include "MotionTable.h"

MotionTableItem::MotionTableItem(int ID, float x, float y, float z, ATTACK_TYPE type, bool skill, bool course, bool isavoid)
{
	mMotionID		= ID;
	mVelocity		= VGet(x,y,z);
	mTrgAttack		= type;
	mIsSkill		= skill;
	mIsChangeCourse = course;
	mIsAvoid		= isavoid;
}

MotionTableItem::~MotionTableItem()
{

}