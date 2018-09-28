// Dlg_TheOneTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Editor.h"
#include "Dlg_TheOneTab.h"
#include "afxdialogex.h"

#include <TransPosition.h>
#include <Renderer_Sprite.h>
#include "Edit_Class.h" 

#include <Collider2D_DE.h>
#include "View_Component.h"

#include <Renderer_Sprite.h>

//#include <>
#include <Panza.h>
#include <Bottom.h>
#include <Bird.h>
#include <Bomb.h>
#include <Bird_Launcher.h>
#include <KRigid_2D.h>

// Dlg_TheOneTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(Dlg_TheOneTab, CDialogEx)

Dlg_TheOneTab::Dlg_TheOneTab(CWnd* pParent /*=NULL*/)
	: TabState(IDD_THEONE, pParent)
{
	Edit_Class::TheOneTab = this;
}

Dlg_TheOneTab::~Dlg_TheOneTab()
{
}

void Dlg_TheOneTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ONETREE, m_TheOneTree);


	m_Droper.m_Parent = this;
	DDX_Control(pDX, IDC_SMALLPAN, m_Droper);

	DDX_Text(pDX, IDC_GRAVITYX, m_GravityX);
	DDX_Text(pDX, IDC_GRAVITYY, m_GravityY);

}


BEGIN_MESSAGE_MAP(Dlg_TheOneTab, CDialogEx)
	ON_NOTIFY(TVN_SELCHANGED, IDC_ONETREE, &Dlg_TheOneTab::OnTvnSelchangedOnetree)
	ON_NOTIFY(TVN_BEGINDRAG, IDC_ONETREE, &Dlg_TheOneTab::OnTvnBegindragOnetree)
	ON_NOTIFY(TVN_KEYDOWN, IDC_ONETREE, &Dlg_TheOneTab::OnTvnKeydownOnetree)
	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_ONETREE, &Dlg_TheOneTab::OnTvnEndlabeleditOnetree)
	ON_NOTIFY(NM_CLICK, IDC_ONETREE, &Dlg_TheOneTab::OnNMClickOnetree)
	ON_NOTIFY(NM_RCLICK, IDC_ONETREE, &Dlg_TheOneTab::OnNMRClickOnetree)

	ON_BN_CLICKED(IDC_SMALLPAN, &Dlg_TheOneTab::OnBnClickedSmallpan)
	ON_BN_CLICKED(IDC_BOTTOMCREATOR, &Dlg_TheOneTab::OnBnClickedBottomcreator)

	ON_CONTROL_RANGE(EN_CHANGE, IDC_GRAVITYX, IDC_GRAVITYY, &Dlg_TheOneTab::OnEnChangedGravity)
	ON_BN_CLICKED(IDC_LAUNCHERCREATOR, &Dlg_TheOneTab::OnBnClickedLaunchercreator)
	ON_BN_CLICKED(IDC_MIDDLEPAN, &Dlg_TheOneTab::OnBnClickedMiddlepan)
	ON_BN_CLICKED(IDC_BIGPAN, &Dlg_TheOneTab::OnBnClickedBigpan)
	ON_BN_CLICKED(IDC_GIANTPAN, &Dlg_TheOneTab::OnBnClickedGiantpan)
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(IDC_DELETEALL, &Dlg_TheOneTab::OnBnClickedDeleteall)
	ON_BN_CLICKED(IDC_BOMBCREATOR, &Dlg_TheOneTab::OnBnClickedBombcreator)
	ON_BN_CLICKED(IDC_PIGCREATOR, &Dlg_TheOneTab::OnBnClickedPigcreator)
	ON_BN_CLICKED(IDC_GRASSCREATOR, &Dlg_TheOneTab::OnBnClickedGrasscreator)
END_MESSAGE_MAP()



// Dlg_TheOneTab 메시지 처리기입니다.


