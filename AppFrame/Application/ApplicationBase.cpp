#include "ApplicationBase.h"

ApplicationBase* ApplicationBase::_lpInstance = NULL;


ApplicationBase::ApplicationBase() {
	_lpInstance = this;
}

ApplicationBase::~ApplicationBase() {
}

bool ApplicationBase::Initialize(HINSTANCE hInstance) {

	// DX���C�u�����̏�����
	if (AppWindowed()) {
		ChangeWindowMode(true);							// �E�B���h�E���[�h�Ɏw�肷��
	}
	SetGraphMode(DispSizeW(), DispSizeH(), 32);
	// �������߂��Ƃ���Ń`���c�L����������iZ�[�x������Ȃ��j�΍�
	SetZBufferBitDepth(32);
	SetOutApplicationLogValidFlag(FALSE);
	SetMouseDispFlag(FALSE);
	if (DxLib_Init() == -1)
	{	// �G���[���N�����璼���ɏI��
		return false;
	}
	if (Effekseer_Init(20000) == -1)
	{
		DxLib_End();
		return -1;
	}
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();
	SetDrawScreen(DX_SCREEN_BACK);		// �`����ʂ𗠉�ʂɃZ�b�g

	// ����������
	srand((unsigned int)time(NULL));

	// ���[�h�T�[�o�̏�����
	_serverMode = new ModeServer();

	return true;
}

bool ApplicationBase::Terminate() {
	// DX���C�u�����J��
	Effkseer_End();
	DxLib_End();
	
	return true;
}


bool ApplicationBase::Input() {
	return true;
}

bool ApplicationBase::Process() {
	_serverMode->ProcessInit();
	_serverMode->Process();
	_serverMode->ProcessFinish();
	return true;
}

bool ApplicationBase::Render() {
	_serverMode->RenderInit();
	_serverMode->Render();
	_serverMode->RenderFinish();
	return true;
}
