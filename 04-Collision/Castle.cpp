#include "Castle.h"



void Castle::Render(Camera * camera)
{
	if (this->isEnable == true)
	{
		CSprites * sprites = CSprites::GetInstance();
		sprite = sprites->Get(10001);
		sprite->Draw(camera, x, y);
	}
}

void Castle::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = t = r = b = 0;
}

Castle::Castle()
{
	CTextures * textures = CTextures::GetInstance();
	CSprites * sprites = CSprites::GetInstance();
	textures->Add(ID_TEX_CASTLE, L"textures\\castle.png", D3DCOLOR_XRGB(237, 28, 36));
	sprites->Add(10001, 0, 0, 95, 287, textures->Get(ID_TEX_CASTLE));
}


Castle::~Castle()
{
}
