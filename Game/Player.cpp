#include "Player.h"
#include "ApplicationGlobal.h"
#include "Camera.h"

Player* Player::mPlInstance = nullptr;
Player::Player() 
{
	mPlInstance = this;
	//位置
	mPos = VGet(0.0f, 0.0f, 0.0f);
	//角度
	mDir = VGet(0.0f, 1.0f, 0.0f);
	SetJsonTransform();
	//移動
	mMove = VGet(0.0f, 0.0f, 0.0f);
	//カプセルの長さ
	mLineSeg = 170.0f;
	//カプセル半径
	mRCap = 30.0f;
	//カプセル頂点(下)
	mCapsule[0] = VGet(mPos.x + 0.0f, mPos.y + 50.0f, mPos.z + 0.0f);
	//カプセル頂点(上)
	mCapsule[1] = VGet(mPos.x + 0.0f, mPos.y - 50.0f, mPos.z + 0.0f);
	//モデル描画
	mModel = 0;
	//アタッチするアニメーション番号
	mAttachIndex = -1;
	//重力初期化
	mGravity = -15.0f;
	//攻撃中か
	mIsAttack = false;
	//無敵中か
	mNoDamage = false;
	//スキル発動中か
	mIsSkill = false;
	//死んでいるか
	mIsDie = false;
	//ゲームオーバーフラグ
	mGameOverFlag = false;
	//最後に押したボタン
	mLastCommand = -1;
	//武器位置
	mWPos[0] = VGet(0, 0, 0);
	mWPos[1] = VGet(0, 0, 0);
	mSkill = new Divine();
	//各パラメータを代入
	mHp = 255;
	mAtk = 0;

	mOldMotion = CHARACTER_MOTION::PLAYER_STAND;
	mMotion = CHARACTER_MOTION::PLAYER_STAND;
	mMotionManager = new MotionTableManager();
	mMotionManager->LoadTable("res/csv/player/Motion/Motion_Table_STAND.csv",		CHARACTER_MOTION::PLAYER_STAND,			MotionTable::MOTION_ENDTYPE::LOOP,	MOTION_LAYER::ALWAYS);
	mMotionManager->LoadTable("res/csv/player/Motion/Motion_Table_RUN.csv",			CHARACTER_MOTION::PLAYER_RUN,			MotionTable::MOTION_ENDTYPE::LOOP,	MOTION_LAYER::PRESS_DOWN);
	mMotionManager->LoadTable("res/csv/player/Motion/Motion_Table_FIRSTATTACK.csv",	CHARACTER_MOTION::PLAYER_FIRSTATTACK,	MotionTable::MOTION_ENDTYPE::END,	MOTION_LAYER::TRIGGER);
	mMotionManager->LoadTable("res/csv/player/Motion/Motion_Table_SECONDATTACK.csv",CHARACTER_MOTION::PLAYER_SECONDATTACK,	MotionTable::MOTION_ENDTYPE::END,	MOTION_LAYER::TRIGGER);
	mMotionManager->LoadTable("res/csv/player/Motion/Motion_Table_LASTATTACK.csv",	CHARACTER_MOTION::PLAYER_LASTATTACK,	MotionTable::MOTION_ENDTYPE::END,	MOTION_LAYER::TRIGGER);
	mMotionManager->LoadTable("res/csv/player/Motion/Motion_Table_DASHATTACK.csv",	CHARACTER_MOTION::PLAYER_DASHATTACK,	MotionTable::MOTION_ENDTYPE::END,	MOTION_LAYER::TRIGGER);
	mMotionManager->LoadTable("res/csv/player/Motion/Motion_Table_SKILL.csv",		CHARACTER_MOTION::PLAYER_SKILL,			MotionTable::MOTION_ENDTYPE::END,	MOTION_LAYER::TRIGGER);
	mMotionManager->LoadTable("res/csv/player/Motion/Motion_Table_SKILLDASH.csv",	CHARACTER_MOTION::PLAYER_SKILLDASH,		MotionTable::MOTION_ENDTYPE::LOOP,	MOTION_LAYER::TRIGGER);
	mMotionManager->LoadTable("res/csv/player/Motion/Motion_Table_DAMAGE.csv",		CHARACTER_MOTION::PLAYER_DAMAGE,		MotionTable::MOTION_ENDTYPE::END,	MOTION_LAYER::DAMAGE);
	mMotionManager->LoadTable("res/csv/player/Motion/Motion_Table_DIE.csv",			CHARACTER_MOTION::PLAYER_DIE,			MotionTable::MOTION_ENDTYPE::DIE,	MOTION_LAYER::TRIGGER);
	mMotionManager->LoadTable("res/csv/player/Motion/Motion_Table_AVOID.csv",		CHARACTER_MOTION::PLAYER_AVOID,			MotionTable::MOTION_ENDTYPE::END,	MOTION_LAYER::TRIGGER);
	mMotionManager->ChangeMotion(mMotion);

	mAttackManager = new AttackTableManager();
	mAttackManager->LoadAttackData("res/csv/player/AttackData/Attack_Data_NONE.csv",			ATTACK_TYPE::NONE,"","");
	mAttackManager->LoadAttackData("res/csv/player/AttackData/Attack_Data_NORMALATTACK.csv",	ATTACK_TYPE::NORMAL_ATTACK, "VO_Fe_Attack01", "SE_Attack01");
	mAttackManager->LoadAttackData("res/csv/player/AttackData/Attack_Data_SCONDATTACK.csv",		ATTACK_TYPE::SCOND_ATTACK,  "VO_Fe_Attack02", "SE_Attack02");
	mAttackManager->LoadAttackData("res/csv/player/AttackData/Attack_Data_THIRDATTACK.csv",		ATTACK_TYPE::THIRD_ATTACK,  "VO_Fe_Attack03", "SE_Attack03");
	mAttackManager->LoadAttackData("res/csv/player/AttackData/Attack_Data_DASHATTACK.csv",		ATTACK_TYPE::DASH_ATTACK,	"VO_Fe_Attack03", "SE_Attack01");
	mAttackManager->AttackChange(ATTACK_TYPE::NONE);
}

