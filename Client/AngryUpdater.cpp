#include "AngryUpdater.h"
#include "Win_Board.h"
#include "Menu_Board.h"
#include "AngryStartUpdater.h"

#include <Core_Class.h>

#include <InputManager.h>
#include <TimeManager.h>
#include <ResourceManager.h>
#include <Renderer_Sprite.h>
#include <Collider2D_DE.h>
#include <KRigid_2D.h>
#include <DebugManager.h>
#include <KFont.h>

#include <GameData.h>
#include <SoundPlayer.h>
#include <KSound.h>
#include <Container_Class.h>
#include <Mouse_Col.h>

AngryUpdater::AngryUpdater()
{
}


AngryUpdater::~AngryUpdater()
{
}

void AngryUpdater::Start_State()
{
	m_CamSpeed = 100.0f;
	wchar_t SName[10];
	std::wstring WName = state()->name();;


	for (size_t i = 0; i < WName.size() - 5; i++)
	{
		SName[i] = WName.c_str()[i + 5];
		SName[i + 1] = 0;
	}

	m_Stage = _wtoi(SName);


	m_WBoard = state()->Create_TheOne(L"WinBoard");
	m_WBoard->Add_Component<Win_Board>(m_Stage);

	m_MBoard = state()->Create_TheOne(L"MenuBoard");
	m_MBoard->Add_Component<Menu_Board>(m_Stage);

	m_WBoard->active_Off();

	WinBoard = false;
	WinDTime = .0f;

	Start_BG();

	std::wstring Temp = PathManager::Find_Path(L"State");

	Temp += state()->name();
	Temp += L".SD";

	Map_Data::Map_Load(state(), Temp.c_str());

	m_Font = ResourceManager<KFont>().Find(L"AngryBirds");

	KPtr<KSound> SS = ResourceManager<KSound>::Find(L"003 BLACKPINK - Forever Young.mp3");
	SoundPlayer thisSP = SoundPlayer();
	// thisSP.Play(L"003 BLACKPINK - Forever Young.mp3");

	m_OriginScreen = window()->size();
	Container_Class::Set_BirdLauncher(state());

	m_SP = m_SkyOne[0]->Add_Component<SoundPlayer>();
	m_SP->Play(L"Begin.mp3");
	m_SP->UnLoop();

	m_EndSound = false;

}

void AngryUpdater::Start_BG()
{
	for (size_t i = 0; i < 2; i++)
	{
		m_SkyOne[i] = state()->Create_TheOne(L"Sky");
		m_SkyOne[i]->Add_Component<Renderer_Sprite>(L"Sky.png");

		m_MountainOne[i] = state()->Create_TheOne(L"Mountain");
		m_MountainOne[i]->Add_Component<Renderer_Sprite>(L"Mountain.png");

		m_WoodOne[i] = state()->Create_TheOne(L"Wood");
		m_WoodOne[i]->Add_Component<Renderer_Sprite>(L"Wood.png");

		m_GroundOne[i] = state()->Create_TheOne(L"Ground");
		m_GroundOne[i]->Add_Component<Renderer_Sprite>(L"AngryGround.png");

		m_SkyOne[i]->Set_Image_RatioW(window()->size().x);
		m_MountainOne[i]->Set_Image_RatioW(window()->size().x);
		m_WoodOne[i]->Set_Image_RatioW(window()->size().x);
		m_GroundOne[i]->Set_Image_RatioW(window()->size().x);

		m_SkyOne[i]->Local_Pos(.0f + window()->size().x * i - 3.0f * i, 95.0f, 23.0f);
		m_MountainOne[i]->Local_Pos(.0f + window()->size().x * i - 3.0f * i, -150.0f, 22.0f);
		m_WoodOne[i]->Local_Pos(.0f + window()->size().x * i - 3.0f * i, -150.0f, 21.0f);
		m_GroundOne[i]->Local_Pos(0.0f + window()->size().x * i - 3.0f * i, -309.0f, 15.0f);


		KPtr<TheOne> BotRigid = state()->Create_TheOne(L"GroundRigid");
		BotRigid->Local_Scale(m_GroundOne[i]->Local_Scale());
		BotRigid->Local_Pos(m_GroundOne[i]->Local_Pos());

		KPtr<Collider2D_DE> Colider = BotRigid->Add_Component<Collider2D_DE>(0);
		Colider->type(COLL_TYPE::COL_RECT2D);
		Colider->color(KColor::White);

		KPtr<KRigid_2D> Rigid = BotRigid->Add_Component<KRigid_2D>();
		Rigid->Set_Type(b2BodyType::b2_staticBody);
	}
}


void AngryUpdater::Update_State()
{
	Update_Cam();
	Update_Mouse();
	Update_WinCheck();
	Update_WinBoard();
}

