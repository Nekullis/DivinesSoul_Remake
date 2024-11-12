//----------------------------------------------------------------------
// @filename AttackTableManager.h
// @author: Fukuma Kyohei
// @explanation
// 攻撃情報の管理クラス
// 攻撃に扱うアイテムの処理に関するクラス
//----------------------------------------------------------------------
#pragma once
#include"MotionTableManager.h"
#include "AttackTable.h"

//攻撃情報の情報をまとめるクラス
class AttackTableManager
{
public:
	AttackTableManager();
	~AttackTableManager();
	static AttackTableManager* mAtkManagerInstance;
	void Process();
	//外部ファイルで攻撃情報取得
	void LoadAttackData(const std::string& filename, ATTACK_TYPE type, std::string voicename, std::string sename);
	//指定した攻撃タイプをコンテナに追加
	void AddTable(ATTACK_TYPE type, AttackTable* table);
	//攻撃情報変更
	void AttackChange(ATTACK_TYPE type);
	//ゲッター
	static AttackTableManager*	GetInstance()		  { return mAtkManagerInstance; }
	std::map<int, AttackTable*> GetAttackList()		  { return mAttackList; }
	AttackTable*				GetTable()			  { return mTable; }
	ATTACK_TYPE					GetType()		const { return mType; }
	bool						GetIsTrg()		const { return mIsTrg; }
	bool						GetIsChange()	const { return mIsChange; }
	int							GetAttackCount()const { return mAttackCnt; }
	int							GetMaxCount()	const { return mCountMax; }
protected:
	//コンテナ
	std::map<int, AttackTable*> mAttackList;
	//テーブル
	AttackTable* mTable;
	//タイプ
	ATTACK_TYPE mType;
	//トリガ入力中か
	bool mIsTrg;
	//変更できるか
	bool mIsChange;
	//モーションカウント
	int mAttackCnt;
	//最大カウント
	int mCountMax;

};

