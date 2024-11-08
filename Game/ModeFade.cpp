#include "ModeFade.h"

ModeFade::ModeFade(bool fade)
{
	//�t�F�[�h�^�C�v�ݒ�
	_isFade = fade;
	//���Ԋl��
	_nowTime = GetNowCount();
	//�t�F�[�h�C���̏ꍇ
	if (_isFade)
	{
		_alphaStart = 255;
		_alphaEnd = 0;
	}
	//�t�F�[�h�A�E�g�̏ꍇ
	else
	{
		_alphaStart = 0;
		_alphaEnd = 255;
	}
	_alphaFade = _alphaStart;
}

bool ModeFade::Initialize()
{
	if (!base::Initialize()) { return false; }
	return true;
}

bool ModeFade::Terminate()
{
	base::Terminate();
	return true;
}

bool ModeFade::Process()
{
	float facter = 6.0f;
	float time = 60.0f / 60.0f * 1000.0f * facter;
	//�t�F�[�h���[�h�ȊO�̏������~
	ModeServer::GetInstance()->SkipProcessUnderLayer();
	base::Process();
	_alphaFade = Math::EasingLinear((GetNowCount() - _nowTime), _alphaStart, _alphaEnd, time);
	if (GetNowCount() - _nowTime >= time)
	{
		// ���̃��[�h���폜�\��
		ModeServer::GetInstance()->Del(this);
	}
	return true;
}

bool ModeFade::Render()
{
	base::Render();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alphaFade);
	DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, _alphaFade);
	return true;
}


