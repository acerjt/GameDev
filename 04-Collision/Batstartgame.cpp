#include "Batstartgame.h"


void Batstartgame::Update(DWORD dt)
{

}



void Batstartgame::Render(Camera *camera)
{
	animations[0]->Render1(camera,x, y);
}

void Batstartgame::Render()
{
	animations[0]->Render1(x, y);
}
Batstartgame::Batstartgame():CGameObject()
{
	CTextures * textures = CTextures::GetInstance();
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	LPANIMATION ani;

	textures->Add(ID_TEX_START_GAME, L"textures\\startgame.png", D3DCOLOR_XRGB(128, 0, 0));
	LPDIRECT3DTEXTURE9 texbatstartgame = textures->Get(ID_TEX_START_GAME);
	sprites->Add(2001, 540, 41, 684, 148, texbatstartgame);
	sprites->Add(2002, 691, 41, 835, 148, texbatstartgame);
	sprites->Add(2003, 841, 41, 985, 148, texbatstartgame);
	sprites->Add(2004, 992, 41, 1136, 148, texbatstartgame);
	sprites->Add(2005, 1139, 41, 1283, 148, texbatstartgame);

	sprites->Add(2006, 540, 152, 684, 259, texbatstartgame);
	sprites->Add(2007, 691, 152, 835, 259, texbatstartgame);
	sprites->Add(2008, 841, 152, 985, 259, texbatstartgame);
	sprites->Add(2009, 992, 152, 1136, 259, texbatstartgame);
	sprites->Add(2010, 1139, 152, 1283, 259, texbatstartgame);

	sprites->Add(2011, 540, 263, 684, 370, texbatstartgame);
	sprites->Add(2012, 691, 263, 835, 370, texbatstartgame);
	sprites->Add(2013, 841, 263, 985, 370, texbatstartgame);
	sprites->Add(2014, 992, 263, 1136, 370, texbatstartgame);
	sprites->Add(2015, 1139, 263, 1283, 370, texbatstartgame);

	ani = new CAnimation(65);	// walk right big
	ani->Add(2001);
	ani->Add(2002);
	ani->Add(2003);
	ani->Add(2004);
	ani->Add(2005);
	ani->Add(2006);
	ani->Add(2007);
	ani->Add(2008);
	ani->Add(2009);
	ani->Add(2010);
	ani->Add(2011);
	ani->Add(2012);
	ani->Add(2013);
	ani->Add(2014);
	ani->Add(2015);
	animations->Add(2001, ani);
	this->AddAnimation(2001);
}
Batstartgame::~Batstartgame()
{
}









void Batstartgame::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BAT_ST_BBOX_WIDTH;
	b = y + BAT_ST_BBOX_HEIGHT;
}



