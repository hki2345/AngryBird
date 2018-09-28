#include "AngryStartUpdater.h"
#include <Core_Class.h>


#include <InputManager.h>

#include <ResourceManager.h>
#include <DebugManager.h>
#include <KFont.h>
#include <SoundPlayer.h>
#include <KSound.h>
#include <Mouse_Col.h>

#include <Renderer_Sprite.h>
#include <Collider2D_DE.h>
#include <GameData.h>

AngryStartUpdater::AngryStartUpdater() : m_Title(true)
{
}


AngryStartUpdater::~AngryStartUpdater()
{
}

void AngryStartUpdater::Start_State()
{
	if (true == m_Title)
	{
		m_StartFsm = START_TYPE::START_TITLE;
	}
	else
	{
		m_StartFsm = START_TYPE::START_LEVEL;
		m_SP->Play(L"Angry Birds Theme Song.mp3");
		m_SP->Loop();
		return;
	}

	Start_BG();
	Start_Intro();
	Start_Episode();
	Start_Level();

	UnActive_Intro();
	UnActive_Episode();
	UnActive_Level();

	m_Back->active_Off();
	m_Font = ResourceManager<KFont>().Find(L"AngryBirds");

	m_SP = m_SkyOne[0]->Add_Component<SoundPlayer>();
	m_SP->Play(L"Angry Birds Theme Song.mp3");
	m_SP->Loop();


	if (true == m_Title)
	{
		m_Title = false;
	}
}


void AngryStartUpdater::Start_BG()
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
		m_GroundOne[i]->Add_Component<Renderer_Sprite>(L"Ground.png");

		m_SkyOne[i]->Set_Image_RatioW(window()->size().x);
		m_MountainOne[i]->Set_Image_RatioW(window()->size().x);
		m_WoodOne[i]->Set_Image_RatioW(window()->size().x);
		m_GroundOne[i]->Set_Image_RatioW(window()->size().x);


		m_SkyOne[i]->Local_Pos(.0f + window()->size().x * i - 3.0f * i, 95.0f, 13.0f);
		m_MountainOne[i]->Local_Pos(.0f + window()->size().x * i - 3.0f* i, -150.0f, 12.0f);
		m_WoodOne[i]->Local_Pos(.0f + window()->size().x * i - 3.0f * i, -150.0f, 11.0f);
		m_GroundOne[i]->Local_Pos(0.0f + window()->size().x * i - 3.0f * i, -285.0f, 10.0f);
	}
}

void  AngryStartUpdater::Start_Intro()
{
	PlayBtn = state()->Create_TheOne(L"Play_Btn");
	PlayBtn->Add_Component<Renderer_Sprite>(L"Play_Btn.png");
	PlayBtn->Add_Component<Collider2D_DE>(0);
	PlayBtn->Local_Pos(0.0f, .0f, 5.0f);
	PlayBtn->Set_ImageSize();

	m_Logo = state()->Create_TheOne(L"Logo");
	m_Logo->Add_Component<Renderer_Sprite>(L"Logo.png");
	m_Logo->Local_Pos(0.0f, 200.0f, 5.0f);
	m_Logo->Set_ImageSize();
}

void AngryStartUpdater::Start_Episode()
{
	m_Back = state()->Create_TheOne(L"Back_Btn");
	m_Back->Add_Component<Renderer_Sprite>(L"Back_Btn.png");
	m_Back->Add_Component<Collider2D_DE>(0);
	m_Back->Local_Pos(-640.0f + 50.0f, 300.0f, 3.0f);
	m_Back->Set_ImageSize();

	for (size_t i = 0; i < 3; i++)
	{
		std::wstring Temp = L"Episode";
		wchar_t IntTemp[2] = L"";
		_itow_s((int)(i + 1), IntTemp, sizeof(wchar_t), 10);

		Temp += IntTemp;
		m_Episode[i] = state()->Create_TheOne(Temp.c_str());

		Temp += L".png";
		m_Episode[i]->Add_Component<Renderer_Sprite>(Temp.c_str());
		m_Episode[i]->Add_Component<Collider2D_DE>(0);
		m_Episode[i]->Local_Pos(400.0f * i, .0f, 5.0f);
		m_Episode[i]->Set_ImageSize();

	}

	m_EpisodeSelect = state()->Create_TheOne(L"Select_Episode");
	m_EpisodeSelect->Add_Component<Renderer_Sprite>(L"Select_Episode.png");
	m_EpisodeSelect->Local_Pos(0.0f, 250.0f, 5.0f);
	m_EpisodeSelect->Set_ImageSize();
}

