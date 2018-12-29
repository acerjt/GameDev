#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "GameObject.h"
#include "Scenes.h"
#include "Define.h"
#include "Batstartgame.h"
#include "StartKeyObject.h"
#include "Brick.h"
#include "Torch.h"
#include "Candle.h"
#include "Stair.h"
#include "StairCheckObject.h"
#include "Wall.h"
class LoadResources
{
public:
	void Load(string file, vector<LPGAMEOBJECT> *listObject);
	void LoadObject(int id, int type, float x, float y, int width, int height, vector<LPGAMEOBJECT> *listObject);
	LoadResources();
	~LoadResources();
};

