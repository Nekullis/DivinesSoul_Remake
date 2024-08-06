#include "GameEvent.h"
#include "ApplicationGlobal.h"
GameEvent* GameEvent::_evInstance = nullptr;
GameEvent::GameEvent()
{
	_evInstance = this;
	//クラス初期化
	mEnManager = new EnemyManager();
	//敵、武器モデル
	mHandle[0] = gGlobal.mGetModel()["EN_Osero"]._handle;
	mHandle[1] = gGlobal.mGetModel()["EN_Crab"]._handle;
	mHandle[2] = gGlobal.mGetModel()["EN_Romanoff"]._handle;
	mWeaponModel[0] = gGlobal.mGetModel()["W_Sword"]._handle;
	mWeaponModel[1] = gGlobal.mGetModel()["W_Axe"]._handle;
	//イベントUI
	mHandleQuestFeld[0] = gGlobal.mGetGraph()["UI_Feld_Quest_01"]._handle;
	mHandleQuestFeld[1] = gGlobal.mGetGraph()["UI_Feld_Quest_02"]._handle;
	mHandleQuestFeld[2] = gGlobal.mGetGraph()["UI_Feld_Quest_03"]._handle;
	mHandleQuestFeld[3] = gGlobal.mGetGraph()["UI_Feld_Quest_04"]._handle;
	mHandleQuestFeld[4] = gGlobal.mGetGraph()["UI_Feld_Quest_05"]._handle;
	mHandleQuestFeld[5] = gGlobal.mGetGraph()["UI_Feld_Quest_06"]._handle;
	mHandleQuestFeld[6] = gGlobal.mGetGraph()["UI_Feld_Quest_07"]._handle;
	mHandleQuestFeld[7] = gGlobal.mGetGraph()["UI_Feld_Quest_08"]._handle;
	mHandleQuestFeld[8] = gGlobal.mGetGraph()["UI_Feld_Quest_09"]._handle;
	mHandleQuestFeld[9] = gGlobal.mGetGraph()["UI_Feld_Quest_10"]._handle;
	mHandleQuestFeld[10] = gGlobal.mGetGraph()["UI_Feld_Quest_11"]._handle;
	mHamdleQuestRomanoff[0] = gGlobal.mGetGraph()["UI_Romanoff_Quest_01"]._handle;
	mHamdleQuestRomanoff[1] = gGlobal.mGetGraph()["UI_Romanoff_Quest_02"]._handle;
	mHamdleQuestRomanoff[2] = gGlobal.mGetGraph()["UI_Romanoff_Quest_03"]._handle;
	mHamdleQuestRomanoff[3] = gGlobal.mGetGraph()["UI_Romanoff_Quest_04"]._handle;
	mHamdleQuestRomanoff[4] = gGlobal.mGetGraph()["UI_Romanoff_Quest_05"]._handle;
	mHamdleQuestRomanoff[5] = gGlobal.mGetGraph()["UI_Romanoff_Quest_06"]._handle;
	mHamdleQuestRomanoff[6] = gGlobal.mGetGraph()["UI_Romanoff_Quest_07"]._handle;
	//wave番号
	mInitNum = 0;
	mQuestNum = -1;
	mDivineEv = 0;
	//初期wave
	EnemyWaveInit(mInitNum);
	//イベント用
	mStoryEv = 0;
	mWaveEv = 0;
	mHpEv = -1;
	mHpCast = 3000;
	RegisterEvent();

}
GameEvent::~GameEvent()
{

}

bool GameEvent::GameOver()
{
	if (gGlobal.mPM->P_GetDie())
	{
		int begin_game_over_time = 180;
		while (1)
		{
			begin_game_over_time--;
			if (begin_game_over_time <= 0) { break; }
		}
		if (begin_game_over_time <= 0) { return true; }
	}
	return false;
}

bool GameEvent::GameClear(EN_Romanoff* en)
{
	if (mStoryEv >= 1)
	{
		if (en->GetDeleteFlag())
		{
			int begin_game_over_time = 120;
			while (1)
			{
				begin_game_over_time--;
				if (begin_game_over_time <= 0) { break; }
			}
			if (begin_game_over_time <= 0) { return true; }
		}
	}
	return false;
}

