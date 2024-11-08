#include "EN_Romanoff.h"
#include "GameEvent.h"
EN_Romanoff* EN_Romanoff::_bossInstance = nullptr;
EN_Romanoff::EN_Romanoff(int model, int weapon, VECTOR vpos, VECTOR vdir) :base(model, weapon, vpos, vdir)
{
	_bossInstance = this;
	//初期値を設定
	MV1SetPosition(mModel, mPos);
	//体力
	mHp = 4000;
	//攻撃力
	mAtk = 20;
	//死んでいるか
	mDie = false;
	//判定カプセル内の要素を初期化
	//カプセルの半径
	mRadius = 45;
	//線分の長さ
	mLineSeg = 191;
	//カプセルの位置
	mCapsule[0] = mPos;
	mCapsule[1] = VAdd(mPos, VGet(0, mLineSeg, 0));
	//アタッチするアニメーション番号の初期化
	mAttachIndex = MV1AttachAnim(mModel, 6, -1, FALSE);
	mName = "romanoff_stand";
	//総再生時間の初期化
	mTotalTime = gGlobal.mRS->mGetAttach()[mName]._attach_time;
	//武器サイズ
	mWeaponSize = 50;
	mDamageCnt = 5;
	//ステータスを未発見に
	ChangeStatus(STATUS::NODISCOVERY);
	mType = ENEMYTYPE::ROMANOFF;
}

EN_Romanoff::~EN_Romanoff()
{
	MV1DeleteModel(mModel);
	MV1DetachAnim(mModel, mAttachIndex);
}

void EN_Romanoff::ChangeStatus(STATUS en_status)
{
	//ステータスの代入
	mData.status = en_status;
	//カウントリセット
	mActionCnt = 0;
	mTimeCnt = 0;
	switch (mData.status)
	{
	case STATUS::DAMAGE:
		mData.motionTotalFrame = 42;
	}
}