Player::~Player()
{
	delete mSkill;
	delete mMotionManager;
	delete mAttackManager;
	MV1DetachAnim(mModel, mAttachIndex);
}

void Player::SetJsonTransform()
{
	JsonUtility* jUtil;
	jUtil = new JsonUtility();
	nlohmann::json player_pos = jUtil->Import("res/Json/Player_pos.json").at("Player Start");
	for (auto& data : player_pos)
	{
		data.at("translate").at("x").get_to(mPos.x);
		data.at("translate").at("z").get_to(mPos.y);
		data.at("translate").at("y").get_to(mPos.z);
		// 座標の変換
		mPos.z *= -1.f;
		data.at("rotate").at("x").get_to(mDir.x);
		data.at("rotate").at("z").get_to(mDir.y);
		data.at("rotate").at("y").get_to(mDir.z);
		// 回転はdegree→radianに
		mDir.x = Math::DegToRad(mDir.x);
		mDir.y = Math::DegToRad(mDir.y);
		mDir.z = Math::DegToRad(mDir.z);
	}
}

void Player::Initialize(int handle, int weapon)
{
	// モデルデータのロード（テクスチャも読み込まれる）	
	mModel = handle;
	mDashModel = MV1LoadModel("res/Model/Character/Player/A_DashAttack.mv1");
	// 3Dモデルの1番目のアニメーションをアタッチする
	mAttachIndex = MV1AttachAnim(mModel, 0, -1, FALSE);
	//武器モデルのロード
	mWModel = weapon;
	mOldIndex = -1;
	mRate = 1.f;
}

