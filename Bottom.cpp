#include "Bottom.h"
#include "Panza.h"
#include <KMacro.h>

#include <State.h>
#include <Collider2D_DE.h>
#include <KRigid_2D.h>
#include <Renderer_Sprite.h>
#include <KFont.h>

#include <ResourceManager.h>


Bottom::Bottom()
{
}


Bottom::~Bottom()
{
}



bool Bottom::Init()
{
	std::wstring NewName;

	for (int i = 0; i < 50; i++)
	{
		NewName = L"Bottom";
		wchar_t BackNumber[50];
		_itow_s(i, BackNumber, 10);

		NewName += BackNumber;

		if (false == state()->this_RenderManager.Is_Name(NewName.c_str()))
		{
			break;
		}

		else if (i >= 50)
		{
			KASSERT(true);
		}
	}


	// 바닥이자 판자일 수 없다.
	KASSERT(nullptr != Get_Component<Panza>());

	m_Collider = Add_Component<Collider2D_DE>(0);
	m_Rigid = Add_Component<KRigid_2D>();
	m_Render = Add_Component<Renderer_Sprite>(L"Bottom_Back.png");

	m_Collider->color(KColor::White);
	m_Collider->type(COLL_TYPE::COL_POLY2D);
	m_Rigid->Set_Type(b2BodyType::b2_staticBody);

	m_Render->name(NewName.c_str());
	one()->name(L"Bottom");

	return true;
}

void Bottom::Update()
{
	if (true == m_Rigid->IsChangeVertex())
	{
		m_Rigid->Create_Mesh(m_Render->name());
		m_Render->Set_Mesh();
	}
}


void Bottom::Set_Transform(const KVector& _Pos, const KVector& _Rotate, const KVector& _Scale)
{
	one()->Local_Pos(_Pos);
	one()->Local_Rotate(_Rotate);
	one()->Local_Scale(_Scale);
	m_Rigid->Set_Transform();
}

void Bottom::Set_Pos(const KVector& _Pos)
{
	one()->Local_Pos(_Pos);
	m_Rigid->Set_Transform();
}

void Bottom::Set_Rotate(const KVector& _Rotate)
{
	one()->Local_Rotate(_Rotate);
	m_Rigid->Set_Transform();
}
void Bottom::Set_Scale(const KVector& _Scale)
{
	one()->Local_Scale(_Scale);
	m_Rigid->Set_Transform();
}


// Mass, Inertia, Center
void Bottom::MassData(const KVector& _Value)
{
	m_Rigid->MassData(_Value);
}
KVector Bottom::MassData() const { return m_Rigid->MassData(); }

// Density, Friction, Restitude
void Bottom::FigureData(const KVector3& _Value)
{
	m_Rigid->FigureData(_Value);
}
KVector3 Bottom::FigureData() const { return m_Rigid->FigureData(); }




void Bottom::save(const wchar_t* _Name)
{
	m_Rigid->save(_Name);
}

void Bottom::load(const wchar_t* _Name)
{
	m_Rigid->load(_Name);
}