bool EN_Romanoff::A_Process()
{
	//1フレーム前のステータスと違うのなら処理
	if (mOldAnimation != mAnimation)
	{
		//アニメーションのデタッチ
		MV1DetachAnim(mModel, mAttachIndex);
		//ステータスによってアタッチするアニメーションの変更
		switch (mAnimation)
		{
		//待機
		case ANIMATION::WAIT:
			//キーを一致させるために文字列を代入
			mName = "romanoff_stand";
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		//ダメージ
		case ANIMATION::DAMAGE:
			//キーを一致させるために文字列を代入
			mName = "romanoff_damage";
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		//攻撃
		case ANIMATION::FIRSTATTACK:
			//キーを一致させるために文字列を代入
			mName = "romanoff_attack1";
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		case ANIMATION::SECONDATTACK:
			//キーを一致させるために文字列を代入
			mName = "romanoff_attack2";
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		//走行
		case ANIMATION::RUN:
			//キーを一致させるために文字列を代入
			mName = "romanoff_run";
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		//走行
		case ANIMATION::DIE:
			//キーを一致させるために文字列を代入
			mName = "romanoff_die";
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
	mOldAnimation = mAnimation;
	return true;
}

void EN_Romanoff::DiscoveryProcess(VECTOR pl_pos)
{
	float dis_discovery = 2000.0f;
	mAnimation = ANIMATION::WAIT;
	//プレイヤーと敵の位置の差分を出す
	VECTOR v = VSub(mPos, pl_pos);
	//ベクトルのサイズを計算
	float len = VSize(v);
	if (len <= dis_discovery)
	{
		ChangeStatus(STATUS::WAIT);
		GameEvent::GetInstance()->SetEvent(1);
	}

}

void EN_Romanoff::WaitProcess()
{
	int action_num = rand() % 10;
	mAnimation = ANIMATION::WAIT;
	mActionCnt++;
	if (mActionCnt >= 70)
	{
		if (action_num < 7)
		{
			//ステータスを走行に
			ChangeStatus(STATUS::RUN);
		}
		else if (action_num >= 7)
		{
			//ステータスを突撃に
			ChangeStatus(STATUS::ASSAULT);
		}
		
	}
}

void EN_Romanoff::Move(float speed, VECTOR pl_pos)
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

void EN_Romanoff::RunProcess(VECTOR pl_pos)
{
	//アニメーションを走行に
	mAnimation = ANIMATION::RUN;
	//スピードを設定
	float speed = 8.3;
	//カウント加算
	mActionCnt++;
	//移動処理
	Move(speed, pl_pos);
	//プレイヤーと敵の位置の差分を出す
	VECTOR v = VSub(mPos, pl_pos);
	//ベクトルのサイズを計算
	float len = VSize(v);
	//カウントが規定数、もしくはベクトルサイズが規定以内
	if (len <= 100)
	{
		//ステータスを攻撃に変更
		ChangeStatus(STATUS::ATTACK);
	}
	else if (mActionCnt >= 360 && len >= 100)
	{
		//ステータスを攻撃に変更
		ChangeStatus(STATUS::ASSAULT);
	}

}

VECTOR EN_Romanoff::AttackPos()
{
	VECTOR vec = { 0 };
	int frame_index = MV1SearchFrame(mModel, "Character1_Hips");
	//位置をローカルからグローバルに変換するマトリックスを作成
	MATRIX matrix = MV1GetFrameLocalWorldMatrix(mModel, frame_index);
	vec = VTransform(VGet(0, 0, 0), matrix);
	return VGet(vec.x, 0, vec.z);
}

bool EN_Romanoff::Attack()
{
	if (mActionCnt >= 25 && mActionCnt <= 35 ||
		mActionCnt >= 45 && mActionCnt <= 70)
	{
		return true;
	}
	return false;
}

void EN_Romanoff::AttackProcess()
{
	mActionCnt++;
	std::string se_voice = "VO_Ro_Attack";
	SoundItemBase* snditem_voice = gGlobal.mSndServer.Get(se_voice);
	if (Attack())
	{
		//_vPos = AttackPos();
		mIsAttack = true;
	}
	else
	{
		mIsAttack = false;
	}
	if (mActionCnt >= 0 && mActionCnt < 40)
	{
		mAnimation = ANIMATION::FIRSTATTACK;
		if (snditem_voice && snditem_voice->IsLoad())
		{
			// 再生中か？
			if (snditem_voice->IsPlay() == false)
			{
				// 再生する
				snditem_voice->Play();
			}
		}
	}
	else if (mActionCnt >= 40 && mActionCnt < 112)
	{
		mAnimation = ANIMATION::SECONDATTACK;
	}
	else if (mActionCnt == 112)
	{
		ChangeStatus(STATUS::WAIT);
	}
}

bool EN_Romanoff::Assult()
{
	if (mActionCnt >= 85 && mActionCnt <= 95)
	{
		return true;
	}
	return false;
}

void EN_Romanoff::AssaultProcess(VECTOR pl_pos)
{
	//スピードを設定
	float speed = 30.0;
	float finish_frame = 125;
	float assult_start_frame = 40;
	float dis_assult = 100;
	std::string voice[3] =
	{
		"VO_Ro_Divine1",
		"VO_Ro_DIvine2",
		"VO_Ro_DIvine3"
	};
	SoundItemBase* snditem_voice = gGlobal.mSndServer.Get(voice[rand() % 3]);
	//カウント加算
	mActionCnt++;
	//プレイヤーと敵の位置の差分を出す
	VECTOR v = VSub(mPos, pl_pos);
	//ベクトルのサイズを計算
	float len = VSize(v);
	if (mActionCnt == 1)
	{
		snditem_voice->Play();
	}
	if (mActionCnt < assult_start_frame)
	{
		//アニメーションを走行に
		Move(speed, pl_pos);
		mAnimation = ANIMATION::RUN;
	}
	else if (mActionCnt == assult_start_frame)
	{
		mAnimation = ANIMATION::FIRSTATTACK;
	}
	else if (mActionCnt == finish_frame)
	{
		ChangeStatus(STATUS::WAIT);
	}
	
	if (Assult())
	{
		//_vPos = AttackPos();
		mIsAttack = true;
	}
	if (mActionCnt < 85 || mActionCnt > 95)
	{
		mIsAttack = false;
	}

}


void EN_Romanoff::DieProcess()
{
	std::string se_voice = "VO_Ro_Blow";
	SoundItemBase* snditem_voice = gGlobal.mSndServer.Get(se_voice);
	mAnimation = ANIMATION::DIE;
	if (snditem_voice && snditem_voice->IsLoad())
	{
		// 再生中か？
		if (snditem_voice->IsPlay() == false)
		{
			// 再生する
			snditem_voice->Play();
		}
	}
	mDie = true;
}

void EN_Romanoff::DamageProcess()
{
	mActionCnt++;
	mAnimation = ANIMATION::DAMAGE;
	//カウントが総フレームに達した
	if (mActionCnt >= mData.motionTotalFrame)
	{
		//ステータスを走行に
		ChangeStatus(STATUS::WAIT);
	}

}

bool EN_Romanoff::Damage(VECTOR pl_pos, int subpoint, int nextframe)
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
	mDamageCnt--;
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
		v = VScale(VNorm(v), 50);
		//ステータスをダメージに
		if (mDamageCnt <= 0)
		{
			ChangeStatus(STATUS::DAMAGE);
			mDamageCnt = 5;
		}
	}
	mPos = VAdd(mPos, v);
	mNextFrame = nextframe;
	mNoDamage = true;
	return true;
}

