#include "GameXPad.h"

GameXPad* GameXPad::padInstance = nullptr;
GameXPad::GameXPad()
{
	padInstance = this;
	//初期化
	for (int i = 0; i < MAX_PAD_BUTTON; i++)
	{
		_xTrg[i] = 0;
		_xRel[i] = 0;
	}
	_xTrgRt = 0;
	_xTrgLt = 0;
	_xRelRt = 0;
	_xRelLt = 0;
}

GameXPad::~GameXPad()
{
}

bool GameXPad::Input()
{
	//キー,トリガの変数
	uchar key_old[MAX_PAD_BUTTON];
	uchar trg_r_old = _xInput.RightTrigger;
	uchar trg_l_old = _xInput.LeftTrigger;
	for (int i = 0; i < MAX_PAD_BUTTON; i++)
	{
		//ローカル変数に代入
		key_old[i] = _xInput.Buttons[i];
	}
	//XInputから得られる情報の代入
	GetJoypadXInputState(DX_INPUT_PAD1, &_xInput);
	//トリガ、リリースキーの作成
	for (int i = 0; i < MAX_PAD_BUTTON; i++)
	{
		_xTrg[i] = (_xInput.Buttons[i] ^ key_old[i]) & _xInput.Buttons[i];
		_xRel[i] = (_xInput.Buttons[i] ^ key_old[i]) & ~_xInput.Buttons[i];
	}
	_xTrgRt = (_xInput.RightTrigger ^ trg_r_old) & _xInput.RightTrigger;
	_xTrgLt = (_xInput.LeftTrigger ^ trg_l_old) & _xInput.LeftTrigger;
	_xRelRt = (_xInput.RightTrigger ^ trg_r_old) & ~_xInput.RightTrigger;
	_xRelLt = (_xInput.LeftTrigger ^ trg_l_old) & ~_xInput.LeftTrigger;
	return true;
}

bool GameXPad::IsInputStickLeft()
{
	//左アナログスティックが動かされているならtrue
	if (_xInput.ThumbLX != 0 || _xInput.ThumbLY != 0) { return true; }
	return false;
}
bool GameXPad::IsInputStickRight()
{
	//右アナログスティックが動かされているならtrue
	if(_xInput.ThumbRX != 0 || _xInput.ThumbRY != 0) { return true; }
	return false;
}
