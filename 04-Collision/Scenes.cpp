#include "Scenes.h"


int Scenes::changescene = 0;

void Scenes::Update(DWORD dt)
{
}

void Scenes::Render(Camera *camera)
{
	switch (changescene)
	{
	case 0:
		animations[0]->Render(camera, x, y);
		break;
	case 1:
		animations[1]->Render(camera, x, y);
		break;
	}
}
void Scenes::Render()
{
	animations[0]->Render(x, y);
	
	//RenderBoundingBox();
}


void Scenes::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x;// +SCENE_BBOX_WIDTH;
	b = y;// +SCENE_BBOX_HEIGHT;
}


Scenes::Scenes():CGameObject()
{
	CTextures * textures = CTextures::GetInstance();
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	LPANIMATION ani;
	textures->Add(ID_TEX_START_GAME, L"textures\\startgame.png", D3DCOLOR_XRGB(128, 0, 0));
	LPDIRECT3DTEXTURE9 texscenestartgame = textures->Get(ID_TEX_START_GAME);
	sprites->Add(1001, 4, 4, 517, 448, texscenestartgame);
	textures->Add(ID_TEX_INTRO, L"textures\\intro.png", D3DCOLOR_XRGB(255, 255, 255));
	LPDIRECT3DTEXTURE9 texintro = textures->Get(ID_TEX_INTRO);
	sprites->Add(1002, 0, 0, 512, 448, texintro);
	ani = new CAnimation(100);
	ani->Add(1001);
	animations->Add(1001, ani);
	ani = new CAnimation(100);
	ani->Add(1002);
	animations->Add(1002, ani);
	this->AddAnimation(1001);
	this->AddAnimation(1002);
}


Scenes::~Scenes()
{
}
