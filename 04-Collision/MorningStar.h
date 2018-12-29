#pragma once
#include "GameObject.h"
#include "Textures.h"



#define MORNINGSTAR	0
#define MORNINGSTAR_1	1
#define MORNINGSTAR_2	2

#define MORNINGSSTAR_ANI_LEFT	 0
#define MORNINGSSTAR_ANI_RIGHT	 1
#define MORNINGSSTAR_ANI_LEFT_1  2
#define MORNINGSSTAR_ANI_RIGHT_1 3
#define MORNINGSSTAR_ANI_LEFT_2  4
#define MORNINGSSTAR_ANI_RIGHT_2 5

#define MORNINGSTAR_SET_POSITION_X				90
#define MORNINGSTAR_SET_POSITION_Y				16
#define	MORNINGSTAR_SET_POSITION_X_1			95
#define MORNINGSTAR_SET_POSITION_BOUNDINGBOX_Y	10

#define MORNINGSTAR_BBOX_WIDTH 44
#define MORNINGSTAR_BBOX_HEIGHT 42
#define MORNINGSTAR_1_BBOX_WIDTH 44
#define MORNINGSTAR_1_BBOX_HEIGHT 42
#define MORNINGSTAR_2_BBOX_WIDTH 74
#define MORNINGSTAR_2_BBOX_HEIGHT 42
class MorningStar :public CGameObject
{
private:
	int anirender;
	CAnimation * ani;
	int damage;
public:
	void Render(Camera *camera);
	void Render(Camera *camera,int ani);
	void SetPosition(float x, float y,bool Issit);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void ResetAnimation();
	int GetCurrentFrameOfMorningStar();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	MorningStar();
	~MorningStar();
};

