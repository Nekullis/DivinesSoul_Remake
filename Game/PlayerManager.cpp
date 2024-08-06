#include "PlayerManager.h"

PlayerManager::PlayerManager() {

}

PlayerManager::~PlayerManager() 
{
	P_Delete();
}

void PlayerManager::Initialize() 
{
	// �v���C���[�}�l�[�W���[���̂̏������֐��i�O���[�o���łł��Ă���̂ňꉞ���܂����j
}

void PlayerManager::Process() 
{
 // �K�`���Ȃǂŕϓ������X�e�[�^�X��ύX�Ȃǃv���C���[�̃Q�[����ʈȊO�ł̏������L�q�i�K�v�ɉ����đ��₷�j
}

// �ȉ���P�`�`�̓v���C���[���̊֐������̊K�w�ł�����悤�ɂ��Ă���
void PlayerManager::P_Materialize() 
{
	mPl = new Player();
}

void PlayerManager::P_Delete() 
{
	delete mPl;
}

void PlayerManager::P_Initialize(int handle, int weapon) 
{
	mPl->Initialize(handle, weapon);
}

void PlayerManager::P_Process(VECTOR campos, VECTOR camtarget, SkillSlot* slot) 
{
	// �K�v�Ƃ���Ή�������ǉ�����(�v���C���[�N���X�̊֐����܂Ƃ߂�Ȃ�)
	mPl->Process(campos, camtarget,slot);
}

void PlayerManager::P_AnimProcess() 
{
	mPl->A_Process();
}

void PlayerManager::P_CalcuProcess() 
{
	mPl->C_Process();
}

void PlayerManager::P_Damage(VECTOR pos, int subpoint)
{
	mPl->Damage(pos,subpoint);
}

void PlayerManager::Render() {
	// �v���C���[�̕`��ȊO�ɂ��v���C���[�Ɋւ���f�o�b�O��񂪗~����������`�悷��
	mPl->Render();
}

void PlayerManager::DebugRender() {
	mPl->PlDebug();
}