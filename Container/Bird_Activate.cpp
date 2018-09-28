#include "Bird.h"
#include "Bird_Launcher.h"
#include "Container_Class.h"

#include <KMacro.h>

#include <Collider2D_DE.h>
#include <Collider2DManager.h>
#include <State.h>
#include <KRigid_2D.h>
#include <Renderer_Sprite.h>
#include <KFont.h>

#include <InputManager.h>
#include <TimeManager.h>
#include <ResourceManager.h>
#include <WriteStream.h>
#include <ReadStream.h>
#include <SoundPlayer.h>

#include <Mouse_Col.h>
#include <KRaycast_2D.h>



void Bird::Update_Activate()
{
	if (nullptr != one()->state()->this_Collider2DManager.Collision_Check(0, m_Collider))
	{
		m_BS = BIRD_STATE::BS_UNPOWER;
	}

	switch (m_BT)
	{
	case Bird::BT_BOMB:
		Activate_Bomb();
		break;
	case Bird::BT_BLUE:
		Activate_Blue();
		break;
	case Bird::BT_BUBBLE:
		Activate_Bubble();
		break;
	case Bird::BT_CHUCK:
		Activate_Chuck();
		break;
	case Bird::BT_HAL:
		Activate_Hal();
		break;
	case Bird::BT_MATILDA:
		Activate_Matilda();
		break;
	case Bird::BT_MIGHTY_EAGLE:
		Activate_MightyEagle();
		break;
	case Bird::BT_RED:
		Activate_Red();
		break;
	case Bird::BT_TERENCE:
		Activate_Terence();
		break;
	case Bird::BT_MATILDAEGG:
		Activate_Egg();
		break;
	case Bird::BT_NUM:
	case Bird::BT_NONE:
		break;
	default:
		break;
	}

	if (m_BT != Bird::BT_HAL)
	{
		m_BS = BIRD_STATE::BS_UNPOWER; 
	}
}




void Bird::Activate_Bomb()
{
	if (nullptr == m_Ray)
	{
		m_Ray = Add_Component<KRaycast_2D>();
	}

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

	state()->camera()->Shaking(1.0f, 100.0f);

	one()->set_Death();
}

void Bird::Activate_Blue()
{
	KPtr<TheOne> NewOne1 = state()->Create_TheOne(L"Bird");
	KPtr<TheOne> NewOne2 = state()->Create_TheOne(L"Bird");
	KPtr<Bird> NewBird1 = NewOne1->Add_Component<Bird>(Bird::BIRD_TYPE::BT_BLUE);
	KPtr<Bird> NewBird2 = NewOne2->Add_Component<Bird>(Bird::BIRD_TYPE::BT_BLUE);

	KVector4 TempVec = one()->Local_Pos();
	KVector2 TempVelo = m_Rigid->Body()->GetLinearVelocity();

	NewOne1->Local_Pos(TempVec.x, TempVec.y + one()->Local_Scale().y, TempVec.z);
	NewOne2->Local_Pos(TempVec.x, TempVec.y - one()->Local_Scale().y, TempVec.z);

	NewBird1->m_Rigid->Impulse({ TempVelo.x, TempVelo.y + 50.0f });
	NewBird2->m_Rigid->Impulse({ TempVelo.x, TempVelo.y - 50.0f });

	NewBird1->m_BS =  Bird::BIRD_STATE::BS_ACTCRUISE;
	NewBird2->m_BS =  Bird::BIRD_STATE::BS_ACTCRUISE;

	NewBird1->m_Launcher = this->m_Launcher;
	NewBird2->m_Launcher = this->m_Launcher;
}

void Bird::Activate_Bubble()
{
	m_Render->image(L"Bubble_Bomb.png");
	float Size = 300.0f;
	one()->Local_Scale(Size, Size, 10.0f);
	m_Rigid->Set_Transform();
}

void Bird::Activate_Chuck()
{
	KVector2 Dir = m_Rigid->Body()->GetLinearVelocity();
	Dir.normalize();
	m_Rigid->Impulse(m_Rigid->Body()->GetLinearVelocity() + Dir * 500.0f);
}

void Bird::Activate_Hal()
{
	float TempPowerX = 50.0f * DELTATIME;
	float TempPowerY = 5.0f * DELTATIME;

	KVector2 ThisVelo = m_Rigid->Body()->GetLinearVelocity();
	m_Rigid->Impulse({ ThisVelo.x - ThisVelo.x * TempPowerX, ThisVelo.y - ThisVelo.y * TempPowerY });
}

void Bird::Activate_Matilda()
{
	KPtr<TheOne> NewOne = state()->Create_TheOne(L"Egg");
	KPtr<Bird> NewBird = NewOne->Add_Component<Bird>(Bird::BIRD_TYPE::BT_MATILDAEGG);

	KVector2 Dir = { 1.0f, 1.0f };
	Dir.normalize();
	m_Rigid->Impulse(m_Rigid->Body()->GetLinearVelocity() + Dir * 500.0f);

	KVector4 TempVec = one()->Local_Pos();
	KVector2 TempVelo = m_Rigid->Body()->GetLinearVelocity();

	NewOne->Local_Pos(TempVec.x, TempVec.y - one()->Local_Scale().y, TempVec.z);
	NewBird->m_Rigid->Impulse({ .0f , -200.0f });
	NewBird->m_BS = Bird::BIRD_STATE::BS_CRUISE;
	NewBird->m_Launcher = this->m_Launcher;
}

void Bird::Activate_MightyEagle()
{

}

void Bird::Activate_Red()
{
	return;
}

void Bird::Activate_Terence()
{
	return;
}

void Bird::Activate_Egg()
{
	if (nullptr == m_Ray)
	{
		m_Ray = Add_Component<KRaycast_2D>();
	}

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
			else if (Bird::BIRD_TYPE::BT_MATILDA != Data->KRigid->Get_Component<Bird>()->Bird_Type())
			{
				continue;
			}
		}

		Distance = one()->Local_Pos().m_Pos.distance(Data->KRigid->one()->Local_Pos().m_Pos);
		Data->KRigid->Impulse(Dir * 15000.0f / Distance);
	}


	one()->set_Death();	
}