void Player::A_Process()
{
	std::string mname;
	if (mOldMotion != mMotionManager->GetMotion())
	{
		//MV1DetachAnim(mModel, mAttachIndex);
		mOldIndex = mAttachIndex;
		mRate = 1.f;
		switch (mMotion)
		{
		case CHARACTER_MOTION::PLAYER_STAND:
			// 待機状態のアニメーションをアタッチする
			mname = "player_stand";
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mname]._attach_index, -1, FALSE);
			break;
		case CHARACTER_MOTION::PLAYER_RUN:
			// 走るアニメーションをアタッチする
			mname = "player_run";
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mname]._attach_index, -1, FALSE);
			break;
		case CHARACTER_MOTION::PLAYER_FIRSTATTACK:
			//縦斬りモーションをアタッチする
			mname = "player_attack1";
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mname]._attach_index, -1, FALSE);
			break;
		case CHARACTER_MOTION::PLAYER_SECONDATTACK:
			//横斬りモーションをアタッチする
			mname = "player_attack2";
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mname]._attach_index, -1, FALSE);
			break;
		case CHARACTER_MOTION::PLAYER_LASTATTACK:
			//回転斬りモーションをアタッチする
			mname = "player_attack3";
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mname]._attach_index, -1, FALSE);
			break;
		case CHARACTER_MOTION::PLAYER_DASHATTACK:
			//ダッシュ攻撃モーションをアタッチする
			//mname = "player_avoid";
			mAttachIndex = MV1AttachAnim(mModel, 0, mDashModel, true);
			break;
		case CHARACTER_MOTION::PLAYER_SKILL:
			//ディバインスキルを使用するモーションをアタッチする
			mname = "player_skill";
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mname]._attach_index, -1, FALSE);
			break;
		case CHARACTER_MOTION::PLAYER_SKILLDASH:
			//ディバインスキルを使用するモーションをアタッチする
			mname = "player_run";
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mname]._attach_index, -1, FALSE);
			break;
		case CHARACTER_MOTION::PLAYER_AVOID:
			//回避モーションをアタッチする
			mname = "player_avoid";
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mname]._attach_index, -1, FALSE);
			break;
		case CHARACTER_MOTION::PLAYER_DAMAGE:
			//ダメージモーションをアタッチする
			mname = "player_damage";
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mname]._attach_index, -1, FALSE);
			break;
		case CHARACTER_MOTION::PLAYER_DIE:
			//死亡モーションをアタッチする
			mname = "player_blow";
			mAttachIndex = MV1AttachAnim(mModel, gGlobal.mGetAttach()[mname]._attach_index, -1, FALSE);
			break;
		}
		//モーションステータス変更
		mMotionManager->ChangeMotion(mMotion);
	}
	if (mOldIndex != -1)
	{
		mRate -= 0.1;
		MV1SetAttachAnimBlendRate(mModel, mOldIndex, mRate);
		MV1SetAttachAnimBlendRate(mModel, mAttachIndex, 1.f - mRate);
		if (mRate <= 0.0f)
		{
			mOldIndex = -1;
			mRate = 0.f;
			MV1DetachAnim(mModel, mOldIndex);
		}
	}
	//旧モーション更新
	mOldMotion = mMotion;
	// 再生時間をセットする
	int motioncnt = mMotionManager->GetMotionCnt();
	MV1SetAttachAnimTime(mModel, mAttachIndex, motioncnt);
}

void Player::SetWeapon()
{
	//プレイヤーのモデルから武器を装備するフレームを探す
	int frame_index = MV1SearchFrame(mModel, "joint_sword");
	//位置をローカルからグローバルに変換するマトリックスを作成
	MATRIX weapon_matrix = MV1GetFrameLocalWorldMatrix(mModel, frame_index);
	mWPos[0] = VTransform(VGet(0, 0, 0), weapon_matrix);
	mWPos[1] = VTransform(VGet(0, 100, 0), weapon_matrix);
	//武器の位置を手のフレームに設定
	MV1SetMatrix(mWModel, weapon_matrix);
}

CHARACTER_MOTION Player::SkillMotion()
{
	CHARACTER_MOTION motion;
	for (int i = 0; i < MAX_SKILL_NUM; i++)
	{
		int cnt = mSkill->GetSkill(i).divineCnt;
		if (cnt > 0 && cnt <= 38)
		{
			switch (mSkill->GetSkill(i).skillName)
			{
			case Divine::SKILLNAME::BREATH:
			case Divine::SKILLNAME::CIRCLE:
			case Divine::SKILLNAME::EXPLOSION:
			case Divine::SKILLNAME::LASER:
			case Divine::SKILLNAME::SLASH:
			case Divine::SKILLNAME::SONIC:
			case Divine::SKILLNAME::VACUUM:
				motion = CHARACTER_MOTION::PLAYER_SKILL;
				break;
			case Divine::SKILLNAME::DASH:
				motion = CHARACTER_MOTION::PLAYER_SKILLDASH;
				break;
			}
		}
		else if (cnt > 38) { motion = CHARACTER_MOTION::PLAYER_STAND; }
	}
	return motion;
}

