
#pragma once
#include <d3dx9.h>
#include <iostream>
#include <string>
//#include "GameObject.h"
using namespace std;

#define FRAME_RATE 20

class Font//:public CGameObject
{
private:
	LPD3DXFONT font;
	RECT fontPosition;
	void Render(char* text, float x, float y, D3DCOLOR color);
	DWORD localTime;
	int frameRate;
	bool isDrawAnimation;
	//void Render(char* text, float x, float y, D3DCOLOR color);
	void Initialize();

public:
	Font(LPDIRECT3DDEVICE9 d3ddev, int size, int screenWidth, int screenHeight);
	void updateAnimation();
	void render(char* text, float x, float y);
	void render(int number, float x, float y);
	void render(float number, float x, float y);
	void renderAnimation(char* text, float x, float y, int deltaTime);
	void renderAnimation(int number, float x, float y, int deltaTime);
	void onLost();
	Font();
	~Font();
};
