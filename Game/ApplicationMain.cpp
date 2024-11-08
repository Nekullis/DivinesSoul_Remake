
#include "ApplicationMain.h"
#include "ModeGame.h"
#include "ModeTitle.h"
#include "ModeLogo.h"
#include <thread>

// ����
ApplicationMain				g_oApplicationMain;

bool ApplicationMain::Initialize(HINSTANCE hInstance) {
	if (!base::Initialize(hInstance)) { return false; }

	// �A�v���P�[�V�����O���[�o���̏�����
	mInit = new std::thread(&ApplicationGlobal::Init, &gGlobal);
	// ���[�h�̓o�^
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
	//����������Ă����
	if (gGlobal.mIsLoad && mInit != nullptr)
	{
		//�������ϐ��̍폜
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