#include "Bird.h"
#include "Bird_Launcher.h"
#include "Container_Class.h"

#include <KMacro.h>

#include <Collider2D_DE.h>
#include <Collider2DManager.h>
#include <State.h>
#include <KRigid_2D.h>
#include <KRaycast_2D.h>
#include <Renderer_Sprite.h>
#include <KFont.h>
#include <SoundPlayer.h>

#include <InputManager.h>
#include <TimeManager.h>
#include <ResourceManager.h>
#include <WriteStream.h>
#include <ReadStream.h>

#include <Mouse_Col.h>



Bird::Bird()
{
}


Bird::~Bird()
{
}

bool Bird::Init(const BIRD_TYPE& _Type)
{
	m_BirdTime = .0f;

	m_BS = BIRD_STATE::BS_STAND;

	m_BT = _Type;
	Init_Bird();

	return true;
}


bool Bird::Init(const BIRD_TYPE& _Type, KPtr<Bird_Launcher> _Launcher, const size_t& _Index)
{
	m_BirdTime = .0f;
	m_Launcher = _Launcher;

	mStandByInx = _Index;
	PrevStandByInx = mStandByInx;

	m_BS = BIRD_STATE::BS_STAND;

	
	m_BT = _Type;
	Init_Bird();


	return true;
}


void Bird::Update()
{
	Update_State();

	if (true == m_Launcher->is_Death())
	{
		one()->set_Death();
	}
	// Update_Damage();
	// Update_Image();
}

void Bird::Update_Damage()
{
	if (m_Rigid->CollisionForce())
	{

	}
}

void Bird::Update_Image()
{

}

void Bird::Damage()
{

}


void Bird::Update_State()
{
	switch (m_BS)
	{
	case Bird::BS_STAND:
		Update_Stand();
		break;
	case Bird::BS_MOVE:
		Update_Move();
		break;
	case Bird::BS_LOAD:
		Update_Load();
		break;
	case Bird::BS_STANDBY:
		Update_StandBy();
		break;
	case Bird::BS_TRIGGER:
		Update_Trigger();
		break;
	case Bird::BS_FIRE:
		Update_Fire();
		break;
	case Bird::BS_CRUISE:
		Update_Cruise();
		break;
	case Bird::BS_ACTIVATE:
		Update_Activate();
		break;
	case Bird::BS_ACTCRUISE:
		Update_ActCruise();
		break;
	case Bird::BS_UNPOWER:
		Update_UnPowered();
		break;
	case Bird::BS_IGNITION:
		Update_Ingnition();
		break;
	case Bird::BS_NUM:
	case Bird::BS_NONE:
	default:
		break;
	}
}



void Bird::Update_Stand()
{
	if (0 == mStandByInx && PrevStandByInx == mStandByInx)
	{
		if (nullptr == m_Launcher->ReadyBird())
		{
			m_Launcher->ReadyBird(this);
		}

		m_BS = BIRD_STATE::BS_STANDBY;
		return;
	}
	else if (PrevStandByInx > mStandByInx)
	{
		m_BirdTime = .0f;
		m_BS = BIRD_STATE::BS_MOVE;
	}

	m_BirdTime += DELTATIME;

	if (8.0f < m_BirdTime)
	{
		m_Rigid->Impulse(KVector2(.0f, 50.0f));
		m_BirdTime = .0f;
	}

	if (true == m_Launcher->one()->transform()->BWorld())
	{
		std::list<KPtr<Bird>> TempList = m_Launcher->BirdList();
		std::list<KPtr<Bird>>::iterator SLIST = TempList.begin();
		std::list<KPtr<Bird>>::iterator ELIST = TempList.end();
		float Size = 30 + one()->Local_Scale().x;;

		for (size_t i = 0; i < mStandByInx; i++)
		{
			if (SLIST != ELIST)
			{
				Size += (*SLIST)->one()->Local_Scale().x + 3.0f;
			}
			else if(SLIST == ELIST)
			{
				break;
			}

			++SLIST;
		}

		one()->Local_Pos(
			m_Launcher->one()->Local_Pos().x - (float)Size,
			m_Launcher->one()->Local_Pos().y - 10.0f, one()->Local_Pos().z);

		one()->Local_Rotate(KVector4::Zero);
		m_Rigid->Set_Transform();
		m_Rigid->Reset_Impulse();
		m_Rigid->Active_Vertex(false);

		PrevStandByInx = mStandByInx;
	}
}

