#pragma once
#include "Renderer_Sprite.h"
#include "KImage.h"

class Renderer_UI : public Renderer_Sprite
{
private:
	KVector		UI_Size;
	KVector2	UI_Pos;

public:
	Renderer_UI();
	~Renderer_UI();

public:
	void UIRender() override;
};