void Player::SkillVoice()
{
	//キー用変数初期化
	std::string voice;
	//各スキルによって設定
	for (int i = 0; i < MAX_SKILL_NUM; i++)
	{
		switch (mSkill->GetSkill(i).skillName)
		{
		//ブレス
		case Divine::SKILLNAME::BREATH:
			voice = "VO_Fe_Breath";
			break;
		//サークル
		case Divine::SKILLNAME::CIRCLE:
			voice = "VO_Fe_Circle";
			break;
		//エクスプロージョン
		case Divine::SKILLNAME::EXPLOSION:
			voice = "VO_Fe_Explosion";
			break;
		//レーザー
		case Divine::SKILLNAME::LASER:
			voice = "VO_Fe_Laser";
			break;
		//スラッシュ
		case Divine::SKILLNAME::SLASH:
			voice = "VO_Fe_Slash";
			break;
		//ダッシュ
		case Divine::SKILLNAME::DASH:
			voice = "VO_Fe_Avoid";
			break;
		//ソニックウェーブ
		case Divine::SKILLNAME::SONIC:
			voice = "VO_Fe_Slash";
			break;
		//バキューム
		case Divine::SKILLNAME::VACUUM:
			voice = "VO_Fe_Attack03";
			break;
		}
		if (mSkill->GetSkill(i).divineCnt > 0 && mSkill->GetSkill(i).divineCnt < 10)
		{
			SoundItemBase* snditem_voice = gGlobal.mSndServer.Get(voice);
			if (snditem_voice && snditem_voice->IsLoad())
			{
				//再生中でないなら
				if (!snditem_voice->IsPlay())
				{
					//再生する
					snditem_voice->Play();
				}
			}
		}
	}
}

void Player::PlayerSkill(SkillSlot* slot, VECTOR campos, VECTOR camtarget)
{
	//スロットの配列取得
	std::array<kindDivine, 3> _slot = slot->GetSlot();
	//Xボタンを押した
	if (gGlobal.gPad->GetXTrg(XINPUT_BUTTON_X))
	{
		//スロット1のスキル発動
		mSkill->Invocation(1, _slot[1]);
		//最終押下ボタンを1に
		mLastCommand = 1;
	}
	//Yボタンを押した
	if (gGlobal.gPad->GetXTrg(XINPUT_BUTTON_Y))
	{
		//スロット0のスキル発動
		mSkill->Invocation(1, _slot[0]);
		//最終押下ボタンを0に
		mLastCommand = 0;
	}
	//Aボタンを押した
	if (gGlobal.gPad->GetXTrg(XINPUT_BUTTON_A))
	{
		//スロット2のスキル発動
		mSkill->Invocation(1, _slot[2]);
		//最終押下ボタンを2に
		mLastCommand = 2;
	}
	// 向きからY軸回転を算出
	VECTOR vRot = { 0,0,0 };
	vRot.y = atan2(mDir.x * -1, mDir.z * -1);
	mDir.y = vRot.y;
	//モデルの回転値をモデルに代入
	MV1SetRotationXYZ(mModel, vRot);
	mSkill->Process(mPos, mDir.y);
	//ボイス設定
	SkillVoice();
	//各スキル
	for (int i = 0; i < MAX_SKILL_NUM; i++)
	{
		if (mSkill->GetSkill(i).divineCnt > 0 && mSkill->GetSkill(i).divineCnt < 54)
		{
			//既定のカウント時モーションを固定
			mMotion = SkillMotion();
		}
	}
	
}

void Player::Damage(VECTOR pos,int subpoint)
{
	//ダメージボイス設定
	std::string se_code_damage[3] =
	{
		"VO_Fe_Damage1",
		"VO_Fe_Damage2",
		"VO_Fe_Damage3",
	};
	//死亡ボイス設定
	std::string se_code_die[2] =
	{
		"VO_Fe_Blow1",
		"VO_Fe_Blow2"
	};
	SoundItemBase* snditem_voice= gGlobal.mSndServer.Get("");
	//体力減少
	mHp = mHp - subpoint;
	//体力が0より少ない
	if (mHp <= 0)
	{
		//モーションを死亡に
		mMotion = CHARACTER_MOTION::PLAYER_DIE;
		//ボイスを登録
		snditem_voice = gGlobal.mSndServer.Get(se_code_die[rand() % 2]);
	}
	//体力が0より多い
	if (mHp > 0)
	{
		//攻撃状態でないのなら
		if (mAttackManager->GetType() == ATTACK_TYPE::NONE)
		{
			//モーションをダメージに
			mMotion = CHARACTER_MOTION::PLAYER_DAMAGE;
			//ボイスを登録
			snditem_voice = gGlobal.mSndServer.Get(se_code_damage[rand() % 3]);
		}
	}
	
	if (snditem_voice && snditem_voice->IsLoad())
	{
		//音量設定
		snditem_voice->SetVolume(255);
		// 再生中か？
		if (snditem_voice->IsPlay() == false)
		{
			// 再生する
			snditem_voice->Play();
		}
	}
	////敵とプレイヤー位置の差を求める
	VECTOR v = VSub(mPos, pos);
	////正規化した後ベクトルを50倍に
	v = VScale(VNorm(v),50);
	//移動値にベクトルを加算
	mMove = VAdd(mMove, v);
	//位置に移動値を加算
	mPos = VAdd(mPos, mMove);
	//スキル発動状態をリセット
	mSkill->Reset();
}

