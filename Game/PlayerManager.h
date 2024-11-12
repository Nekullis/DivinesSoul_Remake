//----------------------------------------------------------------------
// @filename PlayerManager.h
// @author: Fukuma Kyohei, Nara Mitsuki
// @explanation
// プレイヤー管理クラス
// プレイヤー処理を安全に上の階層で扱えるようにするクラス
//----------------------------------------------------------------------
#pragma once
#include "Player.h"
class PlayerManager
{
public:
	PlayerManager();
	virtual ~PlayerManager();
	void Initialize();
	void Process();
	// プレイヤー描画含む、もしデバッグ情報を描画するのであればまとめる
	void Render(); 
	// プレイヤークラスから持ってきた処理を階層を上げてマネージャーから直に使えるようにしている
	// ゲーム本編に入ってきたとき、プレイヤーを出現させる・それまでに受け取った数値で初期化
	void P_Materialize(); 
	void P_Delete();
	void P_Initialize(int handle, int weapon);
	void P_Process(VECTOR campos, VECTOR camtarget,SkillSlot* slot);
	void P_AnimProcess();
	void P_CalcuProcess();
	void P_Damage(VECTOR pos, int subpoint);
	//ゲッター
	Player* P_Get() { return mPl; }
	VECTOR	P_GetMove()			{ return mPl->GetMove(); }
	VECTOR	P_GetPos()			{ return mPl->GetPos(); }
	VECTOR	P_GetDir()			{ return mPl->GetDir(); }
	Divine* P_GetSkill()		{ return mPl->GetDivine(); }
	int		P_GetHp()			{ return mPl->GetHp(); }
	bool	P_GetDie()			{ return mPl->GetGameOver(); }
	int		P_GetCommand()		{ return mPl->GetLastCommand(); }
	void	P_SetPos(VECTOR any){ mPl->SetPos(any); }
private:
	Player* mPl;
};

