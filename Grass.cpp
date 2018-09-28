#include "Grass.h"
#include "Panza.h"
#include "Bottom.h"
#include <KMacro.h>

#include <State.h>
#include <Collider2D_DE.h>
#include <KRigid_2D.h>
#include <Renderer_Sprite.h>
#include <KFont.h>

#include <ResourceManager.h> 
#include <Sprite_Changer.h>
#include <WriteStream.h>
#include <ReadStream.h>


Grass::Grass()
{
}


Grass::~Grass()
{
	if (m_ColPos != nullptr)
	{
		m_ColPos->set_Death();
	}
}

bool Grass::Init(const size_t& _Inx)
{
	int Size = 10;
	std::wstring DataName = L"Grass.png";

	if (nullptr == m_Render)
	{
		m_Render = Add_Component<Renderer_Sprite>(DataName.c_str());
	}
	else
	{
		m_Render->image(DataName.c_str());
	}
	
	m_Render->image()->Split(2, 3);
	m_Render->index(_Inx);
	one()->name(L"Grass");
	m_Render->inde_scale({ 80.0f, 54.0f, 10.0f, .0f});

	if (nullptr == m_ColPos)
	{
		m_ColPos = state()->Create_TheOne(L"Grass_ColPos");
		m_Collider = m_ColPos->Add_Component<Collider2D_DE>(0);
	}
	
	m_Collider->color(KColor::Green);
	m_Collider->type(COLL_TYPE::COL_RECT2D);
	m_ColPos->Local_Scale(10.0f, 10.0f, 10.0f);
	m_ColPos->Local_Pos(one()->Local_Pos().m_Pos, 6.0f);
	one()->Local_Pos(one()->Local_Pos().m_Pos, 6.0f);

	return true;
}

void Grass::Update()
{
	if (true == m_ColPos->transform()->BWorld())
	{
		one()->Local_Pos(m_ColPos->Local_Pos().m_Pos, 6.0f);
	}
}