void Bird::Update_Move()
{
	if (PrevStandByInx != mStandByInx)
	{
		m_Rigid->Impulse(KVector2(10.0f, 50.0f));
		m_Rigid->AngularImpulse(-10.0f);
		PrevStandByInx = mStandByInx;
	}

	m_BirdTime += DELTATIME;

	if (1.0f < m_BirdTime)
	{
		one()->Local_Rotate(KVector4::Zero);
		m_Rigid->Set_Transform();
		m_Rigid->Reset_Impulse();
		m_BS = BIRD_STATE::BS_STAND;
	}
}

void Bird::Update_Load()
{
	m_BirdTime += DELTATIME;

	if (8.0f < m_BirdTime)
	{
		m_Rigid->Impulse(KVector2(10.0f, 20.0f));
		m_BirdTime = .0f;
	}

	if (nullptr != one()->state()->this_Collider2DManager.Collision_Check(0, m_Collider))
	{
		m_BS = BIRD_STATE::BS_STANDBY;
	}		
}


void Bird::Update_StandBy()
{
	if (m_Collider == Mouse_Col::Mouse_Down(Mouse_Col::MOUSE_BTN::MBTN_LEFT))
	{
		m_BS = BIRD_STATE::BS_TRIGGER;
		m_LaunchCol = m_Collider;
		m_Sound = false;
	}

	else
	{
		one()->Local_Pos(m_Launcher->Launch_Point().x, m_Launcher->Launch_Point().y + 10.0f, 10.0f);
		m_Rigid->Set_Transform();
	}
}
void Bird::Update_Trigger()
{
	if (false == m_Sound)
	{
		SoundPlayer thisSP = SoundPlayer();
		thisSP.Play(L"Trigger.mp3");
		thisSP.Play(L"RedTrigger.mp3");
		m_Sound = true;
	}

	KVector2 LP = m_Launcher->Launch_Point();
	float LaunchDis = 20.0f;
	float Power = LP.distance(one()->Local_Pos().m_Pos);
	KPtr<Collider2D_DE> TempCol = Mouse_Col::Mouse_Press(Mouse_Col::MOUSE_BTN::MBTN_LEFT);

	// 발사시점
	if (KEY_UP("MOUSE_LB"))
	{
		m_BS = BIRD_STATE::BS_FIRE;
		m_Launcher->DeleteBird(this);
		m_Launcher->MinusIdxBird();
		m_LaunchCol = nullptr;
		m_BirdTime = .0f;
	}

	// 발사대 안에서 위치
	else if(KEY_PRESS("MOUSE_LB") && m_Collider == TempCol)
	{
		if(Power < LaunchDis)
		{
			one()->Local_Pos(state()->camera()->screen_to_world(InputManager::mouse_pos()), 10.0f);
			m_Rigid->Set_Transform();
			m_Rigid->Reset_Impulse();
		}
	}

	// 발사대 밖에서 위치
	else if (KEY_PRESS("MOUSE_LB") && nullptr != m_LaunchCol)
	{
		KVector2 Aim = LP - state()->camera()->screen_to_world(InputManager::mouse_pos());
		Aim.normalize();
		Aim *= LaunchDis;

		KVector Temp = one()->Local_Pos();
		one()->Local_Pos(LP.x - Aim.x, LP.y - Aim.y, Temp.z);
		m_Rigid->Set_Transform();
		m_Rigid->Reset_Impulse();
	}
}

void Bird::Update_Fire()
{
	// 월드별 구분은 되지만 결국... 바텀에서 막힌다.
	// -> 저장 데이터는 건들이지 않는 것이 포인트임//
	//m_Collider->set_Death();
	//m_Rigid->set_Death();

	//m_Collider = Add_Component<Collider2D_DE>(0);
	//m_Rigid = Add_Component<KRigid_2D>();
	//Init_Collider();


	KVector2 LP = m_Launcher->Launch_Point();
	KVector2 Dir = LP - one()->Local_Pos().m_Pos;
	Dir.normalize();
	float LaunchDis = 20.0f;
	float Power = LP.distance(one()->Local_Pos().m_Pos);

	float FIrePower = 1.0f;

	if (Power < LaunchDis)
	{
		m_Rigid->Impulse(KVector(20.0f)  * Dir * Power);
	}

	else
	{
		m_Rigid->Impulse(KVector(20.0f) * Dir * LaunchDis);
	}

	m_BS = BIRD_STATE::BS_CRUISE;
	SoundPlayer thisSP = SoundPlayer();
	thisSP.Play(L"RedCruise.mp3");

	m_Sound = false;
}

