#pragma once
#include "dxlib.h"
//定数
constexpr auto MAX_PAD_BUTTON = 16;
using uchar = unsigned char;
//XPadボタンの中身
// 0  XINPUT_BUTTON_DPAD_UP
// 1  XINPUT_BUTTON_DPAD_DOWN
// 2  XINPUT_BUTTON_DPAD_LEFT
// 3  XINPUT_BUTTON_DPAD_RIGHT
// 4  XINPUT_BUTTON_START
// 5  XINPUT_BUTTON_BACK
// 6  XINPUT_BUTTON_LEFT_THUMB
// 7  XINPUT_BUTTON_RIGHT_THUMB
// 8  XINPUT_BUTTON_LEFT_SHOULDER
// 9  XINPUT_BUTTON_RIGHT_SHOULDER
// 10 XINPUT_BUTTON
// 11 XINPUT_BUTTON
//   (10,11はDXライブラリには記載されていない)
// 12 XINPUT_BUTTON_A
// 13 XINPUT_BUTTON_B
// 14 XINPUT_BUTTON_X
// 15 XINPUT_BUTTON_Y

//Xインプットタイプのゲームパッドクラス
class GameXPad
{
public:
	GameXPad();
	~GameXPad();
	static GameXPad* padInstance;
	bool Input();
	//入力されているか
	bool IsInputStickLeft();
	bool IsInputStickRight();
	//ゲッター
	static GameXPad* GetInstance() { return padInstance; }
	//ボタン
	bool GetXKey(int index) { return _xInput.Buttons[index]; }
	bool GetXTrg(int index) { return _xTrg[index]; }
	bool GetXRel(int index) { return _xRel[index]; }
	//アナログパッド
	short GetXRx() { return _xInput.ThumbRX; }
	short GetXRy() { return _xInput.ThumbRY; }
	short GetXLx() { return _xInput.ThumbLX; }
	short GetXLy() { return _xInput.ThumbLY; }
	//トリガ
	uchar GetXRt() { return _xInput.RightTrigger; }
	uchar GetXLt() { return _xInput.LeftTrigger; }
	uchar GetXTrgRt() { return _xTrgRt; }
	uchar GetXTrgLt() { return _xTrgLt; }
	uchar GetXRelRt() { return _xRelRt; }
	uchar GetXRelLt() { return _xRelLt; }

protected:
	//Xインプット
	XINPUT_STATE _xInput;
	//ボタン(トリガ)
	int _xTrg[MAX_PAD_BUTTON];
	//ボタン(リリース)
	int _xRel[MAX_PAD_BUTTON];
	//右トリガ
	int _xTrgRt;
	//左トリガ
	int _xTrgLt;
	//右リリース
	int _xRelRt;
	//左リリース
	int _xRelLt;

};

