#include "Panza.h"
#include "Bottom.h"
#include <KMacro.h>

#include <Collider2D_DE.h>
#include <KRigid_2D.h>
#include <Renderer_Sprite.h>
#include <KFont.h>
#include <SoundPlayer.h>


#include <ResourceManager.h>
#include <Sprite_Changer.h>
#include <WriteStream.h>
#include <ReadStream.h>

#include "Container_Class.h"


Panza::Panza()
{
}


Panza::~Panza()
{
}


bool Panza::Init(const PAN_MAT_TYPE& _Mat, const PAN_SHP_TYPE& _Shape, const PAN_SIZ_TYPE& _Size, const bool& _Init /*true*/)
{

	m_Font = ResourceManager<KFont>().Find(L"AngryBirds");

	// 바닥이자 판자일 수 없다.
	KASSERT(nullptr != Get_Component<Bottom>());

	m_MatType = _Mat;
	m_ShapeType = _Shape;
	m_SizeType = _Size;
	m_hp = 4;

	if (nullptr == m_Collider)
	{
		m_Collider = Add_Component<Collider2D_DE>(0);
	}
	if (nullptr == m_Rigid)
	{
		m_Rigid = Add_Component<KRigid_2D>();
	}

	Set_Panza(_Init);
	one()->Local_Pos(one()->Local_Pos().m_Pos, 10.0f);
	
	return true;
}


void Panza::Update()
{
	Update_Damage();
	Update_Image();
}

void Panza::Reset_Rigid()
{
	if (true == one()->BWorld())
	{
		m_Rigid->Reset_Impulse();
	}
}

void Panza::Update_Damage()
{
	float Bojung = 20.0f;
	float Force = m_Rigid->CollisionForce();
	// Force /= Bojung;

	if(Bojung * 6.0f < Force)
	{
		Container_Class::This_BirdLauncher()->Plus_Score((int)Force);
		Damage();

		if (0 == m_hp)
		{
			SoundPlayer thisSP = SoundPlayer();
			switch (m_MatType)
			{
			case Panza::PMT_ICE:
				thisSP.Play(L"IceBroke.mp3");
				break;
			case Panza::PMT_WOOD:
				thisSP.Play(L"WoodBroke.mp3");
				break;
			case Panza::PMT_STONE:
				thisSP.Play(L"StoneBroke.mp3");
				break;
			case Panza::PMT_NONE:
			case Panza::PMT_NUMBER:
				break;
			default:
				break;
			}

			Container_Class::This_BirdLauncher()->Plus_Score(500);
			one()->set_Death();
		}
	}
}

void Panza::Update_Image()
{
	m_Render->index(4 - m_hp);
}

void Panza:: Damage()
{
	--m_hp;
}


