
#include "ApplicationMain.h"
#include "ModeGameover.h"
#include "ModeGame.h"

bool ModeGameover::Initialize() {
	if (!base::Initialize()) { return false; }
	_cg[0] = gGlobal.mRS->mGetGraph()["gameover_continue"]._handle;
	_cg[1] = gGlobal.mRS->mGetGraph()["gameover_reset"]._handle;
	_selection = 0;
	return true;
}

bool ModeGameover::Terminate() {
	base::Terminate();
	return true;
}

bool ModeGameover::Process() {
	base::Process();
	std::string bgmName = "BGM_GameOver";//�����ʃR�[�h��������
	SoundItemBase* sndItem = gGlobal.mSndServer.Get(bgmName);
	sndItem->SetVolume(100);
	// �ǂݍ��݊������Ă��邩�H
	if (sndItem && sndItem->IsLoad()) {
		// �Đ������H
		if (sndItem->IsPlay() == false) {
			// �Đ�����
			sndItem->Play();
		}
	}
	if (gGlobal.gPad->GetXTrg(XINPUT_BUTTON_DPAD_UP))   { _selection = 0; }
	if (gGlobal.gPad->GetXTrg(XINPUT_BUTTON_DPAD_DOWN)) { _selection = 1; }
	if (gGlobal.gPad->GetXTrg(XINPUT_BUTTON_A)) 
	{
		sndItem->Stop();
		switch (_selection)
		{
		case 0:
			// ���̃��[�h���폜�\��
			ModeServer::GetInstance()->Del(this);
			// ���̃��[�h��o�^
			ModeServer::GetInstance()->Add(new ModeGame(), 1, "game");
			break;
		case 1:
			// ���̃��[�h���폜�\��
			ModeServer::GetInstance()->Del(this);
			// ���̃��[�h��o�^
			ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");
			break;
		}
		
	}

	return true;
}

bool ModeGameover::Render() {
	base::Render();

	DrawGraph(0, 0, _cg[_selection], TRUE);
	return true;
}