//----------------------------------------------------------------------
// @filename MotionTableManager.h
// @author: Fukuma Kyohei
// @explanation
// モーション管理クラス
// モーションの追加、変更を管理するクラス
//----------------------------------------------------------------------
#pragma once
#include "MotionTable.h"
#include <map>
#include <string>
#include <utility>
class MotionTableManager
{
public:
	MotionTableManager();
	virtual ~MotionTableManager();
	static MotionTableManager* mMotTableInstance;
	void Process();
	//外部ファイルからデータ取得
	void LoadTable(const std::string& filename, CHARACTER_MOTION motion, MotionTable::MOTION_ENDTYPE endtype, MOTION_LAYER layer);
	//モーションテーブル追加
	void AddTable(CHARACTER_MOTION motionID,MotionTable* table);
	//モーション変更
	void ChangeMotion(CHARACTER_MOTION motion);
	//ゲッター
	static MotionTableManager*	GetInstance()			{ return mMotTableInstance; }
	int							GetMotionCnt() const	{ return mMotionCnt; }
	int							GetMaxCnt()	   const	{ return mCountMax; }
	MotionTable*				GetTable()				{ return mTable; }
	CHARACTER_MOTION			GetMotion()				{ return mMotion; }
	std::map<int, std::pair<MotionTable::MOTION_ENDTYPE, MotionTable*>> GetMotionList() { return mMotionList; }
protected:
	//テーブルコンテナ
	std::map<int, std::pair<MotionTable::MOTION_ENDTYPE, MotionTable*>> mMotionList;
	MotionTable* mTable;
	CHARACTER_MOTION mMotion;
	MOTION_LAYER mLayer;
	//モーションカウント
	int mMotionCnt;
	//最大カウント
	int mCountMax;
};

