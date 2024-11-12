//----------------------------------------------------------------------
// @filename ApplicationGlobal.h
// @author: Fukuma Kyohei, Nara Mitsuki 
// @explanation
// �A�v���P�[�V�������ʂ̃N���X
// ���[�h�𒴂��ĕێ����������Ȃǂ��L�^���邽�߂̃N���X
//----------------------------------------------------------------------
#pragma once
#include "appframe.h"
#include "PlayerManager.h"
#include "ResourceServer.h"
#include "SoundServer.h"

class ApplicationGlobal
{public:
	ApplicationGlobal();
	virtual ~ApplicationGlobal();

	bool Init();

	void PadInput();
	
	// Global�̂ݗ�O�ł悭�g���̂ŒZ�߂ɂ��܂�
	ResourceServer* mRS;
	GameXPad* gPad;
	PlayerManager* mPM;	
	SoundServer mSndServer;
	std::unordered_map<std::string, GRAPH_INFO>		mGetGraph()		{ return mRS->mGetGraph(); }
	std::unordered_map<std::string, DIVGRAPH_INFO>	mGetDivGraph()	{ return mRS->mGetDivGraph(); }
	std::unordered_map<std::string, MODEL_INFO>		mGetModel()		{ return mRS->mGetModel(); }
	std::unordered_map<std::string, EFFECT_INFO>	mGetEffect()	{ return mRS->mGetEffect(); }
	std::unordered_map<std::string, ATTACH_INFO>	mGetAttach()	{ return mRS->mGetAttach(); }


	enum class stage  
	{
		none , stage1, stage2, stage3
	};
	stage mStageNum;
	bool mIsLoad;
};

extern ApplicationGlobal gGlobal;