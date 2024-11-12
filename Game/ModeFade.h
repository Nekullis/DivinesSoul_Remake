//----------------------------------------------------------------------
// @filename ModeFade.h
// @author: Fukuma Kyohei
// @explanation
// �N���A��̉f����`�悷��N���X
//----------------------------------------------------------------------
#pragma once
#include "appframe.h"
class ModeFade :public ModeBase
{
	using base = ModeBase;
public:
	//true:fadein,false:fadeout
	ModeFade(bool fade);
	bool Initialize()override;
	bool Terminate()override;
	bool Process()override;
	bool Render()override;
protected:
	//�J�n���l
	int _alphaStart;
	//�I�����l
	int _alphaEnd;
	//����(�~���b�P��)
	int _nowTime;
	//�t�F�[�h���l
	int _alphaFade;
	//�t�F�[�h�C�����t�F�[�h�A�E�g��
	bool _isFade;
};