void GameEvent::RegisterEvent()
{	//イベント構造体の作成
	EVENT ev[MAX_EVENT_NUM] =
	{
		{mHandleQuestFeld[0],	  0, 150, false, "VO_Fe_Quest_01"},
		{mHandleQuestFeld[1],	  0, 300, false, "VO_Fe_Quest_02"},
		{mHandleQuestFeld[2],	  0, 180, false, "VO_Fe_Quest_03"},
		{mHandleQuestFeld[3],	  0, 300, false, "VO_Fe_Quest_04"},
		{mHandleQuestFeld[4],	  0, 480, false, "VO_Fe_Quest_05"},
		{mHandleQuestFeld[5],	  0, 180, false, "VO_Fe_Quest_06"},
		{mHandleQuestFeld[6],	  0, 300, false, "VO_Fe_Quest_07"},
		{mHandleQuestFeld[7],	  0, 360, false, "VO_Fe_Quest_08"},
		{mHandleQuestFeld[8],	  0, 300, false, "VO_Fe_Quest_09"},
		{mHandleQuestFeld[9],	  0, 120, false, "VO_Fe_Quest_10"},
		{mHandleQuestFeld[10],	  0, 120, false, "VO_Fe_Quest_11"},
		{mHamdleQuestRomanoff[0], 0, 300, false, "VO_Ro_Quest_01"},
		{mHamdleQuestRomanoff[1], 0, 480, false, "VO_Ro_Quest_02"},
		{mHamdleQuestRomanoff[2], 0, 480, false, "VO_Ro_Quest_03"},
		{mHamdleQuestRomanoff[3], 0, 480, false, "VO_Ro_Quest_04"},
		{mHamdleQuestRomanoff[4], 0, 480, false, "VO_Ro_Quest_05"},
		{mHamdleQuestRomanoff[5], 0, 600, false, "VO_Ro_Quest_06"},
		{mHamdleQuestRomanoff[6], 0, 900, false, "VO_Ro_Quest_07"},
	};
	for (int i = 0; i < MAX_EVENT_NUM; i++)
	{	//メンバ変数に移動
		mEvent[i] = std::move(ev[i]);
	}
}

bool GameEvent::WaveNum(int i)
{	//waveに関するイベント番号
	if (i == 2 || i == 3 || i == 4 || i == 5 || i == 6)
	{
		return true;
	}
	return false;
}

bool GameEvent::StoryNum(int i)
{	//ストーリーに関するイベント番号
	if (i == 7 || i == 8 || i == 11 || i == 12 || i == 13 || i == 14)
	{
		return true;
	}
	return false;
}

bool GameEvent::DivineNum(int i)
{	//ディバインに関するイベント番号
	if (i == 0 || i == 1)
	{
		return true;
	}
	return false;
}

void GameEvent::OccurEvent(int i)
{	//イベント発生
	//番号の代入
	mQuestNum = i;
	//イベント発生中なのでtrueに
	mEvent[mQuestNum].isOccur = true;
	//その番号のボイスを代入
	SoundItemBase* snditem_voice = gGlobal.mSndServer.Get(mEvent[mQuestNum].voiceCode);
	//音量調整
	snditem_voice->SetVolume(255);
	if (mEvent[mQuestNum].eventCnt <= 10)
	{
		if (snditem_voice && snditem_voice->IsLoad())
		{	// 再生中でないなら
			if (snditem_voice->IsPlay() == false)
			{	// 再生する
				snditem_voice->Play();
			}
		}
	}
}

void GameEvent::OccurProcess()
{	//番号が初期値でない
	if (mQuestNum != -1)
	{	//イベント発生中ならその番号のイベントカウントを加算
		if (mEvent[mQuestNum].isOccur) { mEvent[mQuestNum].eventCnt++; }
		//イベントカウントが規定値まで達した
		if (mEvent[mQuestNum].eventCnt >= mEvent[mQuestNum].maxEventCnt)
		{	//発生終了したのでfalseに
			mEvent[mQuestNum].isOccur = false;
			//カウントリセット
			mEvent[mQuestNum].eventCnt = 0;
			//番号を代入
			int old_num = mQuestNum;
			//番号初期化
			mQuestNum = -1;
			//各イベントカウントの加算
			if (WaveNum(old_num))
			{
				mWaveEv++;
			}
			if (StoryNum(old_num))
			{
				mStoryEv++;
			}
			if (DivineNum(old_num))
			{
				mDivineEv++;
			}
		}
	}
}

