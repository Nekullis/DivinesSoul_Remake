//----------------------------------------------------------------------
// @filename MapEntity.h
// @author: Fukuma Kyohei, Nara Mitsuki
// @explanation
// マップクラス
// 背景、ステージに使用するオブジェクトの処理クラス
//----------------------------------------------------------------------
#pragma once
#include "appframe.h"
#include "ApplicationGlobal.h"
#include "JsonUtility.h"
#include <vector>

class MapEntity
{
	typedef ApplicationGlobal::stage stage;
public:
	MapEntity();
	virtual ~MapEntity();
	void Initialize(stage global);
	void Process();
	void Render();
	//アニメーションしているか
	bool IsPlayAnimation(std::string s);
	//アニメーションのついたモデル用構造体
	struct ANIMATIONMODEL
	{
		int model;
		float factor;
		float playTime;
		int attachIndex;
		int totalTime;
	};
protected:
	VECTOR mPos;
	VECTOR mDir;
	VECTOR mMove;
	// 3Dモデルハンドル
	// <名前, モデルハンドル>
	std::map<std::string, int> mMapModelHandle;		
	// 3Dブロック情報
	struct BLOCKPOS {
		std::string		name;
		// 座標
		double		x, y, z;
		// 回転
		double		rx, ry, rz;
		// 拡大
		double		sx, sy, sz;
		// モデルハンドル
		int			modelHandle;
		// 描画フレーム
		int			drawFrame;
	};
	std::vector<BLOCKPOS>	mBlockPos;
	//アニメーション用
	std::vector<ANIMATIONMODEL> mAnim;
};

