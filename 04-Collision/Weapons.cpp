#include "Weapons.h"
#include "Brick.h"
#include "Enemy.h"
#include "Simon.h"

Weapons::Weapons()
{
	isEnable = false;
}


Weapons::~Weapons()
{
}


void Weapons::Update(int t,DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	
	if (nx > 0)
		vx = 0.2;
	else if (nx < 0)
		vx = -0.2;
	if (dynamic_cast<HolyWater *>(this))
	{
		HolyWater*holywater = dynamic_cast<HolyWater *>(this);
		if (holywater->IsFire())
		{
			vx = 0;
			vy = 0;
		}
	}	
	CGameObject::Update(dt);
	x += dx;
	y += dy;
	if (dynamic_cast<Axe *>(this))
	{
		Axe*axe = dynamic_cast<Axe *>(this);
		axe->Update(t, dt, coObjects);
	}
	else
		if (dynamic_cast<Dagger *>(this))
		{
			Dagger*dagger = dynamic_cast<Dagger *>(this);
			dagger->Update(t, dt, coObjects);
		}
		else
			if (dynamic_cast<Boomerang *>(this))
			{
				Boomerang*boomerang = dynamic_cast<Boomerang *>(this);
				boomerang->Update(t, dt, coObjects);
			}
			else
				if (dynamic_cast<HolyWater *>(this))
				{
					HolyWater*holywater = dynamic_cast<HolyWater *>(this);
					holywater->Update(t, dt, coObjects);
					return;
				}
				else
					if (dynamic_cast<StopWatch *>(this))
					{
						StopWatch*stopwatch = dynamic_cast<StopWatch *>(this);
						stopwatch->Update(dt, coObjects);
						return;
					}
}
void Weapons::ResetAnimation()
{
	resetAni(0);
	resetAni(1);
}
void Weapons::Render(Camera * camera)
{
	if (nx > 0)
		animations[1]->Render(camera, x, y);
	else if (nx < 0)
		animations[0]->Render(camera, x, y);
	D3DXVECTOR3 currentcamera = camera->GetCameraPosition();
	if (x < currentcamera.x || x>currentcamera.x + SCREEN_WIDTH)
	{
		isEnable = false;
	}
}







void Weapons::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{

}