void AngryUpdater::Update_Cam()
{
	KPtr<Camera> Cam = state()->camera();
	KVector CPos = Cam->one()->Local_Pos();


	if (KEY_PRESS("Up"))
	{
		// 올라가면 안됌
		if (Cam->screen_size().y * .5f + CPos.y > 360.0f)
		{
			state()->camera()->one()->Local_Pos(
				CPos.x,
				360.0f - Cam->screen_size().y * .5f,
				CPos.z);
		}
		else
		{
			state()->camera()->one()->transform()->Moving(KVector::Up * m_CamSpeed);
		}
	}
	if (KEY_PRESS("Down"))
	{
		// 내려가면 안됌
		if (-Cam->screen_size().y * .5f + CPos.y < -360.0f)
		{
			state()->camera()->one()->Local_Pos(
				CPos.x,
				-360.0f + Cam->screen_size().y * .5f,
				CPos.z);
		}
		else
		{
			state()->camera()->one()->transform()->Moving(KVector::Down * m_CamSpeed);
		}
	}
	if (KEY_PRESS("Left"))
	{
		// 올라가면 안됌
		if (-Cam->screen_size().x * .5f + CPos.x < -300.0f)
		{
			state()->camera()->one()->Local_Pos(
				-300.0f + Cam->screen_size().x * .5f,
				CPos.y,
				CPos.z);
		}
		else
		{
			state()->camera()->one()->transform()->Moving(KVector::Left * m_CamSpeed);
		}
	}
	if (KEY_PRESS("Right"))
	{
		// 올라가면 안됌
		if (Cam->screen_size().x * .5f + CPos.x > 1000.0f)
		{
			state()->camera()->one()->Local_Pos(
				1000.0f - Cam->screen_size().x * .5f,
				CPos.y,
				CPos.z);
		}
		else
		{
			state()->camera()->one()->transform()->Moving(KVector::Right * m_CamSpeed);
		}
	}
}

void AngryUpdater::Update_Mouse()
{
	float ZoomSize = 50.0f;
	KVector2 Temp = state()->camera()->screen_size();
	float ratio = Temp.y / Temp.x;

	if (KEY_PRESS("MOUSE_MB"))
	{
		if (KEY_DOWN("MOUSE_LB"))
		{
			state()->camera()->screen_size({ Temp.x - (50.0f * 1.0f), Temp.y - (50.0f * ratio) });
		}
		else if (KEY_DOWN("MOUSE_RB"))
		{
			state()->camera()->screen_size({ Temp.x + (50.0f * 1.0f), Temp.y + (50.0f * ratio) });
		}
	}

	// 최소 최대 줌 설정
	if (state()->camera()->screen_size().x < m_OriginScreen.x * .5f)
	{
		state()->camera()->screen_size(m_OriginScreen * .5f);
	}
	else if (state()->camera()->screen_size().x > m_OriginScreen.x)
	{
		state()->camera()->screen_size(m_OriginScreen);
	}
}

void AngryUpdater::Update_WinCheck()
{
	if (0 == state()->Count_Name(L"Pig"))
	{
		WinDTime += DELTATIME;

		if (WinDTime > 3.0f && false == WinBoard)
		{
			Win_Stage();
		}

		if (false == m_EndSound)
		{
			m_SP->Play(L"End.mp3");
			m_EndSound = true;
		}
	}
}

void AngryUpdater::Update_WinBoard()
{
	KPtr<Collider2D_DE> Col = MOUSE_DOWN(Mouse_Col::MOUSE_BTN::MBTN_LEFT);

	if (nullptr == Col)
	{
		return;
	}

	std::wstring ColName = Col->one()->name();

	if (L"SSelect" == ColName)
	{
		window()->this_StateManager.change_state(L"Title");
		End_Angry();
	}

	if (L"Replay" == ColName)
	{
		window()->this_StateManager.change_state(state()->name()); 
		End_Angry();
	}

	if (L"NSelect" == ColName)
	{
		if (12 == m_Stage)
		{
			window()->this_StateManager.change_state(state()->name());
			End_Angry();
		}
			
		++m_Stage;
		wchar_t Num[4] = {};
		std::wstring NextStage = L"Stage";
		_itow_s(m_Stage, Num, 10);
		NextStage += Num;

		window()->this_StateManager.change_state(NextStage.c_str());
		End_Angry();
	}
}

void AngryUpdater::Win_Stage()
{
	WinBoard = true;

	if (false == m_WBoard->is_Active())
	{
		m_WBoard->active_On();

		User_Data::ScoreData TScore;
		TScore.HighScore = Container_Class::This_BirdLauncher()->GameScore();
		TScore.Stage = m_Stage;

		User_Data::InsertScore(TScore);
		User_Data::SaveScore();
	} 

	m_WBoard->active_On();
}

void AngryUpdater::UI_Render()
{

	int TempVec = (int)window()->size().x;

	float TempX = window()->size().x;

	wchar_t tempchar[100] = { 0, };


	float Board = 1.0f;

}

void AngryUpdater::Debug_Render()
{
#ifdef _DEBUG

	wchar_t tempchar[100] = { 0, };

	swprintf_s(tempchar, L"FPS: %3.2f", 1.0f / DELTATIME);
	m_Font->draw_font(tempchar, { 10.0f, 40.0f }, 20.0f, KColor::White.color_to_reverse255(), FW1_TEXT_FLAG::FW1_TOP);

#endif // _DEBUG
}

void AngryUpdater::End_Angry()
{
	m_MBoard->set_Death();
	m_WBoard->set_Death();
	Container_Class::Erase_BirdLauncher(state());
}