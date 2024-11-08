#include "Effect.h"
Effect* Effect::efInstance = nullptr;
Effect::Effect(std::string handle, float size)
{
	efInstance = this;
	mPos = VGet(0, 0, 0);
	mSize = size;
	mDir = VGet(0,0,0);
	mEffectResourceHandle = LoadEffekseerEffect(handle.c_str(), mSize);
	mUseFlag = true;
	mPlayFlag = false;
	//Effekseerにより再生中のエフェクトを更新する。
	SetPosPlayingEffekseer3DEffect(mPlayEffectHandle, mPos.x, mPos.y, mPos.z);
}

Effect::~Effect()
{
	// エフェクトリソースを削除する。
	DeleteEffekseerEffect(mEffectResourceHandle);
}
bool Effect::Play()
{
	if (mUseFlag)
	{
		//エフェクトを再生する
		mPlayEffectHandle = PlayEffekseer3DEffect(mEffectResourceHandle);
	}
	if (mPlayEffectHandle != -1)
	{
		//再生中ならtrueに
		mPlayFlag = true;
	}
	return true;
	
}
bool Effect::Stop()
{
	StopEffekseer3DEffect(mPlayEffectHandle);
	return true;
}
bool Effect::Process()
{
	//Effekseerにより再生中のエフェクトを更新する。
	SetPosPlayingEffekseer3DEffect(mPlayEffectHandle, mPos.x, mPos.y, mPos.z);
	//角度を変更する
	SetRotationPlayingEffekseer3DEffect(mPlayEffectHandle, mDir.x, mDir.y, mDir.z);
	////再生が終わったらフラグをfalseに
	return true;
}

bool Effect::Update()
{
	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();
	//マネージャーを通し複数使う場合はUpdateEffekseer3Dはマネージャークラスに置く
	UpdateEffekseer3D();
	return true;
}

bool Effect::Draw()
{
	// Effekseerにより再生中のエフェクトを描画する。
	DrawEffekseer3D();
	return true;
}