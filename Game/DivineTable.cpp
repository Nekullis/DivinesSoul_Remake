#include "DivineTable.h"
#include "ApplicationGlobal.h"
DivineTable::DivineTable()
{
	mItem.clear();
	mReInvocationCnt = 0;
	mColCnt = 0;
	mIsPlaying = false;
	mInvocationFlag = true;
}

DivineTable::~DivineTable()
{
}

void DivineTable::AddItem(DivineItem item)
{
	mItem.push_back(item);
}

void DivineTable::Process()
{
	int tablenum = 0;
	//スキル発動可能でないのならカウントを増やす
	if (!mInvocationFlag)
	{
		mReInvocationCnt++;
	}
	//カウントが特定のフレームに達した
	if (mColCnt > mItem[tablenum].GetStartColFrame())
	{
		mItem[tablenum].GetEffect()->SetUseFlag(false);
	}
	//カウントが発動可能フレームまで達したなら
	if (mReInvocationCnt > mItem[tablenum].GetReInvocationFrame())
	{
		//エフェクト再生可能フラグをtrueに
		mItem[tablenum].GetEffect()->SetUseFlag(true);
		//スキル発動フラグをtrueに
		mInvocationFlag = true;
		//カウントリセット
		mReInvocationCnt = 0;
	}
	//ディバイン発動中なら
	if (mIsPlaying) 
	{ 
		//カウント加算
		mColCnt++; 
	}
	if (mItem[tablenum].GetEffect()->GetPlayFlag())
	{
		//向きの単位をラジアンに変更
		float effectdir = Math::DegToRad(mItem[tablenum].GetEffectDir());
		//プレイヤーの位置、向き取得
		VECTOR plpos = Player::GetInstance()->GetPos();
		float pldir = Player::GetInstance()->GetDir().y;
		MATRIX matrix = MGetRotY(pldir);
		//向きを変更する
		mItem[tablenum].GetEffect()->SetDir(VGet(0, pldir + effectdir, 0));
		//位置を変更
		mItem[tablenum].GetEffect()->SetPos(VAdd(plpos, VTransform(mItem[tablenum].GetPos(), matrix)));
		//プロセスを回す
		mItem[tablenum].GetEffect()->Process();
	}
	//エフェクトの再生
	if (mColCnt == mItem[tablenum].GetStartColFrame())
	{
		mItem[tablenum].GetEffect()->Play();
		//何回も再生されないように条件を付ける
		if (mColCnt < mItem[tablenum].GetStartColFrame())
		{
			SoundItemBase* snditem_se = gGlobal.mSndServer.Get(mItem[tablenum].GetSECode());
			if (snditem_se && snditem_se->IsLoad())
			{	// 再生中か？
				if (snditem_se->IsPlay() == false)
				{	// 再生する
					snditem_se->Play();
				}
			}
		}
	}
}

void DivineTable::Render()
{
	int tablenum = 0;
	if (mItem[tablenum].GetEffect()->GetPlayFlag())
	{
		mItem[tablenum].GetEffect()->Draw();
	}
}


