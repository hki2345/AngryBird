// Dlg_Grass.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Editor.h"
#include "Dlg_Grass.h"
#include "afxdialogex.h"

#include <Renderer_Sprite.h>


// Dlg_Grass ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(Dlg_Grass, Dlg_Component)

Dlg_Grass::Dlg_Grass(CWnd* pParent /*=NULL*/)
	: Dlg_Component(IDD_GRASS, pParent)
{
	Y_SIZE = 400;
}

Dlg_Grass::~Dlg_Grass()
{
}

void Dlg_Grass::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	int StartId = IDC_ANGRECT;

	for (size_t i = 0; i < 6; i++)
	{
		DDX_Control(pDX, StartId, m_GrassBtn[i]);
		++StartId;
	}
}


BEGIN_MESSAGE_MAP(Dlg_Grass, CDialogEx)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_ANGRECT, IDC_GIANTRADIO, &Dlg_Grass::OnCbnSelchangeImagecom)
END_MESSAGE_MAP()



void Dlg_Grass::OnCbnSelchangeImagecom(UINT _Id)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.int ind = _id - IDC_PANMASS;
	// ���� ũ�Ⱑ �ΰ��ۿ� �ȵȴ�.
	// ������ �ƿ� ����

	int StartId = IDC_ANGRECT; 
	StartId = _Id - StartId;
	
	if (nullptr != m_Grass)
	{
		m_Grass->Get_Component<Renderer_Sprite>()->index(StartId);
	}
}

void Dlg_Grass::set_component(Component* _Com)
{
	if (_Com->typeinfo() != &typeid(Grass))
	{
		return;
	}

	m_Grass = (Grass*)_Com;

	UpdateData(TRUE);

	if (nullptr != m_Grass)
	{
		m_GrassBtn[(int)m_Grass->Get_Component<Renderer_Sprite>()->index()].SetCheck(TRUE);
	}

	UpdateData(FALSE);
}