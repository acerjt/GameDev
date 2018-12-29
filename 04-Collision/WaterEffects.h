#pragma once
#include "WaterEffect.h"
class WaterEffects
{
private:
	D3DXVECTOR3 position;
	D3DXVECTOR3 velocity[3];
	WaterEffect *watereffect[3];
	bool isEnable;
public:
	WaterEffects();
	~WaterEffects();
	void SetPosition(float x, float y);
	D3DXVECTOR3 GetPosition() { return position; }
	void Render(Camera *camera);
	void Update(DWORD dt);
	void SetVelocity();
	bool IsEnable() { return isEnable; }
	void SetEnable(bool _isEnable) { isEnable = _isEnable; }
};

