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
	//�e�[�u��������
	MotionTable* table = new MotionTable();
	CFile file(filename);
	if (file.Success())
	{
		//�o�C�g���Z�p���[�J���ϐ�
		int c = 0;
		//�t�@�C���f�[�^�擾
		const char* p = (const char*)file.Data();
		//�t�@�C���T�C�Y�擾
		int size = file.Size();
		//�T�C�Y�O�ɂȂ�܂Ń��[�v
		while (c < size)
		{
			//���[�V�����e�[�u���̃A�C�e���ɕK�v�ȃ��[�J���ϐ�������
			int id = 0;
			float velocity[3] = { 0 };
			int type = 0;
			int isskill = 0;
			int iscourse = 0;
			int isavoid = 0;
			//�t�@�C���̏ォ��','�A�󔒁A�R���g���[���R�[�h�𖳎����Ȃ���v�f���擾
			c += GetDecNum(&p[c], &id);
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &velocity[0]);
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &velocity[1]);
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &velocity[2]);
			c += FindString(&p[c], ',', &p[size]); c++; c += GetDecNum(&p[c], &type);
			c += FindString(&p[c], ',', &p[size]); c++; c += GetDecNum(&p[c], &isskill);
			c += FindString(&p[c], ',', &p[size]); c++; c += GetDecNum(&p[c], &iscourse);
			c += FindString(&p[c], ',', &p[size]); c++; c += GetDecNum(&p[c], &isavoid);
			c += SkipSpace(&p[c], &p[size]);
			//���[�V�����e�[�u���̃A�C�e��������
			MotionTableItem stand = { id,velocity[0],velocity[1],velocity[2],static_cast<ATTACK_TYPE>(type),static_cast<bool>(isskill),static_cast<bool>(iscourse),static_cast<bool>(isavoid) };
			//�A�C�e�����e�[�u���ɒǉ�
			table->AddItem(stand);
		}
		table->SetEndType(endtype);
		table->SetLayer(layer);
		//�}�l�[�W���[�Ƀe�[�u���ǉ�
		AddTable(motion, std::move(table));
	}

}

void MotionTableManager::ChangeMotion(CHARACTER_MOTION motion)
{
	//�^�ϊ�
	int i = static_cast<int>(motion);
	//�v�f��T��
	auto itr = mMotionList.find(i);
	//�����ꂽ��ύX
	if (itr != mMotionList.end())
	{
		mTable = itr->second.second;
		mMotion = motion;
		//�ő�J�E���g���e�[�u���̑��v�f����
		mCountMax = mTable->GetItem().size();
		mMotionCnt = 0;
	}
}

void MotionTableManager::Process()
{
	//�J�E���g���ő�Ŗ�����Ή��Z
	mMotionCnt++;
	//�J�E���g���K�萔�ɒB�����烊�Z�b�g
	if (mMotionCnt >= mCountMax) { mMotionCnt = 0; }
	//�U���}�l�[�W���̕ύX�t���O���擾
	bool change = AttackTableManager::GetInstance()->GetIsChange();
	//�ύX�\�Ȃ�
	if (change)
	{
		//�e���[�V�����ōU���\�Ȃ�U������ύX����
		ATTACK_TYPE type = mTable->GetItem()[mMotionCnt].GetTrgAttack();
		if (type != ATTACK_TYPE::NONE)
		{
			AttackTableManager::GetInstance()->AttackChange(type);
		}
	}

}