void GameEvent::EnemyWaveInit(int i)
{
	//キー
	std::string wave[6] =
	{
		"Enemy_Wave1",
		"Enemy_Wave2",
		"Enemy_Wave3",
		"Enemy_Wave4",
		"Enemy_Wave5",
		"Enemy_Wave8",
	};
	//位置
	VECTOR pos = VGet(0, 0, 0);
	//角度
	VECTOR dir = VGet(0, 0, 0);
	//jsonの初期化
	JsonUtility* jUtil;
	jUtil = new JsonUtility();
	//jsonのインポート
	nlohmann::json enemy_pos = jUtil->Import("res/Json/Enemy_pos.json").at(wave[i]);
	//インポートされた敵の位置の分繰り返す
	for (auto& data : enemy_pos)
	{
		std::string name;
		//名前の取得
		data.at("objectName").get_to(name);
		//座標を各要素で取得
		data.at("translate").at("x").get_to(pos.x);
		data.at("translate").at("z").get_to(pos.y);
		data.at("translate").at("y").get_to(pos.z);
		data.at("rotate").at("x").get_to(dir.x);
		data.at("rotate").at("z").get_to(dir.y);
		data.at("rotate").at("y").get_to(dir.z);
		dir.x = Math::DegToRad(dir.x);	// 回転はdegree→radianに
		dir.y = Math::DegToRad(dir.y);
		dir.z = Math::DegToRad(dir.z);
		//UE5では座標系が違うので変換する
		pos.z *= -1;
		//取得した名前でスポーンさせる敵を変える
		if (name == "EN_Osero")
		{	//oseroのスポーン
			mEnManager->Spawn(new EN_Osero(mHandle[0], mWeaponModel[0], pos, dir));
		}
		else if (name == "EN_Crab")
		{	//crabのスポーン
			mEnManager->Spawn(new EN_Crab(mHandle[1], -1, pos, dir));
		}
		else if (name == "EN_Romanoff")
		{	//romanoffのスポーン
			mEnManager->Spawn(new EN_Romanoff(mHandle[2], mWeaponModel[1], pos, dir));
		}
	}
}

void GameEvent::WaveProcess()
{
	//スポーンするための敵を格納しているコンテナを取得
	std::list<Enemy*> list = mEnManager->GetEnemyList();
	//マネージャーのプロセスを実行
	mEnManager->Process(gGlobal.mPM->P_GetPos());
	//敵の数が0になった
	if (list.size() <= 0)
	{
		//wave番号を更新
		mInitNum++;
		if (mStoryEv == 0)
		{
			mWaveEv++;
		}
		//wavw番号がwave変化可能数内
		if (mInitNum < MAX_SPAWN_WAVE)
		{	//waveを更新する
			EnemyWaveInit(mInitNum);
		}
	}
}

void GameEvent::EventProcess()
{
	OccurProcess();
	//waveに関するイベント番号
	switch (mWaveEv)
	{
	case 0:
		OccurEvent(2);
		break;
	case 2:
		OccurEvent(3);
		break;
	case 4:
		OccurEvent(4);
		break;
	case 6:
		OccurEvent(5);
		break;
	case 8:
		OccurEvent(6);
		break;
	}
	//ストーリーに関するイベント番号
	switch (mStoryEv)
	{
	case 1:
		OccurEvent(11);
		break;
	case 2:
		OccurEvent(7);
		break;
	case 4:
		OccurEvent(12);
		break;
	case 5:
		OccurEvent(13);
		break;
	case 6:
		OccurEvent(8);
		break;
	case 7:
		OccurEvent(14);
		break;
	}
	//ディバインに関するイベント番号
	switch (mDivineEv)
	{
	case 1:
		OccurEvent(0);
		break;
	case 2:
		OccurEvent(1);
		break;
	}

}

