#include "DivineTable.h"

DivineItem::DivineItem(DIVINENAME name, VECTOR pos, int atk, float size, float invocationframe, float reinvocationframe, float startframe, float endframe, Effect* effect, float effectdir, std::string se, std::string voice)
{
	//èâä˙âª
	mName				=	name;
	mPos				=	pos;
	mAtkPoint			=	atk;
	mSize				=	size;
	mInvocationFrame	=	invocationframe;
	mReInvocationFrame	=	reinvocationframe;
	mStartColFrame		=	startframe;
	mEndColFrame		=	endframe;
	mEffect				=	effect;
	mEffectDir			=	effectdir;
	mSECode				=	se;
	mVoiceCode			=	voice;
}

DivineItem::~DivineItem()
{
	delete mEffect;
}