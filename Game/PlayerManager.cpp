#include "PlayerManager.h"

PlayerManager::PlayerManager() {

}

PlayerManager::~PlayerManager() 
{
	P_Delete();
}

void PlayerManager::Initialize() 
{
	// プレイヤーマネージャー自体の初期化関数（グローバルでできているので一応作りました）
}

void PlayerManager::Process() 
{
 // ガチャなどで変動したステータスを変更などプレイヤーのゲーム画面以外での処理を記述（必要に応じて増やす）
}

// 以下のP～～はプレイヤー内の関数を一つ上の階層でつかえるようにしている
void PlayerManager::P_Materialize() 
{
	mPl = new Player();
}

void PlayerManager::P_Delete() 
{
	delete mPl;
}

void PlayerManager::P_Initialize(int handle, int weapon) 
{
	mPl->Initialize(handle, weapon);
}

void PlayerManager::P_Process(VECTOR campos, VECTOR camtarget, SkillSlot* slot) 
{
	// 必要とあらば何かしら追加する(プレイヤークラスの関数をまとめるなど)
	mPl->Process(campos, camtarget,slot);
}

void PlayerManager::P_AnimProcess() 
{
	mPl->A_Process();
}

void PlayerManager::P_CalcuProcess() 
{
	mPl->C_Process();
}

void PlayerManager::P_Damage(VECTOR pos, int subpoint)
{
	mPl->Damage(pos,subpoint);
}

void PlayerManager::Render() {
	// プレイヤーの描画以外にもプレイヤーに関するデバッグ情報が欲しかったら描画する
	mPl->Render();
}

void PlayerManager::DebugRender() {
	mPl->PlDebug();
}