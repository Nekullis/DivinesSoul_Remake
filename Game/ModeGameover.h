//----------------------------------------------------------------------
// @filename ModeGameOver.h
// @author: Fukuma Kyohei
// @explanation
// �v���C���[���S��̉摜��`�悷�郂�[�h
//----------------------------------------------------------------------
#pragma once
#include"ModeTitle.h"
class ModeGameover : public ModeBase
{
	typedef ModeBase base;
public:
	bool Initialize();
	bool Terminate();
	bool Process();
	bool Render();

protected:
	int _cg[2];
	int _selection;

};

