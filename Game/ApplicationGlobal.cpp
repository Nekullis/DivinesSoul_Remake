#include "ApplicationGlobal.h"

ApplicationGlobal		gGlobal;

ApplicationGlobal::ApplicationGlobal() 
{

}

ApplicationGlobal::~ApplicationGlobal() 
{
	delete mPM;
	mRS->ExcludeObject_map("res/Json/ObjectList.json");
	delete gPad;
	delete mRS;
}

bool ApplicationGlobal::Init() 
{
	mIsLoad = false;
	mRS = new ResourceServer();
	mPM = new PlayerManager();
	gPad = new GameXPad();
	mStageNum = stage::none;

	mRS->JsonToJMap("res/Json/ObjectList.json");
	mRS->JMapToArray();
	mIsLoad = true;
	return true;
}


void ApplicationGlobal::PadInput() 
{
	gPad->Input();
}