void AngryStartUpdater::Start_Level()
{
	//for (size_t i = 0; i < 4; i++)
	//{
	//	for (size_t h = 0; h < 3; h++)
	//	{
	//		for (size_t k = 0; k < 3; k++)
	//		{
	//			m_LevelStar[i][h][k] = state()->Create_TheOne(L"Level Start");
	//			m_LevelStar[i][h][k]->Add_Component<Renderer_Sprite>(L"LevelStar.png");
	//			m_LevelStar[i][h][k]->Get_Component<Renderer_Sprite>()->image()->Split(2, 1);
	//			m_LevelStar[i][h][k]->Local_Scale(60.0f, 60.0f, 10.0f);
	//		}
	//	}
	//}


	int StageInx = 1;
	std::wstring Temp = L"Stage";
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			wchar_t StageNum[4] = {};
			std::wstring stageName = Temp;
			_itow_s(StageInx, StageNum, 10);
			stageName += StageNum;

			m_Level[j][i] = state()->Create_TheOne(stageName.c_str());
			m_Level[j][i]->Add_Component<Renderer_Sprite>(L"Level_Select1.png");
			m_Level[j][i]->Add_Component<Collider2D_DE>(0);
			m_Level[j][i]->Local_Pos(
				250.0f * j - window()->size().x_part() + 250.0f, 
				200.0f * i * -1.0f + 150.0f, 5.0f);
			m_Level[j][i]->Set_ImageSize();
			++StageInx;
		}
	}

	m_LevelSelect = state()->Create_TheOne(L"Select_Level");
	m_LevelSelect->Add_Component<Renderer_Sprite>(L"Select_Level.png");
	m_LevelSelect->Local_Pos(0.0f, 300.0f, 5.0f);
	m_LevelSelect->Set_ImageSize();
}



void AngryStartUpdater::End_State()
{
	m_SP->Stop();
}

void AngryStartUpdater::UI_Render()
{
	int TStage = 1;
	if (START_TYPE::START_LEVEL == m_StartFsm)
	{
		wchar_t tempchar[100] = { 0, };
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 4; j++)
			{
				swprintf_s(tempchar, L"%d", TStage);
				m_Font->draw_font(tempchar, { 245.0f * j + 250.0f,
					200.0f * i  + 170.0f }, 40.0f, KColor::White.color_to_reverse255(), FW1_TEXT_FLAG::FW1_CENTER);
				++TStage;
			}
		}
	}
}

void AngryStartUpdater::Debug_Render()
{
#ifdef _DEBUG

	wchar_t tempchar[100] = { 0, };

	swprintf_s(tempchar, L"FPS: %3.2f", 1.0f / DELTATIME);
	m_Font->draw_font(tempchar, { 10.0f, 40.0f }, 20.0f, KColor::White.color_to_reverse255(), FW1_TEXT_FLAG::FW1_TOP);

#else

	wchar_t tempchar[100] = { 0, };

	swprintf_s(tempchar, L"");
	m_Font->draw_font(tempchar, { 10.0f, 40.0f }, 20.0f, KColor::White.color_to_reverse255(), FW1_TEXT_FLAG::FW1_TOP);

#endif // _DEBUG

}

void AngryStartUpdater::Update_State()
{
	switch (m_StartFsm)
	{
	case AngryStartUpdater::START_TITLE:
		Update_Title();
		break;
	case AngryStartUpdater::START_INTRO:
		Update_Intro();
		Update_BG();
		break;
	case AngryStartUpdater::START_EPISODE:
		Update_Episode();
		Update_BG();
		break;
	case AngryStartUpdater::START_LEVEL:
		Update_Level();
		Update_BG();
		break;
	case AngryStartUpdater::START_NONE:
	case AngryStartUpdater::START_NUM:
	default:
		break;
	}
}




void AngryStartUpdater::Update_Title()
{
	UnActive_Level();
	UnActive_Episode();
	UnActive_Level();

	KPtr<Collider2D_DE> m_Col = MOUSE_DOWN(Mouse_Col::MOUSE_BTN::MBTN_LEFT);

	if (nullptr != m_Col)
	{
		std::wstring Teamp = m_Col->one()->name();

		if (L"Title" == Teamp)
		{
			m_Col->one()->set_Death();
			m_StartFsm = START_TYPE::START_INTRO;
		}
		else if (L"Back_Btn" == Teamp)
		{
			m_StartFsm = START_TYPE::START_INTRO;
			return;
		}
	}
}

void AngryStartUpdater::Update_Intro()
{
	Active_Intro();
	UnActive_Episode();
	UnActive_Level();

	KPtr<Collider2D_DE> m_Col = MOUSE_DOWN(Mouse_Col::MOUSE_BTN::MBTN_LEFT);

	if (nullptr != m_Col)
	{
		std::wstring Teamp = m_Col->one()->name();

		if (L"Play_Btn" == Teamp)
		{
			m_StartFsm = START_TYPE::START_EPISODE;
		}
	}

}

void AngryStartUpdater::Update_Episode()
{
	UnActive_Intro();
	Active_Episode();
	UnActive_Level();

	KPtr<Collider2D_DE> m_Col = MOUSE_DOWN(Mouse_Col::MOUSE_BTN::MBTN_LEFT);

	if (nullptr != m_Col)
	{
		std::wstring Teamp = m_Col->one()->name();

		if (L"Back_Btn" == Teamp)
		{
			m_StartFsm = START_TYPE::START_INTRO;
			return;
		}

		if (L"Episode1" == Teamp)
		{
			m_StartFsm = START_TYPE::START_LEVEL;
		}
	}
}

