#pragma once
#include "dxlib.h"
#include "EffekseerForDXLib.h"
#include <string>
#include <map>
class Effect
{
public:
	Effect(std::string handle, float size);
	virtual ~Effect();
	static Effect* efInstance;
	bool Play();
	bool Stop();
	bool Process();
	bool Draw();
	bool Debug();
	//何回も呼び出す必要のない関数なのでこの関数はマネージャーあるいはゲームメインに置くこと
	bool Update();
	//ゲッター
	bool GetUseFlag()				{ return mUseFlag; }
	bool GetPlayFlag()				{ return mPlayFlag; }
	static Effect* GetInstance()	{ return efInstance; }
	//セッター
	void SetPos(VECTOR v)	{ mPos=v; }
	void SetSize(float s)	{ mSize = s; }
	void SetDir(VECTOR v)	{ mDir = v; }
	void SetUseFlag(bool f) { mUseFlag = f; }
protected:
	//エフェクトをロードする
	int mEffectResourceHandle;
	//再生用ハンドル
	int mPlayEffectHandle;
	//位置
	VECTOR mPos;
	//サイズ
	float mSize;
	//向き
	VECTOR mDir;
	//再生可能フラグ
	bool mUseFlag;
	//再生中のフラグ
	bool mPlayFlag;
};