void Bird::Update_ActCruise()
{

	KPtr<Collider2D_DE> TempCol = one()->state()->this_Collider2DManager.Collision_Check(0, m_Collider);

	if (nullptr != TempCol)
	{
		std::wstring TempStr = TempCol->one()->name();
		if (L"Panza" == TempStr ||
			L"Bottom" == TempStr)
		{
			m_BS = BIRD_STATE::BS_UNPOWER;
		}
	}

}

void Bird::Update_Cruise()
{	
	KPtr<Collider2D_DE> TempCol = one()->state()->this_Collider2DManager.Collision_Check(0, m_Collider);
	
	if (nullptr != TempCol)
	{
		std::wstring TempStr = TempCol->one()->name();
		if (L"Panza" == TempStr || L"Bottom" == TempStr || L"StateBottom" == TempStr)
		{
			// 알은 작용과정으로 처리
			if (m_BT == BIRD_TYPE::BT_MATILDAEGG)
			{
				m_BS = BIRD_STATE::BS_ACTIVATE;
				return;
			}

			m_BS = BIRD_STATE::BS_UNPOWER;
		}
	}

	if (KEY_DOWN("MOUSE_LB"))
	{
		if (m_BT == BIRD_TYPE::BT_MATILDAEGG)
		{
			return;
		}

		m_BS = BIRD_STATE::BS_ACTIVATE;
	}
}

void Bird::Update_UnPowered()
{

	if (false == m_Sound)
	{
		SoundPlayer thisSP = SoundPlayer();
		thisSP.Play(L"RedUnPower.mp3");
		m_Sound = true;
	}

	m_BirdTime += DELTATIME;

	if (BIRD_TYPE::BT_MATILDA == m_BT)
	{
		m_Render->index(6);
	}

	if (5.0f < m_BirdTime)
	{
		one()->set_Death();
	}

	return;
}

void Bird::Update_Ingnition()
{
	KPtr<Collider2D_DE> TempCol = one()->state()->this_Collider2DManager.Collision_Check(0, m_Collider);

	if (nullptr != TempCol)
	{
		std::wstring TempStr = TempCol->one()->name();
		if (L"Panza" == TempStr ||
			L"Bottom" == TempStr)
		{
			m_BS = BIRD_STATE::BS_UNPOWER;
		}
	}
}



void Bird::Init_Bird()
{
	one()->name(L"Bird");
	switch (m_BT)
	{
	case Bird::BT_RED:
		name(L"Red");
		break;
	case Bird::BT_BLUE:
		name(L"Blue");
		break;
	case Bird::BT_BOMB:
		name(L"Bomb");
		break;
	case Bird::BT_BUBBLE:
		name(L"Bubble");
		break;
	case Bird::BT_CHUCK:
		name(L"Chuck");
		break;
	case Bird::BT_HAL:
		name(L"Hal");
		break;
	case Bird::BT_MATILDA:
		name(L"Matilda");
		break;
	case Bird::BT_MATILDAEGG:
		name(L"Matilda Egg");
		break;
	case Bird::BT_TERENCE:
		name(L"Terence");
		break;
	case Bird::BT_MIGHTY_EAGLE:
		name(L"Mighty Eagle");
		break;
	case Bird::BT_NONE:
	case Bird::BT_NUM:
	default:
		break;
	}

	Init_Render();
	Init_Collider();

}

