//----------------------------------------------------------------------
// @filename ModeGameClear.h
// @author: Fukuma Kyohei
// @explanation
// �N���A��̉摜��`�悷�郂�[�h
//----------------------------------------------------------------------
#pragma once
class ModeClear : public ModeBase
{
	typedef ModeBase base;
public:
	bool Initialize();
	bool Terminate();
	bool Process();
	bool Render();

protected:
	int _cg;
};