void Player::PlayerDie()
{
	mNoDamage = true;
	mIsDie = true;
}

void Player::Invincible()
{
	//死亡状態でない
	if (!mIsDie)
	{
		if (mNoDamage) { mInvincibleCnt++; }
		if (mInvincibleCnt > 0 && mInvincibleCnt <= 42)
		{
			mMotion = CHARACTER_MOTION::PLAYER_DAMAGE;
		}
		if (mInvincibleCnt > 80)
		{
			mNoDamage = false;
			mInvincibleCnt = 0;
		}
	}
}

void Player::ActionProcess(VECTOR campos, VECTOR camtarget, SkillSlot* slot)
{
	//移動方向を決める
	mMove = { 0,0,0 };
	//モーションカウント取得
	int motion_cnt = mMotionManager->GetMotionCnt();
	//攻撃カウント取得
	int attack_cnt = mAttackManager->GetAttackCount();
	//カウント最大値取得
	int motioncnt_max = mMotionManager->GetMaxCnt();
	//モーションごとにスキル発動可能フラグ取得
	bool skill = mMotionManager->GetTable()->GetItem()[motion_cnt].GetIsSkill();
	//モーションごとに回避可能フラグ取得
	bool avoid = mMotionManager->GetTable()->GetItem()[motion_cnt].GetIsAvoid();
	//各モーション別処理
	switch (mMotionManager->GetMotion())
	{
	//待機
	case CHARACTER_MOTION::PLAYER_STAND:
		if (mAttackManager->GetIsChange()) { mMotion = CHARACTER_MOTION::PLAYER_FIRSTATTACK; }
		break;
	//走り
	case CHARACTER_MOTION::PLAYER_RUN:
		if (mAttackManager->GetIsChange()) { mMotion = CHARACTER_MOTION::PLAYER_DASHATTACK; }
		break;
	//連続攻撃1撃目
	case CHARACTER_MOTION::PLAYER_FIRSTATTACK:
		if (mAttackManager->GetIsChange()) { mMotion = CHARACTER_MOTION::PLAYER_SECONDATTACK; }
		break;
	//連続攻撃2撃目
	case CHARACTER_MOTION::PLAYER_SECONDATTACK:
		if (mAttackManager->GetIsChange()) { mMotion = CHARACTER_MOTION::PLAYER_LASTATTACK; }
		break;
	//連続攻撃3撃目
	case CHARACTER_MOTION::PLAYER_LASTATTACK:
		break;
	//ダッシュ攻撃
	case CHARACTER_MOTION::PLAYER_DASHATTACK:
		if (mAttackManager->GetIsChange()) { mMotion = CHARACTER_MOTION::PLAYER_SECONDATTACK; }
		break;
	//スキル発動
	case CHARACTER_MOTION::PLAYER_SKILL:
		break;
	//スキル発動(ダッシュ)
	case CHARACTER_MOTION::PLAYER_SKILLDASH:
		break;
	//回避
	case CHARACTER_MOTION::PLAYER_AVOID:
		if (motion_cnt >= motioncnt_max - 1) { mAvoidFlag = false; }
		break;
	//ダメージ
	case CHARACTER_MOTION::PLAYER_DAMAGE:
		break;
	//死亡
	case CHARACTER_MOTION::PLAYER_DIE:
		if (motion_cnt >= motioncnt_max-1)
		{

			mGameOverFlag = true;
		}
		break;
	}
	//攻撃時の声とseを再生する
	if (mAttackManager->GetType() != ATTACK_TYPE::NONE)
	{
		if (attack_cnt == 1)
		{
			//モーションテーブルから再生用の声とseのキーを取得する
			SoundItemBase* snditem_voice = gGlobal.mSndServer.Get(mAttackManager->GetTable()->GetVoiceName());
			SoundItemBase* snditem_se = gGlobal.mSndServer.Get(mAttackManager->GetTable()->GetSeName());
			//音量設定
			snditem_voice->SetVolume(255);
			snditem_se->SetVolume(255);
			// 再生中でないなら
			if (snditem_voice->IsPlay() == false)
			{
				// 再生する
				snditem_voice->Play();
			}
			// 再生中でないなら
			if (snditem_se->IsPlay() == false)
			{
				// 再生する
				snditem_se->Play();
			}
		}
	}
	//カウントが規定値に達した
	if (motion_cnt >= motioncnt_max - 1)
	{
		//ループさせないモーションの場合、待機状態に
		if (mMotionManager->GetTable()->GetEndType() == MotionTable::MOTION_ENDTYPE::END) 
		{ 
			mMotion = CHARACTER_MOTION::PLAYER_STAND; 
		}
	}
	//スキル発動可能ならスキルに関するプロセスを回せるように
	if (skill) { PlayerSkill(slot, campos, camtarget); }
	//回避トリガボタンが押された
	if (gGlobal.gPad->GetXLt())
	{
		//回避可能の状態なら
		if(avoid)
		{
			//回避フラグをtrueに
			mAvoidFlag = true;
			//モーションを変更
			mMotion = CHARACTER_MOTION::PLAYER_AVOID;
		}
	}
	//キャラ移動(カメラ設定に合わせて)
	float dir = atan2(-gGlobal.gPad->GetXLy(), -gGlobal.gPad->GetXLx());
	//カメラの向いている角度を取得
	float com_dir_y = Camera::GetInstance()->GetDir().y;
	MATRIX matrix = MGetRotY(com_dir_y);
	//走る速度の設定
	float mvspeed = mMotionManager->GetTable()->GetItem()[motion_cnt].GetVelocity().z;
	float len = 0.f;
	//アナログパッドが傾いているときのみ移動値を加算
	if (gGlobal.gPad->IsInputStickLeft())
	{
		len = mvspeed;
	}
	mMove.x = len * cos(dir);
	mMove.z = len * sin(dir);
	//vの分移動
	mMove = VTransform(mMove, matrix);
	mPos = VAdd(mPos, mMove);
	mPos.y += mGravity;
	//移動量をそのままキャラの向きにする
	int layer = static_cast<int>(mMotionManager->GetMotionList().at(static_cast<int>(mMotion)).second->GetLayer());
	if (layer <= static_cast<int>(MOTION_LAYER::PRESS_DOWN))
	{
		// 移動していない時は無視するため
		if (gGlobal.gPad->IsInputStickLeft())
		{
			//プレイヤーのモーションを「RUN」に変更
			if (mMotion != CHARACTER_MOTION::PLAYER_SKILLDASH) { mMotion = CHARACTER_MOTION::PLAYER_RUN; }
		}
		else
		{
			// プレイヤーのモーションを「STAND」に変更
			mMotion = CHARACTER_MOTION::PLAYER_STAND;
		}
	}
	bool ischangecourse = mMotionManager->GetTable()->GetItem()[motion_cnt].GetIsChangeCourse();
	//方向転換フラグがtrueなら
	if (ischangecourse)
	{
		//移動量が0でないなら加算
		if (VSize(mMove) != 0){ mDir = mMove; }
	}
	//y座標固定
	if (mPos.y <= 0) { mPos.y = 0; }
	//向き設定
	VECTOR vrot = { 0,0,0 };
	vrot.y = atan2(mDir.x * -1, mDir.z * -1);
	mDir.y = vrot.y;
	//モデル位置更新
	MV1SetPosition(mModel, mPos);
	//モデル回転更新
	MV1SetRotationXYZ(mModel, vrot);
	Invincible();
	//武器設定
	SetWeapon();
	//当たり判定用線分処理
	C_Process();
}

void Player::C_Process() 
{
	//判定カプセルの更新
	mCapsule[0] = mPos;
	mCapsule[1] = VAdd(mPos, VGet(0, mLineSeg, 0));
}

void Player::Process(VECTOR campos, VECTOR camtarget, SkillSlot* slot)
{
	//挙動処理全般
	ActionProcess(campos, camtarget, slot);
	//アニメーション処理
	A_Process();
	//マネージャーフレーム毎処理
	mMotionManager->Process();
	mAttackManager->Process();
}

void Player::Render() 
{
	mSkill->Render();
	// モデルを描画する
	MV1DrawModel(mModel);
	MV1DrawModel(mWModel);
}