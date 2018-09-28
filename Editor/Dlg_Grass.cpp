// Dlg_Grass.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Editor.h"
#include "Dlg_Grass.h"
#include "afxdialogex.h"

#include <Renderer_Sprite.h>


// Dlg_Grass 대화 상자입니다.

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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.int ind = _id - IDC_PANMASS;
	// 원은 크기가 두개밖에 안된다.
	// 별도로 아예 막기

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