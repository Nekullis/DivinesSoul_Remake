#include "Effect.h"
Effect* Effect::efInstance = nullptr;
Effect::Effect(std::string handle, float size)
{
	efInstance = this;
	mPos = VGet(0, 0, 0);
	mSize = size;
	mDir = VGet(0,0,0);
	mEffectResourceHandle = LoadEffekseerEffect(handle.c_str(), mSize);
	mUseFlag = true;
	mPlayFlag = false;
	//Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
	SetPosPlayingEffekseer3DEffect(mPlayEffectHandle, mPos.x, mPos.y, mPos.z);
}

Effect::~Effect()
{
	// �G�t�F�N�g���\�[�X���폜����B
	DeleteEffekseerEffect(mEffectResourceHandle);
}
bool Effect::Play()
{
	if (mUseFlag)
	{
		//�G�t�F�N�g���Đ�����
		mPlayEffectHandle = PlayEffekseer3DEffect(mEffectResourceHandle);
	}
	if (mPlayEffectHandle != -1)
	{
		//�Đ����Ȃ�true��
		mPlayFlag = true;
	}
	return true;
	
}
bool Effect::Stop()
{
	StopEffekseer3DEffect(mPlayEffectHandle);
	return true;
}
bool Effect::Process()
{
	//Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
	SetPosPlayingEffekseer3DEffect(mPlayEffectHandle, mPos.x, mPos.y, mPos.z);
	//�p�x��ύX����
	SetRotationPlayingEffekseer3DEffect(mPlayEffectHandle, mDir.x, mDir.y, mDir.z);
	////�Đ����I�������t���O��false��
	return true;
}

bool Effect::Update()
{
	// DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
	Effekseer_Sync3DSetting();
	//�}�l�[�W���[��ʂ������g���ꍇ��UpdateEffekseer3D�̓}�l�[�W���[�N���X�ɒu��
	UpdateEffekseer3D();
	return true;
}

bool Effect::Draw()
{
	// Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
	DrawEffekseer3D();
	return true;
}