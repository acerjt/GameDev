#include "Item.h"
#include "Brick.h"

Simon* Item::simon = NULL;

void Item::TakeSimonPointer(Simon *simon)
{
	Item::simon = simon;
}

Item::Item()
{
	srand(time(0));
	Random();
	switch (itemType) {
	case ITEM_UPGRADE_1:
		this->width = 28;
		this->height = 28;
		break;
	case ITEM_UPGRADE_2:
		this->width = 28;
		this->height = 28;
		break;
	case ITEM_CROSS:
		this->width = 31;
		this->height = 32;
		break;
	case ITEM_MONEY_RED:
		this->width = 29;
		this->height = 30;
		break;
	case ITEM_MONEY_WHITE:
		this->width = 29;
		this->height = 30;
		break;
	case ITEM_MONEY_PURPLE:
		this->width = 29;
		this->height = 30;
		break;
	case ITEM_INVISIBLE:
		this->width = 33;
		this->height = 40;
		break;
	case ITEM_STOP_WATCH:
		this->width = 29;
		this->height = 32;
		break;
	case ITEM_MORNINGSTAR:
		this->width = 30;
		this->height = 32;
		break;
	case ITEM_SMALL_HEART:
		this->width = 14;
		this->height = 16;
		break;
	case ITEM_BIG_HEART:
		this->width = 24;
		this->height = 20;
		break;
	case ITEM_ROAST:
		this->width = 30;
		this->height = 26;
		break;
	case ITEM_AXE:
		this->width = 29;
		this->height = 28;
		break;
	case ITEM_BOOMERANG:
		this->width = 30;
		this->height = 28;
		break;
	case ITEM_DAGGER:
		this->width = 30;
		this->height = 18;
		break;
	case ITEM_HOLY_WATER:
		this->width = 30;
		this->height = 32;
		break;
	
	}
	this->itemType = itemType;

}

Item::Item(int itemType)
{
	switch (itemType)
	{
	case ITEM_BALL:
		this->AddAnimation(9001);
		this->width = 28;
		this->height = 32;
		break;
	case ITEM_MONEY:
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
		RandomWeapon();

}


void Item::RandomItem()
{
	int percent = rand() % 100; 

	if (percent < 60)
	{
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
		if (simon->GetNumberOfWeapon() == 1) {
			itemType = ITEM_UPGRADE_1;
		}
		else if (simon->GetNumberOfWeapon() == 2) {
			itemType = ITEM_UPGRADE_2;
		}
		else {
			itemType = ITEM_BIG_HEART;
		}
	}
	else
	{
		itemType = ITEM_CROSS;
	}
}


void Item::RandomWeapon()
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
		itemType = ITEM_DAGGER;
	}
	else
	{
		itemType = ITEM_STOP_WATCH;
	}
}

void Item::Render()
{
	CSprites * sprites = CSprites::GetInstance();
	sprite = sprites->Get(itemType);
	sprite->Draw(x, y);
	
}

void Item::Render(Camera *camera)
{
	if (this->isEnable == true) {
		if (itemType == ITEM_BALL)
			animations[0]->Render(camera, x, y);
		else if (itemType == ITEM_MONEY)
		{
			animations[0]->Render(camera, x, y);
			anirender = animations[0];
		}
		else {
			CSprites * sprites = CSprites::GetInstance();
			sprite = sprites->Get(itemType);
			sprite->Draw(camera, x, y);
		}
	}
}
int Item::GetCurrentFrame()
{
	return anirender->getCurrentFrame();
}

void Item::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x-1;
	top = y;
	right = x+width;
	bottom = y+height;
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
