#include "Divine.h"
#include"ApplicationGlobal.h"
Divine* Divine::_divineInstance = nullptr;
Divine::Divine()
{
	_divineInstance = this;
	mPos = VGet(0,0,100);
	mHitFlag = false;
	SKILL skill[8] =
	{//	スキル名, 位置, 当たり判定用サイズ, 再発動フレーム, 再発動までのカウント, 判定用カウント, 発動フラグ, 発動中か, 総合発動時間, 判定開始時間, エフェクト初期化
		{SKILLNAME::BREATH,	  VGet(0,0,0),   0.0f, 320, 0, 0,  30, true, false, 150.0f, 12.0f,  50.0f, new Effect("res/effekseer/bless/bless.efkefc",			   100.0f), "SE_Breath"},
		{SKILLNAME::CIRCLE,	  VGet(0,0,0), 150.0f, 550, 0, 0,   5, true, false, 500.0f, 24.0f, 450.0f, new Effect("res/effekseer/circle/circle.efkefc",				30.0f), "SE_Circle"},
		{SKILLNAME::LASER,	  VGet(0,0,0), 200.0f, 400, 0, 0,   5, true, false, 240.0f, 27.0f, 70.0f,  new Effect("res/effekseer/laser/Laser.efkefc",				30.0f), "SE_Laser"},
		{SKILLNAME::SLASH,	  VGet(0,0,0), 300.0f, 300, 0, 0,  30, true, false,  96.0f, 12.0f,  30.0f, new Effect("res/effekseer/slash/slash2.efkefc",				80.0f), "SE_Slash"},
		{SKILLNAME::EXPLOSION,VGet(0,0,0), 480.0f, 400, 0, 0, 100, true, false, 150.0f, 10.0f,  15.0f, new Effect("res/effekseer/explosion/explosion_new3.efkefc",	50.0f), "SE_Explosion"},
		//{SKILLNAME::LOCKON,	   	VGet(0,0,0),   0.0f, 480, 0, 0,  40, true, false, 150.0f,  0.0f,   0.0f, new Effect("res/effekseer/lockon/lockon.efkefc", 15.0f),	"SE_Lockon"},
		{SKILLNAME::DASH,	  VGet(0,0,0), 100.0f, 180, 0, 0,  10, true, false,  60.0f, 15.0f,  60.0f, new Effect("res/effekseer/dash/dash.efkefc",					50.0f), "SE_DashAttack"},
		{SKILLNAME::VACUUM,	  VGet(0,0,0),   0.0f, 600, 0, 0,   0, true, false, 350.0f, 30.0f, 120.0f, new Effect("res/effekseer/vacuum/vacuum.efkefc",				50.0f), "SE_Vacuum"},
		{SKILLNAME::SONIC,	  VGet(0,0,0), 400.0f, 240, 0, 0,  20, true, false,  75.0f,  5.0f,  50.0f, new Effect("res/effekseer/sonicwave/sonicwave.efkefc",		50.0f), "SE_Sonic"}
	};
	for (int i = 0; i < MAX_SKILL_NUM; i++)
	{
		mSkill[i] = std::move(skill[i]);
	}
}

Divine::~Divine()
{

}

void Divine::Invocation(int type, kindDivine skillname)
{
	int i = static_cast<int>(skillname);
	if (mSkill[i].invocationFlag)
	{
		//発動中かどうかをtrueに
		mSkill[i].isPlaying = true;
		//スキル発動可能かどうかをfalseに
		mSkill[i].invocationFlag = false;
	}
}

void Divine::Reset()
{
	for (int i = 0; i < MAX_SKILL_NUM; i++)
	{
		if (mSkill[i].isPlaying)
		{
			//発動中かどうかをtrueに
			mSkill[i].isPlaying = false;
			//スキル発動可能かどうかをfalseに
			mSkill[i].invocationFlag = false;
			mSkill[i].effect->Stop();
		}
		mSkill[i].colCnt = 0;
	}
	
}

