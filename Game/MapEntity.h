//----------------------------------------------------------------------
// @filename MapEntity.h
// @author: Fukuma Kyohei, Nara Mitsuki
// @explanation
// �}�b�v�N���X
// �w�i�A�X�e�[�W�Ɏg�p����I�u�W�F�N�g�̏����N���X
//----------------------------------------------------------------------
#pragma once
#include "appframe.h"
#include "ApplicationGlobal.h"
#include "JsonUtility.h"
#include <vector>

class MapEntity
{
	typedef ApplicationGlobal::stage stage;
public:
	MapEntity();
	virtual ~MapEntity();
	void Initialize(stage global);
	void Process();
	void Render();
	//�A�j���[�V�������Ă��邩
	bool IsPlayAnimation(std::string s);
	//�A�j���[�V�����̂������f���p�\����
	struct ANIMATIONMODEL
	{
		int model;
		float factor;
		float playTime;
		int attachIndex;
		int totalTime;
	};
protected:
	VECTOR mPos;
	VECTOR mDir;
	VECTOR mMove;
	// 3D���f���n���h��
	// <���O, ���f���n���h��>
	std::map<std::string, int> mMapModelHandle;		
	// 3D�u���b�N���
	struct BLOCKPOS {
		std::string		name;
		// ���W
		double		x, y, z;
		// ��]
		double		rx, ry, rz;
		// �g��
		double		sx, sy, sz;
		// ���f���n���h��
		int			modelHandle;
		// �`��t���[��
		int			drawFrame;
	};
	std::vector<BLOCKPOS>	mBlockPos;
	//�A�j���[�V�����p
	std::vector<ANIMATIONMODEL> mAnim;
};

