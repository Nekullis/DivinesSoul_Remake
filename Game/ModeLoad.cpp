#include "ModeLoad.h"
#include "ApplicationGlobal.h"
#include "ModeGame.h"

bool ModeLoad::Initialize()
{
	if (!base::Initialize()) { return false; }
	_changePage = 0;
	return true;
}

bool ModeLoad::Terminate()
{
	base::Terminate();
	return true;
}

bool ModeLoad::Process()
{
	base::Process();
	auto clamp0to2 = [](int& i)
	{
		if (i < 0) { i = 0; }
		else if (i > 2) { i = 2; }
	};
	int old_change = _changePage;
	if (gGlobal.gPad->GetXTrg(XINPUT_BUTTON_DPAD_RIGHT))
	{
		_changePage++;
	}
	if (gGlobal.gPad->GetXTrg(XINPUT_BUTTON_DPAD_LEFT))
	{
		_changePage--;
	}
	clamp0to2(_changePage);
	if (old_change != _changePage)
	{
		SoundItemBase* sndse_page = gGlobal.mSndServer.Get("SE_Page");
		sndse_page->Play();
	}
	if (gGlobal.gPad->GetXTrg(XINPUT_BUTTON_A))
	{
		SoundItemBase* sndse = gGlobal.mSndServer.Get("SE_UI_Decision");
		sndse->Play();
		// ‚±‚Ìƒ‚[ƒh‚ðíœ—\–ñ
		ModeServer::GetInstance()->Del(this);
		// ŽŸ‚Ìƒ‚[ƒh‚ð“o˜^
		ModeServer::GetInstance()->Add(new ModeGame(), 1, "game");
	}
	return true;
}

bool ModeLoad::Render()
{
	base::Render();
	int cg[3] =
	{
		gGlobal.mRS->mGetGraph()["load_page1"]._handle,
		gGlobal.mRS->mGetGraph()["load_page2"]._handle,
		gGlobal.mRS->mGetGraph()["load_page3"]._handle,
	};
	DrawGraph(0, 0, cg[_changePage], TRUE);
	return true;
}
