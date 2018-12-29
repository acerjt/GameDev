#pragma once
#include "Enemy.h"
#define BLACK_LEOPARD_WALKING_SPEED 0.17f
#define BLACK_LEOPARD_JUMP_SPEED	0.4f

#define BLACK_LEOPARD_BBOX_WIDTH 56
#define BLACK_LEOPARD_BBOX_HEIGHT 32

#define BLACK_LEOPARD_STATE_WALKING_LEFT	100
#define BLACK_LEOPARD_STATE_WALKING_RIGHT	200					
#define BLACK_LEOPARD_STATE_IDLE			300
#define BLACK_LEOPARD_STATE_JUMP			400
#define BLACK_LEOPARD_STATE_WALKING			500

#define BLACK_LEOPARD_ANI_IDLE_LEFT		0
#define BLACK_LEOPARD_ANI_WALKING_LEFT	1
#define BLACK_LEOPARD_ANI_JUMP_LEFT		2
#define BLACK_LEOPARD_ANI_IDLE_RIGHT	3
#define BLACK_LEOPARD_ANI_WALKING_RIGHT	4
#define BLACK_LEOPARD_ANI_JUMP_RIGHT	5
#define BLACK_LEOPARD_ANI_DIE 10
class BlackLeopard:public Enemy
{
	bool IsJump;
	int ani;
	bool isGroundedNext;
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render(Camera *camera);
	void SetState(int state);
	void SetIsGroundNexTFrame(bool isground) { this->isGroundedNext = isground; }
	BlackLeopard();
	~BlackLeopard();
};