void AngryStartUpdater::Update_Level()
{
	UnActive_Intro();
	UnActive_Episode();
	Active_Level();

	KPtr<Collider2D_DE> m_Col = MOUSE_DOWN(Mouse_Col::MOUSE_BTN::MBTN_LEFT);

	if (nullptr != m_Col)
	{
		std::wstring Teamp = m_Col->one()->name();
		if (L"Back_Btn" == Teamp)
		{
			m_StartFsm = START_TYPE::START_EPISODE;
			return;
		}

		state()->statemanager()->change_state(Teamp.c_str());
	}
}

void AngryStartUpdater::Update_BG() 
{
	m_SkyOne[0]->transform()->Moving({ -20.0f, .0f, .0f, .0f });
	m_MountainOne[0]->transform()->Moving({ -50.0f, .0f, .0f, .0f });
	m_WoodOne[0]->transform()->Moving({ -80.0f, .0f, .0f, .0f });
	m_GroundOne[0]->transform()->Moving({ -100.0f, .0f, .0f, .0f });
	
	m_SkyOne[1]->Local_Pos(
		m_SkyOne[0]->Local_Pos().x + m_SkyOne[0]->Local_Scale().x - 3.0f,
		m_SkyOne[0]->Local_Pos().y,
		m_SkyOne[0]->Local_Pos().z);
	m_MountainOne[1]->Local_Pos(
		m_MountainOne[0]->Local_Pos().x + m_MountainOne[0]->Local_Scale().x - 3.0f,
		m_MountainOne[0]->Local_Pos().y,
		m_MountainOne[0]->Local_Pos().z);
	m_WoodOne[1]->Local_Pos(
		m_WoodOne[0]->Local_Pos().x + m_WoodOne[0]->Local_Scale().x - 3.0f,
		m_WoodOne[0]->Local_Pos().y,
		m_WoodOne[0]->Local_Pos().z);
	m_GroundOne[1]->Local_Pos(
		m_GroundOne[0]->Local_Pos().x + m_GroundOne[0]->Local_Scale().x - 3.0f,
		m_GroundOne[0]->Local_Pos().y,
		m_GroundOne[0]->Local_Pos().z);

	if (m_SkyOne[0]->Local_Pos().x < 0 - window()->size().x)
	{
		m_SkyOne[0]->Local_Pos(.0f + window()->size().x, 95.0f, 13.0f);
		KPtr<TheOne> Temp = m_SkyOne[0];
		m_SkyOne[0] = m_SkyOne[1];
		m_SkyOne[1] = Temp;
	}
	if (m_MountainOne[0]->Local_Pos().x < 0 - window()->size().x)
	{
		m_MountainOne[0]->Local_Pos(.0f + window()->size().x, -150.0f, 12.0f);
		KPtr<TheOne> Temp = m_MountainOne[0];
		m_MountainOne[0] = m_MountainOne[1];
		m_MountainOne[1] = Temp;
	}
	if (m_WoodOne[0]->Local_Pos().x < 0 - window()->size().x)
	{
		m_WoodOne[0]->Local_Pos(.0f + window()->size().x, -150.0f, 11.0f);
		KPtr<TheOne> Temp = m_WoodOne[0];
		m_WoodOne[0] = m_WoodOne[1];
		m_WoodOne[1] = Temp;
	}
	if (m_GroundOne[0]->Local_Pos().x < 0 - window()->size().x)
	{
		m_GroundOne[0]->Local_Pos(.0f + window()->size().x, -285.0f, 10.0f);
		KPtr<TheOne> Temp = m_GroundOne[0];
		m_GroundOne[0] = m_GroundOne[1];
		m_GroundOne[1] = Temp;
	}
}


void AngryStartUpdater::Active_Intro()
{
	m_Logo->active_On();
	for (size_t i = 0; i < 2; i++)
	{
		m_GroundOne[i]->active_On();
		m_WoodOne[i]->active_On();
		m_MountainOne[i]->active_On();
		m_SkyOne[i]->active_On();
	}
	PlayBtn->active_On();
}
void AngryStartUpdater::Active_Episode()
{
	m_EpisodeSelect->active_On();
	for (size_t i = 0; i < 3; i++)
	{
		m_Episode[i]->active_On();
		// m_Lock[i]->active_On();
	}
}
void AngryStartUpdater::Active_Level()
{
	m_LevelSelect->active_On();
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			m_Level[j][i]->active_On();
			// m_LevelLock[i]->active_On();
		}
	}
}



void AngryStartUpdater::UnActive_Intro()
{
	m_Logo->active_Off();
	PlayBtn->active_Off();


	m_Back->active_On();
}
void AngryStartUpdater::UnActive_Episode()
{
	m_EpisodeSelect->active_Off();
	for (size_t i = 0; i < 3; i++)
	{
		m_Episode[i]->active_Off();
		// m_Lock[i]->active_Off();
	}
}
void AngryStartUpdater::UnActive_Level()
{
	m_LevelSelect->active_Off();
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			m_Level[j][i]->active_Off();
			// m_LevelLock[i]->active_Off();
		}
	}
}