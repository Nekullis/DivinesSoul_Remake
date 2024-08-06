#pragma once
#include"dxlib.h"
#include"MathCollision.h"
#include"string"
#include"ApplicationGlobal.h"
class Enemy
{
public:
	enum ENEMYTYPE
	{
		NOCHARA,
		OSERO,
		CRAB,
		ROMANOFF
	};
	enum STATUS
	{
		//未発見
		NODISCOVERY,
		//待機
		WAIT,
		//休憩
		REST,
		//攻撃
		ATTACK,
		//突撃
		ASSAULT,
		//ダメージ
		DAMAGE,
		//走行
		RUN,
		//警戒
		CAUTION,
		//死亡
		DIE,
	};
	struct ACTIONDATA
	{
		//ステータス
		STATUS status;
		//モーションのトータルフレーム
		float motionTotalFrame;
		//探索範囲
		float searchArea;
	};
public:
	Enemy(int model, int weapon, VECTOR vpos, VECTOR vdir);
	virtual ~Enemy();
	virtual bool Process(VECTOR pl_pos);
	virtual bool Render();
	virtual bool Debug();
	virtual bool Delete();
	virtual bool Damage(VECTOR pl_pos, int subpoint,int nextframe);
	virtual bool Suction(VECTOR pl_pos,  int nextframe);
	//ステータス変更
	virtual void ChangeStatus(STATUS en_status);
	//ゲッター
	VECTOR	GetPos()			{ return mPos; }
	VECTOR	GetDir()			{ return mDir; }
	float	GetRadius()			{ return mRadius; }
	float	GetSeg()			{ return mLineSeg; }
	bool	GetAttackFlag()		{ return mIsAttack; }
	VECTOR	GetWeaponPos(int i)	{ return mWeaponPos[i]; }
	float	GetWeaponSize()		{ return mWeaponSize; }
	bool	GetInvincible()		{ return mNoDamage; }
	int		GetHp()				{ return mHp; }
	int		GetATK()			{ return mAtk; }
	bool	GetDeleteFlag()		{ return mDeleteFlag; }
	ENEMYTYPE GetEnemyType()	{ return mType; }
	//セッター
	void  SetPos(VECTOR i)		{ mPos = VAdd(mPos, i); }
	void  SetDir(VECTOR i)		{ mDir = i; }
	void  SetAttackFlag(bool i)	{ mIsAttack = i; }
	void  SetStatus(STATUS status) { ChangeStatus(status); }
protected:
	ENEMYTYPE mType;
	//位置
	VECTOR mPos;
	//向き
	VECTOR mDir;
	//移動量
	VECTOR mMove;
	//カプセル用
	VECTOR mCapsule[2];
	//半径
	float mRadius;
	//線分の長さ
	float mLineSeg;
	//体力
	int mHp;
	//攻撃力
	int mAtk;
	//カウント
	int mActionCnt;
	//時間
	int mTimeCnt;
	//無敵時間
	int mInvincibleCnt;
	//次判定までのカウント
	int mNextFrame;
	//攻撃中か
	bool mIsAttack;
	//ダメージを受けた
	bool mDamage;
	//無敵中か
	bool mNoDamage;
	//体力が0かどうか
	bool mDie;
	//消去するフラグ
	bool mDeleteFlag;
	//モデル
	int mModel;
	std::string mName;
	//アタッチするアニメーションインデックス
	int mAttachIndex;
	//アニメーションのトータル時間
	float mTotalTime;
	//アニメーション時間
	float mPlayTime;
	//武器モデル
	int mWeaponModel;
	//武器位置
	VECTOR mWeaponPos[2];
	//武器サイズ
	float mWeaponSize;


};

