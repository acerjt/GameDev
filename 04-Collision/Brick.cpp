#include "Brick.h"
#include "Game.h"

void CBrick::Render(Camera *camera)
{
	
	D3DXVECTOR3 pos = D3DXVECTOR3(x,y,0);
	CSprites * sprites = CSprites::GetInstance();
	switch (chose) {
		case STATE_INTRO:
			sprite = sprites->Get(ID_TEX_TRANSPARENT);
			break;
		case STATE_OUT_CASTLE:
			sprite = sprites->Get(5001);
			break;
	}


	for (int j = 0; j < height / 32; j++)
	{
		pos.y = y - 32 * j;
		for (int i = 0; i < width / 32; i++)
		{
			pos.x = x + 32 * i;
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
	textures->Add(ID_TEX_BRICK_OUT_CASTLE, L"textures\\brick_out_castle.png", D3DCOLOR_XRGB(237, 28, 36));
	sprites->Add(5001, 0, 0, 31, 31, textures->Get(ID_TEX_BRICK_OUT_CASTLE));
	this->width = width;
	this->height = height;
	this->chose = chose;
}
