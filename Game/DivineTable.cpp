#include "DivineTable.h"
#include "ApplicationGlobal.h"
DivineTable::DivineTable()
{
	mItem.clear();
	mReInvocationCnt = 0;
	mColCnt = 0;
	mIsPlaying = false;
	mInvocationFlag = true;
}

DivineTable::~DivineTable()
{
}

void DivineTable::AddItem(DivineItem item)
{
	mItem.push_back(item);
}

void DivineTable::Process()
{
	int tablenum = 0;
	//�X�L�������\�łȂ��̂Ȃ�J�E���g�𑝂₷
	if (!mInvocationFlag)
	{
		mReInvocationCnt++;
	}
	//�J�E���g������̃t���[���ɒB����
	if (mColCnt > mItem[tablenum].GetStartColFrame())
	{
		mItem[tablenum].GetEffect()->SetUseFlag(false);
	}
	//�J�E���g�������\�t���[���܂ŒB�����Ȃ�
	if (mReInvocationCnt > mItem[tablenum].GetReInvocationFrame())
	{
		//�G�t�F�N�g�Đ��\�t���O��true��
		mItem[tablenum].GetEffect()->SetUseFlag(true);
		//�X�L�������t���O��true��
		mInvocationFlag = true;
		//�J�E���g���Z�b�g
		mReInvocationCnt = 0;
	}
	//�f�B�o�C���������Ȃ�
	if (mIsPlaying) 
	{ 
		//�J�E���g���Z
		mColCnt++; 
	}
	if (mItem[tablenum].GetEffect()->GetPlayFlag())
	{
		//�����̒P�ʂ����W�A���ɕύX
		float effectdir = Math::DegToRad(mItem[tablenum].GetEffectDir());
		//�v���C���[�̈ʒu�A�����擾
		VECTOR plpos = Player::GetInstance()->GetPos();
		float pldir = Player::GetInstance()->GetDir().y;
		MATRIX matrix = MGetRotY(pldir);
		//������ύX����
		mItem[tablenum].GetEffect()->SetDir(VGet(0, pldir + effectdir, 0));
		//�ʒu��ύX
		mItem[tablenum].GetEffect()->SetPos(VAdd(plpos, VTransform(mItem[tablenum].GetPos(), matrix)));
		//�v���Z�X����
		mItem[tablenum].GetEffect()->Process();
	}
	//�G�t�F�N�g�̍Đ�
	if (mColCnt == mItem[tablenum].GetStartColFrame())
	{
		mItem[tablenum].GetEffect()->Play();
		//������Đ�����Ȃ��悤�ɏ�����t����
		if (mColCnt < mItem[tablenum].GetStartColFrame())
		{
			SoundItemBase* snditem_se = gGlobal.mSndServer.Get(mItem[tablenum].GetSECode());
			if (snditem_se && snditem_se->IsLoad())
			{	// �Đ������H
				if (snditem_se->IsPlay() == false)
				{	// �Đ�����
					snditem_se->Play();
				}
			}
		}
	}
}

void DivineTable::Render()
{
	int tablenum = 0;
	if (mItem[tablenum].GetEffect()->GetPlayFlag())
	{
		mItem[tablenum].GetEffect()->Draw();
	}
}


