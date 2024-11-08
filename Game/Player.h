#pragma once
#include "appframe.h"
#include "Divine.h"
#include <string>
#include "MotionTableManager.h"
#include "AttackTableManager.h"

//プレイヤー処理全般のクラス
class Player
{
public:
	Player();
	virtual ~Player();
	void Initialize(int handle,int weapon);
	//インスタンス
	static Player* mPlInstance;
	void ActionProcess(VECTOR campos, VECTOR camtarget, SkillSlot* slot);
	//Animation:アニメーション進行処理
	void A_Process();
	//Calcalate:計算系処理
	void C_Process();
	void Process(VECTOR campos, VECTOR camtarget, SkillSlot* slot);
	//描画
	void Render();
	//スキルモーション
	CHARACTER_MOTION SkillMotion();
	//jsonを用いた位置設定
	void SetJsonTransform();
	//武器装備
	void SetWeapon();
	//スキル発動時ボイス
	void SkillVoice();
	//プレイヤースキル処理
	void PlayerSkill(SkillSlot* slot,  VECTOR campos, VECTOR camtarget);
	//プレイヤー死亡処理
	void PlayerDie();
	//被ダメージ後処理
	void Invincible();
	//ダメージ
	void Damage(VECTOR pos,int subpoint);
	//ゲッター
	static Player* GetInstance()			 { return mPlInstance; }
	VECTOR GetMove()				const	 { return mMove; }
	VECTOR GetPos()					const	 { return mPos; }
	VECTOR GetDir()					const	 { return mDir; }
	float  GetRadius()				const	 { return mRCap; }
	float  GetSeg()					const	 { return mLineSeg; }
	int	   GetLastCommand()			const	 { return mLastCommand; }
	bool   GetAvoidFlag()			const	 { return mAvoidFlag; }
	int    GetHp()					const	 { return mHp; }
	int    GetAtk()					const	 { return mAtk; }
	bool   GetGameOver()			const	 { return mGameOverFlag; }
	bool   GetInvincible()			const	 { return mNoDamage; }
	int    GetAttachIndex()			const	 { return mAttachIndex; }
	VECTOR GetWeaponPos(int i)		const	 { return mWPos[i]; }
	Divine* GetDivine()						 { return mSkill; }
	MotionTableManager* GetMotionManager()	 { return mMotionManager; }
	AttackTableManager* GetAttackManager()	 { return mAttackManager; }
	//セッター
	void SetPos(VECTOR any)		{ mPos = any; }
	void SetMove(VECTOR vec)	{ mMove = vec; }
	void SetGravity(float gra)	{ mGravity = gra; }
	void SetAttackFlag(bool a)	{ mIsAttack = a; }
	void SetInvincible(bool i)  { mNoDamage = i; }
	void SetStatusSkill(bool i) { mIsSkill = i; }

private:
	//位置
	VECTOR mPos;
	//角度、向き
	VECTOR mDir;
	//移動量
	VECTOR mMove;
	//カプセルの長さ
	float mLineSeg;
	//当たり判定用
	VECTOR mCapsule[2];
	float mRCap;
	//武器判定位置
	VECTOR mWeaponVPos;
	//重力値
	float mGravity;
	//体力
	int mHp;
	//攻撃力
	int mAtk;
	//無敵カウント
	int mInvincibleCnt;
	//攻撃中かどうか
	bool mIsAttack;
	bool mNoDamage;
	bool mIsSkill;
	bool mIsDie;
	bool mGameOverFlag;
	//回避フラグ
	bool mAvoidFlag;
	//最後に押したボタン
	int mLastCommand;
	//3Dモデル描画用
	//描画モデル
	int mModel;
	int mDashModel;
	//アタッチするアニメーションインデックス
	int mAttachIndex;
	//以前のアタッチされたアニメーションインデックス
	float mOldIndex;
	//新旧インデックスの入れ替わりレート
	int mRate;
	//武器モデル
	int mWModel;
	//武器位置
	VECTOR mWPos[2];
	//ディバインスキルクラス
	Divine* mSkill;
	//モーションマネージャー
	MotionTableManager* mMotionManager;
	//攻撃マネージャー
	AttackTableManager* mAttackManager;
	//旧モーション
	CHARACTER_MOTION mOldMotion;
	//新モーション
	CHARACTER_MOTION mMotion;

};

