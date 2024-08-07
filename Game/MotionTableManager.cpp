#include "MotionTableManager.h"
#include "AttackTableManager.h"
#include "appframe.h"
#include "Player.h"

MotionTableManager* MotionTableManager::mMotTableInstance = nullptr;
MotionTableManager::MotionTableManager()
{
	mMotTableInstance	= this;
	mMotionCnt			= 0;
	mCountMax			= 0;
	mTable				= new MotionTable;
	mMotion				= CHARACTER_MOTION::PLAYER_STAND;
	mLayer				= MOTION_LAYER::ALWAYS;
}

MotionTableManager::~MotionTableManager()
{
	delete mTable;
}

void MotionTableManager::AddTable(CHARACTER_MOTION motionID, MotionTable* table)
{
	int id = static_cast<int>(motionID);
	mMotionList.emplace(id, std::make_pair(table->GetEndType(), table));
}

void MotionTableManager::LoadTable(const std::string& filename, CHARACTER_MOTION motion, MotionTable::MOTION_ENDTYPE endtype, MOTION_LAYER layer)
{
	//テーブル初期化
	MotionTable* table = new MotionTable();
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
			float velocity[3] = { 0 };
			int type = 0;
			int isskill = 0;
			int iscourse = 0;
			int isavoid = 0;
			//ファイルの上から','、空白、コントロールコードを無視しながら要素を取得
			c += GetDecNum(&p[c], &id);
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &velocity[0]);
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &velocity[1]);
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &velocity[2]);
			c += FindString(&p[c], ',', &p[size]); c++; c += GetDecNum(&p[c], &type);
			c += FindString(&p[c], ',', &p[size]); c++; c += GetDecNum(&p[c], &isskill);
			c += FindString(&p[c], ',', &p[size]); c++; c += GetDecNum(&p[c], &iscourse);
			c += FindString(&p[c], ',', &p[size]); c++; c += GetDecNum(&p[c], &isavoid);
			c += SkipSpace(&p[c], &p[size]);
			//モーションテーブルのアイテム初期化
			MotionTableItem stand = { id,velocity[0],velocity[1],velocity[2],static_cast<ATTACK_TYPE>(type),static_cast<bool>(isskill),static_cast<bool>(iscourse),static_cast<bool>(isavoid) };
			//アイテムをテーブルに追加
			table->AddItem(stand);
		}
		table->SetEndType(endtype);
		table->SetLayer(layer);
		//マネージャーにテーブル追加
		AddTable(motion, std::move(table));
	}

}

void MotionTableManager::ChangeMotion(CHARACTER_MOTION motion)
{
	//型変換
	int i = static_cast<int>(motion);
	//要素を探す
	auto itr = mMotionList.find(i);
	//見つけれたら変更
	if (itr != mMotionList.end())
	{
		mTable = itr->second.second;
		mMotion = motion;
		//最大カウントをテーブルの総要素数に
		mCountMax = mTable->GetItem().size();
		mMotionCnt = 0;
	}
}

void MotionTableManager::Process()
{
	//カウントが最大で無ければ加算
	mMotionCnt++;
	//カウントが規定数に達したらリセット
	if (mMotionCnt >= mCountMax) { mMotionCnt = 0; }
	//攻撃マネージャの変更フラグを取得
	bool change = AttackTableManager::GetInstance()->GetIsChange();
	//変更可能なら
	if (change)
	{
		//各モーションで攻撃可能なら攻撃情報を変更する
		ATTACK_TYPE type = mTable->GetItem()[mMotionCnt].GetTrgAttack();
		if (type != ATTACK_TYPE::NONE)
		{
			AttackTableManager::GetInstance()->AttackChange(type);
		}
	}

}
