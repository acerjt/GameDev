#include "WaterEffects.h"



WaterEffects::WaterEffects()
{
	for (int i = 0; i < 3; i++)
	{
		watereffect[i] = new WaterEffect();	
	}
	isEnable = false;
}


WaterEffects::~WaterEffects()
{
}

void WaterEffects::SetPosition(float x, float y)
{
	for (int i = 0; i < 3; i++)
	{
		watereffect[i]->SetPosition(x, y);
	}
}

void WaterEffects::Render(Camera * camera)
{
	for (int i = 0; i < 3; i++)
		watereffect[i]->Render(camera);
}

void WaterEffects::Update(DWORD dt)
{
	for (int i = 0; i < 3; i++)
	{
		watereffect[i]->SetPosition(watereffect[i]->GetPosition().x + velocity[i].x * dt,
			watereffect[i]->GetPosition().y + velocity[i].y  * dt);
		velocity[i].y += 0.0008 * dt;
	}
	position = watereffect[1]->GetPosition();
}

void WaterEffects::SetVelocity()
{
	velocity[0].x = -0.05;
	velocity[0].y = 0.03;

	velocity[1].x = 0;
	velocity[1].y = 0.035;

	velocity[2].x = 0.05;
	velocity[2].y = 0.03;
}
