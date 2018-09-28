#include "Renderer_UI.h"
#include "DirectXHeader_DE.h"
#include "KMacro.h"
#include "KWindow.h"
#include "ResourceManager.h"
#include "Shader.h"
#include "Blend.h"

#include "Texture.h"
#include "Sampler.h"



Renderer_UI::Renderer_UI()
{
}


Renderer_UI::~Renderer_UI()
{
}


void Renderer_UI::UIRender()
{
	KVector2 SCSize = state()->camera()->screen_size();
	KVector2 WSize = window()->size();


	one()->Local_Pos(
		SCSize * ((WSize * .5f - 1.0f) + UI_Pos) / WSize + state()->camera()->one()->Local_Pos(), .3f);
	one()->Local_Scale(SCSize * UI_Size / WSize, 5.0f);
}