void Panza::Set_Panza(const bool& _Init)
{
	int Size = 10;
	bool TInit = _Init;

	m_FileName.clear();

	switch (m_MatType)
	{
	case Panza::PMT_ICE:
		m_Collider->color({ .0f, 1.0f, .0f, 1.0f });
		m_FileName += L"I+";
		m_Collider->color(KColor::Cyan);
		break;
	case Panza::PMT_WOOD:
		m_Collider->color({ .0f, 1.0f, .0f, 1.0f });
		m_FileName += L"W+";
		m_Collider->color(KColor::Yellow);
		break;
	case Panza::PMT_STONE:
		m_Collider->color({ .0f, 1.0f, .0f, 1.0f });
		m_FileName += L"S+";
		m_Collider->color(KColor::Black);
		break;
	case Panza::PMT_NUMBER:
	case Panza::PMT_NONE:
	default:
		break;
	}

	switch (m_ShapeType)
	{
	case Panza::PSH_ABS_TRIANGLE:
		m_Collider->mode(COLL_TYPE::COL_POLY2D);
		m_FileName += L"ABSTRI+";
		break;
	case Panza::PSH_RIA_TRIANGLE:
		m_Collider->mode(COLL_TYPE::COL_POLY2D);
		m_FileName += L"RIATRI+";
		break;
	case Panza::PSH_ABS_RECT:
		m_Collider->mode(COLL_TYPE::COL_RECT2D);
		m_FileName += L"ABSRECT+";
		break;
	case Panza::PSH_ANG_RECT:
		m_Collider->mode(COLL_TYPE::COL_RECT2D);
		m_FileName += L"ANGRECT+";
		break;
	case Panza::PSH_CIRCLE:
		m_Collider->mode(COLL_TYPE::COL_CIRCLE2D);
		m_FileName += L"CIRCLE+";
		break;
	case Panza::PSH_NUMBER:
	case Panza::PSH_NONE:
	default:
		break;
	}

	switch (m_SizeType)
	{
	case Panza::PSI_SMALL:
		if (Panza::PSH_ANG_RECT == m_ShapeType)
		{
			one()->Local_Scale(KVector(Size * 2.0f, Size * 1.0f, 10.0f));
		}
		else
		{
			one()->Local_Scale(KVector(Size * 1.0f, Size * 1.0f, 10.0f));
		}
		m_FileName += L"S";
		break;
	case Panza::PSI_MIDDLE:
		if (Panza::PSH_ANG_RECT == m_ShapeType)
		{
			one()->Local_Scale(KVector(Size * 4.0f, Size * 1.0f, 10.0f));
		}
		else
		{
			one()->Local_Scale(KVector(Size * 2.0f, Size * 2.0f, 10.0f));
		}
		m_FileName += L"M";
		break;
	case Panza::PSI_BIG:
		if (Panza::PSH_ANG_RECT == m_ShapeType)
		{
			one()->Local_Scale(KVector(Size * 6.0f, Size * 1.0f, 10.0f));
		}
		else
		{
			one()->Local_Scale(KVector(Size * 4.0f, Size * 2.0f, 10.0f));
		}
		m_FileName += L"B";
		break;
	case Panza::PSI_GIANT:
		if (Panza::PSH_ANG_RECT == m_ShapeType)
		{
			one()->Local_Scale(KVector(Size * 8.0f, Size * 1.0f, 10.0f));
		}
		else
		{
			one()->Local_Scale(KVector(Size * 4.0f, Size * 4.0f, 10.0f));
		}
		m_FileName += L"G";
		break;
	case Panza::PSI_NUMBER:
	case Panza::PSI_NONE:
	default:
		break;
	}


	std::wstring DataName = m_FileName + L".png";

	if (nullptr == m_Render)
	{
		m_Render = Add_Component<Renderer_Sprite>(DataName.c_str());

		if (Panza::PSH_ANG_RECT == m_ShapeType)
		{
			m_Render->image()->Split(1, 4);
		}
		else
		{
			m_Render->image()->Split(4, 1);
		}
	}
	else
	{
		m_Render->image(DataName.c_str());
		if (Panza::PSH_ANG_RECT == m_ShapeType)
		{
			m_Render->image()->Split(1, 4);
		}
		else
		{
			m_Render->image()->Split(4, 1);
		}
	}

	m_Render->name(m_FileName.c_str());
	one()->name(L"Panza");

	if (COLL_TYPE::COL_POLY2D == m_Collider->type())
	{
		std::vector<KVector2> Temp;
		if (nullptr == m_Trans->Col_Vertex())
		{
			m_Trans->Col_Vertex(m_Rigid->Poly_Vertex());
		}
		m_Trans->Col_Vertex()->clear();
		
		if (m_ShapeType == PAN_SHP_TYPE::PSH_ABS_TRIANGLE)
		{
			Temp.push_back(KVector2(.0f, one()->Local_Scale().y * .5f));
			Temp.push_back(KVector2(one()->Local_Scale().x * .5f * -1.0f, one()->Local_Scale().y * .5f * -1.0f));
			Temp.push_back(KVector2(one()->Local_Scale().x * .5f * +1.0f, one()->Local_Scale().y * .5f * -1.0f));
		}
		else if (m_ShapeType == PAN_SHP_TYPE::PSH_RIA_TRIANGLE)
		{
			Temp.push_back(KVector2(one()->Local_Scale().x * .5f * -1.0f, one()->Local_Scale().y * .5f));
			Temp.push_back(KVector2(one()->Local_Scale().x * .5f * -1.0f, one()->Local_Scale().y * .5f * -1.0f));
			Temp.push_back(KVector2(one()->Local_Scale().x * .5f * +1.0f, one()->Local_Scale().y * .5f * -1.0f));
		}

		for (size_t i = 0; i < 3; i++)
		{
			m_Trans->Col_Vertex()->push_back(Temp[i]);
		}
		
		m_Rigid->Set_VertexList(m_Trans->Col_Vertex());
		m_Rigid->Active_Vertex(false);
		m_Rigid->Create_Mesh(m_Render->name());
		TInit = false;
	}

	


	if (true == TInit)
	{
		m_Rigid->load(L"Init");
		// m_Rigid->MassData(KVector(100.0f, .2f, .0f));
		// m_Rigid->FigureData(KVector3(1.0f, .2f, .7f));
	}

	m_Rigid->Set_Type(b2BodyType::b2_dynamicBody);
}

void Panza::Set_Transform(const KVector& _Pos, const KVector& _Rotate, const KVector& _Scale)
{
	one()->Local_Pos(_Pos);
	one()->Local_Rotate(_Rotate);
	one()->Local_Scale(_Scale);
	m_Rigid->Set_Transform();
}
void Panza::Set_Pos(const KVector& _Pos)
{
	one()->Local_Pos(_Pos);
	m_Rigid->Set_Transform();
}

void Panza:: Set_Rotate(const KVector& _Rotate)
{
	one()->Local_Rotate(_Rotate);
	m_Rigid->Set_Transform();
}
void Panza::Set_Scale(const KVector& _Scale)
{
	one()->Local_Scale(_Scale);
	m_Rigid->Set_Transform();
}

// Mass, Inertia, Center
void Panza::MassData(const KVector& _Value)
{
	m_Rigid->MassData(_Value);
}
KVector Panza::MassData() const { return m_Rigid->MassData(); }

// Density, Friction, Restitude
void Panza::FigureData(const KVector3& _Value)
{
	m_Rigid->FigureData(_Value);
}
KVector3 Panza::FigureData() const { return m_Rigid->FigureData(); }




void Panza::save()
{
	m_Rigid->save(m_FileName.c_str());
}

void Panza::load()
{
	m_Rigid->load(m_FileName.c_str());
}

void Panza::DebugRender()
{
	// wchar_t tempchar[100] = { 0, };
	// 
	// 
	// swprintf_s(tempchar, L"%d", m_hp);
	// m_Font->draw_font(
	// 	tempchar, one()->Local_Pos().m_Pos + KVector2(-20.0f, 20.0f), 20.0f,
	// 	KColor::White.color_to_reverse255(), FW1_TEXT_FLAG::FW1_TOP);
}