void Bird::Init_Render()
{
	int Size = 10;
	std::wstring DataName = name();
	DataName += L".png";

	if (nullptr == m_Render)
	{
		m_Render = Add_Component<Renderer_Sprite>(DataName.c_str());
	}
	else
	{
		m_Render->image(DataName.c_str());
	}


	switch (m_BT)
	{
	case Bird::BT_RED:
	{
		m_Render->image()->Split(6, 1);
		one()->Local_Scale(Size * 2.0f, Size * 2.5f, 10.0f);
		break;
	}
	case Bird::BT_BLUE:
	{
		m_Render->image()->Split(6, 1);
		one()->Local_Scale(Size * 1.0f, Size * 1.5f, 10.0f);
		break;
	}
	case Bird::BT_BOMB:
	{
		m_Render->image()->Split(9, 1);
		one()->Local_Scale(Size * 3.0f, Size * 4.0f, 10.0f);
		break;
	}
	case Bird::BT_BUBBLE:
	{
		m_Render->image()->Split(3, 1);
		one()->Local_Scale(Size * 1.0f, Size * 1.5f, 10.0f);
		break;
	}
	case Bird::BT_CHUCK:
	{
		m_Render->image()->Split(7, 1);
		one()->Local_Scale(Size * 2.0f, Size * 2.0f, 10.0f);
		break;
	}
	case Bird::BT_HAL:
	{
		m_Render->image()->Split(7, 1);
		one()->Local_Scale(Size * 4.0f, Size * 2.0f, 10.0f);
		break;
	}
	case Bird::BT_MATILDA:
	{
		m_Render->image()->Split(7, 1);
		one()->Local_Scale(Size * 3.0f, Size * 4.0f, 10.0f);
		break;
	}
	case Bird::BT_MATILDAEGG:
	{
		one()->Local_Scale(Size * 2.5f, Size * 3.0f, 10.0f);
		break;
	}
	case Bird::BT_TERENCE:
	{
		m_Render->image()->Split(5, 1);
		one()->Local_Scale(Size * 5.0f, Size * 5.0f, 10.0f);
		break;
	}
	case Bird::BT_MIGHTY_EAGLE:
	{
		m_Render->image()->Split(3, 1);
		one()->Local_Scale(Size * 2.5f, Size * 2.0f, 10.0f);
		break;
	}
	case Bird::BT_NONE:
	case Bird::BT_NUM:
	default:
		break;
	}
}

void Bird::Init_Collider()
{
	if (nullptr == m_Collider)
	{
		m_Collider = Add_Component<Collider2D_DE>(0);
	}
	if (nullptr == m_Rigid)
	{
		m_Rigid = Add_Component<KRigid_2D>();
	}


	switch (m_BT)
	{
	case Bird::BT_RED:
	{
		m_Collider->type(COLL_TYPE::COL_CIRCLE2D);
		break;
	}
	case Bird::BT_BLUE:
	{
		m_Collider->type(COLL_TYPE::COL_CIRCLE2D);
		break;
	}
	case Bird::BT_BOMB:
	{
		m_Collider->type(COLL_TYPE::COL_CIRCLE2D);
		break;
	}
	case Bird::BT_BUBBLE:
	{
		m_Collider->type(COLL_TYPE::COL_CIRCLE2D);
		break;
	}
	case Bird::BT_CHUCK:
	{
		m_Collider->type(COLL_TYPE::COL_POLY2D);

		std::vector<KVector2> Temp;
		if (nullptr == m_Trans->Col_Vertex())
		{
			m_Trans->Col_Vertex(m_Rigid->Poly_Vertex());
		}
		m_Trans->Col_Vertex()->clear();
			
		Temp.push_back(KVector2(.0f, one()->Local_Scale().y * .5f));
		Temp.push_back(KVector2(one()->Local_Scale().x * .5f * -1.0f, one()->Local_Scale().y * .5f * -1.0f));
		Temp.push_back(KVector2(one()->Local_Scale().x * .5f * +1.0f, one()->Local_Scale().y * .5f * -1.0f));
			
		for (size_t i = 0; i < 3; i++)
		{
			m_Trans->Col_Vertex()->push_back(Temp[i]);
		}

		m_Rigid->Set_VertexList(m_Trans->Col_Vertex());
		m_Rigid->Create_Mesh(m_Render->name());
		break;
	}
	case Bird::BT_HAL:
	{
		m_Collider->type(COLL_TYPE::COL_CIRCLE2D);
		break;
	}
	case Bird::BT_MATILDA:
	{
		m_Collider->type(COLL_TYPE::COL_CIRCLE2D);
		break;
	}
	case Bird::BT_TERENCE:
	{
		m_Collider->type(COLL_TYPE::COL_CIRCLE2D);
		break;
	}
	case Bird::BT_MIGHTY_EAGLE:
	{
		m_Collider->type(COLL_TYPE::COL_RECT2D);
		break;
	}
	case Bird::BT_MATILDAEGG:
	{
		m_Collider->type(COLL_TYPE::COL_CIRCLE2D);
		break;
	}
	case Bird::BT_NONE:
	case Bird::BT_NUM:
	default:
		break;
	}
	
	m_Rigid->load(L"Init");
	m_Rigid->Set_Type(b2BodyType::b2_dynamicBody);
}



void Bird::save()
{
	m_Rigid->save(name());
}

void Bird::load()
{
	m_Rigid->load(name());
}