#include "MorningStar.h"
#include "Zombie.h"
#include "Torch.h"

MorningStar::MorningStar()
{

	CTextures * textures = CTextures::GetInstance();

	textures->Add(ID_TEX_MORNINGSTAR, L"textures\\morningstar.png", D3DCOLOR_XRGB(255, 0, 255));
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	 
	sprites->Add(7001, 0, 0, 240, 66, textures->Get(ID_TEX_MORNINGSTAR));
	sprites->Add(7002, 241, 0, 481, 66, textures->Get(ID_TEX_MORNINGSTAR));
	sprites->Add(7003, 482, 0, 722, 66, textures->Get(ID_TEX_MORNINGSTAR));

	sprites->Add(7004, 1199, 0, 1439, 66, textures->Get(ID_TEX_MORNINGSTAR));
	sprites->Add(7005, 958, 0, 1198, 66, textures->Get(ID_TEX_MORNINGSTAR));
	sprites->Add(7006, 717, 0, 957, 66, textures->Get(ID_TEX_MORNINGSTAR));

	sprites->Add(7007, 0, 67, 240, 133, textures->Get(ID_TEX_MORNINGSTAR));
	sprites->Add(7008, 241, 67, 481, 133, textures->Get(ID_TEX_MORNINGSTAR));
	sprites->Add(7009, 482, 67, 722, 133, textures->Get(ID_TEX_MORNINGSTAR));

	sprites->Add(7010, 1199, 67, 1439, 133, textures->Get(ID_TEX_MORNINGSTAR));
	sprites->Add(7011, 958, 67, 1198, 133, textures->Get(ID_TEX_MORNINGSTAR));
	sprites->Add(7012, 717, 67, 957, 133, textures->Get(ID_TEX_MORNINGSTAR));

	sprites->Add(7013, 0, 134, 240, 200, textures->Get(ID_TEX_MORNINGSTAR));
	sprites->Add(7014, 241, 134, 481, 200, textures->Get(ID_TEX_MORNINGSTAR));
	sprites->Add(7015, 482, 134, 722, 200, textures->Get(ID_TEX_MORNINGSTAR));

	sprites->Add(7016, 1199, 134, 1439, 200, textures->Get(ID_TEX_MORNINGSTAR));
	sprites->Add(7017, 958, 134, 1198, 200, textures->Get(ID_TEX_MORNINGSTAR));
	sprites->Add(7018, 717, 134, 957, 200, textures->Get(ID_TEX_MORNINGSTAR));
	

	ani = new CAnimation(150);	// idle big right
	ani->Add(7001);
	ani->Add(7002);
	ani->Add(7003);
	animations->Add(7001, ani);
	ani = new CAnimation(150);	// idle big right
	ani->Add(7004);
	ani->Add(7005);
	ani->Add(7006);
	animations->Add(7002, ani);
	ani = new CAnimation(150);
	ani->Add(7007);
	ani->Add(7008);
	ani->Add(7009);
	animations->Add(7003, ani);
	ani = new CAnimation(150);
	ani->Add(7010);
	ani->Add(7011);
	ani->Add(7012);
	animations->Add(7004, ani);
	ani = new CAnimation(150);
	ani->Add(7013);
	ani->Add(7014);
	ani->Add(7015);
	animations->Add(7005, ani);
	ani = new CAnimation(150);
	ani->Add(7016);
	ani->Add(7017);
	ani->Add(7018);
	animations->Add(7006, ani);
	this->AddAnimation(7001);
	this->AddAnimation(7002);
	this->AddAnimation(7003);
	this->AddAnimation(7004);
	this->AddAnimation(7005);
	this->AddAnimation(7006);

}
//
//void MorningStar::Render(Camera *camera)
//{
//
//}


void MorningStar::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	//Calculate dx, dy 
 	CGameObject::Update(dt);

	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<Torch *>(coObjects->at(i))) {
			Torch*torch = dynamic_cast<Torch *>(coObjects->at(i));

			float l1, t1, r1, b1, l2, t2, r2, b2;
			GetBoundingBox(l1, t1, r1, b1);
			torch->GetBoundingBox(l2, t2, r2, b2);

			if (t1 <= b2 && b1 >= t2 && l1 <= r2 && r1 >= l2) {

				if (torch->isEnable==true) {
					torch->isEnable = false;
					torch->isDead = true;
				}
			}
		}


	}
}

