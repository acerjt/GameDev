#include "Item.h"
#include "Brick.h"
bool Item::isKillAll = false;
Simon* Item::simon = NULL;

void Item::TakeSimonPointer(Simon *simon)
{
	Item::simon = simon;
}

Item::Item()
{
	std::srand(time(0));
	Random();

	CTextures * textures = CTextures::GetInstance();
	CSprites * sprites = CSprites::GetInstance();
	switch (itemType) {
	case ITEM_UPGRADE_1:
		textures->Add(ID_TEX_ITEM_UPGRADE_1, L"textures\\DOUBLE_SHOT.png", D3DCOLOR_XRGB(255, 255, 255));
		sprites->Add(ITEM_UPGRADE_1, 0, 0, 27, 27, textures->Get(ID_TEX_ITEM_UPGRADE_1));
		this->width = 28;
		this->height = 28;
		break;
	case ITEM_UPGRADE_2:
		textures->Add(ID_TEX_ITEM_UPGRADE_2, L"textures\\TRIPLE_SHOT.png", D3DCOLOR_XRGB(255, 255, 255));
		sprites->Add(ITEM_UPGRADE_2, 0, 0, 27, 27, textures->Get(ID_TEX_ITEM_UPGRADE_2));
		this->width = 28;
		this->height = 28;
		break;
	case ITEM_ROSARY:
		textures->Add(ID_TEX_ITEM_ROSARY, L"textures\\ROSARY.png", D3DCOLOR_XRGB(255, 0, 255));
		sprites->Add(ITEM_ROSARY, 0, 0, 31, 31, textures->Get(ID_TEX_ITEM_ROSARY));
		this->width = 31;
		this->height = 32;
		break;
	case ITEM_MONEY_RED:
		textures->Add(ID_TEX_ITEM_MONEY, L"textures\\money.png", D3DCOLOR_XRGB(255, 0, 255));
		sprites->Add(ITEM_MONEY_RED,0 , 0, 29, 29, textures->Get(ID_TEX_ITEM_MONEY));
		this->width = 29;
		this->height = 30;
		break;
	case ITEM_MONEY_WHITE:
		textures->Add(ID_TEX_ITEM_MONEY, L"textures\\money.png", D3DCOLOR_XRGB(255, 0, 255));
		sprites->Add(ITEM_MONEY_WHITE, 30, 0, 59, 29, textures->Get(ID_TEX_ITEM_MONEY));
		this->width = 29;
		this->height = 30;
		break;
	case ITEM_MONEY_PURPLE:
		textures->Add(ID_TEX_ITEM_MONEY, L"textures\\money.png", D3DCOLOR_XRGB(255, 0, 255));
		sprites->Add(ITEM_MONEY_PURPLE, 60, 0, 89, 29, textures->Get(ID_TEX_ITEM_MONEY));
		this->width = 29;
		this->height = 30;
		break;
	case ITEM_INVISIBLE:
		textures->Add(ID_TEX_ITEM_INVISIBLE, L"textures\\INVICIBILITY_ITEM.png", D3DCOLOR_XRGB(255, 0, 255));
		sprites->Add(ITEM_INVISIBLE, 0, 0, 32, 39, textures->Get(ID_TEX_ITEM_INVISIBLE));
		this->width = 33;
		this->height = 40;
		break;
	case ITEM_STOP_WATCH:
		textures->Add(ID_TEX_ITEM_STOP_WATCH, L"textures\\STOP_WATCH.png", D3DCOLOR_XRGB(255, 0, 255));
		sprites->Add(ITEM_STOP_WATCH, 0, 0, 29, 31, textures->Get(ID_TEX_ITEM_STOP_WATCH));
		this->width = 29;
		this->height = 32;
		break;
	case ITEM_MORNINGSTAR:
		textures->Add(ID_TEX_ITEM_MORNING_STAR, L"textures\\MORNING_STAR.png", D3DCOLOR_XRGB(255, 0, 255));
		sprites->Add(ITEM_MORNINGSTAR, 0, 0, 31, 31, textures->Get(ID_TEX_ITEM_MORNING_STAR));
		this->width = 31;
		this->height = 32;
		break;
	case ITEM_SMALL_HEART:
		textures->Add(ID_TEX_ITEM_SMALL_HEART, L"textures\\SMALL_HEART.png", D3DCOLOR_XRGB(255, 0, 255));
		sprites->Add(ITEM_SMALL_HEART, 0, 0, 15, 15, textures->Get(ID_TEX_ITEM_SMALL_HEART));
		this->width = 16;
		this->height = 16;
		break;
	case ITEM_BIG_HEART:
		textures->Add(ID_TEX_ITEM_BIG_HEART, L"textures\\BIG_HEART.png", D3DCOLOR_XRGB(255, 0, 255));
		sprites->Add(ITEM_BIG_HEART, 0, 0, 23, 19, textures->Get(ID_TEX_ITEM_BIG_HEART));
		this->width = 24;
		this->height = 20;
		break;
	case ITEM_ROAST:
		textures->Add(ID_TEX_ITEM_ROAST, L"textures\\ROAST.png", D3DCOLOR_XRGB(255, 0, 255));
		sprites->Add(ITEM_ROAST, 0, 0, 31, 25, textures->Get(ID_TEX_ITEM_ROAST));
		this->width = 31;
		this->height = 26;
		break;
	case ITEM_AXE:
		textures->Add(ID_TEX_ITEM_AXE, L"textures\\AXE.png", D3DCOLOR_XRGB(255, 0, 255));
		sprites->Add(ITEM_AXE, 0, 0, 29, 27, textures->Get(ID_TEX_ITEM_AXE));
		this->width = 29;
		this->height = 28;
		break;
	case ITEM_CROSS:
		textures->Add(ID_TEX_ITEM_CROSS, L"textures\\CROSS.png", D3DCOLOR_XRGB(255, 0, 255));
		sprites->Add(ITEM_CROSS, 0, 0, 29, 27, textures->Get(ID_TEX_ITEM_CROSS));
		this->width = 29;
		this->height = 28;
		break;
	case ITEM_KNIFE:
		textures->Add(ID_TEX_ITEM_KNIFE, L"textures\\KNIFE.png", D3DCOLOR_XRGB(255, 0, 255));
		sprites->Add(ITEM_KNIFE, 0, 0, 31, 17, textures->Get(ID_TEX_ITEM_KNIFE));
		this->width = 31;
		this->height = 18;
		break;
	case ITEM_HOLY_WATER:
		textures->Add(ID_TEX_ITEM_HOLY_WATER, L"textures\\HOLY_WATER.png", D3DCOLOR_XRGB(255, 0, 255));
		sprites->Add(ITEM_HOLY_WATER, 0, 0, 31, 31, textures->Get(ID_TEX_ITEM_HOLY_WATER));
		this->width = 31;
		this->height = 32;
		break;
	
	}
	this->itemType = itemType;

}

