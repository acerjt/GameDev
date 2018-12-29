/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102
	
	SAMPLE 04 - COLLISION

	This sample illustrates how to:

		1/ Implement SweptAABB algorithm between moving objects
		2/ Implement a simple (yet effective) collision frame work

	Key functions: 
		CGame::SweptAABB
		CGameObject::SweptAABBEx
		CGameObject::CalcPotentialCollisions
		CGameObject::FilterCollision

		CGameObject::GetBoundingBox
		
================================================================ */

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Simon.h"
#include "Camera.h"
#include "StateManager.h"
#include <string>
#include <iostream>
#include <fstream>
#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"04 - Collision"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)


#define MAX_FRAME_RATE 120


CGame *game;
Camera *camera;
static Simon *simon;
StateManager* stateManager;



class CSampleKeyHander: public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler; 

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
		
	case DIK_S:
		if (simon->IsJump == false && simon->isControlKey())
		{
			simon->SetState(SIMON_STATE_JUMP);
		}
		break;
	case DIK_Z:
		GameState::changeState=true;
		break;
	case DIK_RETURN:  
		if (stateManager->stateID == STATE_START_GAME)
			StateStartGame::isPress = true;
		break;
	case DIK_X:
		if(simon->isControlKey())
			simon->StartThrowing();
			break;
	case DIK_0:
		simon->SetPosition(300, 0);
		break;
	case DIK_1:
		simon->SetPosition(2800,0);
		break;
	case DIK_2:
		simon->SetPosition(3300, 258);
		break;
	case DIK_3:
		simon->SetPosition(3700, 0);
		break;
	case DIK_4:
		simon->SetPosition(5000, 0);
		break;
	case DIK_Q:
		simon->SetTypeOfWeapon(ITEM_AXE);
		break;
	case DIK_W:
		simon->SetTypeOfWeapon(ITEM_BOOMERANG);
		break;
	case DIK_E:
		simon->SetTypeOfWeapon(ITEM_DAGGER);
		break;
	case DIK_R:
		simon->SetTypeOfWeapon(ITEM_HOLY_WATER);
		break;
	case DIK_T:
		simon->SetTypeOfWeapon(ITEM_STOP_WATCH);
		break;
	case DIK_D:
		if(simon->GetNumberOfWeapon()<3)
		simon->IncreaseWeapon();
		break;
	}
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}
	

void CSampleKeyHander::KeyState(BYTE *states)
{

		if (simon->GetState() == SIMON_STATE_DIE) return;
		if (simon->isControlKey())
		{	
		if (game->IsKeyDown(DIK_A))
			simon->StartFighting();
	
		 if (game->IsKeyDown(DIK_RIGHT) &&simon->IsHurt==false)
				simon->SetState(SIMON_STATE_WALKING_RIGHT);
			else if (game->IsKeyDown(DIK_LEFT) && simon->IsHurt == false)
				simon->SetState(SIMON_STATE_WALKING_LEFT);
			else if (game->IsKeyDown(DIK_DOWN))
				simon->SetState(SIMON_STATE_SIT);
			else if(!simon->IsHurt)
				simon->SetState(SIMON_STATE_IDLE);
		 if ((game->IsKeyDown(DIK_UP)))
			 simon->OnStairHandle(1);
		 if ((game->IsKeyDown(DIK_DOWN)))
			 simon->OnStairHandle(2);
		}
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources 
	In this example: load textures, sprites, animations and mario object

	TO-DO: Improve this function by loading texture,sprite,animation,object from file
*/
void LoadResources(LPDIRECT3DDEVICE9 d3ddv, LPD3DXSPRITE sprite)
{
	simon = new Simon();
	camera = new Camera(0, 0);
	stateManager = new StateManager(d3ddv,sprite);
	stateManager->LoadState(STATE_START_GAME,simon);
}
void LoadTextures(wstring file)
{
	wifstream input;
	input.open(file, wifstream::in);
	wstring checkEnd;
	int id;
	wstring filepath;
	int Color_R;
	int Color_G;
	int Color_B;
	while (input >> checkEnd)
	{
		if (checkEnd == L"END")
		{
			return;
		}
		else 
		{
			id = stoi(checkEnd.c_str());
			input >> filepath >> Color_R >> Color_G >> Color_B;
			CTextures * textures = CTextures::GetInstance();
			LPCWSTR a = (LPCWSTR)filepath.c_str();
			textures->Add(id, a, D3DCOLOR_XRGB(Color_R, Color_G, Color_B));		
		}
	}
}
void LoadSprites(wstring file)
{
	wifstream input;
	input.open(file, wifstream::in);
	wstring checkEnd;
	int id;
	int left;
	int top;
	int right;
	int bottom;
	int idtexture;
	while (input >> checkEnd)
	{
		if (checkEnd == L"END")
		{
			return;
		}
		else
		{
			id = stoi(checkEnd.c_str());
			input >> left >> top >> right >> bottom >> idtexture;
			CTextures * textures = CTextures::GetInstance();
			CSprites * sprites = CSprites::GetInstance();
			sprites->Add(id, left, top, right, bottom, textures->Get(idtexture));
		}
	}
}
void LoadAnimations(wstring file)
{
	wifstream input;
	input.open(file, wifstream::in);
	wstring checkEnd;
	int id;
	int frames;
	int time;
	while (input >> checkEnd)
	{
		if (checkEnd == L"END")
		{
			return;
		}
		else
		{
			id = stoi(checkEnd.c_str());
			input >> time >>frames;
			CAnimations * animations = CAnimations::GetInstance();
			LPANIMATION ani;
			ani = new CAnimation(time);
			int *x;
			x = new int[frames];
			for (int i = 0; i < frames; i++)
			{
				input >> x[i];
				ani->Add(x[i]);
			}
			animations->Add(id, ani);
		}
	}
}
/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	stateManager->Update(dt);
}

/*
	Render a frame 
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		//// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, game->color);
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		stateManager->Render(camera);

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd) 
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();
			
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);	
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);
	LoadTextures(L"loadresourcesfromfile\\texture_load.txt");
	LoadSprites(L"loadresourcesfromfile\\sprite_load.txt");
	LoadAnimations(L"loadresourcesfromfile\\animation_load.txt");
	LoadResources(game->d3ddv,game->spriteHandler);
	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}