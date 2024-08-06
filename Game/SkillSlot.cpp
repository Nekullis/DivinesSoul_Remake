#include "SkillSlot.h"
#include "ApplicationGlobal.h"
#include "GameEvent.h"
SkillSlot::SkillSlot() {
	mSlotdivine = 0;
	mSpinspeed = 5000;
	mReeltime = 0;
	for (int i = 0; i < mSlot.size(); i++) {
		if (i == 0) {
			mSlot[i] = kindDivine::BLEATH;
		}
		if (i == 1) {
			mSlot[i] = kindDivine::CIRCLE;
		}
		if (i == 2) {
			mSlot[i] = kindDivine::DASH;
		}
	}
	RegisterCall();
	mVoiceNum = -1;
	mIsSpin = false;
}

SkillSlot::~SkillSlot() {


}

void SkillSlot::RegisterCall(){
	//���[�J���ō\���̂��`
	CALLVOICE call[MAX_VOICE]
	{
		{0,180,false,"VO_Ca_Breath"},
		{0,180,false,"VO_Ca_Circle"},
		{0,180,false,"VO_Ca_Laser"},
		{0,180,false,"VO_Ca_Slash"},
		{0,180,false,"VO_Ca_Explosion"},
		{0,180,false,"VO_Ca_Dash"},
		{0,180,false,"VO_Ca_Vacuum"},
		{0,180,false,"VO_Ca_Sonic"},
	};
	for (int i = 0; i < MAX_VOICE; i++)
	{	//���g���ړ�
		mCall[i] = std::move(call[i]);
	}
}

void SkillSlot::SlotVoice(int i)
{
	//�{�C�X�ԍ�����
	mVoiceNum = i;
	//�Đ����Ȃ̂�true��
	mCall[mVoiceNum].isCall = true;
	//�{�C�X�L�[����
	SoundItemBase* snditem_voice = gGlobal.mSndServer.Get(mCall[mVoiceNum].voiceCode);
	//�J�E���g���K�萔�ɒB���Ă��Ȃ�
	if (mCall[mVoiceNum].callCnt <= mCall[mVoiceNum].maxCallCnt)
	{
		if (snditem_voice && snditem_voice->IsLoad())
		{	// �Đ����łȂ��Ȃ�
			if (snditem_voice->IsPlay() == false)
			{	// �Đ�����
				snditem_voice->Play();
			}
		}
	}
}

void SkillSlot::CallProcess()
{
	//�Đ����Ȃ�΃J�E���g���Z
	if (mCall[mVoiceNum].isCall) { mCall[mVoiceNum].callCnt++; }
	//�J�E���g���K�萔�ɒB����
	if (mCall[mVoiceNum].callCnt >= mCall[mVoiceNum].maxCallCnt)
	{	//�Đ�����������̂�false��
		mCall[mVoiceNum].isCall = false;
	}
}

void SkillSlot::SlotSpin(int slotnum){
	SoundItemBase* snditem_se = gGlobal.mSndServer.Get("SE_Slot_Finish");
	if (mSpinspeed > 0) {
		mIsSpin = true;
		mReeltime += mSpinspeed;
		mSpinspeed -= 30;
	}
	if (mReeltime >= TO_NEXTDIV) {
		mSlotdivine = rand() % 8;
		mReeltime = 0;
	}
	if (mSpinspeed <= 0) {
		mReeltime = 0;
		kindDivine divine = static_cast <kindDivine>(mSlotdivine);
		mSlot[slotnum] = divine;
		while (1)
		{
			if (mSlot[0] != mSlot[1] && 
				mSlot[1] != mSlot[2] && 
				mSlot[2] != mSlot[0]) { break; }
			mSlotdivine++;
			divine = static_cast <kindDivine>(mSlotdivine);
			mSlot[slotnum] = divine;
		}
		snditem_se->Play();
		SlotVoice(mSlotdivine);
		mSpinspeed = 5000;
		mIsSpin = false;
		if (GameEvent::GetInstance()->GetDivineEvent() == 0)
		{
			GameEvent::GetInstance()->SetDivineEvent(1);
		}
	}
}

void SkillSlot::Process()
{
	CallProcess();
}

void SkillSlot::Render() 
{
	int cg[8] =
	{
		gGlobal.mGetGraph()["UI_slot_bleath"]._handle,
		gGlobal.mGetGraph()["UI_slot_circle"]._handle,
		gGlobal.mGetGraph()["UI_slot_lasar"]._handle,
		gGlobal.mGetGraph()["UI_slot_slash"]._handle,
		gGlobal.mGetGraph()["UI_slot_explosion"]._handle,
		gGlobal.mGetGraph()["UI_slot_dashattack"]._handle,
		gGlobal.mGetGraph()["UI_slot_vacuum"]._handle,
		gGlobal.mGetGraph()["UI_slot_sonic"]._handle,
	};
	if (mReeltime > 0) {
		DrawGraph(880, 890, cg[mSlotdivine], TRUE);
	}

}