#include "stdafx.h"
#include "EditUpdater.h"

#include <KWindow.h>
#include <InputManager.h>
#include <DebugManager.h>
#include <Mouse_Col.h>
#include <KThread.h>
#include <TimeManager.h>
#include <Panza.h>
#include <Bird_Launcher.h>
#include <Bird.h>
#include <Bomb.h>
#include <Collider2D_DE.h>
#include <GameData.h>

#include "Dlg_TheOneTab.h"
#include "Edit_Class.h"

EditUpdater::EditUpdater()
{
}


EditUpdater::~EditUpdater()
{
}

void EditUpdater::Update_State()
{
	// 이거 순환참조 일어나서 -> 이거 알아내는 거 힘듬 ㅋㅋ
	// 문제는 업데이터에서 스테이트를 들고 있으려고 하니문제생김 ㅋㅋㅋㅋ
	// FindState = Edit_Class::Cur_State();

	CamMove();
	ObjToMouseCheck();
	Update_Trans();
	Update_Mouse();
	Update_OneTree();
}

void EditUpdater::Start_State()
{
	Number = 0;
	m_bTestThread = true;

	CamSpeed = 100.0f;
	debug_On();

	m_OriginScreen = window()->size();
	// KThread::Start_Thread<EditUpdater>(L"TestThread", &EditUpdater::Func, this);
}


void EditUpdater::Update_Mouse()
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

void EditUpdater::CamMove()
{
	if (KEY_PRESS("Up"))
	{
		state()->camera()->one()->transform()->Moving(KVector::Up * CamSpeed);
	}
	if (KEY_PRESS("Down"))
	{
		state()->camera()->one()->transform()->Moving(KVector::Down * CamSpeed);
	}
	if (KEY_PRESS("Left"))
	{
		state()->camera()->one()->transform()->Moving(KVector::Left * CamSpeed);
	}
	if (KEY_PRESS("Right"))
	{
		state()->camera()->one()->transform()->Moving(KVector::Right * CamSpeed);
	}
}


// 마우스 에 따라다니는 충돌체 - 충돌 체크
void EditUpdater::ObjToMouseCheck()
{
	Edit_Vertex();
	Edit_One();
}


void EditUpdater::Edit_Vertex()
{
	// 이거 폴리건 편집할 때 체크
	if (KEY_DOWN("MOUSE_LB"))
	{
		if (false == Mouse_InScreen())
		{
			if (nullptr != Edit_Class::BottomTab && TRUE == Edit_Class::BottomTab->EditOn())
			{
				Edit_Class::BottomTab->EditOn(FALSE);
				return;
			}
		}
	}

	// 버텍스 생성
	if (nullptr != Edit_Class::BottomTab && TRUE == Edit_Class::BottomTab->EditOn() &&
		KEY_DOWN("MOUSE_LB") && true == Mouse_InScreen())
	{
		// 다시 한번 체크 -> 최신화
		KPtr<Collider2D_DE> m_Col = Mouse_Col::Mouse_Down(Mouse_Col::MOUSE_BTN::MBTN_LEFT);
		KPtr<TheOne> TempOne;
		if (nullptr != m_Col && true == m_Col->is_Active())
		{
			TempOne = m_Col->one();

			// 현재 집은 게 있으면 탈출
			if (nullptr != TempOne) { return; }
		}

		Edit_Class::BottomTab->Create_Vertex();
		return;
	}
	
	if (KEY_DOWN("MOUSE_RB"))
	{
		if (nullptr != Edit_Class::BottomTab)
		{
			Edit_Class::BottomTab->EditOn(FALSE);
			return;
		}

		// 다시 한번 체크 -> 최신화
		KPtr<Collider2D_DE> m_Col = MOUSE_DOWN(Mouse_Col::MOUSE_BTN::MBTN_RIGHT);
		std::wstring Temp;
		if (nullptr != m_Col && true == m_Col->is_Active())
		{
			Temp = m_Col->one()->name();

			if (Temp == L"Bomb")
			{
				m_Col->Get_Component<Bomb>()->Activate_Bomb();
			}
		}
	}
}