bool Divine::Calcalate(VECTOR pos, float roty)
{
	MATRIX matrix = MGetRotY(roty);
	VECTOR _all_skill_calc_pos[MAX_SKILL_NUM] =
	{
		VGet(0,0,0),
		VGet(0,100,0),
		VGet(0,100,400 - (24 * mSkill[2].colCnt)),
		VGet(0,0,0),
		VGet(0,100,-630),
		//VGet(0,0,0),
		VGet(0,0,0),
		VGet(0,100,-50),
		VGet(0,0,0)
	};
	for (auto i = 0; i < MAX_SKILL_NUM; i++)
	{
		if (mSkill[i].isPlaying)
		{
			if (mSkill[i].colCnt > mSkill[i].startColFrame &&
				mSkill[i].colCnt <= mSkill[i].endColFrame)
			{
				mSkill[i].vPos = VAdd(pos, VTransform(_all_skill_calc_pos[i], matrix));
			}
		}
	}
	return true;
}

bool Divine::Process(VECTOR pos, float roty)
{
	Calcalate(pos, roty);
	//スキルの位置
	VECTOR all_skill_pos[MAX_SKILL_NUM] =
	{
		VGet(0,0,0),
		VGet(0,0,0),
		VGet(0,100,-200),
		VGet(0,0,0),
		VGet(0,0,-630),
		//VGet(0,0,0),
		VGet(0,100,-100),
		VGet(0,100,-50),
		VGet(0,0,0)
	};
	//y軸回転のためのマトリクス作成
	MATRIX matrix = MGetRotY(roty);
	float all_skill_dir[MAX_SKILL_NUM] =
	{
		90.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f
	};
	for (int i = 0; i < MAX_SKILL_NUM; i++)
	{
		//スキル発動可能でないのならカウントを増やす
		if (!mSkill[i].invocationFlag)
		{
			mSkill[i].divineCnt++;
		}
		//カウントが特定のフレームに達した
		if(mSkill[i].colCnt >= mSkill[i].startColFrame + 10)
		{
			//再生可能フラグをfalseに
			mSkill[i].effect->SetUseFlag(false);
		}
		//カウントが発動可能フレームまで達したなら
		if (mSkill[i].divineCnt >= mSkill[i].reInvocationFrame)
		{
			//エフェクト再生可能フラグをtrueに
			mSkill[i].effect->SetUseFlag(true);
			//スキル発動フラグをtrueに
			mSkill[i].invocationFlag = true;
			//カウントリセット
			mSkill[i].divineCnt = 0;
		}
		//再生中でなければコンティニュー
		if (!mSkill[i].isPlaying) continue;
		else{ mSkill[i].colCnt++;}
		//エフェクト再生中なら
		if (mSkill[i].effect->GetPlayFlag())
		{
			//向きの単位をラジアンに変更
			all_skill_dir[i] = Math::DegToRad(all_skill_dir[i]);
			//向きを変更する
			mSkill[i].effect->SetDir(VGet(0,roty+all_skill_dir[i], 0));
			//位置を変更
			mSkill[i].effect->SetPos(VAdd(pos, VTransform(all_skill_pos[i], matrix)));
			//プロセスを回す
			mSkill[i].effect->Process();
		}
		//エフェクトの再生
		if (mSkill[i].colCnt == mSkill[i].startColFrame)
		{
			mSkill[i].effect->Play();
			//何回も再生されないように条件を付ける
			if (mSkill[i].colCnt <= mSkill[i].startColFrame + 1)
			{
				SoundItemBase* snditem_se = gGlobal.mSndServer.Get(mSkill[i].seCode);
				if (snditem_se && snditem_se->IsLoad())
				{	// 再生中か？
					if (snditem_se->IsPlay() == false)
					{	// 再生する
						snditem_se->Play();
					}
				}
			}
		}
		//判定カウントが総発動時間に到達した
		if (mSkill[i].colCnt >= mSkill[i].invocationFrame)
		{
			//発動していないのでfalse
			mSkill[i].isPlaying = false;
			//カウントリセット
			mSkill[i].colCnt = 0;
		}
	}
	return true;
}

bool Divine::Render()
{
	//エフェクトの描画
	for (int i = 0; i < MAX_SKILL_NUM; i++)
	{
		if (mSkill[i].effect->GetPlayFlag())
		{
			mSkill[i].effect->Draw();
		}
	}
	
	return true;
}
bool Divine::Debug()
{
	DrawFormatString(300, 0, GetColor(0, 0, 255), "Cnt =%d", mSkill[3].divineCnt);
	DrawFormatString(300, 20, GetColor(0, 0, 255), "Cnt =%d", mSkill[4].divineCnt);
	return true;
}