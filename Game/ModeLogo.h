//----------------------------------------------------------------------
// @filename ModeLogo.h
// @author: Fukuma Kyohei
// @explanation
// ���S�摜��`�悷�郂�[�h
//----------------------------------------------------------------------
#pragma once
#include "appFrame.h"
class ModeLogo : public ModeBase
{
	using base = ModeBase;
public:
	bool Initialize()override;
	bool Terminate()override;
	bool Process()override;
	bool Render()override;
protected:
	//���S�n���h��
	int _cgLogo;
	//�J�E���g
	int _modeCnt;

};

