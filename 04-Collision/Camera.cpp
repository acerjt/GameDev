#include "Camera.h"


Camera::Camera(float x, float y)
{
	this->cameraPosition.x = x;
	this->cameraPosition.y = y;
	this->cameraPosition.z = 0;
}


Camera::~Camera()
{
}

D3DXVECTOR3 Camera::SetPositionInViewPort(D3DXVECTOR3 position)
{

	D3DXVECTOR3 vp_pos;

	//test
	vp_pos.x = position.x - this->cameraPosition.x;
	vp_pos.y = position.y -this->cameraPosition.y;
	//--

	return D3DXVECTOR3(vp_pos.x, vp_pos.y, 0);
}

void Camera::SetCameraPosition(float x, float y)
{
	this->cameraPosition.x = x;
	this->cameraPosition.y = y;
}

D3DXVECTOR3 Camera::GetCameraPosition()
{
	return this->cameraPosition;
}
