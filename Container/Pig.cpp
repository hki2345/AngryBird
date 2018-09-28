#include "Pig.h"
#include "Bottom.h"
#include "Container_Class.h"

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


Pig::Pig()
{
}


Pig::~Pig()
{
}





bool Pig::Init(const PIG_SIZ_TYPE& _Mat)
{
	// 바닥이자 판자일 수 없다.
	KASSERT(nullptr != Get_Component<Bottom>());

	m_SizeType = _Mat;
	m_PigState = PIG_STATE::PIG_STANBY;
	m_hp = 4;


	one()->Local_Pos(one()->Local_Pos().m_Pos, 10.0f);
	Init_Render();
	Init_Collider();

	return true;
}




void Pig::Init_Render()
{
	int Size = 10;

	switch (m_SizeType)
	{
	case Pig::PIG_NONE:
		break;
	case Pig::PIG_SMALL:
		one()->Local_Scale(1.5f * Size);
		break;
	case Pig::PIG_MIDDLE:
		one()->Local_Scale(2.5f * Size);
		break;
	case Pig::PIG_BIG:
		one()->Local_Scale(4.0f * Size);
		break;
	case Pig::PIG_GIANT:
		one()->Local_Scale(5.0f * Size);
		break;
	case Pig::PIG_NUMBER:
		break;
	default:
		break;
	}

	std::wstring DataName = L"Pig.png";

	if (nullptr == m_Render)
	{
		m_Render = Add_Component<Renderer_Sprite>(DataName.c_str());
		m_Render->image()->Split(7, 3);
	}
	else
	{
		m_Render->image(DataName.c_str());
		m_Render->image()->Split(7, 3);
	}

	m_Render->index(8);
	one()->name(L"Pig");
}

void Pig::Init_Collider()
{
	if (nullptr == m_Collider)
	{
		m_Collider = Add_Component<Collider2D_DE>(0);
	}
	if (nullptr == m_Rigid)
	{
		m_Rigid = Add_Component<KRigid_2D>();
	}

	m_Collider->color(KColor::Green);
	m_Collider->type(COLL_TYPE::COL_CIRCLE2D);

	m_Rigid->MassData(KVector(100.0f, .2f, .0f));
	m_Rigid->FigureData(KVector3(1.0f, .2f, .7f));
	m_Rigid->Set_Type(b2BodyType::b2_dynamicBody);
}


void Pig::Update()
{
	Update_Damage();
	Update_Image();
}

void Pig::Update_Damage()
{
	float Bojung = 20.0f;
	float Force = m_Rigid->CollisionForce();
	// Force /= Bojung;

	if (Bojung * 2.0f < Force)
	{
		Container_Class::This_BirdLauncher()->Plus_Score((int)Force);
		Damage();

		if (0 == m_hp)
		{
			SoundPlayer thisSP = SoundPlayer();
			thisSP.Play(L"PigDie.mp3");
			Container_Class::This_BirdLauncher()->Plus_Score(5000);
			one()->set_Death();
		}
	}
}

void Pig::Damage()
{
	--m_hp;
}


void Pig::Update_Image()
{
	m_Render->index(8);
}



void Pig::save()
{
	m_Rigid->save(name());
}
void Pig::load()
{
	m_Rigid->load(name());
}








void Pig::Reset_Rigid()
{
	if (true == one()->BWorld())
	{
		m_Rigid->Reset_Impulse();
	}
}
void Pig::Set_Transform(const KVector& _Pos, const KVector& _Rotate, const KVector& _Scale)
{
	one()->Local_Pos(_Pos);
	one()->Local_Rotate(_Rotate);
	one()->Local_Scale(_Scale);
	m_Rigid->Set_Transform();
}
void Pig::Set_Pos(const KVector& _Pos)
{
	one()->Local_Pos(_Pos);
	m_Rigid->Set_Transform();
}
void Pig::Set_Rotate(const KVector& _Rotate)
{
	one()->Local_Rotate(_Rotate);
	m_Rigid->Set_Transform();
}
void Pig::Set_Scale(const KVector& _Scale)
{
	one()->Local_Scale(_Scale);
	m_Rigid->Set_Transform();
}


// Mass, Inertia, Center
void Pig::MassData(const KVector& _Value)
{
	m_Rigid->MassData(_Value);
}
KVector Pig::MassData() const
{
	return m_Rigid->MassData();
}

// Density, Friction, Restitude
void Pig::FigureData(const KVector3& _Value)
{
	m_Rigid->FigureData(_Value);
}
KVector3 Pig::FigureData() const
{
	return m_Rigid->FigureData();
}