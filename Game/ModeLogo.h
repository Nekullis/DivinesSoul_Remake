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

