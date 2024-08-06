#pragma once
#include "DxLib.h"
// MyMath�ɃC���N���[�h���Ă���̂ł����G���[�N�������炢�����Ă݂Ă��������B

// ���̂܂�܏����Ƃ߂�ǂ��̂Ŏg���Ƃ����typedef�����Ă�������
// ��Ftypedef  MyStruct::MYRECT<�g�������^> �b�g�������^���ȗ����������b_rect;
namespace MyStruct {
	// RECT�p�\����
	template<typename T>
	struct MYRECT {
		T		x, y, w, h;
	};

	// RECT�p�\����+�A���t�@(��͏㉺���E�̃X�s�[�h)
	//template<typename T>
	//struct MYRECT_PLUS {
	//	MYRECT<T> Rect;
	//  ��F	T     mx, my;
	//};

	// CIRCLE�p�\����
	template<typename T>
	struct MYCIRCLE {
		T x, y;
		T r;
	};
	
	// CIRCLE�p�\����+�A���t�@(��͓����������ǂ���)
	//template<typename T>
	//struct MYCIRCLE_PLUS {
	//	MYCIRCLE<T> Circle;
	//	bool hit;
	//};

		// VECTOR�\����
	template<typename T>
	struct MYVECTOR {
		T x, y, z;
	};

	// Sphere�\����
	template<typename T>
	struct MYSPHERE {
		VECTOR position;
		T radius;
	};

	// Color�\���́iR,G,B�j
	struct s_COLOR
	{		int r, g, b;	};

	// �A�i���O�X�e�B�b�N���E�̍��W
	struct ANALOGSTICK
	{
		float lx, ly, rx, ry, analogMin;	// ���E�A�i���O�X�e�B�b�N�̍��W�ƃA�i���O臒l�i�F������ŏ��̓����̕��j
	};
}