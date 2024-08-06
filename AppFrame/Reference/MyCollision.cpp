#include "Mycollision.h"
#include "MyMath.h"


// 2D�ɂ�����v�Z�֐�
bool ColDetect::IsHitBox(
  I_rect rect1,		// �ЂƂ߂�box ����(x,y), �傫��w,h
  I_rect rect2	// �ӂ��߂�box ����(x,y), �傫��w,h
)
{
  if (rect1.x < rect2.x + rect2.w && rect2.x < rect1.x + rect1.w		// x�����̔���
    && rect1.y < rect2.y + rect2.h && rect2.y < rect1.y + rect1.h		// y�����̔���
    )
  {
    // 2��box�͓������Ă���
    return true;
  }

  // 2��box�͓������Ă��Ȃ�
  return false;
}

bool ColDetect::IsHitCircle(
  F_circle circle1,		// �ЂƂ߂�circle ���S(x,y), ���ar
  F_circle circle2			// �ӂ��߂�circle ���S(x,y), ���ar
) {
  int w, h, r;
  w = circle1.x - circle2.x;
  h = circle1.y - circle2.y;
  r = circle1.r + circle2.r;
  if (r * r > w * w + h * h) {
    return true;
  }
  return false;
}

bool ColDetect::IsHitCircleRect(
  F_circle circle,    // �~�̔���
  I_rect rect         // ��`�̔���  
) {
  int x, y;
  float rad, deg;
  // 360�_�Ƃ��ē����蔻�肵����ꍇ�ɂ���ďd���Ȃ�܂���
  for (deg = 0; deg <= 360; deg += 90) {
    rad = Math::DegToRad(deg);
    x = (circle.x + circle.r * cos(rad));
    y = (circle.y + circle.r * sin(rad));

    // �������Ă���E�E�E����N�_�̋�`�̂݁i���Ԃ��Ȃ��̂Łj
    if (rect.x < x && x < rect.x + rect.w && rect.y < y && y < rect.y + rect.h) {
      return true;
    }
  }

  return false;
}