#pragma once
#include <d3dx9.h>
#include "Define.h"

class Camera
{
private:
	D3DXVECTOR3 cameraPosition;
public:
	Camera(float x, float y);
	~Camera();
	D3DXVECTOR3 SetPositionInCamera(D3DXVECTOR3 position);
	void SetCameraPosition(float x, float y);
	D3DXVECTOR3 GetCameraPosition();
};