void EditUpdater::Edit_One()
{
	// 누를 고 있을 시 -> 객체 이동
	if (KEY_PRESS("MOUSE_LB"))
	{
		// 널 피티알 검사 이유는 포커스 객체가 있을 것을 가정하기 때문
		if (true == Mouse_InScreen() && nullptr == Edit_Class::FocusOne)
		{
			// 다시 한번 체크 -> 최신화
			KPtr<Collider2D_DE> m_Col = MOUSE_DOWN(Mouse_Col::MOUSE_BTN::MBTN_LEFT);
			KPtr<TheOne> TempOne;
			if (nullptr != m_Col && true == m_Col->is_Active())
			{
				TempOne = m_Col->one();

				// 현재 집은 게 없으면 탈출
				if (nullptr == TempOne) { return; }

				Edit_Class::FocusOne = TempOne;
				Edit_Class::SelectOne = TempOne;
			}
		}
		else if (false == Mouse_InScreen())
		{
			Edit_Class::FocusOne = nullptr;
		}

		// 관심 객체 -> 지금 관심있는 것만 움직일 수 잇음
		// + 회전 조절가능
		if (nullptr != Edit_Class::FocusOne)
		{
			// 밑바닥이면 통과
			std::wstring Name = Edit_Class::FocusOne->name();
			if (L"StateBottom" == Name)
			{
				return;
			}

			// 새면 통과
			if (L"Bird" == Name)
			{
				return;
			}
			
			Edit_Class::FocusOne->Local_Pos({ Core_Class::main_state()->camera()->screen_to_world(
				InputManager::mouse_pos()) , Edit_Class::FocusOne->Local_Pos().z });



			// 판자면-> 속도 초기화
			KPtr<Panza> ThisPan = Edit_Class::FocusOne->Get_Component<Panza>();
			if (nullptr != ThisPan)
			{
				ThisPan->Reset_Rigid();
			}
			KPtr<Pig> ThisPig = Edit_Class::FocusOne->Get_Component<Pig>();
			if (nullptr != ThisPig)
			{
				ThisPig->Reset_Rigid();
			}
			KPtr<Bomb> ThisBomb = Edit_Class::FocusOne->Get_Component<Bomb>();
			if (nullptr != ThisBomb)
			{
				ThisBomb->Reset_Rigid();
			}


			if (KEY_DOWN("LeftRot"))
			{
				Edit_Class::FocusOne->transform()->Local_Rotate( .0f, .0f, 90.0f );
			}
			else if (KEY_DOWN("RightRot"))
			{
				Edit_Class::FocusOne->transform()->Local_Rotate( .0f, .0f, .0f );
			}
		}
	}

	if (KEY_UP("MOUSE_LB"))
	{
		Edit_Class::FocusOne = nullptr;
/*
		if (nullptr != Edit_Class::SelectOne && true == Mouse_InScreen())
		{
			if (nullptr != Edit_Class::SelectOne->Get_Component<Panza>() ||
				nullptr != Edit_Class::SelectOne->Get_Component<Bird_Launcher>())
			{
				Edit_Class::m_View_Component->Dlg_Release();
				Edit_Class::m_View_Component->set_one(Edit_Class::SelectOne);
			}
		}*/
	}
}


void EditUpdater::Update_Trans()
{
	if (nullptr == Edit_Class::TransTab)
	{
		return;
	}

	if (nullptr != Edit_Class::TransTab->m_Trans && true == KEY_UP("MOUSE_LB"))
	{
		Edit_Class::TransTab->Update_EditValue();
	}
}

void EditUpdater::Update_OneTree()
{
	if (nullptr != Edit_Class::TheOneTab)
	{
		if (Map_Data::Map_Count(Core_Class::main_state()) != Edit_Class::TheOneTab->TheOne_TreeCount())
		{
			Edit_Class::TheOneTab->Reset_OneTree();
		}
	}
}


void EditUpdater::Debug_Render()
{
	wchar_t Arr[256];
	
	KVector2 MPos = state()->camera()->screen_to_world(InputManager::mouse_pos());

	swprintf_s(Arr, L"World\tPos: %3.0f, %3.0f", MPos.x, MPos.y);
	DRAW_FONT(Arr, { 10.0f, 20.0f }, 20.0f);

	swprintf_s(Arr, L"Window\tPos: %3.0f, %3.0f", InputManager::mouse_pos().x, InputManager::mouse_pos().y);
	DRAW_FONT(Arr, { 10.0f, 40.0f }, 20.0f);

	swprintf_s(Arr, L"FPS: %3.2f", 1 / DELTATIME);
	DRAW_FONT(Arr, { 10.0f, 60.0f }, 20.0f);

	swprintf_s(Arr, L"Cam Pos: %3.2f %3.2f", Core_Class::main_state()->camera()->one()->Local_Pos().x, Core_Class::main_state()->camera()->one()->Local_Pos().y);
	DRAW_FONT(Arr, { 10.0f, 80.0f }, 20.0f);
}

void EditUpdater::TestThread()
{
	if (KEY_DOWN("Quit"))
	{
		KThread::Start_Thread<EditUpdater>(L"TestThread", &EditUpdater::Func, this);

		if (true == m_bTestThread)
		{
			KThread::Pause_Thread(L"TestThread");
			CheckNumber = Number;
			m_bTestThread = false;
		}
		else {
			KThread::Recov_Thread(L"TestThread");
			m_bTestThread = true;
		}
	}
}

unsigned int EditUpdater::Func(void* _Test)
{
	Number = 0;
	float Time = 0.0f;

	KPtr<TimeManager::Timer> ptr = TimeManager::Create_Timer(L"TestTimer");

	while (true)
	{
		Time += ptr->Update();

		if (Time > 0.5f)
		{
			++Number;
			Time = 0.0f;
		}
	}

	return 0;
}


bool EditUpdater::Mouse_InScreen()
{
	KVector CPos = Core_Class::main_state()->camera()->one()->Local_Pos();
	KVector2 MPos = state()->camera()->screen_to_world(InputManager::mouse_pos());

	if (window()->size().x_part() < fabsf(MPos.x - CPos.x) ||
		window()->size().y_part() < fabsf(MPos.y - CPos.y))
	{
		return false;
	}
	return true;
}