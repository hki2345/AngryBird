// Dlg_Bottom.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Editor.h"
#include "Dlg_Bottom.h"
#include "afxdialogex.h"
#include "Edit_Class.h"
#include <KRigid_2D.h>
#include <InputManager.h>

// Dlg_Bottom 대화 상자입니다.

IMPLEMENT_DYNAMIC(Dlg_Bottom, Dlg_Component)

Dlg_Bottom::Dlg_Bottom(CWnd* pParent /*=NULL*/)
	: Dlg_Component(IDD_BOTTOM, pParent)
{
	m_VerIdx = 0;
	Y_SIZE = 250;
	Edit_Class::BottomTab = this;
}

Dlg_Bottom::~Dlg_Bottom()
{
	Edit_Class::BottomTab = nullptr;
}

void Dlg_Bottom::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	int StartId = IDC_ICERADIO;
	StartId = IDC_PANMASS;

	for (size_t i = 0; i < 7; i++)
	{
		DDX_Control(pDX, StartId, m_PanValue[i]);
		DDX_Text(pDX, StartId, m_PanFloat[i]);
		++StartId;
	}

	DDX_Control(pDX, IDC_BOTTOMEDIT, m_Edit);
	DDX_Control(pDX, IDC_LBOTTOM, m_BCheck);
}


BEGIN_MESSAGE_MAP(Dlg_Bottom, CDialogEx)
	ON_CONTROL_RANGE(EN_CHANGE, IDC_PANMASS, IDC_PANREDI, &Dlg_Bottom::OnEnChangedPanValue)
	ON_BN_CLICKED(IDC_BOTTOMEDIT, &Dlg_Bottom::OnBnClickedBottomedit)
END_MESSAGE_MAP()


// Dlg_Bottom 메시지 처리기입니다.


// Dlg_Panza 메시지 처리기입니다.
void Dlg_Bottom::OnEnChangedPanValue(UINT _id)
{
	int ind = _id - IDC_PANMASS;

	bool check = false;

	// 짱나게 0 일때 데이터 최신화를 하면 커서가 앞으로 이동함 ㅋㅋㅋㅋ
	if (.0f == m_PanFloat[ind])
	{
		check = true;
	}

	UpdateData(TRUE);
	UpdateData(FALSE);

	if (true == check)
	{
		m_PanValue[ind].SetSel(1, 1);
	}

	Update_Panza();
}


void Dlg_Bottom::set_component(Component* _Com)
{
	if (_Com->typeinfo() != &typeid(Bottom))
	{
		return;
	}

	m_Bottom = (Bottom*)_Com;

	UpdateData(TRUE);


	KVector Temp;

	Temp = m_Bottom->MassData();
	m_PanFloat[0] = Temp.x;
	m_PanFloat[1] = Temp.y;
	m_PanFloat[2] = Temp.z;
	m_PanFloat[3] = Temp.w;

	Temp = m_Bottom->FigureData();
	m_PanFloat[4] = Temp.x;
	m_PanFloat[5] = Temp.y;
	m_PanFloat[6] = Temp.z;

	UpdateData(FALSE);
}

void Dlg_Bottom::Update_Panza()
{
	if (nullptr == m_Bottom)
	{
		return;
	}


	KVector Temp;
	float* PanData = m_PanFloat;
	memcpy(&Temp, PanData, sizeof(KVector));
	m_Bottom->MassData(Temp);

	PanData += 4;
	memcpy(&Temp, PanData, sizeof(KVector3));
	m_Bottom->FigureData(Temp.m_Vector3);
}

void Dlg_Bottom::OnBnClickedBottomedit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (TRUE == m_Edit.IsWindowEnabled())
	{
		m_Edit.EnableWindow(FALSE);
	}

	m_Bottom->Get_Component<KRigid_2D>()->Active_Vertex(true);

	UpdateData(TRUE);
	UpdateData(FALSE);
}

BOOL Dlg_Bottom::EditOn()
{
	return !(m_Edit.IsWindowEnabled());
}

void Dlg_Bottom::EditOn(const BOOL& _Value)
{
	m_Edit.EnableWindow(!_Value);

	if (TRUE == !_Value)
	{
		m_Bottom->Get_Component<KRigid_2D>()->Active_Vertex(false);
	}

	UpdateData(TRUE);
	UpdateData(FALSE);
}

void Dlg_Bottom::Create_Vertex()
{
	if (8 < m_VerIdx + 1)
	{
		// 경고창
		AfxMessageBox(L"사용할 수 있는 버텍스의\n개수를 넘었습니다.\n\n추가를 취소합니다.");
		return;
	}
	m_Bottom->Get_Component<KRigid_2D>()->Insert_Vertex(Core_Class::main_state()->camera()->screen_to_world(InputManager::mouse_pos()));
	m_VerIdx = m_Bottom->Get_Component<KRigid_2D>()->Vertex_Data()->size();
}