bool EN_Romanoff::Suction(VECTOR pl_pos, int nextframe)
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
	ChangeStatus(STATUS::DAMAGE);
	VECTOR v = VSub(mPos, pl_pos);
	v = VScale(VNorm(v), -5);
	mPos = VAdd(mPos, v);
	mNextFrame = nextframe;
	mNoDamage = true;
	return true;
}

void EN_Romanoff::SetWeapon()
{
	//プレイヤーのモデルから武器を装備するフレームを探す
	int frame_index = MV1SearchFrame(mModel, "joint_axe");
	//位置をローカルからグローバルに変換するマトリックスを作成
	MATRIX weapon_matrix = MV1GetFrameLocalWorldMatrix(mModel, frame_index);
	MATRIX weapon_dir_matrix = MGetRotY(1.75);
	weapon_matrix = MMult(weapon_dir_matrix,weapon_matrix);
	//武器位置の設定
	mWeaponPos[0] = VTransform(VGet(0, 0, 0), weapon_matrix);
	mWeaponPos[1] = VTransform(VGet(0, 150, 0), weapon_matrix);
	//武器の位置を手のフレームに設定
	MV1SetMatrix(mWeaponModel, weapon_matrix);
}

void EN_Romanoff::Invincible(int nextframe)
{
	//無敵時間中のみカウントを増やす
	if (mNoDamage) { mInvincibleCnt++; }
	//カウントが規定数に達する
	if (mInvincibleCnt >= nextframe)
	{
		//無敵フラグをfalseに
		mNoDamage = false;
		//カウントリセット
		mInvincibleCnt = 0;
	}
}

bool EN_Romanoff::C_Process(VECTOR pl_pos)
{
	mStatus = mData.status;
	//カウントの加算
	mTimeCnt++;
	//当たり判定カプセルの位置を変更
	mCapsule[0] = mPos;
	mCapsule[1] = VAdd(mPos, VGet(0, mLineSeg, 0));
	//状態によって処理を変更
	switch (mStatus)
	{
	case STATUS::NODISCOVERY:
		DiscoveryProcess(pl_pos);
		break;
	//待機
	case STATUS::WAIT:
		WaitProcess();
		break;
	//走行
	case STATUS::RUN:
		RunProcess(pl_pos);
		break;
	//ダメージ
	case STATUS::DAMAGE:
		DamageProcess();
		break;
	//攻撃
	case STATUS::ATTACK:
		AttackProcess();
		break;
	//突撃
	case STATUS::ASSAULT:
		AssaultProcess(pl_pos);
		break;
	//死亡
	case STATUS::DIE:
		DieProcess();
		break;
	}
	//埋まらないように位置を調整
	if (mPos.y <= 0|| mPos.y >= 0)
	{
		mPos.y = 0;
	}
	Invincible(mNextFrame);
	SetWeapon();
	//角度を求めるのだが座標系が違うので変更
	float angle = atan2(-mDir.x, -mDir.z);
	//モデルの向きを設定
	MV1SetRotationXYZ(mModel, VGet(0, angle, 0));
	MV1SetPosition(mModel, mPos);
	return true;
}

bool EN_Romanoff::Process(VECTOR pl_pos)
{
	C_Process(pl_pos);
	A_Process();
	return true;
}

bool EN_Romanoff::Render()
{
	MV1SetAttachAnimTime(mModel, mAttachIndex, mPlayTime);
	MV1DrawModel(mModel);
	MV1DrawModel(mWeaponModel);
	return true;
}

bool EN_Romanoff::Debug()
{
	return true;
}

bool EN_Romanoff::Delete()
{
	return true;
}








