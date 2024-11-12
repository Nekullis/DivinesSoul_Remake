//----------------------------------------------------------------------
// @filename Effect.h
// @author: Fukuma Kyohei
// @explanation
// �G�t�F�N�g�Ǘ��N���X
// �X�L���������̃G�t�F�N�g���Ǘ�����N���X
//----------------------------------------------------------------------
#pragma once
#include "dxlib.h"
#include "EffekseerForDXLib.h"
#include <string>
#include <map>
class Effect
{
public:
	Effect(std::string handle, float size);
	virtual ~Effect();
	static Effect* efInstance;
	bool Play();
	bool Stop();
	bool Process();
	bool Draw();
	//������Ăяo���K�v�̂Ȃ��֐��Ȃ̂ł��̊֐��̓}�l�[�W���[���邢�̓Q�[�����C���ɒu������
	bool Update();
	//�Q�b�^�[
	bool GetUseFlag()		  const { return mUseFlag; }
	bool GetPlayFlag()		  const { return mPlayFlag; }
	static Effect* GetInstance()	{ return efInstance; }
	//�Z�b�^�[
	void SetPos(VECTOR v)	{ mPos=v; }
	void SetSize(float s)	{ mSize = s; }
	void SetDir(VECTOR v)	{ mDir = v; }
	void SetUseFlag(bool f) { mUseFlag = f; }
protected:
	//�G�t�F�N�g�����[�h����
	int mEffectResourceHandle;
	//�Đ��p�n���h��
	int mPlayEffectHandle;
	//�ʒu
	VECTOR mPos;
	//�T�C�Y
	float mSize;
	//����
	VECTOR mDir;
	//�Đ��\�t���O
	bool mUseFlag;
	//�Đ����̃t���O
	bool mPlayFlag;
};

