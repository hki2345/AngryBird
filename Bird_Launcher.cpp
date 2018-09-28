#include "Bird_Launcher.h"
#include "GameData.h"


#include <Core_Class.h>

#include <Renderer_Sprite.h>
#include <KRigid_2D.h>
#include <Collider2D_DE.h>
#include <KFont.h>

#include <KWindow.h>
#include <ResourceManager.h>
#include <DebugManager.h>
#include <State.h>


Bird_Launcher::Bird_Launcher() :m_GameScore(0), m_MovingScore(0)
{
	for (size_t i = 0; i < 3; i++)
	{
		m_HighScore[i] = 0;
	}
}


Bird_Launcher::~Bird_Launcher()
{
}

bool Bird_Launcher::Init()
{
	// 바닥이자 판자일 수 없다.
	m_Render[0] = Add_Component<Renderer_Sprite>(L"Bird_Launcher1.png");
	m_Render[1] = Add_Component<Renderer_Sprite>(L"Bird_Launcher2.png");


	m_Render[0]->inde_pivot(KVector4(one()->Local_Pos().x, one()->Local_Pos().y, one()->Local_Pos().z + 20.0f));
	m_Render[1]->inde_pivot(KVector4( one()->Local_Pos().x - 6.25f, one()->Local_Pos().y + 8.25f, one()->Local_Pos().z - 5.0f));
	m_Render[0]->inde_scale(m_Render[0]->image_size() * .25f);
	m_Render[1]->inde_scale(m_Render[1]->image_size() * .25f);
	m_Launch_Point = one()->Local_Pos().m_Pos;

	KVector Temp = m_Render[0]->image_size();
	Temp.x += m_Render[0]->image_size().x;

	one()->Local_Scale(10.0f, 20.0f, 10.0f);

	m_Collider = Add_Component<Collider2D_DE>(0);

	m_Font = ResourceManager<KFont>().Find(L"AngryBirds");


	wchar_t SName[10];
	std::wstring WName = state()->name();
	
	if (0 >= (int)WName.size() - 5)
	{
		return true;
	}

	for (size_t i = 0; i < WName.size() - 5; i++)
	{
		SName[i] = WName.c_str()[i + 5];
		SName[i + 1] = 0;
	}

	int m_Stage = _wtoi(SName);

	User_Data::LoadScore();
	m_RecordScore = User_Data::FindScore(m_Stage);

	if (-1 == m_RecordScore)
	{
		m_RecordScore = 0;
	}

	return true;
}

void Bird_Launcher::Update()
{
	Update_LP();
	Update_List();
}

