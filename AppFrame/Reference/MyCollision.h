#pragma once
#include <math.h>
#include "MyStruct.h"

class ColDetect {
  // MyStruct����g���\���̂��y�Ɏg����悤�Ƀ^�C�v�f�B�t����
  typedef  MyStruct::MYRECT<int> I_rect;
  typedef MyStruct::MYCIRCLE<float> F_circle;
public:
  // �����蔻��p�B2��box�������������𔻒�
// �������Ă�����1, �������Ă��Ȃ�������0��Ԃ�
  static bool IsHitBox(
    I_rect rect1,		// �ЂƂ߂�box ����(x,y), �傫��w,h
    I_rect rect2	// �ӂ��߂�box ����(x,y), �傫��w,h
  );

  // �����蔻��p�B2�̉~�������������𔻒�
// �������Ă�����1, �������Ă��Ȃ�������0��Ԃ�
  static bool IsHitCircle(
    F_circle circle1,		// �ЂƂ߂�circle ���S(x,y), ���ar
    F_circle circle2		// �ӂ��߂�circle ���S(x,y), ���ar
  );

  // �����蔻��p�B�~�Ƌ�`�������������𔻒�i�s���S�Ȃ��߁A�v�X�V�j
// �������Ă�����1, �������Ă��Ȃ�������0��Ԃ�
  static bool IsHitCircleRect(
    F_circle circle,    // �~�̔���
    I_rect rect         // ��`�̔���      
  );

};

