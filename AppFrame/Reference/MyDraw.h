#pragma once
#include "DxLib.h"		// VECTOR��MATRIX���`�Ƃ��Ďg�����߁A.h�ɓ���Ă���
#include "MyStruct.h"

namespace DXLib_Depend {// DXLib�Ɉˑ����Ă���
	// �摜�̒��S�ŉ�]���ĕ`�悷��
	static void MyDrawModiGraph(MATRIX mView, VECTOR position, float zoom, float angle, int width, int height, int cgHandle);

	// �摜�̒��S�ŉ�]���ĕ`�悷��(���E���]��)
	static void MyDrawTurnModiGraph(MATRIX mView, VECTOR position, float zoom, float angle, int width, int height, int cgHandle);

	// 4�_���w�肵�Ďl�p��`��
	static void MyDraw4PointBox(MATRIX mView, VECTOR pos[4], unsigned int Color, int FillFlag);

	// ��`��`��
	static void MyDrawBox(MATRIX mView, int x1, int y1, int x2, int y2, unsigned int Color, int FillFlag);

	static void MyDrawExtendGraph(MATRIX mView, int x1, int y1, int x2, int y2, unsigned int handle, int FillFlag);

	static void MyDrawDeformationGraph(MATRIX mView, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, float direction, int handle, int FillFlag);

	static void MyDrawRect(MATRIX mView, MyStruct::MYRECT<int> rc, unsigned int Color, int FillFlag);

	static void MyDrawLine(MATRIX mView, int x1, int y1, int x2, int y2, int Color);

	static void MyDrawCircle(MATRIX mView, int x, int y, int r);

	// �ʒu�𑵂��ĕ������`��
	// posBaseX = -1:������, 0:����, 1:�E����
	static void DrawPosString(int x, int y, int posBaseX, unsigned int color, const char* str);

}

