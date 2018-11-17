#include "Helicopter.h"

void Helicopter::Update(DWORD dt)
{
	CGameObject::Update(dt);
	vx = -HELICOPTER_SPEED;
	x += dx;
}

void Helicopter::Render(Camera *camera)
{
	animations[0]->Render(camera,x, y);
}
void Helicopter::Render()
{
	animations[0]->Render(x, y);
}

void Helicopter::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + HELICOPTER_BBOX_WIDTH;
	bottom = y + HELICOPTER_BBOX_HEIGHT;
}



Helicopter::Helicopter()
{
	CTextures * textures = CTextures::GetInstance();
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	LPANIMATION ani;

	textures->Add(ID_TEX_HELICOPTER, L"textures\\helicopter.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texhelicopter = textures->Get(ID_TEX_HELICOPTER);
	sprites->Add(3001, 0, 0, 64, 28, texhelicopter);
	ani = new CAnimation(100);
	ani->Add(3001);
	animations->Add(3001, ani);
	this->AddAnimation(3001);
}


Helicopter::~Helicopter()
{
}
