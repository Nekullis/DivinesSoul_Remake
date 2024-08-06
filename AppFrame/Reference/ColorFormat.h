#pragma once
#include "MyStruct.h"
#include "DXLib.h"

namespace Color {
	typedef MyStruct::s_COLOR s_RGB;// RGB�̍\����

	// �K�v�Ƃ���Βǉ����Ă䂭
	static s_RGB red{ 255,0,0 };
	static s_RGB blue{ 0,0,255 };
	static s_RGB yellow{ 255,255,0 };
	static s_RGB green{ 0,128,0 };
	static s_RGB purple{ 128,0,128 };
	static s_RGB black{ 0,0,0 };
	static s_RGB white{ 255,255,255 };
	static s_RGB gray{ 128,128,128 };

	// DXLib�Ŏg����悤�ɂ���i���̊֐������̂܂�GetColor�̓���Ƃ���ɂ��Ă͂߂�j
	static unsigned int Setting(s_RGB rgb) {
		return GetColor(rgb.r, rgb.g, rgb.b);
	}

	//�����Ƃ��͈ȉ��̂悤�ɂȂ�
	// 	��@int Red = Color::Setting(Color::red);
}