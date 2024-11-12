//----------------------------------------------------------------------
// @filename SkillSlot.h
// @author: Fukuma Kyohei, NaraMitsuki
// @explanation
// スキルスロット
// 使用できるスキルを変更させるためのクラス
//----------------------------------------------------------------------
#pragma once
#include "AppFrame.h"
#include "ResourceServer.h"
#include "JsonUtility.h"
#include "EnumInfo.h"
#include  <map>

//定数
constexpr float TO_NEXTDIV = 10000.0f;
constexpr auto MAX_VOICE = 8;

class SkillSlot{
public:
	//追加音声
	struct CALLVOICE
	{
		//カウント
		int callCnt;
		//カウント最大値
		int maxCallCnt;
		//発声中か
		bool isCall;
		//ボイスのキー
		std::string voiceCode;
	};
	SkillSlot();
	virtual ~SkillSlot();
	//ボイス登録
	void RegisterCall();
	//ボイス出力
	void SlotVoice(int i);
	//ボイス再生関連処理
	void CallProcess();
	//スロット回転処理
	void SlotSpin(int slotnum);
	//スロット関連処理まとめ
	void Process();
	//スロット描画
	void Render();
	//ゲッター
	std::array<kindDivine, 3>	GetSlot() const { return mSlot; }
	bool						GetIsSpin() const { return mIsSpin; }

protected:
	//スロット用スキル番号
	int mSlotdivine;
	//回転速度
	int mSpinspeed;
	//ガチャリール時間
	int mReeltime;
	//ボイス番号
	int mVoiceNum;
	//ガチャが回っているか
	bool mIsSpin;
	//音声構造体
	CALLVOICE mCall[MAX_VOICE];
	//スロット格納用配列
	std::array<kindDivine, 3> mSlot;

};