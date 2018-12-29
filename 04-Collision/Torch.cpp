#include "Torch.h"

void Torch::Render(Camera *camera)
{
	CGameObject::Render(camera);
	if (this->isEnable==true)
	{
		animations[0]->Render(camera, x, y);
	}
}
void Torch::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + TORCH_BBOX_WIDTH;
	b = y + TORCH_BBOX_HEIGHT;
}

Torch::Torch()
{
	this->AddAnimation(8001);
}


Torch::~Torch()
{
}