void GameEvent::CastEnemy(int i)
{
	std::string cast[3] =
	{
		"Boss_Cast_Wave1",
		"Boss_Cast_Wave2",
		"Boss_Cast_Wave3",
	};
	//位置
	VECTOR pos = VGet(0, 0, 0);
	//角度
	VECTOR dir = VGet(0, 0, 0);
	//jsonの初期化
	JsonUtility* jUtil;
	jUtil = new JsonUtility();
	//jsonのインポート
	nlohmann::json enemy_pos = jUtil->Import("res/Json/Boss_Cast_Enemy.json").at(cast[i]);
	//インポートされた敵の位置の分繰り返す
	for (auto& data : enemy_pos)
	{
		std::string name;
		//名前の取得
		data.at("objectName").get_to(name);
		//座標を各要素で取得
		data.at("translate").at("x").get_to(pos.x);
		data.at("translate").at("z").get_to(pos.y);
		data.at("translate").at("y").get_to(pos.z);
		data.at("rotate").at("x").get_to(dir.x);
		data.at("rotate").at("z").get_to(dir.y);
		data.at("rotate").at("y").get_to(dir.z);
		dir.x = Math::DegToRad(dir.x);	// 回転はdegree→radianに
		dir.y = Math::DegToRad(dir.y);
		dir.z = Math::DegToRad(dir.z);
		//UE5では座標系が違うので変換する
		pos.z *= -1;
		//取得した名前でスポーンさせる敵を変える
		if (name == "EN_Osero")
		{	//oseroのスポーン
			mEnManager->Spawn(new EN_Osero(mHandle[0], mWeaponModel[0], pos, dir));
		}
		else if (name == "EN_Crab")
		{	//crabのスポーン
			mEnManager->Spawn(new EN_Crab(mHandle[1], -1, pos, dir));
		}
	}
}

void GameEvent::CastProcess()
{
	//ストーリーに関するイベント番号が0以上
	if (mStoryEv >= 1)
	{	//ボスの体力比較用変数が規定値以上
		if (mHpCast >= 1000)
		{	//ボスの体力が比較変数値より小さい
			if (EN_Romanoff::GetInstance()->GetHp() <= mHpCast)
			{	//hpイベント加算
				mHpEv++;
				//敵の召喚
				CastEnemy(mHpEv);
				//体力比較変数が規定値
				if (mHpCast == 2000)
				{	//ストーリーイベント加算
					mStoryEv++;
				}
				//比較用変数を減少
				mHpCast -= 1000;
			}
		}
	}

}

void GameEvent::Process()
{
	//敵召喚に関する処理
	CastProcess();
	//イベントに関する処理
	EventProcess();
	//ウェーブに関する処理
	WaveProcess();
}

void GameEvent::DrawQuest()
{
	if (mQuestNum != -1)
	{	//イベント発生中なら
		if (mEvent[mQuestNum].isOccur)
		{	//画像表示
			DrawGraph(0, 0, mEvent[mQuestNum].handleUI, TRUE);
		}
	}
}

void GameEvent::DrawWave()
{	//waveの文字描写用ハンドル
	int cg_wave = gGlobal.mRS->mGetGraph()["UI_wave"]._handle;
	//現wave数描写用ハンドル
	int cg_wave_num = gGlobal.mRS->mGetDivGraph()["wave_number"].handle[mInitNum + 1];
	int cg_wave_slash = gGlobal.mRS->mGetGraph()["wave_slash"]._handle;
	///最大wave数描写用ハンドル
	int cg_wave_max = gGlobal.mRS->mGetDivGraph()["wave_number"].handle[MAX_SPAWN_WAVE];
	DrawGraph(30, 196, cg_wave, true);
	DrawGraph(55, 270, cg_wave_num, true);
	DrawGraph(100, 300, cg_wave_slash, true);
	DrawGraph(130, 330, cg_wave_max, true);
}

void GameEvent::DrawEventUI()
{
	DrawQuest();
	DrawWave();
}

void GameEvent::Render()
{
	//敵の描写
	mEnManager->Render();

}