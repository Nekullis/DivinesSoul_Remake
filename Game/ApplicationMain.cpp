
#include "ApplicationMain.h"
#include "ModeGame.h"
#include "ModeTitle.h"
#include "ModeLogo.h"
#include <thread>

// 実体
ApplicationMain				g_oApplicationMain;

bool ApplicationMain::Initialize(HINSTANCE hInstance) {
	if (!base::Initialize(hInstance)) { return false; }

	// アプリケーショングローバルの初期化
	mInit = new std::thread(&ApplicationGlobal::Init, &gGlobal);
	// モードの登録
	ModeServer::GetInstance()->Add(new ModeLogo(), 10, "Logo");
	ModeServer::GetInstance()->Add(new ModeSound(), 99999, "SoundLayer");

	return true;
}

bool ApplicationMain::Terminate() {
	base::Terminate();
	return true;
}


bool ApplicationMain::Input() {
	base::Input();
	gGlobal.PadInput();
	return true;
}

bool ApplicationMain::Process() {
	//初期化されていれば
	if (gGlobal.mIsLoad && mInit != nullptr)
	{
		//初期化変数の削除
		mInit->detach();
		delete mInit;
		mInit = nullptr;
	}
	base::Process();
	return true;
}

bool ApplicationMain::Render() {
	base::Render();
	return true;
}