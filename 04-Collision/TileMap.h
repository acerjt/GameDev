#pragma once
#include <vector>
#include "Sprites.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class TileMap
{
private:
	int **matrix;			//ma tran cua tile map

	int rows;				//so hang cua tile map
	int cols;				//so cot cua tile map

	float width;			//chieu dai cua map
	float height;			//chieu cao cua map

	float frameWidth;		//chieu dai cua tung tile
	float frameHeight;		//chieu cao cua tung tile

	int spritePerRow;

	CSprite *sprite;
public:
	TileMap(float _width, float _height, CSprite *_sprite, float _frameWidth, float _frameHeight);
	~TileMap();
	
	void LoadListTileFromFile(const char* file);
	void Render(Camera *camera);
	//void SetColor(D3DCOLOR color) { sprite->SetColor(color); }
};

