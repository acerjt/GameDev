#include "FireBall.h"

void FireBall::Update(DWORD dt)
{
	if (nx > 0)
		vx = FIRE_BALL_SPEED;
	else
		vx = -FIRE_BALL_SPEED;
	CGameObject::Update(dt);
	x += dx;
	y += dy;
	
}

void FireBall::Render(Camera * camera)
{
	if (isEnable)
	{
		CSprites * sprites = CSprites::GetInstance();
		sprite = sprites->Get(24001);
		sprite->Draw(camera, x, y);
	}
	D3DXVECTOR3 currentcamera = camera->GetCameraPosition();
	if (x < currentcamera.x || x>currentcamera.x + SCREEN_WIDTH)
		isEnable = false;
	CGameObject::Render(camera);
}
void FireBall::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = l + FIRE_BALL_BBOX_WIDTH;
	b = t + FIRE_BALL_BBOX_HEIGHT;
}

FireBall::FireBall()
{

}


FireBall::~FireBall()
{
}
