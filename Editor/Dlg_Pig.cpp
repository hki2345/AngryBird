// Dlg_Pig.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Editor.h"
#include "Dlg_Pig.h"
#include "afxdialogex.h"


// Dlg_Pig ��ȭ �����Դϴ�.

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


// Dlg_Pig �޽��� ó�����Դϴ�.


void Dlg_Pig::Update_Pig(UINT _Id)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.int ind = _id - IDC_PANMASS;
	// ���� ũ�Ⱑ �ΰ��ۿ� �ȵȴ�.
	// ������ �ƿ� ����

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