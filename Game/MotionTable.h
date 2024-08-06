#pragma once
#include "DxLib.h"
#include "vector"

enum class  CHARACTER_MOTION
{
	//待機
	PLAYER_STAND,
	//走り
	PLAYER_RUN,
	//一撃目
	PLAYER_FIRSTATTACK,
	//二撃目
	PLAYER_SECONDATTACK,
	//三撃目
	PLAYER_LASTATTACK,
	//ダッシュ攻撃
	PLAYER_DASHATTACK,
	//ディバインスキル
	PLAYER_SKILL,
	//ディバインスキル(ダッシュ)
	PLAYER_SKILLDASH,
	//回避
	PLAYER_AVOID,
	//ダメージ
	PLAYER_DAMAGE,
	//体力0
	PLAYER_DIE
};

//どういう状態でモーションが動くか
enum class MOTION_LAYER
{
	//常に動いている
	ALWAYS,
	//押下状態で動く
	PRESS_DOWN,
	//トリガ入力で動く
	TRIGGER,
	//被ダメージで動く
	DAMAGE
};

enum class ATTACK_TYPE
{
	//攻撃していない
	NONE,
	//一撃目
	NORMAL_ATTACK,
	//二撃目
	SCOND_ATTACK,
	//三撃目
	THIRD_ATTACK,
	//ダッシュ攻撃
	DASH_ATTACK
};

class MotionTableItem
{
public:
	MotionTableItem(int, float, float, float, ATTACK_TYPE, bool, bool, bool);
	~MotionTableItem();
	//ゲッター
	int			GetMotionID()		{ return mMotionID; }
	VECTOR		GetVelocity()		{ return mVelocity; }
	ATTACK_TYPE	GetTrgAttack()		{ return mTrgAttack; }
	bool		GetIsSkill()		{ return mIsSkill; }
	bool		GetIsChangeCourse() { return mIsChangeCourse; }
	bool		GetIsAvoid()		{ return mIsAvoid; }
protected:
	//ID
	int mMotionID;
	//移動速度
	VECTOR mVelocity;
	//攻撃できるか
	ATTACK_TYPE mTrgAttack;
	//スキルを発動できるか
	bool mIsSkill;
	//方向転換できるか
	bool mIsChangeCourse;
	//回避できるか
	bool mIsAvoid;
};

class MotionTable
{
public:
	enum class MOTION_ENDTYPE
	{
		LOOP,
		END,
		DIE
	};
	MotionTable();
	~MotionTable();
	void Update();
	void AddItem(MotionTableItem item);
	//ゲッター
	std::vector<MotionTableItem> GetItem()  const{ return mItem; }
	MOTION_ENDTYPE GetEndType()				const{ return mEndType; }
	MOTION_LAYER GetLayer()					const{ return mLayer; }
	//セッター
	void SetEndType(MOTION_ENDTYPE endtype)		 { mEndType = endtype; }
	void SetLayer(MOTION_LAYER layer)			 { mLayer = layer; }
protected:
	//コンテナ
	std::vector<MotionTableItem> mItem;
	MOTION_ENDTYPE mEndType;
	MOTION_LAYER mLayer;
};