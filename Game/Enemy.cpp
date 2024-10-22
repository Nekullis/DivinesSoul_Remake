#include "enemy.h"
Enemy::Enemy(int model, int weapon,VECTOR vpos, VECTOR vdir)
{
	mModel = MV1DuplicateModel(model);
	mWeaponModel = MV1DuplicateModel(weapon);
	//初期値を設定
	mPos = vpos;
	mDir = vdir;
	mMove = VGet(0, 0, 0);
	MV1SetPosition(mModel, mPos);
	MV1SetRotationXYZ(mModel, mDir);
	//判定カプセル内の要素を初期化
	mCapsule[0] = mPos;
	mCapsule[1] = VAdd(mPos, VGet(0, 150, 0));
	mRadius = 0;
	mLineSeg = 0;
	mWeaponPos[0] = VGet(0, 0, 0);
	mWeaponPos[1] = VGet(0, 0, 0);
	mWeaponSize = 0;
	//体力
	mHp = 0;
	mAtk = 0;
	mDie = false;
	mDeleteFlag = false;
	//カウント初期化
	mActionCnt = 0;
	mInvincibleCnt = 0;
	mNextFrame = 1;
	mTimeCnt = 0;
	//攻撃中ではないのでfalseに
	mIsAttack = false;
	//ダメージを受けていないので
	mDamage = false;
	mNoDamage = false;
	//再生時間の初期化
	mPlayTime = 0.0f;
	//総再生時間の初期化
	mTotalTime = 0;
	//アタッチするアニメーション番号の初期化
	mAttachIndex = -1;
	mType = ENEMYTYPE::NOCHARA;
}
Enemy::~Enemy()
{
	MV1DeleteModel(mModel);
}

bool Enemy::Process(VECTOR pl_pos)
{
	return true;
}
bool Enemy::Render()
{
	return true;
}
bool Enemy::Debug()
{
	return true;
}
bool Enemy::Delete()
{
	MV1DeleteModel(mModel);
	return true;
}

bool Enemy::Damage(VECTOR pl_pos, int subpoint,int nextframe)
{
	return true;
}

bool Enemy::Suction(VECTOR pl_pos, int nextframe)
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

void Enemy::ChangeStatus(STATUS en_status)
{

}
