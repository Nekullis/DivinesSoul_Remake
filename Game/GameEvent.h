#pragma once
#include "EnemyManager.h"
#include "JsonUtility.h"
#include "EN_Romanoff.h"
//定数
constexpr auto MAX_EVENT_NUM = 18;
constexpr auto MAX_SPAWN_WAVE = 6;
class GameEvent
{
public:
	struct EVENT
	{	
		//画像ハンドル
		int handleUI;
		//イベントカウント
		int eventCnt;
		//イベントカウント最大値
		int maxEventCnt;
		//イベント発生中
		bool isOccur;
		//ボイスキー
		std::string voiceCode;
	};
	GameEvent();
	virtual ~GameEvent();
	//インスタンス
	static GameEvent* _evInstance;
	void Process();
	void Render();
	bool GameOver();
	bool GameClear(EN_Romanoff* en);
	//イベント登録
	void RegisterEvent();
	//イベント発生
	void OccurEvent(int i);
	//wavw更新
	void EnemyWaveInit(int i);
	//イベント発生に関する処理
	void OccurProcess();
	//waveに関する処理
	void WaveProcess();
	//waveに関するイベント番号
	bool WaveNum(int i);
	//ストーリーに関するイベント番号
	bool StoryNum(int i);
	//ディバインに関するイベント番号
	bool DivineNum(int i);
	//イベントに関する処理
	void EventProcess();
	//ボスステージの敵召喚
	void CastEnemy(int i);
	//召喚に関する処理
	void CastProcess();
	//UIの表示(UIクラスに使う)
	void DrawQuest();
	void DrawWave();
	void DrawEventUI();
	//ゲッター
	static GameEvent*	GetInstance()			{ return _evInstance; }
	EnemyManager*		GetEnemyManager()		{ return mEnManager; }
	int					GetEvent()				{ return mStoryEv; }
	int					GetDivineEvent()		{ return mDivineEv; }
	//セッター
	void				SetEvent(int i)			{ mStoryEv += i; }
	void				SetDivineEvent(int i)	{ mDivineEv += i; }
protected:
	//クエスト画像ハンドル
	int mHandleQuestFeld[11];
	int mHamdleQuestRomanoff[7];
	//番号
	int mInitNum;
	int mQuestNum;
	//モデルハンドル
	int mHandle[3];
	//武器モデルハンドル
	int mWeaponModel[2];
	//ボスの体力比較用変数
	int mHpCast;
	//イベントカウント
	int mStoryEv;
	int mWaveEv;
	int mHpEv;
	int mDivineEv;
	//敵マネージャー
	EnemyManager* mEnManager;
	EVENT mEvent[MAX_EVENT_NUM];

};

