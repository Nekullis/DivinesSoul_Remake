#include "EnemyManager.h"
#include "ApplicationMain.h"
EnemyManager::EnemyManager()
{
	mCombo = 0;
}
EnemyManager::~EnemyManager()
{

}

void EnemyManager::Spawn(Enemy* enemy)
{
	mEemyList.push_back(enemy);
}

void EnemyManager::Destroy(Enemy* enemy)
{
	//指定された値の要素を全て削除する。
	mEemyList.remove(enemy);
	delete enemy;
}
void EnemyManager::Process(VECTOR pl_pos)
{
	//一時的な消去するためのコンテナを作成
	std::list<Enemy*> temp_enemies_to_remove;
	for (auto&& enemy : mEemyList)
	{
		enemy->Process(pl_pos);
		if (enemy->GetDeleteFlag())
		{
			mCombo++;
			temp_enemies_to_remove.push_back(enemy);
		}
	}
	// 削除フラグが立ったエネミーをコンテナから削除する
	for (auto&& enemy : temp_enemies_to_remove)
	{
		Destroy(enemy);
	}
}

void EnemyManager::Render()
{
	//敵をコンテナ内にいる数描画する
	for (auto&& enemy : mEemyList)
	{
		enemy->Render();
	}
}