Item::Item(int itemType)
{
	CTextures * textures = CTextures::GetInstance();
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	LPANIMATION ani;
	
	switch (itemType)
	{
	case ITEM_BALL:
		textures->Add(ID_TEX_ITEM_BALL, L"textures\\BALL.png", D3DCOLOR_XRGB(255, 0, 255));
		sprites->Add(9001, 0, 0, 27, 31, textures->Get(ID_TEX_ITEM_BALL));
		sprites->Add(9002, 28, 0, 55, 31, textures->Get(ID_TEX_ITEM_BALL));
		ani = new CAnimation(100);
		ani->Add(9001);
		ani->Add(9002);
		animations->Add(9001, ani);
		this->AddAnimation(9001);
		this->width = 28;
		this->height = 32;
		break;
	case ITEM_MONEY:
		textures->Add(ID_TEX_ITEM_MONEY, L"textures\\money.png", D3DCOLOR_XRGB(255, 0, 255));
		sprites->Add(ITEM_MONEY_RED, 0, 0, 29, 29, textures->Get(ID_TEX_ITEM_MONEY));
		sprites->Add(ITEM_MONEY_WHITE, 30, 0, 59, 29, textures->Get(ID_TEX_ITEM_MONEY));
		sprites->Add(ITEM_MONEY_PURPLE, 60, 0, 89, 29, textures->Get(ID_TEX_ITEM_MONEY));
		ani = new CAnimation(40);
		ani->Add(ITEM_MONEY_RED);
		ani->Add(ITEM_MONEY_WHITE);
		ani->Add(ITEM_MONEY_PURPLE);
		animations->Add(9002, ani);
		this->AddAnimation(9002);
		this->width = 28;
		this->height = 32;
		break;
	}
	this->itemType = itemType;
}




