// Dlg_SceneTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Editor.h"
#include "Dlg_StateTab.h"
#include "afxdialogex.h"
#include "EditUpdater.h"

#include <ResourceManager.h>

#include <Core_Class.h>
#include <Container_Class.h>
#include "Edit_Class.h"


#include <Renderer_Sprite.h>
#include <Collider2D_DE.h>
#include <KRigid_2D.h>

#include <GameData.h>

// Dlg_SceneTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(Dlg_StateTab, TabState)

Dlg_StateTab::Dlg_StateTab(CWnd* pParent /*=NULL*/)
	: TabState(IDD_STATE, pParent),
	m_CurState_Name(_T("Test")),
	m_State_Name(_T("Test"))
{
	Edit_Class::StateTab = this;
}

Dlg_StateTab::~Dlg_StateTab()
{
}

void Dlg_StateTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CURSCENENAME, m_CurState_Name);
	DDX_Text(pDX, IDC_SCENE_NAME, m_State_Name);
	DDX_Control(pDX, IDC_SCENELIST, m_State_List);
}


BEGIN_MESSAGE_MAP(Dlg_StateTab, CDialogEx)
	ON_BN_CLICKED(IDOK, &Dlg_StateTab::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Dlg_StateTab::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_SCENECREATOR, &Dlg_StateTab::OnBnClickedScenecreator)
	ON_LBN_SELCHANGE(IDC_SCENELIST, &Dlg_StateTab::OnLbnSelchangeScenelist)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_STATESAVEBTN, &Dlg_StateTab::OnBnClickedStatesavebtn)
	ON_BN_CLICKED(IDC_STATELOADBTN, &Dlg_StateTab::OnBnClickedStateloadbtn)
END_MESSAGE_MAP()


// Dlg_SceneTab 메시지 처리기입니다.

void Dlg_StateTab::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnOK();
}


void Dlg_StateTab::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnCancel();
}




void Dlg_StateTab::OnBnClickedScenecreator()
{
	UpdateData(TRUE);

	// 예외 처리
	if (m_State_Name == L"")
	{
		// 경고창
		AfxMessageBox(L"이름을 적으삼");
		return;
	}

	CString TempString = m_State_Name;
	TempString.Trim();

	if (TempString == L"")
	{
		// 경고창
		AfxMessageBox(L"띄어쓰기만 있는 건 이름이 아님");
		return;
	}

	KPtr<State> NewState = Core_Class::Main_StateManager().find_state(m_State_Name.GetString());

	if (nullptr != NewState)
	{
		AfxMessageBox(L"이미 있는 스테이트임");
		return;
	}

	m_State_List.AddString(m_State_Name);

	NewState = Core_Class::Main_StateManager().create_state(m_State_Name.GetString());
	NewState->Create_Updater<EditUpdater>();
	NewState->this_KRigid2DManager.gravity({ .0f, -200.0f });
	Core_Class::Main_StateManager().change_state(m_State_Name.GetString());

	KPtr<TheOne> NewCamera = NewState->Create_TheOne();
	KPtr<Camera> CameraCom = NewCamera->Add_Component<Camera>();
	NewCamera->Local_Pos(KVector(.0f, .0f, -10.0f));
	NewCamera->name(L"Camera");
	CameraCom->Insert_LayerData(0, 2, 3, 4);

	KPtr<TheOne> BotRigid = NewState->Create_TheOne(L"StateBottom");
	BotRigid->Local_Scale(10000.0f, 98.0f, 1.0f);
	BotRigid->Local_Pos(4000.0f, -309.0f, 10.0f);

	KPtr<Collider2D_DE> Colider = BotRigid->Add_Component<Collider2D_DE>(0);
	Colider->type(COLL_TYPE::COL_RECT2D);
	Colider->color(KColor::White);

	KPtr<KRigid_2D> Rigid = BotRigid->Add_Component<KRigid_2D>();
	Rigid->Set_Type(b2BodyType::b2_staticBody);



	KPtr<TheOne> BotRigid2 = NewState->Create_TheOne(L"StateBottom");
	BotRigid2->Local_Scale(10000.0f, 98.0f, 1.0f);
	BotRigid2->Local_Pos(4000.0f, -309.0f, 10.0f);

	KPtr<Collider2D_DE> Colider2 = BotRigid2->Add_Component<Collider2D_DE>(1);
	Colider2->type(COLL_TYPE::COL_RECT2D);
	Colider2->color(KColor::White);

	KPtr<KRigid_2D> Rigid2 = BotRigid2->Add_Component<KRigid_2D>();
	Rigid2->Set_Type(b2BodyType::b2_staticBody);


	NewState->this_Collider2DManager.chain(0);

	UpdateData(FALSE);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Dlg_StateTab::OnLbnSelchangeScenelist()
{
	UpdateData(TRUE);

	m_State_List.GetText(m_State_List.GetCurSel(), m_CurState_Name);
	Edit_Class::Cur_State = Core_Class::Main_StateManager().find_state(m_CurState_Name.GetString());

	if (nullptr == Edit_Class::Cur_State)
	{
		m_CurState_Name = L"없음";
		return;
	}

	Core_Class::Main_StateManager().change_state(m_CurState_Name.GetString());
	Container_Class::Set_BirdLauncher(Edit_Class::Cur_State);

	UpdateData(FALSE);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void Dlg_StateTab::Init()
{
	OnBnClickedScenecreator();
}


void Dlg_StateTab::OnShowWindow(BOOL bShow, UINT nStatus)
{
	TabState::OnShowWindow(bShow, nStatus);

	if (bShow == SW_HIDE)
	{
		return;
	}

	if (nullptr == Core_Class::Main_StateManager().find_state(Edit_Class::StateTab->m_CurState_Name))
	{
		return;
	}

	Core_Class::Main_StateManager().change_state(m_CurState_Name);
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void Dlg_StateTab::OnBnClickedStatesavebtn()
{
	UpdateData(TRUE);
	CString NewPath = PathManager::Find_Path(L"State");

	NewPath += m_CurState_Name + L".SD";

	Map_Data::Map_Save(Core_Class::main_state(), NewPath);

	//Core_Class::main_state()->save(NewPath.GetString());
	//Core_Class::main_state()->load(NewPath.GetString(), nullptr, nullptr);

	UpdateData(FALSE);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Dlg_StateTab::OnBnClickedStateloadbtn()
{
	UpdateData(TRUE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString NewPath = PathManager::Find_Path(L"State");

	CString TempName = m_State_Name;
	NewPath += TempName + L".SD";

	KPtr<State> TempState = Core_Class::Main_StateManager().find_state(m_State_Name);

	if (nullptr == TempState)
	{
		OnBnClickedScenecreator();
		TempState = Core_Class::Main_StateManager().find_state(m_State_Name);
		Core_Class::Main_StateManager().change_state(m_State_Name);
	}

	Map_Data::Map_Load(TempState, NewPath);
	Edit_Class::TheOneTab->Reset_OneTree();
	TempState->camera()->one()->Local_Pos(.0f, .0f, -10.0f);

	UpdateData(FALSE);
	//Core_Class::main_state()->save(NewPath.GetString());
}
