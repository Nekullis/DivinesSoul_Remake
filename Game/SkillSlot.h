//----------------------------------------------------------------------
// @filename SkillSlot.h
// @author: Fukuma Kyohei, NaraMitsuki
// @explanation
// �X�L���X���b�g
// �g�p�ł���X�L����ύX�����邽�߂̃N���X
//----------------------------------------------------------------------
#pragma once
#include "AppFrame.h"
#include "ResourceServer.h"
#include "JsonUtility.h"
#include "EnumInfo.h"
#include  <map>

//�萔
constexpr float TO_NEXTDIV = 10000.0f;
constexpr auto MAX_VOICE = 8;

class SkillSlot{
public:
	//�ǉ�����
	struct CALLVOICE
	{
		//�J�E���g
		int callCnt;
		//�J�E���g�ő�l
		int maxCallCnt;
		//��������
		bool isCall;
		//�{�C�X�̃L�[
		std::string voiceCode;
	};
	SkillSlot();
	virtual ~SkillSlot();
	//�{�C�X�o�^
	void RegisterCall();
	//�{�C�X�o��
	void SlotVoice(int i);
	//�{�C�X�Đ��֘A����
	void CallProcess();
	//�X���b�g��]����
	void SlotSpin(int slotnum);
	//�X���b�g�֘A�����܂Ƃ�
	void Process();
	//�X���b�g�`��
	void Render();
	//�Q�b�^�[
	std::array<kindDivine, 3>	GetSlot() const { return mSlot; }
	bool						GetIsSpin() const { return mIsSpin; }

protected:
	//�X���b�g�p�X�L���ԍ�
	int mSlotdivine;
	//��]���x
	int mSpinspeed;
	//�K�`�����[������
	int mReeltime;
	//�{�C�X�ԍ�
	int mVoiceNum;
	//�K�`��������Ă��邩
	bool mIsSpin;
	//�����\����
	CALLVOICE mCall[MAX_VOICE];
	//�X���b�g�i�[�p�z��
	std::array<kindDivine, 3> mSlot;

};