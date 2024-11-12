//----------------------------------------------------------------------
// @filename EnemyManager.h
// @author: Fukuma Kyohei
// @explanation
// 敵の管理クラス
// 敵の追加、削除などの管理クラス
//----------------------------------------------------------------------
#pragma once
#include"dxlib.h"
#include"Enemy.h"
#include"EN_Crab.h"
#include"EN_Osero.h"
#include"EN_Romanoff.h"
#include<list>
// 敵の情報、ポップにかかわるクラス(このクラスでインスタンスを増やしまくるのか、はたまたエネミーのクラス内で増やすかは要選考)
class EnemyManager
{
public:
	EnemyManager();
	virtual ~EnemyManager();
	void Process(VECTOR pl_pos);
	void Render();
	void Spawn(Enemy* enemy);
	void Destroy(Enemy* enemy);
	//ゲッター
	std::list<Enemy*> GetEnemyList()	{ return mEemyList; }
	int GetCombo()				  const { return mCombo; }
	//セッター
	void SetCombo(int i)				{ mCombo = i; }
private:
	//敵のリスト
	std::list<Enemy*> mEemyList;
	//コンボ
	float mCombo;
};