void Item::Random()
{
	int percent = rand() % 100; 

	if (percent < 90)
		RandomItem();
	else
		RandomSubWeapon();

}


void Item::RandomItem()
{
	int percent = rand() % 100; 

	if (percent < 60)
	{
		// If whip level of Simon is max then auto give small heart
		if (simon->GetTypeOfMorningstar() < MORNINGSTAR_2)
		{
			itemType = ITEM_MORNINGSTAR;
		}
		else
		{
			itemType = ITEM_SMALL_HEART;
		}
	}
	else if (percent < 70)
	{
		itemType = ITEM_BIG_HEART;
	}
	else if (percent < 72)
	{
		itemType = ITEM_ROAST;
	}
	else if (percent < 74)
	{
		itemType = ITEM_INVISIBLE;
	}
	else if (percent < 80)
	{
		itemType = ITEM_MONEY_RED;
	}
	else if (percent < 85)
	{
		itemType = ITEM_MONEY_PURPLE;
	}
	else if (percent < 90)
	{
		itemType = ITEM_MONEY_WHITE;
	}
	else if (percent < 95)
	{
		if (simon->GetNoSubWeapon() == 1) {
			itemType = ITEM_UPGRADE_1;
		}
		else if (simon->GetNoSubWeapon() == 2) {
			itemType = ITEM_UPGRADE_2;
		}
		else {
			itemType = ITEM_BIG_HEART;
		}
	}
	else
	{
		itemType = ITEM_ROSARY;
	}
}


void Item::RandomSubWeapon()
{
	int percent = rand() % 100; 

	if (percent < 40)
	{
		itemType = ITEM_AXE;
	}
	else if (percent < 80)
	{
		itemType = ITEM_CROSS;
	}
	else if (percent < 90)
	{
		itemType = ITEM_HOLY_WATER;
	}
	else if (percent < 95)
	{
		itemType = ITEM_KNIFE;
	}
	else
	{
		itemType = ITEM_STOP_WATCH;
	}
}

void Item::Render()
{
	
}

void Item::Render(Camera *camera)
{
	if (this->isEnable == true) {
		if (itemType == ITEM_BALL)
			animations[0]->Render(camera, x, y);
		else if (itemType == ITEM_MONEY)
				animations[0]->Render(camera, x, y);
		else {
			CSprites * sprites = CSprites::GetInstance();
			sprite = sprites->Get(itemType);
			sprite->Draw(camera, x, y);
		}
	}
}

void Item::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x+1;
	top = y+1;
	right = left+width-1;
	bottom = y+height-1;
}

void Item::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);
	if(itemType!=ITEM_MONEY)
		vy += SIMON_GRAVITY * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	if (this->isEnable == true)
	{
		CalcPotentialCollisions(coObjects, coEvents);
	}

	//reset untouchable timer if untouchable time has passed

	if (this->GetState()==ITEM_STATE_UP)
	{
		vy += -0.00100f;
		if (vy <= -0.118f)
			this->SetState(ITEM_STATE_IDLE);
		
	}


	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		//block 
			// nx*0.4f : need to push out a bit to avoid overlapping next frame

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBrick *>(e->obj))
			{
				if (e->ny < 0)
				{
					x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
					y += min_ty * dy + ny * 0.4f;

					if (nx != 0) vx = 0;
					if (ny != 0) vy = 0;
				}
			}

		}

	}

	//clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 


}

void Item::UpgradeMorningstar()
{
	simon->SetTypeOfMorningstar(simon->GetTypeOfMorningstar() + 1);
}

void Item::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case ITEM_STATE_UP:
		vy = -0.1f;
		break;
	case ITEM_STATE_IDLE:
		vy = 0;
		break;
	}
}
Item::~Item()
{
}
