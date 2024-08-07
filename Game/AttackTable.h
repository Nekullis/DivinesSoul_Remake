#pragma once
#include <vector>
#include <string>

//�U���Ɋւ���f�[�^�e�[�u���̗v�f
class AttackTableItem
{
public:
	AttackTableItem(int, bool, bool, bool, bool, bool);
	~AttackTableItem();
	//�Q�b�^�[
	int		GetAttackID()		const	{ return mAttackID; }
	bool	GetIsTrg()			const	{ return mIsTrgButton; }
	bool	GetIsChangeAttack() const	{ return mIsChangeAttack; }
	bool	GetIsColAttack()	const	{ return mIsColAttack; }
	bool	GetIsPlaySE()		const	{ return mIsPlaySE; }
	bool	GetIsPlayVoice()	const	{ return mIsPlayVoice; }
protected:
	//�U���pID
	int mAttackID;
	//�{�^�����͉\��
	bool mIsTrgButton;
	//�U�����ύX�\��
	bool mIsChangeAttack;
	//�U������\��
	bool mIsColAttack;
	bool mIsPlaySE;
	bool mIsPlayVoice;
};

//�U���Ɋւ���f�[�^�e�[�u��
class AttackTable
{
public:
	AttackTable();
	~AttackTable();
	void Update();
	void AddItem(AttackTableItem item);
	//�Q�b�^�[
	std::vector<AttackTableItem> GetItem()		{ return mItem; }
	std::string GetVoiceName()					{ return mVoiceName; }
	std::string GetSeName()						{ return mSeName; }
	//�Z�b�^�[
	void SetVoiceName(std::string voicename)	{ mVoiceName = voicename; }
	void SetSeName(std::string sename)			{ mSeName = sename; }
protected:
	//�e�[�u���A�C�e���R���e�i
	std::vector<AttackTableItem> mItem;
	std::string mVoiceName;
	std::string mSeName;
};