void Bird_Launcher::UIRender()
{
	if (m_GameScore < m_MovingScore)
	{
		m_GameScore += (int)(1.0f / DELTATIME / 20.0f);
	}

	else if (m_GameScore > m_MovingScore)
	{
		m_GameScore -= (int)(1.0f / DELTATIME / 20.0f);
	}

	int TempVec = (int)window()->size().x;

	float TempX = window()->size().x;

	wchar_t tempchar[100] = { 0, };


	float Board = 1.0f;

	swprintf_s(tempchar, L"Score:");
	m_Font->draw_font(tempchar, { TempX - 400.0f+Board, 30.0f + Board}, 50.0f, KColor::Black.color_to_reverse255(), FW1_TEXT_FLAG::FW1_TOP);
												  
	swprintf_s(tempchar, L"%d", m_GameScore);	  
	m_Font->draw_font(tempchar, { TempX - 50.0f+Board, 30.0f + Board}, 50.0f, KColor::Black.color_to_reverse255(), FW1_TEXT_FLAG::FW1_RIGHT);
												 
	swprintf_s(tempchar, L"Score:");			 
	m_Font->draw_font(tempchar, { TempX - 400.0f -Board, 30.0f - Board}, 50.0f, KColor::Black.color_to_reverse255(), FW1_TEXT_FLAG::FW1_TOP);
												
	swprintf_s(tempchar, L"%d", m_GameScore);	
	m_Font->draw_font(tempchar, { TempX - 50.0f -Board, 30.0f - Board}, 50.0f, KColor::Black.color_to_reverse255(), FW1_TEXT_FLAG::FW1_RIGHT);
												
	swprintf_s(tempchar, L"Score:");			
	m_Font->draw_font(tempchar, { TempX - 400.0f +Board, 30.0f - Board}, 50.0f, KColor::Black.color_to_reverse255(), FW1_TEXT_FLAG::FW1_TOP);
												
	swprintf_s(tempchar, L"%d", m_GameScore);	
	m_Font->draw_font(tempchar, { TempX - 50.0f +Board, 30.0f - Board}, 50.0f, KColor::Black.color_to_reverse255(), FW1_TEXT_FLAG::FW1_RIGHT);
												
	swprintf_s(tempchar, L"Score:");			
	m_Font->draw_font(tempchar, { TempX - 400.0f -Board, 30.0f + Board}, 50.0f, KColor::Black.color_to_reverse255(), FW1_TEXT_FLAG::FW1_TOP);
												
	swprintf_s(tempchar, L"%d", m_GameScore);	
	m_Font->draw_font(tempchar, { TempX - 50.0f -Board, 30.0f + Board}, 50.0f, KColor::Black.color_to_reverse255(), FW1_TEXT_FLAG::FW1_RIGHT);



	swprintf_s(tempchar, L"Score:");
	m_Font->draw_font(tempchar, { TempX - 400.0f, 30.0f }, 50.0f, KColor::White.color_to_reverse255(), FW1_TEXT_FLAG::FW1_TOP);

	swprintf_s(tempchar, L"%d", m_GameScore);
	m_Font->draw_font(tempchar, { TempX - 50.0f, 30.0f }, 50.0f, KColor::White.color_to_reverse255(), FW1_TEXT_FLAG::FW1_RIGHT);




	/************* High ************/
	swprintf_s(tempchar, L"HighScore:");
	m_Font->draw_font(tempchar, { TempX - 400.0f + Board, 80.0f + Board }, 50.0f, KColor::Black.color_to_reverse255(), FW1_TEXT_FLAG::FW1_TOP);

	swprintf_s(tempchar, L"%d", m_RecordScore);
	m_Font->draw_font(tempchar, { TempX - 50.0f + Board, 80.0f + Board }, 50.0f, KColor::Black.color_to_reverse255(), FW1_TEXT_FLAG::FW1_RIGHT);

	swprintf_s(tempchar, L"HighScore:");
	m_Font->draw_font(tempchar, { TempX - 400.0f - Board, 80.0f - Board }, 50.0f, KColor::Black.color_to_reverse255(), FW1_TEXT_FLAG::FW1_TOP);

	swprintf_s(tempchar, L"%d", m_RecordScore);
	m_Font->draw_font(tempchar, { TempX - 50.0f - Board, 80.0f - Board }, 50.0f, KColor::Black.color_to_reverse255(), FW1_TEXT_FLAG::FW1_RIGHT);

	swprintf_s(tempchar, L"HighScore:");
	m_Font->draw_font(tempchar, { TempX - 400.0f + Board, 80.0f - Board }, 50.0f, KColor::Black.color_to_reverse255(), FW1_TEXT_FLAG::FW1_TOP);

	swprintf_s(tempchar, L"%d", m_RecordScore);
	m_Font->draw_font(tempchar, { TempX - 50.0f + Board, 80.0f - Board }, 50.0f, KColor::Black.color_to_reverse255(), FW1_TEXT_FLAG::FW1_RIGHT);

	swprintf_s(tempchar, L"HighScore:");
	m_Font->draw_font(tempchar, { TempX - 400.0f - Board, 80.0f + Board }, 50.0f, KColor::Black.color_to_reverse255(), FW1_TEXT_FLAG::FW1_TOP);

	swprintf_s(tempchar, L"%d", m_RecordScore);
	m_Font->draw_font(tempchar, { TempX - 50.0f - Board, 80.0f + Board }, 50.0f, KColor::Black.color_to_reverse255(), FW1_TEXT_FLAG::FW1_RIGHT);



	swprintf_s(tempchar, L"HighScore:");
	m_Font->draw_font(tempchar, { TempX - 400.0f, 80.0f }, 50.0f, KColor::White.color_to_reverse255(), FW1_TEXT_FLAG::FW1_TOP);

	swprintf_s(tempchar, L"%d", m_RecordScore);
	m_Font->draw_font(tempchar, { TempX - 50.0f, 80.0f }, 50.0f, KColor::White.color_to_reverse255(), FW1_TEXT_FLAG::FW1_RIGHT);
}

void Bird_Launcher::Update_LP()
{
	if (true == m_Trans->BWorld())
	{
		KVector2 Temp = one()->Local_Pos().m_Pos;
		Temp.y += 20.0;
		m_Launch_Point = Temp;
	}
}

void Bird_Launcher::Update_List()
{
	if (true == one()->transform()->BWorld())
	{
		m_SBList = m_BirdList.begin();
		m_EBList = m_BirdList.end();

		for (; m_SBList != m_EBList;)
		{
			if (true == (*m_SBList)->is_Death())
			{
				m_SBList = m_BirdList.erase(m_SBList);
			}
			else
			{
				++m_SBList;
			}
		}


		m_SBList = m_BirdList.begin();
		m_EBList = m_BirdList.end();

		size_t Inx = 0;
		for (; m_SBList != m_EBList; ++m_SBList)
		{
			(*m_SBList)->StandBy_IDX(Inx);
			++Inx;
		}
	}
}

void Bird_Launcher::Set_Transform(const KVector& _Pos)
{
	one()->Local_Pos(_Pos);
}



KPtr<Bird> Bird_Launcher::FindBird(KPtr<Bird> _Bird)
{
	m_SBList = m_BirdList.begin();
	m_EBList = m_BirdList.end();

	for (; m_SBList != m_EBList; ++m_SBList)
	{
		if ((*m_SBList) == _Bird)
		{
			return (*m_SBList);
		}
	}

	return nullptr;
}

KPtr<Bird> Bird_Launcher::CreateBird(const Bird::BIRD_TYPE& _Type)
{
	KPtr<TheOne> NewOne = state()->Create_TheOne();
	KPtr<Bird> NewBird = NewOne->Add_Component<Bird>(_Type, this, m_BirdList.size());
	m_BirdList.push_back(NewBird);

	return nullptr;
}

void Bird_Launcher::DeleteBird(KPtr<Bird> _Bird)
{
	m_SBList = m_BirdList.begin();
	m_EBList = m_BirdList.end();

	for (; m_SBList != m_EBList; )
	{
		if ((*m_SBList) == _Bird)
		{
			m_SBList = m_BirdList.erase(m_SBList);
			break;
		}
		else
		{
			++m_SBList;
		}
	}

	return;
}

void Bird_Launcher::MinusIdxBird()
{
	m_SBList = m_BirdList.begin();
	m_EBList = m_BirdList.end();

	for (; m_SBList != m_EBList; ++m_SBList)
	{
		(*m_SBList)->MinusStandBy_IDX();
	}
}