// Dlg_Bird.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Editor.h"
#include "Dlg_Bird.h"
#include "afxdialogex.h"
#include "Edit_Class.h"

#include <KRigid_2D.h>

// Dlg_Bird ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(Dlg_Bird, Dlg_Component)

Dlg_Bird::Dlg_Bird(CWnd* pParent /*=NULL*/)
	: Dlg_Component(IDD_BIRD, pParent)
{
	Y_SIZE = 400;
}

Dlg_Bird::~Dlg_Bird()
{
}

void Dlg_Bird::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	int StartId = IDC_BOMBRADIO;

	for (size_t i = 0; i < 9; i++)
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


BEGIN_MESSAGE_MAP(Dlg_Bird, CDialogEx)
	ON_BN_CLICKED(IDC_BIRDLOAD, &Dlg_Bird::OnBnClickedBirdload)
	ON_BN_CLICKED(IDC_BIRDSAVE, &Dlg_Bird::OnBnClickedBirdsave)
	ON_CONTROL_RANGE(EN_CHANGE, IDC_PANMASS, IDC_PANREDI, &Dlg_Bird::OnEnChangedPanValue)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BOMBRADIO, IDC_TERENCERADIO, &Dlg_Bird::OnEnChangedBirdValue)
END_MESSAGE_MAP()


// Dlg_Bird �޽��� ó�����Դϴ�.


// Dlg_Panza �޽��� ó�����Դϴ�.
void Dlg_Bird::OnEnChangedPanValue(UINT _id)
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

	Update_Bird();
}


void Dlg_Bird::OnEnChangedBirdValue(UINT _id)
{
	int ind = _id - IDC_BOMBRADIO;



	for (size_t i = 0; i < 9; i++)
	{
		m_RadioBtn[i].SetCheck(FALSE);
	}

	m_RadioBtn[ind].SetCheck(TRUE);

	Update_Bird();
	Edit_Class::TheOneTab->Reset_OneTree();
}


void Dlg_Bird::set_component(Component* _Com)
{
	if (_Com->typeinfo() != &typeid(Bird))
	{
		return;
	}

	m_Bird = (Bird*)_Com;

	UpdateData(TRUE);

	int StartId = (int)m_Bird->Bird_Type();
	m_RadioBtn[StartId].SetCheck(TRUE);

	KVector Temp;

	Temp = m_Bird->Get_Component<KRigid_2D>()->MassData();
	m_PanFloat[0] = Temp.x;
	m_PanFloat[1] = Temp.y;
	m_PanFloat[2] = Temp.z;
	m_PanFloat[3] = Temp.w;

	Temp = m_Bird->Get_Component<KRigid_2D>()->FigureData();
	m_PanFloat[4] = Temp.x;
	m_PanFloat[5] = Temp.y;
	m_PanFloat[6] = Temp.z;

	UpdateData(FALSE);
}

void Dlg_Bird::Update_Bird()
{
	if (nullptr == m_Bird)
	{
		return;
	}

	float* PanData = m_PanFloat;

	// �޽� ������Ʈ
	KVector Temp;
	memcpy(&Temp, PanData, sizeof(KVector));
	m_Bird->Get_Component<KRigid_2D>()->MassData(Temp);


	// �ǱԾ� ������Ʈ
	PanData += 4;
	memcpy(&Temp, PanData, sizeof(KVector3));
	m_Bird->Get_Component<KRigid_2D>()->FigureData(Temp.m_Vector3);



	int BirdCnt = 0;

	for (size_t i = 0; i < 9; i++)
	{
		if (TRUE == m_RadioBtn[i].GetCheck())
		{
			BirdCnt = i;
		}
	}

	m_Bird->Init((Bird::BIRD_TYPE)BirdCnt);
}


void Dlg_Bird::OnBnClickedBirdsave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_Bird->save();
}


void Dlg_Bird::OnBnClickedBirdload()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_Bird->load();
	set_component(m_Bird);
}
