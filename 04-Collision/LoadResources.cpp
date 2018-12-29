#include "LoadResources.h"



void LoadResources::Load(string file, vector<LPGAMEOBJECT> *listObject)
{
	ifstream input;
	input.open(file, ifstream::in);

	string checkEnd;
	int id;
	int type;
	float x;
	float y;
	int width;
	int height;

	int count = 0;

	while (input >> checkEnd)
	{
		if (checkEnd == "END")
		{
			count++;
			continue;
		}
		if (count == 0)
		{
			id = atoi(checkEnd.c_str());
			input >> type >> x >> y >> width >> height;
			LoadObject(id, type, x, y, width, height,listObject);
		}
	}
}

void LoadResources::LoadObject(int id, int type, float x, float y, int width, int height, vector<LPGAMEOBJECT> *listObject)
{
	if (type == OBJECT_SCENE)
	{
		CGameObject *object;
		object = new Scenes();
		object->SetId(id);
		object->SetType(type);
		object->SetPosition(x, y);
		object->SetWidth(width);
		object->SetHeight(height);
		listObject->push_back(object);
	}
	else if (type == OBJECT_BATSTART)
		{
			CGameObject *object;
			object = new Batstartgame();
			object->SetId(id);
			object->SetType(type);
			object->SetWidth(width);
			object->SetHeight(height);
			object->SetPosition(x, y);
			listObject->push_back(object);
		}
	else  if (type == OBJECT_BRICK)
	{
		CGameObject *object;
		object = new CBrick();
		object->SetType(type);
		object->SetId(id);
		object->SetPosition(x, y);
		object->SetWidth(width);
		object->SetHeight(height);
		listObject->push_back(object);
	}
	else  if (type == OBJECT_BRICK_1)
	{
		CGameObject *object;
		object = new CBrick();
		object->SetType(type);
		object->SetId(id);
		object->SetPosition(x, y);
		object->SetWidth(width);
		object->SetHeight(height);
		listObject->push_back(object);
	}
	else  if (type == OBJECT_BRICK_2)
	{
		CGameObject *object;
		object = new CBrick();
		object->SetType(type);
		object->SetId(id);
		object->SetPosition(x, y);
		object->SetWidth(width);
		object->SetHeight(height);
		listObject->push_back(object);
	}
	else  if (type == OBJECT_TORCH)
	{
		CGameObject *object;
		object = new Torch();
		object->SetId(id);
		object->SetType(type);
		object->SetPosition(x, y);
		object->SetWidth(width);
		object->SetHeight(height);
		listObject->push_back(object);
	}
	else  if (type == OBJECT_CANDLE)
	{
		Candle *object;
		object = new Candle();
		object->SetId(id);
		object->SetType(type);
		object->SetPosition(x, y);
		object->SetWidth(width);
		object->SetHeight(height);
		listObject->push_back(object);
	}
	else  if (type == OBJECT_STAIR)
	{
		Stair *object;
		object = new Stair();
		object->SetId(id);
		object->SetType(type);
		object->SetPosition(x, y);
		object->SetWidth(width);
		object->SetHeight(height);
		listObject->push_back(object);
	}
	else  if (type == OBJECT_STAIR_1)
	{
		Stair *object;
		object = new Stair();
		object->SetId(id);
		object->SetType(type);
		object->SetPosition(x, y);
		object->SetWidth(width);
		object->SetHeight(height);
		listObject->push_back(object);
	}
	else if (type == OBJECT_STAIR_DOWN_LEFT)
	{
	StairCheckObject *object;
	object = new StairCheckObject();
	object->SetId(id);
	object->SetType(type);
	object->SetPosition(x, y);
	object->SetWidth(width);
	object->SetHeight(height);
	listObject->push_back(object);
	}
	else if (type == OBJECT_STAIR_DOWN_RIGHT)
	{
	StairCheckObject *object;
	object = new StairCheckObject();
	object->SetId(id);
	object->SetType(type);
	object->SetPosition(x, y);
	object->SetWidth(width);
	object->SetHeight(height);
	listObject->push_back(object);
	}
	else if (type == OBJECT_STAIR_UP_LEFT)
	{
	StairCheckObject *object;
	object = new StairCheckObject();
	object->SetId(id);
	object->SetType(type);
	object->SetPosition(x, y);
	object->SetWidth(width);
	object->SetHeight(height);
	listObject->push_back(object);
	}
	else if (type == OBJECT_STAIR_UP_RIGHT)
	{
	StairCheckObject *object;
	object = new StairCheckObject();
	object->SetId(id);
	object->SetType(type);
	object->SetPosition(x, y);
	object->SetWidth(width);
	object->SetHeight(height);
	listObject->push_back(object);
	}
	else if (type == OBJECT_WALL)
	{
	Wall *object;
	object = new Wall();
	object->SetId(id);
	object->SetType(type);
	object->SetPosition(x, y);
	object->SetWidth(width);
	object->SetHeight(height);
	listObject->push_back(object);
	}
	else if (type == OBJECT_WALL_1)
	{
	Wall *object;
	object = new Wall();
	object->SetId(id);
	object->SetType(type);
	object->SetPosition(x, y);
	object->SetWidth(width);
	object->SetHeight(height);
	listObject->push_back(object);
	}
	else if (type == OBJECT_CANDLE)
	{
	Candle *object;
	object = new Candle();
	object->SetId(id);
	object->SetType(type);
	object->SetPosition(x, y);
	object->SetWidth(width);
	object->SetHeight(height);
	listObject->push_back(object);
	}
}

LoadResources::LoadResources()
{
}


LoadResources::~LoadResources()
{
}
