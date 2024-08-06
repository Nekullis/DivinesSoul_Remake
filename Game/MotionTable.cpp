#include "MotionTable.h"

MotionTable::MotionTable()
{
	mItem.clear();
	mEndType = MOTION_ENDTYPE::END;
	mLayer = MOTION_LAYER::ALWAYS;
}

MotionTable::~MotionTable()
{

}

void MotionTable::Update()
{

}

void MotionTable::AddItem(MotionTableItem item)
{
	mItem.push_back(item);
}



