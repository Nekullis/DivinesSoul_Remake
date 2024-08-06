#pragma once
#include <vector>
#include <string>
#include "DxLib.h"
#include "Effect.h"


//スキル名
enum class DIVINENAME : int
{
	//ブレス
	BREATH,
	//サークル
	CIRCLE,
	//レーザー
	LASER,
	//スラッシュ
	SLASH,
	//エクスプロージョン
	EXPLOSION,
	//ダッシュ
	DASH,
	//バキューム
	VACUUM,
	//ソニックウェーブ
	SONIC,
};

class DivineItem
{
public:
	DivineItem(DIVINENAME, VECTOR, int, float, float, float, float, float, Effect*, float, std::string, std::string);
	~DivineItem();
	//ゲッター
	DIVINENAME GetName()			const { return mName; }
	VECTOR GetPos()					const { return mPos; }
	int GetAtk()					const { return mAtkPoint; }
	float GetSize()					const { return mSize; }
	float GetInvocationFrame()		const { return mInvocationFrame; }
	float GetReInvocationFrame()	const { return mReInvocationFrame; }
	float GetStartColFrame()		const { return mStartColFrame; }
	float GetEndColFrame()			const { return mEndColFrame; }
	Effect* GetEffect()					  { return mEffect; }
	float GetEffectDir()			const { return mEffectDir; }
	std::string GetSECode()				  { return mSECode; }
	std::string GetVoiceCode()			  { return mVoiceCode; }
protected:
	//スキル名
	DIVINENAME mName;
	//発動位置
	VECTOR mPos;
	//攻撃力
	int mAtkPoint;
	//当たり判定用サイズ
	float mSize;
	//総合発動時間
	float mInvocationFrame;
	//再発動までのフレーム
	float mReInvocationFrame;
	//判定開始時間
	float mStartColFrame;
	//判定終了時間
	float mEndColFrame;
	//使うエフェクト
	Effect* mEffect;
	//エフェクト向き
	float mEffectDir;
	//SE識別キー
	std::string mSECode;
	//ボイス識別キー
	std::string mVoiceCode;
};

class DivineTable
{
public:
	DivineTable();
	~DivineTable();
	void Process();
	void Render();
	void AddItem(DivineItem item);
	//ゲッター
	std::vector<DivineItem> GetItem()	{ return mItem; }
	bool GetPlaying()					{ return mIsPlaying; }
	bool GetInvocationFlag()			{ return mInvocationFlag; }
	//セッター
	void SetPlaying(bool flag)			{ mIsPlaying; }
	void SetInvocationFlag(bool flag)	{ mInvocationFlag = flag; }
	void SetReInvocationCnt(int cnt)	{ mReInvocationCnt = cnt; }
	void SetIsCollisionCnt(int cnt)		{ mColCnt = cnt; }
protected:
	std::vector<DivineItem> mItem;
	//再発動までのカウント
	int mReInvocationCnt;
	//判定用カウント
	int mColCnt;
	//発動中か
	bool mIsPlaying;
	//発動フラグ
	bool mInvocationFlag;
	
};

