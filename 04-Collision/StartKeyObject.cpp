#include "StartKeyObject.h"



void StartKeyObject::Render(Camera * camera)
{
	D3DXVECTOR3 pos;
	RECT rect;
	pos = D3DXVECTOR3(x, y, 0);
	rect.left = x;
	rect.top = y;
	rect.right = x + width;
	rect.bottom = y + height;
	CSprites * sprites = CSprites::GetInstance();
	if (isEnable != true)
	{
		sprite = sprites->Get(ID_TEX_BLACK);
		sprite->Draw(pos, rect);
	}
}

void StartKeyObject::Render()
{
	D3DXVECTOR3 pos;
	RECT rect;
	pos = D3DXVECTOR3(x, y, 0);
	rect.left = x;
	rect.top = y;
	rect.right = x + width;
	rect.bottom = y + height;
	CSprites * sprites = CSprites::GetInstance();
	sprite = sprites->Get(ID_TEX_BLACK);
	sprite->Draw(pos, rect);
}

void StartKeyObject::Update(DWORD dt)
{
	CGameObject::Update(dt);
	TimeDisplay += dt;
	if (TimeDisplay >= 300)
	{
		isEnable = !isEnable;
		TimeDisplay -= 300;
	}
}

void StartKeyObject::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

StartKeyObject::StartKeyObject(int width, int height)
{
	TimeDisplay = 0;
	this->width = width;
	this->height = height;
}


StartKeyObject::~StartKeyObject()
{
}
