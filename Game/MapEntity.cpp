#include "MapEntity.h"

MapEntity::MapEntity() {
	std::string path = "res/Stage/";

	JsonUtility* jUtil;
	jUtil = new JsonUtility();
	nlohmann::json stage = jUtil->Import("res/Json/stage/DS_Stage.json").at("Stage");
	//nlohmann::json stage = jUtil->Import("res/Json/stage/Stage_Pos.json").at("asset");
	for (auto& data : stage) {	// �����f�[�^����
		BLOCKPOS pos;
		data.at("objectName").get_to(pos.name);
		// UE�͍�����W�n/Zup ��������W�n/Yup �ɕϊ����擾
		data.at("translate").at("x").get_to(pos.x);
		data.at("translate").at("z").get_to(pos.y);
		data.at("translate").at("y").get_to(pos.z);
		pos.z *= -1.f;				// ���W�̕ϊ�
		data.at("rotate").at("x").get_to(pos.rx);
		data.at("rotate").at("z").get_to(pos.ry);
		data.at("rotate").at("y").get_to(pos.rz);
		pos.rx = Math::DegToRad(pos.rx);	// ��]��degree��radian��
		pos.ry = Math::DegToRad(pos.ry);
		pos.rz = Math::DegToRad(pos.rz);
		data.at("scale").at("x").get_to(pos.sx);
		data.at("scale").at("z").get_to(pos.sy);
		data.at("scale").at("y").get_to(pos.sz);

		// ���O�̃��f�������łɓǂݍ��ݍς��H
		if (mMapModelHandle.count(pos.name) == 0) {
			mMapModelHandle[pos.name] = gGlobal.mRS->mGetModel()[pos.name]._handle;
		}

		// ���O����g�����f���n���h�����\���t���[�������߂�
		if (mMapModelHandle.count(pos.name) > 0) {
			pos.modelHandle = mMapModelHandle[pos.name];
			pos.drawFrame = MV1SearchFrame(pos.modelHandle, pos.name.c_str());
		}
		if (IsPlayAnimation(pos.name)) {
			//�\���̂̐錾
			ANIMATIONMODEL  _animModel;
			//���f���n���h��
			_animModel.model = mMapModelHandle[pos.name];
			//�A�j���[�V�����X�s�[�h�̌W��
			_animModel.factor= gGlobal.mRS->mGetAttach()[pos.name]._attach_speed;
			//�A�j���[�V�����A�^�b�`�C���f�b�N�X
			_animModel.attachIndex = MV1AttachAnim(_animModel.model, 0, -1, FALSE);
			//�A�j���[�V������������
			_animModel.totalTime = gGlobal.mRS->mGetAttach()[pos.name]._attach_time;
			//�A�j���[�V�����Đ�����
			_animModel.playTime = rand() % 5;
			//�R���e�i�Ɋi�[
			mAnim.push_back(_animModel);
		}
		// �f�[�^���R���e�i�ɒǉ��i���f���ԍ�������΁j
		if (pos.modelHandle != -1) {
			mBlockPos.push_back(pos);
		}
	}
}

bool MapEntity::IsPlayAnimation(std::string s)
{
	//�A�j���[�V�����Ώۂ̃��f���n���h��
	if (s == "grassShake2" || s == "E_Flag" || s == "E_Flag2" || s == "BigTreeLeaf"){
		return true;
	}
	return false;
}

MapEntity::~MapEntity() {
	mBlockPos.clear();
	mMapModelHandle.clear();
}

void MapEntity::Initialize(stage global) {

}

void MapEntity::Process() {
	for (auto&& anim : mAnim){
		//�Đ����x�̓��f���ɂ���ĕς�邽�ߌW����������
		anim.playTime += 1 * anim.factor;
		//���Đ����Ԃɓ��B
		if (anim.playTime >= anim.totalTime) {
			//�Đ����Ԃ�0��
			anim.playTime = 0;
		}
	}
}

void MapEntity::Render() {
		// 3D�u���b�N��`�悷��
	for (auto ite = mBlockPos.begin(); ite != mBlockPos.end(); ++ite) {
		MV1SetPosition((*ite).modelHandle, VGet((*ite).x, (*ite).y, (*ite).z));
		MV1SetRotationXYZ((*ite).modelHandle, VGet((*ite).rx, (*ite).ry, (*ite).rz));
		MV1SetScale((*ite).modelHandle, VGet((*ite).sx, (*ite).sy, (*ite).sz));
		MV1DrawFrame((*ite).modelHandle, (*ite).drawFrame);
		for (auto&& anim : mAnim){
			MV1SetAttachAnimTime(anim.model, anim.attachIndex, anim.playTime);
		}
		MV1DrawModel((*ite).modelHandle);
	}
}


