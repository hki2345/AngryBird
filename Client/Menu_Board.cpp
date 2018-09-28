#include "Menu_Board.h"
#include "AngryStartUpdater.h"

#include <Mouse_Col.h>
#include <State.h>
#include <Renderer_Sprite.h>
#include <Collider2D_DE.h>
#include <ResourceManager.h>
#include <KFont.h>
#include <KWindow.h>



Menu_Board::Menu_Board()
{
}


Menu_Board::~Menu_Board()
{
	SSelect->set_Death();
	Replay->set_Death();
	Play->set_Death();
	Back->set_Death();
	Pause->set_Death();
}


bool Menu_Board::Init(const int& _Stage)
{
	Stage = _Stage;
	m_Font = ResourceManager<KFont>().Find(L"AngryBirds");

	SSelect = state()->Create_TheOne(L"SSelect");
	SSelect->Add_Component<Renderer_Sprite>(L"StageSelect_Btn.png");
	SSelect->Add_Component<Collider2D_DE>(0);

	Replay = state()->Create_TheOne(L"Replay");
	Replay->Add_Component<Renderer_Sprite>(L"Replay.png");
	Replay->Add_Component<Collider2D_DE>(0);

	Play = state()->Create_TheOne(L"Play");
	Play->Add_Component<Renderer_Sprite>(L"Play.png");
	Play->Add_Component<Collider2D_DE>(0);

	Back = state()->Create_TheOne(L"Back");
	Back->Add_Component<Renderer_Sprite>(L"MenuBoard.png");
	Back->Add_Component<Collider2D_DE>(0);

	Pause = state()->Create_TheOne(L"Pause");
	Pause->Add_Component<Renderer_Sprite>(L"Back_Btn.png");
	Pause->Add_Component<Collider2D_DE>(0);
	
	return true;
}


void Menu_Board::Update()
{
	if (true == m_Menu)
	{
		Set_Board();
	}
	else
	{
		UNSet_Board();
	}

	Set_Pause();
	Update_Col();
}

void Menu_Board::Update_Col()
{
	KPtr<Collider2D_DE> Col = MOUSE_DOWN(Mouse_Col::MOUSE_BTN::MBTN_LEFT);

	if (nullptr == Col)
	{
		return;
	}

	std::wstring ColName = Col->one()->name();

	if (L"Pause" == ColName)
	{
		if (true == m_Menu)
		{
			m_Menu = false;
		}
		else
		{
			m_Menu = true;
		}
	}
	else if (L"Play" == ColName)
	{
		m_Menu = false;
	}
	// else if (L"Replay" == ColName)
	// {
	// 	window()->this_StateManager.change_state(state()->name());
	// 	one()->set_Death();
	// }
	// else if (L"SSelect" == ColName)
	// {
	// 	// window()->this_StateManager.change_state(L"Title");
	// 	one()->set_Death();
	// }
}

void Menu_Board::Set_Pause()
{
	KPtr<Camera> Cam = state()->camera();
	KPtr<TheOne> CamOne = state()->camera()->one();
	KVector2 CPos = CamOne->Local_Pos().m_Pos;

	Pause->Local_Pos(
		Cam->screen_size().x * -550.0f / 1280.0f + CPos.x,
		Cam->screen_size().y * 300 / 720.0f + CPos.y, 4.0f);

	Pause->Local_Scale(
		Cam->screen_size().x * 90.0f / 1280.0f,
		Cam->screen_size().y * 90.0f / 720.0f, 10.0f);
}




