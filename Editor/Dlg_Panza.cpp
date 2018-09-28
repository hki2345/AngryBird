// Dlg_Panza.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Editor.h"
#include "Dlg_Panza.h"
#include "afxdialogex.h"

#include <ResourceManager.h>
#include <KRigid_2D.h>
#include "Edit_Class.h"

// Dlg_Panza ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(Dlg_Panza, Dlg_Component)

Dlg_Panza::Dlg_Panza(CWnd* pParent /*=NULL*/)
	: Dlg_Component(IDD_PANZA, pParent), m_Panza(nullptr)
{
	Y_SIZE = 400;
}

Dlg_Panza::~Dlg_Panza()
{
}

void Dlg_Panza::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);


	int StartId = IDC_ICERADIO;

	for (size_t i = 0; i < 12; i++)
	{
		DDX_Control(pDX, StartId, m_RadioBtn[i]);
		++StartId;
	}

	StartId = IDC_PANMASS;

	for (size_t i = 0; i < 7; i++)
	{
		DDX_Control(pDX, StartId, m_PanValue[i]);
		DDX_Text(pDX, StartId, m_PanFloat[i]);
		++StartId;
	}
}


BEGIN_MESSAGE_MAP(Dlg_Panza, CDialogEx)
	ON_CONTROL_RANGE(EN_CHANGE, IDC_PANMASS, IDC_PANREDI, &Dlg_Panza::OnEnChangedPanValue)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_ICERADIO, IDC_GIANTRADIO, &Dlg_Panza::OnEnChangedPanValue)
	ON_BN_CLICKED(IDC_PANZASAVE, &Dlg_Panza::OnBnClickedPanzasave)
	ON_BN_CLICKED(IDC_PANZALOAD, &Dlg_Panza::OnBnClickedPanzaload)
END_MESSAGE_MAP()


// Dlg_Panza �޽��� ó�����Դϴ�.
void Dlg_Panza::OnEnChangedPanValue(UINT _id)
{
	int ind = _id - IDC_PANMASS;

	bool check = false;

	// ¯���� 0 �϶� ������ �ֽ�ȭ�� �ϸ� Ŀ���� ������ �̵��� ��������
	if (.0f == m_PanFloat[ind] && ind >= 0)
	{
		check = true;
	}

	UpdateData(TRUE);
	UpdateData(FALSE);

	if (true == check && ind >= 0)
	{
		m_PanValue[ind].SetSel(1, 1);
	}


	// ���� ũ�Ⱑ �ΰ��ۿ� �ȵȴ�.
	// ������ �ƿ� ����
	else if (
		TRUE == m_RadioBtn[7].GetCheck())
	{
		m_RadioBtn[9].EnableWindow(FALSE);
		m_RadioBtn[10].EnableWindow(FALSE);

		for (size_t i = 0; i < 2; i++)
		{
			m_RadioBtn[9 + i].SetCheck(FALSE);
		}

		for (size_t i = 0; i < 4; i++)
		{
			if (TRUE == m_RadioBtn[8 + i].GetCheck())
			{
				break;
			}
			else if (3 == i)
			{
				m_RadioBtn[8].SetCheck(TRUE);
			}
		}
	}
	else if (
		TRUE == m_RadioBtn[3].GetCheck() ||
		TRUE == m_RadioBtn[4].GetCheck())
	{
		m_RadioBtn[8].EnableWindow(FALSE);
		m_RadioBtn[9].EnableWindow(FALSE);
		m_RadioBtn[10].EnableWindow(FALSE);

		for (size_t i = 0; i < 3; i++)
		{
			m_RadioBtn[8 + i].SetCheck(FALSE);
		}

		// �ﰢ���� Giant ��
		m_RadioBtn[11].SetCheck(TRUE);
	}

	// �������� ũ�⸦ ������ �� �����Ƿ� �ٽ� �� ǰ
	else if (
		TRUE == m_RadioBtn[5].GetCheck() ||
		TRUE == m_RadioBtn[6].GetCheck())
	{
		for (size_t i = 0; i < 3; i++)
		{
			m_RadioBtn[8 + i].EnableWindow(TRUE);
		}
	}

	Update_Panza();
}


void Dlg_Panza::set_component(Component* _Com)
{
	if (_Com->typeinfo() != &typeid(Panza))
	{
		return;
	}

	m_Panza = (Panza*)_Com;

	UpdateData(TRUE);

	int StartId = (int)m_Panza->Material_Type();
	m_RadioBtn[StartId].SetCheck(TRUE);

	StartId = (int)m_Panza->Shape_Type() + Panza::PAN_MAT_TYPE::PMT_NUMBER;
	m_RadioBtn[StartId].SetCheck(TRUE);

	StartId = (int)m_Panza->Size_Type() + Panza::PAN_MAT_TYPE::PMT_NUMBER + Panza::PAN_SHP_TYPE::PSH_NUMBER;
	m_RadioBtn[StartId].SetCheck(TRUE);


	KVector Temp;

	Temp = m_Panza->MassData();
	m_PanFloat[0] = Temp.x;
	m_PanFloat[1] = Temp.y;
	m_PanFloat[2] = Temp.z;
	m_PanFloat[3] = Temp.w;

	Temp = m_Panza->FigureData();
	m_PanFloat[4] = Temp.x;
	m_PanFloat[5] = Temp.y;
	m_PanFloat[6] = Temp.z;

	UpdateData(FALSE);
}

void Dlg_Panza::Update_Panza() 
{
	if (nullptr == m_Panza)
	{
		return;
	}


	// �޽� ������Ʈ
	KVector Temp;
	float* PanData = m_PanFloat;
	memcpy(&Temp, PanData, sizeof(KVector));
	m_Panza->MassData(Temp);


	// �ǱԾ� ������Ʈ
	PanData += 4;
	memcpy(&Temp, PanData, sizeof(KVector3));
	m_Panza->FigureData(Temp.m_Vector3);



	int MatCnt = 0;
	int ShpCnt = 0;
	int SizCnt = 0;


	for (size_t i = 0; i < 3; i++)
	{
		if (TRUE == m_RadioBtn[i].GetCheck())
		{
			MatCnt = i;
		}
	}
	
	for (size_t i = 0; i < 5; i++)
	{
		if (TRUE == m_RadioBtn[i + 3].GetCheck())
		{
			ShpCnt = i;
		}
	}
	
	for (size_t i = 0 ; i <  4; i++)
	{
		if (TRUE == m_RadioBtn[i + 8].GetCheck())
		{
			SizCnt = i;
		}
	}

	m_Panza->Init((Panza::PAN_MAT_TYPE)MatCnt, (Panza::PAN_SHP_TYPE)ShpCnt, (Panza::PAN_SIZ_TYPE)SizCnt, false);

	Edit_Class::TheOneTab->Reset_OneTree();
}

void Dlg_Panza::OnBnClickedPanzasave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_Panza->save();
}


void Dlg_Panza::OnBnClickedPanzaload()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_Panza->load();
	set_component(m_Panza);
}
