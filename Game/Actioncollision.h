#pragma once
#include "PlayerManager.h"
#include "EnemyManager.h"
#include "EN_Osero.h"
#include "EN_Crab.h"
#include "divine.h"
#include "MathCollision.h"
#include <cmath>
#include <list>
class ActionCollision
{
public:
	ActionCollision();
	virtual ~ActionCollision();
	bool Process			(Player* pl, EnemyManager* _enemy);
	//�L�����ƃ}�b�v�̉����o��
	bool MapColProcess		(Player* pl, EnemyManager* _enemy);
	//�e�����o���֐��̂܂Ƃ�
	bool ActionColProcess	(Player* pl, EnemyManager* _enemy);
	//�X�L����p��������̏���
	bool DivineColProcess	(Player* pl, EnemyManager* _enemy);
	//�}�b�v�����o������
	bool MapColPlayer		(Player* pl);
	//player��enemy�̉����o���A�U�����菈��
	bool PtoEColProcess		(Player* pl, EnemyManager* _enemy);
	//enemy���m�̉����o������
	bool EntoEnColProcess	(EnemyManager* _enemy);
	//�X�L���̓����蔻��̊e�֐�
	bool DivineColCircle	(VECTOR p_pos, float p_r, VECTOR e_pos, float e_r);
	bool DivineColBreath	(VECTOR p_pos, VECTOR p_fvec, VECTOR e_pos, float cos);
	bool DivineColLaser		(VECTOR p_s_pos, VECTOR p_e_pos, float p_r, VECTOR e_s_pos, VECTOR e_e_pos, float e_r);
	bool DivineColSlash		(VECTOR p_pos, float p_r, VECTOR e_pos, float e_r);
	bool DivineColExplosion	(VECTOR p_s_pos, VECTOR p_e_pos, float p_r, VECTOR e_s_pos, VECTOR e_e_pos, float e_r);
	bool DivineColDash		(VECTOR p_s_pos, VECTOR p_e_pos, float p_r, VECTOR e_s_pos, VECTOR e_e_pos, float e_r);
	bool DivineColVacuum	(VECTOR p_pos, VECTOR p_fvec, VECTOR e_pos, float cos);
	bool DivineColSonic		(VECTOR p_pos, float p_r, VECTOR e_pos, float e_r);
protected:
	//�X�L���ƃJ�v�Z���̍ŒZ����
	float mDisDivinetoCap;
	//�X�e�[�W���f��
	int mStageModel;
	//�S�̂̍U��ID
	int mAttackID;
};

