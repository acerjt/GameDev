#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include "Camera.h"
using namespace std;

class CSprite
{
public: 
	int id;				
	int left;
	int top;
	int right;
	int bottom;	
	LPDIRECT3DTEXTURE9 texture;
	CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	void Draw(float x, float y, int alpha = 255);
	void Draw(Camera *camera, float x, float y, int alpha = 255);
	void Draw(D3DXVECTOR3 &pos, RECT &rect, int alpha = 255);
	void Draw(Camera* camera, D3DXVECTOR3 &pos, int alpha=255);
};

typedef CSprite * LPSPRITE;

/*
	Manage sprite database
*/
class CSprites
{
	static CSprites * __instance;

	unordered_map<int, LPSPRITE> sprites;

public:
	void Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	LPSPRITE Get(int id);

	static CSprites * GetInstance();
};

/*
	Sprite animation
*/
class CAnimationFrame
{
	LPSPRITE sprite;
	DWORD time;

public:
	CAnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }
};

typedef CAnimationFrame *LPANIMATION_FRAME;

class CAnimation
{
public:	DWORD lastFrameTime;
public: int defaultTime;
public: int currentFrame;
	vector<LPANIMATION_FRAME> frames;
public:
	CAnimation(int defaultTime) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(int spriteId, DWORD time = 0);
	virtual void Render(float x, float y, int alpha=255);
	virtual void Render(Camera *camera, float x, float y, int alpha = 255);
	int getCurrentFrame() { return currentFrame; }
	void reset() { currentFrame = -1; lastFrameTime = -1; }
};

typedef CAnimation *LPANIMATION;

class CAnimations
{
	static CAnimations * __instance;

	unordered_map<int, LPANIMATION> animations;

public:
	void Add(int id, LPANIMATION ani);
	LPANIMATION Get(int id);

	static CAnimations * GetInstance();
};

