#include "StateStartGame.h"

bool StateStartGame::isPress = false;

StateStartGame::StateStartGame()
{
	changeState = false;
	camera = new Camera(0, 0);
	scene = new Scenes();
	scene->SetPosition(0, 6);
	batstartgame = new Batstartgame();
	batstartgame->SetPosition(366.0f, 194);
	startkeyobject = new StartKeyObject(222,20);
	startkeyobject->SetPosition(143, 251);
	simon = new Simon();
	simon->SetControlKey(false);
}


StateStartGame::~StateStartGame()
{
}
void StateStartGame::Render(Camera *camera)
{
	scene->Render(camera);
	batstartgame->Render(camera);
	startkeyobject->Render(camera);
}

void StateStartGame::Update(DWORD dt)
{ 
	batstartgame->Update(dt);
	if (isPress==true)
	{ 
		CAnimations * animations = CAnimations::GetInstance();
		LPANIMATION ani;
		if (batstartgame->GetAnimation() < 2)
		{
			if (batstartgame->GetAnimation() == 0)
			{
				if (batstartgame->GetCurrentFrameOfBatstartgame() == 0)
				{
					ani = new CAnimation(65);
					ani->Add(2001);
					animations->Add(2003, ani);
					batstartgame->AddAnimation(2003);
					batstartgame->SetAnimation(2);
				}
				if (batstartgame->GetCurrentFrameOfBatstartgame() == 1)
				{
					ani = new CAnimation(65);
					ani->Add(2002);
					animations->Add(2003, ani);
					batstartgame->AddAnimation(2003);
					batstartgame->SetAnimation(2);
				}
				if (batstartgame->GetCurrentFrameOfBatstartgame() == 2)
				{
					ani = new CAnimation(65);
					ani->Add(2003);
					animations->Add(2003, ani);
					batstartgame->AddAnimation(2003);
					batstartgame->SetAnimation(2);
				}
				if (batstartgame->GetCurrentFrameOfBatstartgame() == 3)
				{
					ani = new CAnimation(65);
					ani->Add(2004);
					animations->Add(2003, ani);
					batstartgame->AddAnimation(2003);
					batstartgame->SetAnimation(2);
				}
				if (batstartgame->GetCurrentFrameOfBatstartgame() == 4)
				{
					ani = new CAnimation(65);
					ani->Add(2005);
					animations->Add(2003, ani);
					batstartgame->AddAnimation(2003);
					batstartgame->SetAnimation(2);
				}
				if (batstartgame->GetCurrentFrameOfBatstartgame() == 5)
				{
					ani = new CAnimation(65);
					ani->Add(2006);
					animations->Add(2003, ani);
					batstartgame->AddAnimation(2003);
					batstartgame->SetAnimation(2);
				}
				if (batstartgame->GetCurrentFrameOfBatstartgame() == 6)
				{
					ani = new CAnimation(65);
					ani->Add(2007);
					animations->Add(2003, ani);
					batstartgame->AddAnimation(2003);
					batstartgame->SetAnimation(2);
				}
				if (batstartgame->GetCurrentFrameOfBatstartgame() == 7)
				{
					ani = new CAnimation(65);
					ani->Add(2008);
					animations->Add(2003, ani);
					batstartgame->AddAnimation(2003);
					batstartgame->SetAnimation(2);
				}
				if (batstartgame->GetCurrentFrameOfBatstartgame() == 8)
				{
					ani = new CAnimation(65);
					ani->Add(2009);
					animations->Add(2003, ani);
					batstartgame->AddAnimation(2003);
					batstartgame->SetAnimation(2);
				}
				if (batstartgame->GetCurrentFrameOfBatstartgame() == 9)
				{
					ani = new CAnimation(65);
					ani->Add(2010);
					animations->Add(2003, ani);
					batstartgame->AddAnimation(2003);
					batstartgame->SetAnimation(2);
				}
				if (batstartgame->GetCurrentFrameOfBatstartgame() == 10)
				{
					ani = new CAnimation(65);
					ani->Add(2011);
					animations->Add(2003, ani);
					batstartgame->AddAnimation(2003);
					batstartgame->SetAnimation(2);
				}
				if (batstartgame->GetCurrentFrameOfBatstartgame() == 11)
				{
					ani = new CAnimation(65);
					ani->Add(2012);
					animations->Add(2003, ani);
					batstartgame->AddAnimation(2003);
					batstartgame->SetAnimation(2);
				}
				if (batstartgame->GetCurrentFrameOfBatstartgame() == 12)
				{
					ani = new CAnimation(65);
					ani->Add(2013);
					animations->Add(2003, ani);
					batstartgame->AddAnimation(2003);
					batstartgame->SetAnimation(2);
				}
			}
			if (batstartgame->GetAnimation() == 1)
			{
				if (batstartgame->GetCurrentFrameOfBatstartgame() == 0)
				{
					ani = new CAnimation(65);
					ani->Add(2013);
					animations->Add(2003, ani);
					batstartgame->AddAnimation(2003);
					batstartgame->SetAnimation(2);
				}
				if (batstartgame->GetCurrentFrameOfBatstartgame() == 1)
				{
					ani = new CAnimation(65);
					ani->Add(2014);
					animations->Add(2003, ani);
					batstartgame->AddAnimation(2003);
					batstartgame->SetAnimation(2);
				}
				if (batstartgame->GetCurrentFrameOfBatstartgame() == 2)
				{
					ani = new CAnimation(65);
					ani->Add(2015);
					animations->Add(2003, ani);
					batstartgame->AddAnimation(2003);
					batstartgame->SetAnimation(2);
				}
			}
		}
		
		startkeyobject->Update(dt);
		timeDelay += dt;
		if (timeDelay >= STATE_START_GAME_LIVE_TIME)
		{
			SetChangingState(true);
		}
		
	}	
}
bool StateStartGame::GetChangingState()
{
	return GameState::GetChangingState();
}
void StateStartGame::SetChangingState(bool status)
{
	GameState::SetChangingState(status);
}

void StateStartGame::DestroyAll() 
{
	delete(camera);
	listObject.clear();
	coObjects.clear();
	delete(scene);
	delete(batstartgame);
	delete(startkeyobject);
}


