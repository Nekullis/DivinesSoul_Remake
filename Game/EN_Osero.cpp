#include "EN_Osero.h"
EN_Osero::EN_Osero(int model, int weapon, VECTOR vpos, VECTOR vdir) : base(model, weapon, vpos, vdir)
{
	//初期値を設定
	MV1SetPosition(mModel, mPos);
	//体力
	mHp = 50;
	//攻撃力
	mAtk = 8;
	//死んでいるか
	mDie = false;
	//カプセルの半径
	mRadius = 35;
	//線分の長さ
	mLineSeg = 191;
	//カプセルの位置
	mCapsule[0] = mPos;
	mCapsule[1] = VAdd(mPos, VGet(0, mLineSeg, 0));
	//アタッチするアニメーション番号の初期化
	mAttachIndex = MV1AttachAnim(mModel, 6, -1, FALSE);
	//総再生時間の初期化
	mTotalTime = gGlobal.mRS->mGetAttach()["osero_stand"]._attach_time;
	//武器サイズ
	mWeaponSize = 30;
	//ステータスを待機状態に
	ChangeStatus(STATUS::WAIT);
	mType = ENEMYTYPE::OSERO;
}
EN_Osero::~EN_Osero()
{
	MV1DeleteModel(mModel);
	MV1DetachAnim(mModel, mAttachIndex);
}
void EN_Osero::ChangeStatus(STATUS en_status)
{
	mActionCnt = 0;
	mTimeCnt = 0;
	//ステータスの代入
	mStatus = en_status;
	//各状態の総モーションフレームと探索範囲の代入
	switch (mStatus)
	{
	//待機
	case WAIT:
		mData.motionTotalFrame = 0;
		mData.searchArea = 1000;
		break;
	//ダメージ
	case DAMAGE:
		mData.motionTotalFrame = 42;
		mData.searchArea = 0;
		break;
	//警戒
	case CAUTION:
		mData.motionTotalFrame = 0;
		mData.searchArea = 0;
		break;
	//攻撃
	case ATTACK:
		mData.motionTotalFrame = 38;
		mData.searchArea = 200;
		break;
	//走行
	case RUN:
		mData.motionTotalFrame = 31;
		mData.searchArea = 200;
		break;
	}
}
bool EN_Osero::A_Process()
{
	//std::string mName;
	std::string name[2] =
	{
		"osero_walk_left",
		"osero_walk_right",
	};
	//1フレーム前のステータスと違うのなら処理
	if (mOldStatus != mStatus)
	{
		//アニメーションのデタッチ
		MV1DetachAnim(mModel, mAttachIndex);
		//ステータスによってアタッチするアニメーションの変更
		switch (mStatus)
		{
		//待機
		case STATUS::WAIT:
			//キーを一致させるために文字列を代入
			mName = "osero_stand";
			mAttachIndex = MV1AttachAnim(mModel,gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		//ダメージ
		case STATUS::DAMAGE:
			//キーを一致させるために文字列を代入
			mName = "osero_damage";
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		//警戒
		case STATUS::CAUTION:
			//キーを一致させるために文字列を代入
			mName = name[rand() % 2];
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		//攻撃
		case STATUS::ATTACK:
			//キーを一致させるために文字列を代入
			mName = "osero_attack1";
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		//走行
		case STATUS::RUN:
			//キーを一致させるために文字列を代入
			mName = "osero_run";
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
			//走行
		case STATUS::DIE:
			//キーを一致させるために文字列を代入
			mName = "osero_die";
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		}
		// アタッチしたアニメーションの総再生時間を取得する
		mTotalTime = gGlobal.mRS->mGetAttach()[mName]._attach_time;
		mPlayTime = 0.0f;
	}
	
	// 再生時間を進める
	mPlayTime += 1.0f;
	// 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
	if (mPlayTime >= mTotalTime)
	{
		if (mDie)
		{
			mPlayTime = mTotalTime;
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
	}
	//一時的なステータスの変更
	mOldStatus = mStatus;
	return true;
}
void EN_Osero::WaitProcess(VECTOR pl_pos)
{
	//プレイヤーと敵の位置の差分を出す
	VECTOR v = VSub(mPos, pl_pos);
	//ベクトルのサイズを計算
	float len = VSize(v);
	//敵からプレイヤーの距離が探索範囲内
	if (len * len <= mData.searchArea * mData.searchArea)
	{
		//ステータスを走行に
		ChangeStatus(STATUS::RUN);
	}
}


void EN_Osero::Move(float speed, VECTOR pl_pos)
{
	//ローカル変数を設定
	VECTOR vec_pl_pos = VGet(0, 0, 0);
	VECTOR vector = VGet(0, 0, 0);
	//自身の位置とプレイヤーのベクトルを作成
	vec_pl_pos = VSub(pl_pos, mPos);
	//ベクトルを正規化
	VECTOR vunit = VNorm(vec_pl_pos);
	//正規化したベクトルを
	vector = vunit;
	//向きを設定するために代入
	mDir = vec_pl_pos;
	//方向ベクトルにスピードをかけたものを移動ベクトルとする
	mMove = VScale(vector, speed);
	//位置ベクトルに移動ベクトルを加算
	mPos = VAdd(mPos, mMove);
}

void EN_Osero::RunProcess(VECTOR pl_pos)
{
	float speed = 10;
	Move(speed, pl_pos);
	//プレイヤーと敵の位置の差分を出す
	VECTOR v = VSub(mPos, pl_pos);
	//ベクトルのサイズを計算
	float len = VSize(v);
	//敵からプレイヤーの距離が探索範囲内
	if (len * len <= mData.searchArea * mData.searchArea)
	{
		//ステータスを警戒に
		ChangeStatus(STATUS::CAUTION);
	}
	if (len >= 2100)
	{
		//ステータスを待機に
		ChangeStatus(STATUS::WAIT);
	}

}
void EN_Osero::CautionProcess(VECTOR pl_pos)
{
	mActionCnt++;
	float attack_frame = 70 * (rand() % 10 + 1);
	if (mName == "osero_walk_left")
	{
		mPos.x += 0.1;
	}
	if (mName == "osero_walk_right")
	{
		mPos.x -= 0.1;
	}
	//プレイヤーと敵の位置の差分を出す
	VECTOR v = VSub(pl_pos, mPos);
	//ベクトルのサイズを計算
	float len = VSize(v);
	//プレイヤーと敵の判定カプセルの合計
	float add_radius = mData.searchArea + 30;
	MATRIX m = MGetRotY(mDir.y);
	VECTOR vec = VGet(m.m[2][0], m.m[2][1], m.m[2][2]);
	//vec = VScale(vec, -1);
	//プレイヤーが敵の索敵範囲に入った
	if (MathCollision::CollisionPointAndFan(vec, v, 50))
	{
		//カウントが攻撃までのフレームに達した
		if (mActionCnt >= attack_frame)
		{
			//ステータスを攻撃に
			ChangeStatus(STATUS::ATTACK);
		}
	}
	if (len >= 300)
	{
		//ステータスを走行に
		ChangeStatus(STATUS::RUN);
	}
}
void EN_Osero::AttackProcess()
{
	mActionCnt++;
	//攻撃中なのでフラグをtrueに
	mIsAttack = true;
	//カウントが総モーションフレームに達した
	if (mActionCnt >= mData.motionTotalFrame)
	{
		//攻撃が終わったのでフラグをfalseに
		mIsAttack = false;
		//ステータスを走行に
		ChangeStatus(STATUS::RUN);
	}
}

void EN_Osero::DamageProcess()
{
	mActionCnt++;
	//カウントが総フレームに達した
	if (mActionCnt >= mData.motionTotalFrame)
	{
		//ステータスを走行に
		ChangeStatus(STATUS::RUN);
	}
}

void EN_Osero::DieProcess()
{
	mDie = true;
	mIsAttack = false;
}
void EN_Osero::SetWeapon()
{
	//プレイヤーのモデルから武器を装備するフレームを探す
	int frame_index = MV1SearchFrame(mModel, "joint_sword");
	//位置をローカルからグローバルに変換するマトリックスを作成
	MATRIX weapon_matrix = MV1GetFrameLocalWorldMatrix(mModel, frame_index);
	mWeaponPos[0] = VTransform(VGet(0, 0, 0), weapon_matrix);
	mWeaponPos[1] = VTransform(VGet(0, 100, 0), weapon_matrix);
	//武器の位置を手のフレームに設定
	MV1SetMatrix(mWeaponModel, weapon_matrix);
}

void EN_Osero::Invincible(int nextframe)
{
	////無敵時間中のみカウントを増やす
	//if (mNoDamage) { mInvincibleCnt++; }
	//if (mInvincibleCnt >= mNextFrame)
	//{
	//	mNoDamage = false;
	//	mInvincibleCnt = 0;
	//}
}
VECTOR EN_Osero::AttackPos()
{
	return VECTOR();
}
bool EN_Osero::C_Process(VECTOR pl_pos)
{
	
	//カウントの加算
	mTimeCnt++;
	//当たり判定カプセルの位置を変更
	mCapsule[0] = mPos;
	mCapsule[1] = VAdd(mPos, VGet(0, mLineSeg, 0));
	//状態によって処理を変更
	switch (mStatus)
	{
	//待機
	case STATUS::WAIT:
		WaitProcess(pl_pos);
		break;
	//走行
	case STATUS::RUN:
		RunProcess(pl_pos);
		break;
	//ダメージ
	case STATUS::DAMAGE:
		DamageProcess();
		break;
	//警戒
	case STATUS::CAUTION:
		CautionProcess(pl_pos);
		break;
	//攻撃
	case STATUS::ATTACK:
		AttackProcess();
		break;
	//死亡
	case STATUS::DIE:
		DieProcess();
		break;
	}
	//埋まらないように位置を調整
	mPos.y -= 10;
	if (mPos.y <= 0)
	{
		mPos.y = 0;
	}
	//無敵時間中のみカウントを増やす
	Invincible(mNextFrame);
	SetWeapon();
	//モデルの位置を設定
	MV1SetPosition(mModel, mPos);
	//角度を求めるのだが座標系が違うので変更
	float angle = atan2(-mDir.x, -mDir.z);
	//モデルの向きを設定
	MV1SetRotationXYZ(mModel, VGet(0,angle,0));
	return true;
}

bool EN_Osero::Process(VECTOR pl_pos)
{
	A_Process();
	C_Process(pl_pos);
	return true;
}

bool EN_Osero::Damage(VECTOR pl_pos,int subpoint, int nextframe)
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
		v = VScale(VNorm(v), 85);
		ChangeStatus(STATUS::DAMAGE);
	}
	mPos = VAdd(mPos, v);
	/*mNextFrame = nextframe;
	mNoDamage = true;*/
	return true;
}

bool EN_Osero::Suction(VECTOR pl_pos, int nextframe)
{
	Enemy::Suction(pl_pos,nextframe);
	return true;
}

bool EN_Osero::Render()
{
	MV1SetAttachAnimTime(mModel, mAttachIndex, mPlayTime);
	MV1SetRotationXYZ(mWeaponModel, VGet(0, 0.5, 0));
	MV1DrawModel(mModel);
	MV1DrawModel(mWeaponModel);
	return true;
}
bool EN_Osero::Debug()
{
	base::Debug();
	DrawFormatString(0, 200, GetColor(255, 255, 255), "cnt=%d", mActionCnt);
	DrawFormatString(0, 200, GetColor(255, 255, 255), "time=%d", mPlayTime);
	return true;
}
bool EN_Osero::Delete()
{
	base::Delete();
	return true;
}
