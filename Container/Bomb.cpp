#include "Bomb.h"
#include "Bottom.h"
#include "Bird.h"

#include <KMacro.h>

#include <Collider2D_DE.h>
#include <KRigid_2D.h>
#include <KRaycast_2D.h>
#include <Renderer_Sprite.h>
#include <KFont.h>

#include <SoundPlayer.h>
#include <ResourceManager.h>
#include <Sprite_Changer.h>
#include <WriteStream.h>
#include <ReadStream.h>



Bomb::Bomb()
{
}


Bomb::~Bomb()
{
}




bool Bomb::Init()
{
	// 바닥이자 판자일 수 없다.
	KASSERT(nullptr != Get_Component<Bottom>());
	m_State = BOMB_STATE::STAND_BY;


	Init_Render();
	Init_Collider();

	return true;
}




void Bomb::Init_Render()
{
	int Size = 10;

	one()->Local_Scale(1.5f * Size);

	std::wstring DataName = L"Bomb_OBJ.png";

	if (nullptr == m_Render)
	{
		m_Render = Add_Component<Renderer_Sprite>(DataName.c_str());
	}
	else
	{
		m_Render->image(DataName.c_str());
	}

	one()->name(L"Bomb");
}

void Bomb::Init_Collider()
{
	if (nullptr == m_Collider)
	{
		m_Collider = Add_Component<Collider2D_DE>(0);
	}
	if (nullptr == m_Rigid)
	{
		m_Rigid = Add_Component<KRigid_2D>();
	}
	if (nullptr == m_Ray)
	{
		m_Ray = Add_Component<KRaycast_2D>();
	}

	m_Collider->color(KColor::Red);
	m_Collider->type(COLL_TYPE::COL_RECT2D);

	m_Rigid->MassData(KVector(100.0f, .2f, .0f));
	m_Rigid->FigureData(KVector3(1.0f, .2f, .7f));
	m_Rigid->Set_Type(b2BodyType::b2_dynamicBody);
}


void Bomb::Update()
{
	Update_Damage();
}

void Bomb::Update_Damage()
{
	float Force = m_Rigid->CollisionForce();

	if (150.0f < Force)
	{
		Activate_Bomb();
	}
}

void Bomb::Activate_Bomb()
{
	KRaycast_2D::RayData* Data;

	for (size_t i = 0; i < 360; i++)
	{
		KVector2 Dir = KVector2(cos(i * KMath::DegToRad * -1.0f), sin(i * KMath::DegToRad* -1.0f));
		float Distance = 0;

		Data = m_Ray->check(one()->Local_Pos().m_Pos, Dir * 1000.0f);
		if (nullptr == Data->KRigid)
		{
			continue;
		}


		std::wstring TempName = Data->KRigid->one()->name();

		if (L"Bird" == TempName)
		{
			if (Bird::BIRD_STATE::BS_UNPOWER != Data->KRigid->Get_Component<Bird>()->Bird_State())
			{
				continue;
			}
		}

		Distance = one()->Local_Pos().m_Pos.distance(Data->KRigid->one()->Local_Pos().m_Pos);
		Data->KRigid->Impulse(Dir * 15000.0f / Distance);
	}
	

	SoundPlayer thisSP = SoundPlayer();
	thisSP.Play(L"BombAct.mp3");

	one()->set_Death();
}

void Bomb::save()
{
	m_Rigid->save(name());
}
void Bomb::load()
{
	m_Rigid->load(name());
}








void Bomb::Reset_Rigid()
{
	if (true == one()->BWorld())
	{
		m_Rigid->Reset_Impulse();
	}
}
void Bomb::Set_Transform(const KVector& _Pos, const KVector& _Rotate, const KVector& _Scale)
{
	one()->Local_Pos(_Pos);
	one()->Local_Rotate(_Rotate);
	one()->Local_Scale(_Scale);
	m_Rigid->Set_Transform();
}
void Bomb::Set_Pos(const KVector& _Pos)
{
	one()->Local_Pos(_Pos);
	m_Rigid->Set_Transform();
}
void Bomb::Set_Rotate(const KVector& _Rotate)
{
	one()->Local_Rotate(_Rotate);
	m_Rigid->Set_Transform();
}
void Bomb::Set_Scale(const KVector& _Scale)
{
	one()->Local_Scale(_Scale);
	m_Rigid->Set_Transform();
}


// Mass, Inertia, Center
void Bomb::MassData(const KVector& _Value)
{
	m_Rigid->MassData(_Value);
}
KVector Bomb::MassData() const
{
	return m_Rigid->MassData();
}

// Density, Friction, Restitude
void Bomb::FigureData(const KVector3& _Value)
{
	m_Rigid->FigureData(_Value);
}
KVector3 Bomb::FigureData() const
{
	return m_Rigid->FigureData();
}