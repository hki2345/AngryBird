#include "Win_Board.h"
#include <State.h>
#include <Renderer_Sprite.h>
#include <Collider2D_DE.h>
#include <ResourceManager.h>
#include <KFont.h>
#include <GameData.h>
#include <Container_Class.h>
#include <SoundPlayer.h>

Win_Board::Win_Board()
{
}


Win_Board::~Win_Board()
{
	SSelect->set_Death();
	Replay->set_Death();
	NSelect->set_Death();
	Back->set_Death();

	for (size_t i = 0; i < 3; i++)
	{
		Star[i]->set_Death();
	}

	HighScore->set_Death();
}



bool Win_Board::Init(const int& _Stage)
{
	m_Stage = _Stage;
	SoundCheck = false;
	STime = .0f;
	m_Score = 5039;
	m_Font = ResourceManager<KFont>().Find(L"AngryBirds");

	SSelect = state()->Create_TheOne(L"SSelect");
	SSelect->Add_Component<Renderer_Sprite>(L"StageSelect_Btn.png");
	SSelect->Add_Component<Collider2D_DE>(0);

	Replay = state()->Create_TheOne(L"Replay");
	Replay->Add_Component<Renderer_Sprite>(L"Replay.png");
	Replay->Add_Component<Collider2D_DE>(0);

	NSelect = state()->Create_TheOne(L"NSelect");
	NSelect->Add_Component<Renderer_Sprite>(L"NextStage_Btn.png");
	NSelect->Add_Component<Collider2D_DE>(0);
	
	Back = state()->Create_TheOne(L"Back");
	Back->Add_Component<Renderer_Sprite>(L"WinBoard.png");
	Back->Add_Component<Collider2D_DE>(0);

	
	
	HighScore = state()->Create_TheOne(L"HighScore");
	HighScore->Add_Component<Renderer_Sprite>(L"HighScore.png");
	
	Star[0] = state()->Create_TheOne(L"LStar");
	Star[0]->Add_Component<Renderer_Sprite>(L"LeftWinStar.png");

	Star[1] = state()->Create_TheOne(L"MStar");
	Star[1]->Add_Component<Renderer_Sprite>(L"MiddleWinStar.png");

	Star[2] = state()->Create_TheOne(L"RStar");
	Star[2]->Add_Component<Renderer_Sprite>(L"RightWinStar.png");

	for (size_t i = 0; i < 3; i++)
	{
		Star[i]->active_Off();
	}
	HighScore->active_Off();

	m_SP = Back->Add_Component<SoundPlayer>();

	m_Start = false;

	return true;
}


void Win_Board::Update()
{
	if (false == m_Start)
	{
		m_Score = Container_Class::This_BirdLauncher()->GameScore();

		User_Data::ScoreData US;
		US.Stage = m_Stage;
		US.HighScore = m_Score;
		m_HighScore = User_Data::Is_HighScore(US);
		m_Start = true;
	}

	Set_Board();
	Update_Star();
}


