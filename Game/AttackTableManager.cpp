#include "AttackTableManager.h"
#include "ApplicationGlobal.h"
#include "appframe.h"

AttackTableManager* AttackTableManager::mAtkManagerInstance = nullptr;
AttackTableManager::AttackTableManager()
{
	mAtkManagerInstance = this;
	mAttackList.clear();
	mType = ATTACK_TYPE::NONE;
	mIsTrg = false;
	mIsChange = false;
	mAttackCnt = 0;
	mCountMax = 0;
	mTable = new AttackTable();
}

AttackTableManager::~AttackTableManager()
{
	mAttackList.clear();
	delete mTable;
}

void AttackTableManager::LoadAttackData(const std::string& filename, ATTACK_TYPE type, std::string voicename, std::string sename)
{
	//テーブル初期化
	AttackTable* table = new AttackTable();
	CFile file(filename);
	if (file.Success())
	{
		//バイト加算用ローカル変数
		int c = 0;
		//ファイルデータ取得
		const char* p = (const char*)file.Data();
		//ファイルサイズ取得
		int size = file.Size();
		//サイズ外になるまでループ
		while (c < size)
		{
			//モーションテーブルのアイテムに必要なローカル変数初期化
			int id = 0;
			int istrg = 0;
			int ischange = 0;
			int iscol = 0;
			//ファイルの上から','、空白、コントロールコードを無視しながら要素を取得
			c += GetDecNum(&p[c], &id);
			c += FindString(&p[c], ',', &p[size]); c++; c += GetDecNum(&p[c], &istrg);
			c += FindString(&p[c], ',', &p[size]); c++; c += GetDecNum(&p[c], &ischange);
			c += FindString(&p[c], ',', &p[size]); c++; c += GetDecNum(&p[c], &iscol);
			c += SkipSpace(&p[c], &p[size]);
			//モーションテーブルのアイテム初期化
			AttackTableItem stand = { id, static_cast<bool>(istrg), static_cast<bool>(ischange), static_cast<bool>(iscol) };
			//アイテムをテーブルに追加
			table->AddItem(stand);
		}
		table->SetVoiceName(voicename);
		table->SetSeName(sename);
		//マネージャーにテーブル追加
		AddTable(type, std::move(table));
	}
}

void AttackTableManager::AddTable(ATTACK_TYPE type, AttackTable* table)
{
	int i = static_cast<int>(type);
	mAttackList[i] = table;
}

void AttackTableManager::AttackChange(ATTACK_TYPE type)
{
	//型変換
	int i = static_cast<int>(type);
	//要素を探す
	auto itr = mAttackList.find(i);
	//見つけれたら変更
	if (itr != mAttackList.end()) 
	{
		mAttackCnt = 0;
		mTable = itr->second;
		mCountMax = mTable->GetItem().size();
		//変更後の攻撃タイプも保存
		mType = type;
		//各値初期化
		mIsChange = false;
		mIsTrg = false;
	}
}

void AttackTableManager::Process()
{
	//カウント加算
	mAttackCnt++;
	//カウントが最大値より大きくなったら攻撃していない状態に
	if (mAttackCnt >= mCountMax) 
	{ 
		AttackChange(ATTACK_TYPE::NONE);
	}
	//カウント時の入力可能かのフラグを取得
	bool istrg = mTable->GetItem()[mAttackCnt].GetIsTrg();
	//トリガボタンを入力しているとき
	if (gGlobal.gPad->GetXTrg(XINPUT_BUTTON_B))
	{
		//入力可能フラグがtrueならtrue
		if (istrg) { mIsTrg = true; }
	}
	//トリガ入力と攻撃変更可能かのフラグで論理積を求める
	mIsChange = mIsTrg && mTable->GetItem()[mAttackCnt].GetIsChangeAttack();
}


