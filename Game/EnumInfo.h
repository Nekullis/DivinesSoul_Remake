//----------------------------------------------------------------------
// @filename EnumInfo.h
// @author: Fukuma Kyohei,Nara Mitsuki
// @explanation
// �X�L���═��̎�ނ��܂Ƃ߂��N���X
//----------------------------------------------------------------------
#pragma once

enum class kindDivine : int
{
	// �X�L��8���
	NONE = -1,
	BLEATH, CIRCLE, LASER, 
	SLASH, EXPLOSION, DASH,
	VACCUM, SONIC_WAVE
};

enum class kindWeapon
{
	SWORD,AXE
};
