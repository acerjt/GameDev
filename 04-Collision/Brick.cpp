#include "Brick.h"
#include "Game.h"

void CBrick::Render(Camera *camera)
{
	//animations[0]->Render(camera,x, y);
	//RenderBoundingBox();
	D3DXVECTOR3 pos = D3DXVECTOR3(x,y,0);
	CSprites * sprites = CSprites::GetInstance();
	switch (chose) {
		case STATE_INTRO:
			sprite = sprites->Get(5001);
			break;
		case STATE_OUT_CASTLE:
			sprite = sprites->Get(5002);
			break;
	}


	for (int j = 0; j < height / 32; j++)
	{
		pos.y = this->y - 32 * j;
		for (int i = 0; i < width / 32; i++)
		{
			pos.x = this->x + 32 * i;
			sprite->Draw(camera,pos);
		}
	}
}
void CBrick::Render()
{
	animations[0]->Render(x, y);
}
void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

CBrick::CBrick(int width, int height,int chose)
{
	CTextures * textures = CTextures::GetInstance();
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	LPANIMATION ani;
	textures->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TRANSPARENT, L"textures\\transparent.png", D3DCOLOR_XRGB(237, 28, 36));
	LPDIRECT3DTEXTURE9 texbbox = textures->Get(ID_TRANSPARENT);
	sprites->Add(5001, 0, 0, 31, 31, texbbox);
	textures->Add(ID_TEX_BRICK_OUT_CASTLE, L"textures\\brick_out_castle.png", D3DCOLOR_XRGB(237, 28, 36));
	LPDIRECT3DTEXTURE9 texbrickoutcastle = textures->Get(ID_TEX_BRICK_OUT_CASTLE);
	sprites->Add(5002, 0, 0, 31, 31, texbrickoutcastle);



	this->width = width;
	this->height = height;
	this->chose = chose;
}
