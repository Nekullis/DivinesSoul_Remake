#include "Camera.h"
#include "Player.h"
#include "ApplicationGlobal.h"
#include <cmath>

Camera* Camera::cameraInstance = nullptr;
Camera::Camera()
{
	cameraInstance = this;
	//注視点初期化
	mTarget = { 0 };
	//位置初期化
	mPos = Player::GetInstance()->GetPos();
	mDir = { 0 };
	//最短描画距離初期化
	mNear = 20;
	//最長描画距離初期化
	mFar = 50000;
	//ばね定数
	mSpring = 0.1;
	//減衰定数
	mDampFactor = 0.8;
	mCurrentPos = mPos;
	mCurrentVelocity = { 0 };
}

Camera::~Camera()
{
}

void Camera::Process(short stix, short stiy)
{
	//パッド入力で角度を代入
	if (gGlobal.gPad->GetXRx() < 0) { mDir.y -= 0.05; }
	if (gGlobal.gPad->GetXRx() > 0) { mDir.y += 0.05; }
	//注視点設定
	VECTOR target;
	VECTOR plpos = Player::GetInstance()->GetPos();
	//カメラ位置をプレーヤー位置に球型座標系から変化した座標系を足した座標にする
	VECTOR pos = VAdd(plpos , Math::ConvertToCartesian(mDir, 700));
	//後頭部より少し高めの位置にする
	pos.y += 300;
	target = plpos; 
	mPos = pos;
	//ばね力計算
	VECTOR springforce = VScale(VSub(mCurrentPos,pos), - mSpring);
	//減衰力計算
	VECTOR dampforce = VScale(mCurrentVelocity, -mDampFactor);
	//総合力を計算している
	VECTOR force = VAdd(springforce,dampforce);
	VECTOR accseler = force;
	//速度更新
	mCurrentVelocity = VAdd(mCurrentVelocity,accseler);
	//位置更新
	mCurrentPos = VAdd(mCurrentPos,mCurrentVelocity);
	mPos = mCurrentPos;
	//カメラ描写の最短距離、最長距離を設定する
	SetCameraNearFar(mNear, mFar);
	//カメラの位置と注視点を反映する
	SetCameraPositionAndTarget_UpVecY(mCurrentPos, target);
}
