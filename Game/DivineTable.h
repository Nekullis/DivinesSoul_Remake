#pragma once
#include <vector>
#include <string>
#include "DxLib.h"
#include "Effect.h"


//�X�L����
enum class DIVINENAME : int
{
	//�u���X
	BREATH,
	//�T�[�N��
	CIRCLE,
	//���[�U�[
	LASER,
	//�X���b�V��
	SLASH,
	//�G�N�X�v���[�W����
	EXPLOSION,
	//�_�b�V��
	DASH,
	//�o�L���[��
	VACUUM,
	//�\�j�b�N�E�F�[�u
	SONIC,
};

class DivineItem
{
public:
	DivineItem(DIVINENAME, VECTOR, int, float, float, float, float, float, Effect*, float, std::string, std::string);
	~DivineItem();
	//�Q�b�^�[
	DIVINENAME GetName()			const { return mName; }
	VECTOR GetPos()					const { return mPos; }
	int GetAtk()					const { return mAtkPoint; }
	float GetSize()					const { return mSize; }
	float GetInvocationFrame()		const { return mInvocationFrame; }
	float GetReInvocationFrame()	const { return mReInvocationFrame; }
	float GetStartColFrame()		const { return mStartColFrame; }
	float GetEndColFrame()			const { return mEndColFrame; }
	Effect* GetEffect()					  { return mEffect; }
	float GetEffectDir()			const { return mEffectDir; }
	std::string GetSECode()				  { return mSECode; }
	std::string GetVoiceCode()			  { return mVoiceCode; }
protected:
	//�X�L����
	DIVINENAME mName;
	//�����ʒu
	VECTOR mPos;
	//�U����
	int mAtkPoint;
	//�����蔻��p�T�C�Y
	float mSize;
	//������������
	float mInvocationFrame;
	//�Ĕ����܂ł̃t���[��
	float mReInvocationFrame;
	//����J�n����
	float mStartColFrame;
	//����I������
	float mEndColFrame;
	//�g���G�t�F�N�g
	Effect* mEffect;
	//�G�t�F�N�g����
	float mEffectDir;
	//SE���ʃL�[
	std::string mSECode;
	//�{�C�X���ʃL�[
	std::string mVoiceCode;
};

class DivineTable
{
public:
	DivineTable();
	~DivineTable();
	void Process();
	void Render();
	void AddItem(DivineItem item);
	//�Q�b�^�[
	std::vector<DivineItem> GetItem()	{ return mItem; }
	bool GetPlaying()					{ return mIsPlaying; }
	bool GetInvocationFlag()			{ return mInvocationFlag; }
	//�Z�b�^�[
	void SetPlaying(bool flag)			{ mIsPlaying; }
	void SetInvocationFlag(bool flag)	{ mInvocationFlag = flag; }
	void SetReInvocationCnt(int cnt)	{ mReInvocationCnt = cnt; }
	void SetIsCollisionCnt(int cnt)		{ mColCnt = cnt; }
protected:
	std::vector<DivineItem> mItem;
	//�Ĕ����܂ł̃J�E���g
	int mReInvocationCnt;
	//����p�J�E���g
	int mColCnt;
	//��������
	bool mIsPlaying;
	//�����t���O
	bool mInvocationFlag;
	
};

