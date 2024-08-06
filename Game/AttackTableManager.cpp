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
	//�e�[�u��������
	AttackTable* table = new AttackTable();
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
			int istrg = 0;
			int ischange = 0;
			int iscol = 0;
			//�t�@�C���̏ォ��','�A�󔒁A�R���g���[���R�[�h�𖳎����Ȃ���v�f���擾
			c += GetDecNum(&p[c], &id);
			c += FindString(&p[c], ',', &p[size]); c++; c += GetDecNum(&p[c], &istrg);
			c += FindString(&p[c], ',', &p[size]); c++; c += GetDecNum(&p[c], &ischange);
			c += FindString(&p[c], ',', &p[size]); c++; c += GetDecNum(&p[c], &iscol);
			c += SkipSpace(&p[c], &p[size]);
			//���[�V�����e�[�u���̃A�C�e��������
			AttackTableItem stand = { id, static_cast<bool>(istrg), static_cast<bool>(ischange), static_cast<bool>(iscol) };
			//�A�C�e�����e�[�u���ɒǉ�
			table->AddItem(stand);
		}
		table->SetVoiceName(voicename);
		table->SetSeName(sename);
		//�}�l�[�W���[�Ƀe�[�u���ǉ�
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
	//�^�ϊ�
	int i = static_cast<int>(type);
	//�v�f��T��
	auto itr = mAttackList.find(i);
	//�����ꂽ��ύX
	if (itr != mAttackList.end()) 
	{
		mAttackCnt = 0;
		mTable = itr->second;
		mCountMax = mTable->GetItem().size();
		//�ύX��̍U���^�C�v���ۑ�
		mType = type;
		//�e�l������
		mIsChange = false;
		mIsTrg = false;
	}
}

void AttackTableManager::Process()
{
	//�J�E���g���Z
	mAttackCnt++;
	//�J�E���g���ő�l���傫���Ȃ�����U�����Ă��Ȃ���Ԃ�
	if (mAttackCnt >= mCountMax) 
	{ 
		AttackChange(ATTACK_TYPE::NONE);
	}
	//�J�E���g���̓��͉\���̃t���O���擾
	bool istrg = mTable->GetItem()[mAttackCnt].GetIsTrg();
	//�g���K�{�^������͂��Ă���Ƃ�
	if (gGlobal.gPad->GetXTrg(XINPUT_BUTTON_B))
	{
		//���͉\�t���O��true�Ȃ�true
		if (istrg) { mIsTrg = true; }
	}
	//�g���K���͂ƍU���ύX�\���̃t���O�Ř_���ς����߂�
	mIsChange = mIsTrg && mTable->GetItem()[mAttackCnt].GetIsChangeAttack();
}