void Dlg_TheOneTab::OnShowWindow(BOOL bShow, UINT nStatus)
{
	TabState::OnShowWindow(bShow, nStatus);

	if (bShow == SW_HIDE)
	{
		return;
	}



	KPtr<State> m_State = Core_Class::Main_StateManager().find_state(Edit_Class::StateTab->m_CurState_Name);
	if (nullptr == m_State)
	{
		return;
	}

	m_GravityX = m_State->gravity().x;
	m_GravityY = m_State->gravity().y;

	
	Reset_OneTree();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void Dlg_TheOneTab::OnTvnSelchangedOnetree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	RECT rc;
	m_TheOneTree.GetItemRect(pNMTreeView->itemNew.hItem, &rc, TRUE);

	POINT Pos;
	GetCursorPos(&Pos);
	m_TheOneTree.ScreenToClient(&Pos);

	// 간이적으로 충돌 체크를 한다. -> AABB
	if (Pos.x < rc.left || Pos.x > rc.right || Pos.y < rc.top || Pos.y > rc.bottom)
	{
		m_SelectObject = nullptr;
		m_TheOneTree.Select(nullptr, TVGN_CARET);
		return;
	}

	m_SelectObject = pNMTreeView->itemNew.hItem;

	TheOne* pOne = (TheOne*)m_TheOneTree.GetItemData(m_SelectObject);

	if (nullptr != pOne)
	{
		Edit_Class::m_View_Component->Dlg_Release();
		Edit_Class::m_View_Component->set_one(pOne);
	}
}


void Dlg_TheOneTab::OnTvnBegindragOnetree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void Dlg_TheOneTab::OnTvnKeydownOnetree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVKEYDOWN pTVKeyDown = reinterpret_cast<LPNMTVKEYDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	if (VK_DELETE == pTVKeyDown->wVKey && nullptr != m_SelectObject)
	{
		TheOne* NewOne = (TheOne*)m_TheOneTree.GetItemData(m_SelectObject);

		if (nullptr != NewOne)
		{
			Edit_Class::m_View_Component->Dlg_Release();

			NewOne->set_Death();
			
			/* 이거 메니저에서 잘 지워는지 체크함 -> 충돌 링크 제거
			KPtr<Collider2D_DE> Ptr = NewOne->Get_Component<Collider2D_DE>();

			if (nullptr != Ptr)
			{
				Ptr->set_Death();
			}*/
		}

		m_TheOneTree.DeleteItem(m_SelectObject);
		m_TheOneTree.SelectItem(nullptr);
	}
}


void Dlg_TheOneTab::OnTvnEndlabeleditOnetree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	TheOne* NewOne = (TheOne*)m_TheOneTree.GetItemData(m_SelectObject);

	if (nullptr != NewOne && nullptr != pTVDispInfo->item.pszText)
	{
		NewOne->name(pTVDispInfo->item.pszText);
		m_TheOneTree.SetItemText(m_SelectObject, pTVDispInfo->item.pszText);
	}
}

