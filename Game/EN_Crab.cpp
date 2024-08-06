#include "EN_Crab.h"
EN_Crab::EN_Crab(int model, int weapon, VECTOR vpos, VECTOR vdir) : base(model, weapon, vpos, vdir)
{
	//初期値を設定
	MV1SetPosition(mModel, mPos);
	//移動量
	mMove = VGet(0, 0, 0);
	//体力
	mHp = 60;
	//攻撃力
	mAtk = 5;
	//判定カプセル内の要素を初期化
	//カプセルの半径
	mRadius = 43;
	//線分の長さ
	mLineSeg = 170;
	//カプセルの位置
	mCapsule[0] = mPos;
	mCapsule[1] = VAdd(mPos, VGet(0, mLineSeg, 0));
	//ステータスを待機状態に
	ChangeStatus(STATUS::WAIT);
	mType = ENEMYTYPE::CRAB;
}
EN_Crab::~EN_Crab()
{
	MV1DeleteModel(mModel);
}

void EN_Crab::ChangeStatus(STATUS en_status)
{
	//ステータスの代入
	mData.status = en_status;
	//カウントリセット
	mActionCnt = 0;
	mTimeCnt = 0;
	//各状態の総モーションフレームと探索範囲の代入
	switch (mData.status)
	{
	//待機
	case STATUS::WAIT:
		mData.motionTotalFrame = 0;
		mData.searchArea = 2000;
		break;
	//攻撃
	case STATUS::ATTACK:
		mData.motionTotalFrame = 0;
		mData.searchArea = 100;
		break;
	//休憩
	case STATUS::REST:
		mData.motionTotalFrame = 60;
		mData.searchArea = 100;
		break;
	//死亡
	case STATUS::DIE:
		mData.motionTotalFrame = 60;
		mData.searchArea = 100;
		break;
	}
}
bool EN_Crab::C_Process(VECTOR pl_pos)
{
	//カウントの加算
	mActionCnt++;
	mTimeCnt++;
	//ステータスをデータ内の変更されたステータスに
	mStatus = mData.status;
	//当たり判定カプセルの位置を変更
	mCapsule[0] = mPos;
	mCapsule[1] = VAdd(mPos, VGet(0, mLineSeg, 0));
	//ローカル変数の初期化
	VECTOR v = VGet(0, 0, 0);
	float len = 0;
	//移動速度
	float speed = 0;
	//状態によって処理を変更　
	switch (mStatus)
	{
		//待機
	case STATUS::WAIT:
		//移動がないため速度を0に
		speed = 0;
		//プレイヤーと敵の位置の差分を出す
		v = VSub(mPos, pl_pos);
		//ベクトルのサイズを計算
		len = VSize(v);
		//敵からプレイヤーの距離が探索範囲内
		if (len * len <= mData.searchArea * mData.searchArea)
		{
			//ステータスを攻撃に
			ChangeStatus(STATUS::ATTACK);
		}
		break;
		//攻撃
	case STATUS::ATTACK:
		//攻撃中なのでフラグをtrueに
		mIsAttack = true;
		//ローカル変数
		VECTOR vec_pl_pos = VGet(0, 0, 0);
		VECTOR vector = VGet(0, 0, 0);
		//移動速度を設定
		speed = 2;
		//0.5秒に１回処理
		if (mTimeCnt >= 30)
		{
			//自身の位置とプレイヤーのベクトルを作成
			vec_pl_pos = VSub(mPos, pl_pos);
			//方向ベクトルとプレイヤーとの位置ベクトルの差分ベクトルを出してその2割のベクトルを出す
			vector = VScale(VSub(mDir, vec_pl_pos), 0.2);
			//差分ベクトルと方向ベクトルを合成することで移動方向のベクトルができる
			vector = VAdd(vector, mDir);
			//合成ベクトルの正規化し、方向ベクトルに
			mDir = VNorm(vector);
			//カウントリセット
			mTimeCnt = 0;
		}
		//方向ベクトルにスピードをかけたものを移動ベクトルとする
		mMove = VScale(mDir, speed);
		//位置ベクトルに移動ベクトルを加算
		mPos = VAdd(mPos, mMove);
		break;
	case STATUS::REST:
		if (mActionCnt > mData.motionTotalFrame)
		{
			//ステータスを攻撃に
			ChangeStatus(STATUS::ATTACK);
		}
		break;
	case STATUS::DAMAGE:
		//カウントが総フレームに達した
		if (mActionCnt >= mData.motionTotalFrame)
		{
			//ステータスを走行に
			ChangeStatus(STATUS::RUN);
		}
		break;
	case STATUS::DIE:
		mIsAttack = false;
		mDie = true;
		Delete();
		break;
	}
	if (mNoDamage) { mInvincibleCnt++; }
	if (mInvincibleCnt >= mNextFrame)
	{
		mNoDamage = false;
		mInvincibleCnt = 0;
	}
	//埋まらないように位置を調整
	if (mPos.y <= 0 || mPos.y >= 0)
	{
		mPos.y = 0;
	}
	if (mDie)
	{
		float rate = 1;
		mStatus = STATUS::DIE;
		for (rate; rate >= 0; rate -= 0.05)
		{
			MV1SetOpacityRate(mModel, rate);
		}
		if (rate < 0)
		{
			Delete();
			mDeleteFlag = true;
		}

	}
	else { mPlayTime = 0; }
	//モデルの位置を設定
	MV1SetPosition(mModel, mPos);
	//モデルの向きを設定
	//角度を求めるのだが座標系が違うので変更
	float angle = atan2(-mDir.x, -mDir.z);
	MV1SetRotationXYZ(mModel, VGet(0,angle,0));
	return true;
}
bool EN_Crab::Damage(VECTOR pl_pos, int subpoint, int nextframe)
{
	SoundItemBase* snditem_se = gGlobal.mSndServer.Get("SE_Damage");
	snditem_se->SetVolume(200);
	if (snditem_se && snditem_se->IsLoad())
	{
		// 再生中か？
		if (snditem_se->IsPlay() == false)
		{
			// 再生する
			snditem_se->Play();
		}
	}
	VECTOR v = VSub(mPos, pl_pos);
	mHp = mHp - subpoint;
	if (mHp <= 0)
	{
		v = VScale(VNorm(v), 100);
		//ステータスを死亡に
		ChangeStatus(STATUS::DIE);
	}
	else if (mHp > 0)
	{
		v = VScale(VNorm(v), 200);
	}
	mPos = VAdd(mPos, v);
	mNextFrame = nextframe;
	return true;
}

bool EN_Crab::Suction(VECTOR pl_pos, int nextframe)
{
	SoundItemBase* snditem_se = gGlobal.mSndServer.Get("SE_Damage");
	if (snditem_se && snditem_se->IsLoad())
	{
		// 再生中か？
		if (snditem_se->IsPlay() == false)
		{
			// 再生する
			snditem_se->Play();
		}
	}

	VECTOR v = VSub(mPos, pl_pos);
	v = VScale(VNorm(v), -5);
	mPos = VAdd(mPos, v);
	mNextFrame = nextframe;
	mNoDamage = true;
	return true;
}

bool EN_Crab::Process(VECTOR pl_pos)
{
	C_Process(pl_pos);
	return true;
}

bool EN_Crab::Render()
{
	MV1SetAttachAnimTime(mModel, mAttachIndex, mPlayTime);
	MV1DrawModel(mModel);
	return true;
}

bool EN_Crab::Debug()
{
	base::Debug();
	return true;
}

bool EN_Crab::Delete()
{
	base::Delete();
	return true;
}






