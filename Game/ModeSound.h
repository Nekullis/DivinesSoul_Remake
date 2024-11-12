//----------------------------------------------------------------------
// @filename ModeSound.h
// @author: Fukuma Kyohei
// @explanation
// ���֌W���Đ��A��~���郂�[�h
//----------------------------------------------------------------------
#include "appframe.h"
#include <string>
#include "SoundItem.h"
#include "ApplicationGlobal.h"

class ModeSound : public ModeBase
{
	typedef ModeBase base;

public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

};



