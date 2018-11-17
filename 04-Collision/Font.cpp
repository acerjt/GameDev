#include "Font.h"

void Font::Initialize()
{
	localTime = 0;
	frameRate = FRAME_RATE;
	isDrawAnimation = true;
}

Font::Font(LPDIRECT3DDEVICE9 d3ddev, int size, int screenWidth, int screenHeight)
{
	this->Initialize();
	fontPosition.top = 0;
	fontPosition.left = 0;
	fontPosition.right = screenWidth;
	fontPosition.bottom = screenHeight;
	D3DXFONT_DESC FontDesc = {
		size,
		0,
		400,
		0,
		false,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_PITCH, L"Arial" };

	//create font
	D3DXCreateFontIndirect(d3ddev, &FontDesc, &font);
}

void Font::updateAnimation()
{
	isDrawAnimation = !isDrawAnimation;
}

void Font::render(char* text, float x, float y)
{
	Render(text, x, y, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void Font::render(int number, float x, float y)
{
	Render((char*)to_string(number).c_str(), x, y, D3DCOLOR_ARGB(255, 255, 255, 255));
}
void Font::render(float number_, float x_, float y_)
{
	Render((char*)to_string(number_).c_str(), x_, y_, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void Font::Render(char* text, float x, float y, D3DCOLOR color)
{
	fontPosition.left = x;
	fontPosition.top = y;
	font->DrawText(NULL,
		L"text",
		-1,
		&fontPosition,
		NULL,
		color); //draw text
}


void Font::renderAnimation(char* text_, float x_, float y_, int deltaTime_)
{
	localTime += deltaTime_;
	if (localTime >= 1000 / frameRate)
	{
		localTime = 0;
		this->updateAnimation();
	}
	if (this->isDrawAnimation)
		Render(text_, x_, y_, D3DCOLOR_ARGB(255, 255, 255, 255));

}
void Font::renderAnimation(int number_, float x_, float y_, int deltaTime_)
{
	localTime += deltaTime_;
	if (localTime >= 1000 / frameRate)
	{
		Render((char*)to_string(number_).c_str(), x_, y_, D3DCOLOR_ARGB(255, 255, 255, 255));
		localTime = 0;
	}
}

void Font::onLost()
{
	font->OnLostDevice();
	font->OnResetDevice();
}


Font::Font()
{
}


Font::~Font()
{
	if (font != NULL)
	{
		font->Release(); //release font
		font = NULL;
	}
}