void Win_Board::Set_Board()
{
	KPtr<Camera> Cam = state()->camera();
	KPtr<TheOne> CamOne = state()->camera()->one();
	KVector2 CPos = CamOne->Local_Pos().m_Pos;

	// 원래 : X = Size : 60.0f; -> 60.0f * Size / 원래 = X
	float StarPosX = 150.0f;
	float StarPosY = 100.0f;
	float BtnPosX = 120.0f;
	float BtnPosY = -200.0f;

	SSelect->Local_Pos(
		Cam->screen_size().x * -BtnPosX / 1280.0f + CPos.x,
		Cam->screen_size().y * BtnPosY / 720.0f + CPos.y, 4.0f);
	Replay->Local_Pos(
		Cam->screen_size().x * .0f / 1280.0f + CPos.x,
		Cam->screen_size().y * BtnPosY / 720.0f + CPos.y, 4.0f);
	NSelect->Local_Pos(
		Cam->screen_size().x * BtnPosX / 1280.0f + CPos.x,
		Cam->screen_size().y * BtnPosY / 720.0f + CPos.y, 4.0f);
	Back->Local_Pos(
		Cam->screen_size().x * .0f / 1280.0f + CPos.x,
		Cam->screen_size().y * .0f / 720.0f + CPos.y, 4.5f);
	HighScore->Local_Pos(
		Cam->screen_size().x * 200.0f / 1280.0f + CPos.x,
		Cam->screen_size().y * -60.0f / 720.0f + CPos.y, 4.0f);
	
	Star[0]->Local_Pos(
		Cam->screen_size().x * -StarPosX / 1280.0f + CPos.x,
		Cam->screen_size().y * StarPosY / 720.0f + CPos.y, 4.0f);
	Star[1]->Local_Pos(
		Cam->screen_size().x * .0f / 1280.0f + CPos.x,
		Cam->screen_size().y * (StarPosY + 10.0f) / 720.0f + CPos.y, 4.0f);
	Star[2]->Local_Pos(
		Cam->screen_size().x * StarPosX / 1280.0f + CPos.x,
		Cam->screen_size().y * StarPosY / 720.0f + CPos.y, 4.0f);


	// 원래 : 60.0f = Size : X; -> 60.0f * Size / 원래 = X
	float StarSize = 200.0f;
	float BtnSize = 100.0f;

	SSelect->Local_Scale(
		Cam->screen_size().x * BtnSize / 1280.0f,
		Cam->screen_size().y * BtnSize / 720.0f, 10.0f);
	Replay->Local_Scale(
		Cam->screen_size().x * BtnSize / 1280.0f,
		Cam->screen_size().y * BtnSize / 720.0f, 10.0f);
	NSelect->Local_Scale(
		Cam->screen_size().x * BtnSize / 1280.0f,
		Cam->screen_size().y * BtnSize / 720.0f, 10.0f);
	Back->Local_Scale(
		Cam->screen_size().x,
		Cam->screen_size().y, 10.0f);
	HighScore->Local_Scale(
		Cam->screen_size().x * 177.0f / 1280.0f,
		Cam->screen_size().y * 155.0f / 720.0f, 10.0f);


	for (size_t i = 0; i < 3; i++)
	{
		Star[i]->Local_Scale(
			Cam->screen_size().x * StarSize / 1280.0f,
			Cam->screen_size().y * StarSize / 720.0f, 10.0f);
	}
}


void Win_Board::Update_Star()
{
	if (false == SoundCheck)
	{
		m_SP->Play(L"WinBoard.mp3");
		m_SP->UnLoop();

		SoundCheck = true;
	}

	m_Star = Map_Data::CountingStar();

	STime += DELTATIME;
	if (1 <= m_Star)
	{
		if (.2f < STime && false == Star[0]->is_Active())
		{
			Star[0]->active_On();
		}

		if (1== m_Star)
		{
			if (1.0f < STime)
			{
				m_SP->Stop();
			}
		}
	}
	if (2 <= m_Star)
	{
		if (1.2f < STime && false == Star[1]->is_Active())
		{
			Star[1]->active_On();
		}

		if (2 == m_Star)
		{
			if (2.0f < STime)
			{
				m_SP->Stop();
			}
		}
	}
	if (3 == m_Star)
	{
		if (2.2f < STime && false == Star[2]->is_Active())
		{
			Star[2]->active_On();
		}

		if (true == m_HighScore)
		{
			if (3.3f < STime)
			{
				m_SP->Stop();
			}
		}
	}
	if (true == m_HighScore)
	{
		if (3.3f < STime)
		{
			HighScore->active_On();
		}
	}
}

void Win_Board::UIRender()
{
	wchar_t tempchar[100] = { 0, };

	swprintf_s(tempchar, L"LEVEL CLEARED!!");
	m_Font->draw_font(tempchar, { 480.0f, 60.0f }, 50.0f,
		KColor::Yellow.color_to_reverse255(), FW1_TEXT_FLAG::FW1_TOP);

	swprintf_s(tempchar, L"%d", m_Score);
	m_Font->draw_font(tempchar, { 590.0f, 360.0f }, 50.0f,
		KColor::White.color_to_reverse255(), FW1_TEXT_FLAG::FW1_TOP);
}