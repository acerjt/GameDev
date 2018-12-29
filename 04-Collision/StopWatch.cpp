#include "StopWatch.h"
#include "Enemy.h"


void StopWatch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	Enemy::IsStop = true;
	Enemy::StartTimeStop();
	if (Enemy::timestop_start > 5000)
		isEnable = false;
}

void StopWatch::Render(Camera * camera)
{
}

void StopWatch::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
}


StopWatch::StopWatch()
{
	useEnergy = 5;
}


StopWatch::~StopWatch()
{
}
