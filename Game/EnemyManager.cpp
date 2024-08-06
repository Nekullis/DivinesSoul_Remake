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
	//�w�肳�ꂽ�l�̗v�f��S�č폜����B
	mEemyList.remove(enemy);
	delete enemy;
}
void EnemyManager::Process(VECTOR pl_pos)
{
	//�ꎞ�I�ȏ������邽�߂̃R���e�i���쐬
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
	// �폜�t���O���������G�l�~�[���R���e�i����폜����
	for (auto&& enemy : temp_enemies_to_remove)
	{
		Destroy(enemy);
	}
}

void EnemyManager::Render()
{
	//�G���R���e�i���ɂ��鐔�`�悷��
	for (auto&& enemy : mEemyList)
	{
		enemy->Render();
	}
}




