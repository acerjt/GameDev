#include "Torch.h"

void Torch::Render(Camera *camera)
{
	if (this->isEnable==true)
	{
		animations[0]->Render(camera, x, y);
	}
}
void Torch::Render()
{
	
		animations[0]->Render(x, y);
		//RenderBoundingBox();

}
void Torch::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {

}
void Torch::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	//l = t = r = b = 0;
	//if (state == TORCH_STATE_1) {
		l = x;
		t = y;
		r = x + TORCH_BBOX_WIDTH;
		b = y + TORCH_BBOX_HEIGHT;
	//}
}

Torch::Torch()
{
	CTextures * textures = CTextures::GetInstance();
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	LPANIMATION ani;

	textures->Add(ID_TEX_TORCH, L"textures\\torch.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 textorch = textures->Get(ID_TEX_TORCH);
	sprites->Add(8001, 0, 0, 31, 63, textorch);
	sprites->Add(8002, 32, 0, 63, 63, textorch);
	ani = new CAnimation(100);	// walk right big
	ani->Add(8001);
	ani->Add(8002);
	animations->Add(8001, ani);
	this->AddAnimation(8001);
}


Torch::~Torch()
{
}
