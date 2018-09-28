// Dlg_Pig.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Editor.h"
#include "Dlg_Pig.h"
#include "afxdialogex.h"


// Dlg_Pig 대화 상자입니다.

IMPLEMENT_DYNAMIC(Dlg_Pig, Dlg_Component)

Dlg_Pig::Dlg_Pig(CWnd* pParent /*=NULL*/)
	: Dlg_Component(IDD_PIG, pParent)
{
	Y_SIZE = 400;
}

Dlg_Pig::~Dlg_Pig()
{
}

void Dlg_Pig::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);


	int StartId = IDC_SMALLRADIO;

	for (size_t i = 0; i < 4; i++)
	{
		DDX_Control(pDX, StartId, m_PigBtn[i]);
		++StartId;
	}
}


BEGIN_MESSAGE_MAP(Dlg_Pig, CDialogEx)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_SMALLRADIO, IDC_GIANTRADIO, &Dlg_Pig::Update_Pig)
END_MESSAGE_MAP()


// Dlg_Pig 메시지 처리기입니다.


void Dlg_Pig::Update_Pig(UINT _Id)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.int ind = _id - IDC_PANMASS;
	// 원은 크기가 두개밖에 안된다.
	// 별도로 아예 막기

	int StartId = IDC_SMALLRADIO;
	StartId = _Id - StartId;

	if (nullptr != m_Pig)
	{
		switch (StartId)
		{
		case 0:
			m_Pig->Init(Pig::PIG_SIZ_TYPE::PIG_SMALL);
			break;

		case 1:
			m_Pig->Init(Pig::PIG_SIZ_TYPE::PIG_MIDDLE);
			break;

		case 2:
			m_Pig->Init(Pig::PIG_SIZ_TYPE::PIG_BIG);
			break;

		case 3:
			m_Pig->Init(Pig::PIG_SIZ_TYPE::PIG_GIANT);
			break;
		default:
			break;
		}
	}
}

void Dlg_Pig::set_component(Component* _Com)
{
	if (_Com->typeinfo() != &typeid(Pig))
	{
		return;
	}

	m_Pig = (Pig*)_Com;

	UpdateData(TRUE);

	if (nullptr != m_Pig)
	{
		m_PigBtn[(int)m_Pig->Size_Type()].SetCheck(TRUE);
	}

	UpdateData(FALSE);
}