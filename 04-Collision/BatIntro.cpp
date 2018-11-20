#include "BatIntro.h"

void BatIntro::Render(Camera *camera)
{
	animations[0]->Render(camera,x, y);
}

void BatIntro::Render()
{
	
}
void BatIntro::Update(DWORD dt)
{
	CGameObject::Update(dt);
	x += dx;
	y -= dy;
}

void BatIntro::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BAT_INTRO_STATE_FLY_UP:
		vx = BAT_INTRO_SPEED;
		vy = BAT_INTRO_SPEED;
		break;
	case BAT_INTRO_STATE_FLY_STRAIGHT:
		vx = -BAT_INTRO_SPEED ;
		vy = BAT_INTRO_SPEED *0.2;
		break;
	}

}

void BatIntro::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = t = r = b = 0;
}

BatIntro::BatIntro()
{
	CTextures * textures = CTextures::GetInstance();
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	LPANIMATION ani;
	textures->Add(ID_TEX_BAT_INTRO, L"textures\\bat.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texbatintro = textures->Get(ID_TEX_BAT_INTRO);
	sprites->Add(4001, 0, 0, 15, 15, texbatintro);
	sprites->Add(4002, 16, 0, 31, 15, texbatintro);
	ani = new CAnimation(100);
	ani->Add(4001);
	ani->Add(4002);
	animations->Add(4001, ani);
	this->AddAnimation(4001);

}


BatIntro::~BatIntro()
{
}