void Menu_Board::Set_Board()
{
	KPtr<Camera> Cam = state()->camera();
	KPtr<TheOne> CamOne = state()->camera()->one();
	KVector2 CPos = CamOne->Local_Pos().m_Pos;

	// 원래 : X = Size : 60.0f; -> 60.0f * Size / 원래 = X
	float TargetPosX = 150.0f;
	float BtnPosX = 50.0f;

	// 크면 정해지기
	Back->Local_Pos(
		Cam->screen_size().x * (-640 + TargetPosX ) / 1280.0f + CPos.x,
		Cam->screen_size().y * .0f / 720.0f + CPos.y, 3.5f);

	SSelect->Local_Pos(
		Cam->screen_size().x * (-640 + TargetPosX + 10.0f) / 1280.0f + CPos.x,
		Cam->screen_size().y * 100.0f / 720.0f + CPos.y, 3.0f);
	Replay->Local_Pos(
		Cam->screen_size().x * (-640 + TargetPosX + 10.0f) / 1280.0f + CPos.x,
		Cam->screen_size().y * -100.0f / 720.0f + CPos.y, 3.0f);
	Play->Local_Pos(
		Cam->screen_size().x *(-640 + TargetPosX - 10.0f) / 1280.0f + CPos.x,
		Cam->screen_size().y * 300.0f / 720.0f + CPos.y, 3.0f);


	// 원래 : 60.0f = Size : X; -> 60.0f * Size / 원래 = X
	float StarSize = 200.0f;
	float BtnSize = 100.0f;

	Back->Local_Scale(
		Cam->screen_size().x * 300.0f / 1280.0f,
		Cam->screen_size().y, 10.0f);
	SSelect->Local_Scale(
		Cam->screen_size().x * BtnSize / 1280.0f,
		Cam->screen_size().y * BtnSize / 720.0f, 10.0f);
	Replay->Local_Scale(
		Cam->screen_size().x * BtnSize / 1280.0f,
		Cam->screen_size().y * BtnSize / 720.0f, 10.0f);
	Play->Local_Scale(
		Cam->screen_size().x * BtnSize / 1280.0f,
		Cam->screen_size().y * BtnSize / 720.0f, 10.0f);
}


void Menu_Board::UNSet_Board()
{
	KPtr<Camera> Cam = state()->camera();
	KPtr<TheOne> CamOne = state()->camera()->one();

	// 원래 : X = Size : 60.0f; -> 60.0f * Size / 원래 = X
	float TargetPosX = -150.0f;
	float BtnPosX = 50.0f;

	
	Back->Local_Pos(
		Cam->screen_size().x * (-640 + TargetPosX) / 1280.0f,
		Cam->screen_size().y * .0f / 720.0f, 3.5f);

	SSelect->Local_Pos(
		Cam->screen_size().x * (-640 + TargetPosX + 10.0f) / 1280.0f,
		Cam->screen_size().y * 100.0f / 720.0f, 3.0f);
	Replay->Local_Pos(
		Cam->screen_size().x * (-640 + TargetPosX + 10.0f) / 1280.0f,
		Cam->screen_size().y * -100.0f / 720.0f, 3.0f);
	Play->Local_Pos(
		Cam->screen_size().x *(-640 + TargetPosX - 10.0f) / 1280.0f,
		Cam->screen_size().y * 300.0f / 720.0f, 3.0f);


	// 원래 : 60.0f = Size : X; -> 60.0f * Size / 원래 = X
	float StarSize = 200.0f;
	float BtnSize = 100.0f;

	Back->Local_Scale(
		Cam->screen_size().x * 300.0f / 1280.0f,
		Cam->screen_size().y, 10.0f);
	SSelect->Local_Scale(
		Cam->screen_size().x * BtnSize / 1280.0f,
		Cam->screen_size().y * BtnSize / 720.0f, 10.0f);
	Replay->Local_Scale(
		Cam->screen_size().x * BtnSize / 1280.0f,
		Cam->screen_size().y * BtnSize / 720.0f, 10.0f);
	Play->Local_Scale(
		Cam->screen_size().x * BtnSize / 1280.0f,
		Cam->screen_size().y * BtnSize / 720.0f, 10.0f);
}


void Menu_Board::UIRender()
{
	if (false == m_Menu)
	{
		return;
	}

	wchar_t tempchar[100] = { 0, };
	swprintf_s(tempchar, L"%d", Stage);
	m_Font->draw_font(tempchar, { 100.0f, 30.0f}, 50.0f,
		KColor::White.color_to_reverse255(), FW1_TEXT_FLAG::FW1_TOP);
}