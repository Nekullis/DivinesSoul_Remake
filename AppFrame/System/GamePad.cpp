#include "GamePad.h"

GamePad::GamePad() {
 _key = 0;
 _trg = 0;
 _rel = 0;
 _st.analogMin = 0.3f;
}

GamePad::~GamePad() {

}

void GamePad::InputAcquisition() {
	int keyold = _key;
	_key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	_trg = (_key ^ keyold) & _key;
	_rel = (_key ^ keyold) & ~_key;

	GetJoypadDirectInputState(DX_INPUT_PAD1, &_di);
	//�@���ꂼ��̓��͂������l��1000�Ȃ̂ŁA�Ƃ����l��1/1000�ɂ��Ďg���₷�����Ă���
	_st = { (float)_di.X / 1000.f, (float)_di.Y / 1000.f,  (float)_di.Z / 1000.f,  (float)_di.Rz / 1000.f, _st.analogMin };

}