//
//void Weapons::CheckCollider(float gameTime, std::vector<GameObject*> *listGameObject)
//{
//	float normalX = 0;
//	float normalY = 0;
//	float timeCollide;
//
//	for (std::vector<GameObject*>::iterator i = listGameObject->begin(); i != listGameObject->end(); i++)
//	{
//		Box tempBox = (*i)->GetCollider()->GetBox();
//		if (collider->AABBCheck(collider->GetBox(), (*i)->GetCollider()->GetBox()))
//		{
//			if ((*i)->GetTag() < 10 && (*i)->GetTag() >= 0)
//			{
//				if (((Enemy*)(*i))->e_isInvincible == false)
//				{
//					((Enemy*)(*i))->SetHP(((Enemy*)(*i))->GetHP() - GetDamage());
//					anim->DoAnimation(1);
//					this->sprite->SetPosition(-1000, -1000);
//					(*i)->GetCollideEffect()->SetVisible(true);
//				}
//			}
//			else if ((*i)->GetTag() == 2000)
//			{
//				if (((Batman*)(*i))->isHurted == false)
//				{
//					((Enemy*)(*i))->SetHP(((Enemy*)(*i))->GetHP() - GetDamage());
//					//((Batman*)(*i))->isHurted = true;
//					anim->DoAnimation(1);
//					this->sprite->SetPosition(-1000, -1000);
//					(*i)->GetCollideEffect()->SetVisible(true);
//				}
//			}
//			else if ((*i)->GetTag() == 2001)
//			{
//				if (((Medusa*)(*i))->isHurted == false)
//				{
//					((Enemy*)(*i))->SetHP(((Enemy*)(*i))->GetHP() - GetDamage());
//					anim->DoAnimation(1);
//					this->sprite->SetPosition(-1000, -1000);
//					(*i)->GetCollideEffect()->SetVisible(true);
//				}
//			}
//			/*if ((*i)->GetTag() < 10 && (*i)->GetTag() >= 0)
//			{
//				((Enemy*)(*i))->SetHP(((Enemy*)(*i))->GetHP() - 2);
//				anim->DoAnimation(1);
//				this->sprite->SetPosition(-1000, -1000);
//				(*i)->GetCollideEffect()->SetVisible(true);
//			}*/
//			else
//				if ((*i)->GetTag() == TAG_GROUND)
//				{
//					anim->DoAnimation(1);
//					this->sprite->SetPosition(-1000, -1000);
//				}
//		}
//		else
//		{
//			Box broadphaseBox = collider->GetSweptBoardphaseBox(collider->GetBox(), gameTime);
//			if (collider->AABBCheck(broadphaseBox, (*i)->GetCollider()->GetBox()))
//			{
//				Box tempBox = (*i)->GetCollider()->GetBox();
//				timeCollide = collider->SweptAABB(gameTime, collider->GetBox(), (*i)->GetCollider()->GetBox(), normalX, normalY);
//				if ((timeCollide >= 0.0f && timeCollide < 1.0f))
//				{
//					if ((*i)->GetTag() < 10 && (*i)->GetTag() >= 0)
//					{
//						if (((Enemy*)(*i))->e_isInvincible == false)
//						{
//							((Enemy*)(*i))->SetHP(((Enemy*)(*i))->GetHP() - GetDamage());
//							anim->DoAnimation(1);
//							this->sprite->SetPosition(-1000, -1000);
//							(*i)->GetCollideEffect()->SetVisible(true);
//						}
//					}
//					else if ((*i)->GetTag() == 2000)
//					{
//						if (((Batman*)(*i))->isHurted == false)
//						{
//							((Enemy*)(*i))->SetHP(((Enemy*)(*i))->GetHP() - GetDamage());
//							//((Batman*)(*i))->isHurted = true;
//							anim->DoAnimation(1);
//							this->sprite->SetPosition(-1000, -1000);
//							(*i)->GetCollideEffect()->SetVisible(true);
//						}
//					}
//					else if ((*i)->GetTag() == 2001)
//					{
//						if (((Medusa*)(*i))->isHurted == false)
//						{
//							((Enemy*)(*i))->SetHP(((Enemy*)(*i))->GetHP() - GetDamage());
//							anim->DoAnimation(1);
//							this->sprite->SetPosition(-1000, -1000);
//							(*i)->GetCollideEffect()->SetVisible(true);
//						}
//					}
//					/*if ((*i)->GetTag() < 10 && (*i)->GetTag() >= 0)
//					{
//						((Enemy*)(*i))->SetHP(((Enemy*)(*i))->GetHP() - 2);
//						anim->DoAnimation(1);
//						this->sprite->SetPosition(-1000, -1000);
//						(*i)->GetCollideEffect()->SetVisible(true);
//					}*/
//					else
//						if ((*i)->GetTag() == TAG_GROUND)
//						{
//							anim->DoAnimation(1);
//							this->sprite->SetPosition(-1000, -1000);
//						}
//				}
//			}
//		}
//	}
//}
//
//bool Weapons::CheckColliderWith(float gameTime, GameObject * gameObject)
//{
//	float normalX = 0;
//	float normalY = 0;
//	float timeCollide;
//
//	Box tempBox = gameObject->GetCollider()->GetBox();
//	if (collider->AABBCheck(collider->GetBox(), gameObject->GetCollider()->GetBox()))
//	{
//		return true;
//	}
//	else
//	{
//		Box broadphaseBox = collider->GetSweptBoardphaseBox(collider->GetBox(), gameTime);
//		if (collider->AABBCheck(broadphaseBox, gameObject->GetCollider()->GetBox()))
//		{
//			Box tempBox = gameObject->GetCollider()->GetBox();
//			timeCollide = collider->SweptAABB(gameTime, collider->GetBox(), gameObject->GetCollider()->GetBox(), normalX, normalY);
//			if ((timeCollide >= 0.0f && timeCollide < 1.0f))
//			{
//				return true;
//			}
//		}
//	}
//	return false;
//}
//
//void Weapons::CheckColliderWithBoss(float gameTime, GameObject *object)
//{
//	if (object->IsEnable() == true && ((Batman*)object)->isHurted == false)
//	{
//		float normalX = 0;
//		float normalY = 0;
//		float timeCollide;
//
//		/*Box tempBox = (object)->GetCollider()->GetBox();
//		if (collider->AABBCheck(collider->GetBox(), object->GetCollider()->GetBox()))
//		{
//			((Enemy*)object)->SetHP(((Enemy*)object)->GetHP() - 2);
//			((Batman*)object)->isHurted = true;
//		}*/
//
//		Box broadphaseBox = collider->GetSweptBoardphaseBox(collider->GetBox(), gameTime);
//		if (collider->AABBCheck(broadphaseBox, object->GetCollider()->GetBox()))
//		{
//			Box tempBox = object->GetCollider()->GetBox();
//			timeCollide = collider->SweptAABB(gameTime, collider->GetBox(), object->GetCollider()->GetBox(), normalX, normalY);
//			if ((timeCollide >= 0.0f && timeCollide < 1.0f))
//			{
//				((Enemy*)object)->SetHP(((Enemy*)object)->GetHP() - 2);
//				((Batman*)object)->isHurted = true;
//				object->GetCollideEffect()->SetVisible(true);
//			}
//		}
//	}
//}