void Dlg_TheOneTab::Reset_OneTree()
{
	Core_Class::Main_StateManager().change_state(Edit_Class::StateTab->m_CurState_Name);

	m_TheOneTree.DeleteAllItems();

	std::unordered_map<int, std::list<KPtr<TheOne>>> AllActor = *Core_Class::next_state()->All_One();

	std::unordered_map<int, std::list<KPtr<TheOne>>>::iterator m_StartMapIter = AllActor.begin();
	std::unordered_map<int, std::list<KPtr<TheOne>>>::iterator m_EndMapIter = AllActor.end();
	

	for (; m_StartMapIter != m_EndMapIter; ++m_StartMapIter)
	{
		std::list<KPtr<TheOne>>::iterator m_StartListIter = m_StartMapIter->second.begin();
		std::list<KPtr<TheOne>>::iterator m_EndListIter = m_StartMapIter->second.end();


		for (; m_StartListIter != m_EndListIter; ++m_StartListIter)
		{
			std::wstring OneName = (*m_StartListIter)->name();

			if (true == (*m_StartListIter)->is_Death())
			{
				continue;
			}

			if (L"Panza" == OneName || L"Bottom" == OneName)
			{
				HTREEITEM item;
				item = m_TheOneTree.InsertItem((*m_StartListIter)->Get_Component<Renderer_Sprite>()->name());
				m_TheOneTree.SetItemData(item, (DWORD_PTR)((TheOne*)(*m_StartListIter)));

				if (nullptr != (*m_StartListIter)->Get_Component<Bird_Launcher>())
				{
					m_Launcher = item;
				}
			}
			else  if (L"Launcher" == OneName)
			{
				HTREEITEM item;
				item = m_TheOneTree.InsertItem((*m_StartListIter)->name());
				m_TheOneTree.SetItemData(item, (DWORD_PTR)((TheOne*)(*m_StartListIter)));

				if (nullptr != (*m_StartListIter)->Get_Component<Bird_Launcher>())
				{
					m_Launcher = item;
				}
			}

			else if (L"Bird" == OneName)
			{
				HTREEITEM item = m_TheOneTree.InsertItem((*m_StartListIter)->Get_Component<Bird>()->name(), m_Launcher);
				m_TheOneTree.SetItemData(item, (DWORD_PTR)((TheOne*)(*m_StartListIter)));
				m_TheOneTree.Expand(m_Launcher, TVE_EXPAND);
			}
			else if (L"Bomb" == OneName)
			{
				HTREEITEM item = m_TheOneTree.InsertItem((*m_StartListIter)->name());
				m_TheOneTree.SetItemData(item, (DWORD_PTR)((TheOne*)(*m_StartListIter)));
			}
			else if (L"Pig" == OneName)
			{
				HTREEITEM item = m_TheOneTree.InsertItem((*m_StartListIter)->name());
				m_TheOneTree.SetItemData(item, (DWORD_PTR)((TheOne*)(*m_StartListIter)));
			}
			else if (L"Grass" == OneName)
			{
				HTREEITEM item = m_TheOneTree.InsertItem((*m_StartListIter)->name());
				m_TheOneTree.SetItemData(item, (DWORD_PTR)((TheOne*)(*m_StartListIter)));
			}
			// (*m_StartListIter)
		}
	}
}

void Dlg_TheOneTab::OnNMClickOnetree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	if (nullptr == m_SelectObject)
	{
		return;
	}


	RECT rc;
	m_TheOneTree.GetItemRect(m_SelectObject, &rc, TRUE);

	POINT Pos;
	GetCursorPos(&Pos);
	m_TheOneTree.ScreenToClient(&Pos);

	// 충돌 바깥이면 해당 뷰를 없앤다.
	if (Pos.x < rc.left || Pos.x > rc.right || Pos.y < rc.top || Pos.y > rc.bottom)
	{
		Edit_Class::m_View_Component->Dlg_Release();
		m_TheOneTree.Select(nullptr, TVGN_CARET);
		return;
	}
}


void Dlg_TheOneTab::OnNMRClickOnetree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	if (nullptr == m_SelectObject)
	{
		return;
	}


	RECT rc;
	m_TheOneTree.GetItemRect(m_SelectObject, &rc, TRUE);

	POINT Pos;
	GetCursorPos(&Pos);
	m_TheOneTree.ScreenToClient(&Pos);

	if (Pos.x < rc.left || Pos.x > rc.right || Pos.y < rc.top || Pos.y > rc.bottom)
	{
		m_SelectObject = nullptr;
		Edit_Class::m_View_Component->Dlg_Release();

		m_TheOneTree.Select(nullptr, TVGN_CARET);
		return;
	}
}


BOOL Dlg_TheOneTab::OnInitDialog()
{
	TabState::OnInitDialog();


	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	CCreateContext         m_context;

	m_context.m_pNewViewClass = RUNTIME_CLASS(View_Component);

	View_Component* pView = (View_Component*)((CFrameWnd*)this)->CreateView(&m_context);

	RECT ViewSize = { 200, 10, 700, 530 };
	pView->ShowWindow(SW_SHOW);
	pView->MoveWindow(&ViewSize);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}





void Dlg_TheOneTab::OnEnChangedGravity(UINT _id)
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// TabState::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);
	UpdateData(FALSE);

	KPtr<State> m_State = Core_Class::Main_StateManager().find_state(Edit_Class::StateTab->m_CurState_Name);
	if (nullptr == m_State)
	{
		return;
	}

	m_State->gravity(KVector2(m_GravityX, m_GravityY));
}

void Dlg_TheOneTab::OnBnClickedDeleteall()
{
	Map_Data::Map_Erase(Core_Class::main_state());

	Reset_OneTree();
}