int MorningStar::GetCurrentFrameOfMorningStar()
{
	if (anirender== MORNINGSSTAR_ANI_RIGHT)
	{
		ani = animations[MORNINGSSTAR_ANI_RIGHT];
	}
	else if (anirender == MORNINGSSTAR_ANI_LEFT)
	{
		ani = animations[MORNINGSSTAR_ANI_LEFT];
	}
	if (anirender == MORNINGSSTAR_ANI_RIGHT_1)
	{
		ani = animations[MORNINGSSTAR_ANI_RIGHT_1];
	}
	else if (anirender == MORNINGSSTAR_ANI_LEFT_1)
	{
		ani = animations[MORNINGSSTAR_ANI_LEFT_1];
	}
	if (anirender == MORNINGSSTAR_ANI_RIGHT_2)
	{
		ani = animations[MORNINGSSTAR_ANI_RIGHT_2];
	}
	else if (anirender == MORNINGSSTAR_ANI_LEFT_2)
	{
		ani = animations[MORNINGSSTAR_ANI_LEFT_2];
	}
	return ani->getCurrentFrame();
}



void MorningStar::SetPosition(float x,float y,bool Issit)
{

	if (Issit == true)
	{
		if(nx<0)
		x -= MORNINGSTAR_SET_POSITION_X_1;
		else
			x -= MORNINGSTAR_SET_POSITION_X;
		y += MORNINGSTAR_SET_POSITION_Y;
	}
	else
		x -= MORNINGSTAR_SET_POSITION_X;
	CGameObject::SetPosition(x, y);
	
	
}

void MorningStar::Render(Camera *camera)
{

	ani = animations[0];
	animations[0]->Render(camera, x, y);
		RenderBoundingBox(camera);

}

void MorningStar::Render(Camera *camera,int ani)
{
	anirender = ani;

	animations[ani]->Render(camera, x, y);

}
void MorningStar::Render()
{
	ani = animations[0];
	animations[0]->Render(x, y);
	//RenderBoundingBox();

}


void MorningStar::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (anirender == MORNINGSSTAR_ANI_RIGHT)
	{
		left = x + MORNINGSTAR_SET_POSITION_X + SIMON_BBOX_WIDTH;
		top = y + MORNINGSTAR_SET_POSITION_BOUNDINGBOX_Y;
		right = left + MORNINGSTAR_BBOX_WIDTH;
		bottom = y + MORNINGSTAR_BBOX_HEIGHT;
	}
	else if (anirender == MORNINGSSTAR_ANI_LEFT)
	{
		left = x+ MORNINGSTAR_SET_POSITION_X - MORNINGSTAR_BBOX_WIDTH;
		top = y + MORNINGSTAR_SET_POSITION_BOUNDINGBOX_Y;
		right = left + MORNINGSTAR_BBOX_WIDTH;
		bottom = y + MORNINGSTAR_BBOX_HEIGHT;
	}
	else if (anirender == MORNINGSSTAR_ANI_RIGHT_1)
	{
		left = x + MORNINGSTAR_SET_POSITION_X + SIMON_BBOX_WIDTH;
		top = y + MORNINGSTAR_SET_POSITION_BOUNDINGBOX_Y;
		right = left + MORNINGSTAR_1_BBOX_WIDTH;
		bottom = y + MORNINGSTAR_1_BBOX_HEIGHT;
	}
	else if (anirender == MORNINGSSTAR_ANI_LEFT_1)
	{
		left = x + MORNINGSTAR_SET_POSITION_X - MORNINGSTAR_1_BBOX_WIDTH;
		top = y + MORNINGSTAR_SET_POSITION_BOUNDINGBOX_Y;
		right = left + MORNINGSTAR_1_BBOX_WIDTH;
		bottom = y + MORNINGSTAR_1_BBOX_HEIGHT;
	}
	else if (anirender == MORNINGSSTAR_ANI_RIGHT_2)
	{
		left = x + MORNINGSTAR_SET_POSITION_X + SIMON_BBOX_WIDTH;
		top = y + MORNINGSTAR_SET_POSITION_BOUNDINGBOX_Y;
		right = left + MORNINGSTAR_2_BBOX_WIDTH;
		bottom = y + MORNINGSTAR_2_BBOX_HEIGHT;
	}
	else if (anirender == MORNINGSSTAR_ANI_LEFT_2)
	{
		left = x + MORNINGSTAR_SET_POSITION_X - MORNINGSTAR_2_BBOX_WIDTH;
		top = y + MORNINGSTAR_SET_POSITION_BOUNDINGBOX_Y;
		right = left + MORNINGSTAR_2_BBOX_WIDTH;
		bottom = y + MORNINGSTAR_2_BBOX_HEIGHT;
	}



}


MorningStar::~MorningStar()
{
}
