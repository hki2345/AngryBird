// Dlg_Launcher.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Editor.h"
#include "Dlg_Launcher.h"
#include "afxdialogex.h"

#include <Bird_Launcher.h>
#include <Bird.h>

#include "Edit_Class.h"


// Dlg_Launcher 대화 상자입니다.

IMPLEMENT_DYNAMIC(Dlg_Launcher, Dlg_Component)

Dlg_Launcher::Dlg_Launcher(CWnd* pParent /*=NULL*/)
	: Dlg_Component(IDD_LAUNCHER, pParent)
{
	Y_SIZE = 400;
}

Dlg_Launcher::~Dlg_Launcher()
{
}

void Dlg_Launcher::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	int StartId = IDC_BOMBRADIO;

	for (size_t i = 0; i < 9; i++)
	{
		DDX_Control(pDX, StartId, m_RadioBtn[i]);
		++StartId;
	}


	StartId = IDC_PANDES;

	for (size_t i = 0; i < 3; i++)
	{
		DDX_Control(pDX, StartId, m_ScoreValue[i]);
		DDX_Text(pDX, StartId, m_ScoreInt[i]);
		++StartId;
	}
}


BEGIN_MESSAGE_MAP(Dlg_Launcher, CDialogEx)
	ON_BN_CLICKED(IDD_DELETEALL, &Dlg_Launcher::OnBnClickedDeleteall)
	ON_BN_CLICKED(IDD_CREATE, &Dlg_Launcher::OnBnClickedCreate)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BOMBRADIO, IDC_TERENCERADIO, &Dlg_Launcher::OnEnChangedBirdValue)
	ON_CONTROL_RANGE(EN_CHANGE, IDC_PANDES, IDC_PANREDI, &Dlg_Launcher::OnEnChangedScoreValue)
END_MESSAGE_MAP()


// Dlg_Launcher 메시지 처리기입니다.


void Dlg_Launcher::OnBnClickedDeleteall()
{
	static std::unordered_map<int, std::list<KPtr<TheOne>>> m_MapList;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_MapList = *(Core_Class::main_state()->All_One());

	std::unordered_map<int, std::list<KPtr<TheOne>>>::iterator S_MAP = m_MapList.begin();
	std::unordered_map<int, std::list<KPtr<TheOne>>>::iterator E_MAP = m_MapList.end();
	for (; S_MAP != E_MAP; ++S_MAP)
	{
		std::list<KPtr<TheOne>>::iterator S_One = S_MAP->second.begin();
		std::list<KPtr<TheOne>>::iterator E_One = S_MAP->second.end();

		for (; S_One != E_One; )
		{
			std::wstring OneName = (*S_One)->name();

			if (L"Bird" == OneName)
			{
				(*S_One)->set_Death();
				S_One = S_MAP->second.erase(S_One);
				continue;
			}
			++S_One;
		}
	}
	Edit_Class::TheOneTab->Reset_OneTree();
}


void Dlg_Launcher::OnBnClickedCreate()
{
	if (nullptr == m_Launcher)
	{
		// 경고창
		AfxMessageBox(L"선택된 발사대가 없습니다.");
	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int BirdCnt = 0;

	for (size_t i = 0; i < 9; i++)
	{
		if (TRUE == m_RadioBtn[i].GetCheck())
		{
			BirdCnt = i;
		}
	}

	m_Launcher->CreateBird((Bird::BIRD_TYPE)BirdCnt);

	Edit_Class::TheOneTab->Reset_OneTree();
}


void Dlg_Launcher::OnEnChangedBirdValue(UINT _id)
{
	int ind = _id - IDC_BOMBRADIO;



	for (size_t i = 0; i < 9; i++)
	{
		m_RadioBtn[i].SetCheck(FALSE);
	}

	m_RadioBtn[ind].SetCheck(TRUE);
}


void Dlg_Launcher::OnEnChangedScoreValue(UINT _id)
{
	int ind = _id - IDC_PANDES;

	bool check = false;

	// 짱나게 0 일때 데이터 최신화를 하면 커서가 앞으로 이동함 ㅋㅋㅋㅋ
	if (.0f == m_ScoreInt[ind] && ind >= 0)
	{
		check = true;
	}

	UpdateData(TRUE);
	UpdateData(FALSE);

	if (true == check && ind >= 0)
	{
		m_ScoreValue[ind].SetSel(1, 1);
	}



	if (nullptr == m_Launcher)
	{
		return;
	}


	// 메스 업데이트
	int* ScoreData = m_ScoreInt;

	m_Launcher->HighScore(ScoreData);
	Edit_Class::TheOneTab->Reset_OneTree();
}

void Dlg_Launcher::set_component(Component* _Com)
{
	if (_Com->typeinfo() != &typeid(Bird_Launcher))
	{
		return;
	}

	m_Launcher = (Bird_Launcher*)_Com;

	UpdateData(TRUE);
	m_RadioBtn[0].SetCheck(TRUE);


	int* TempInt = m_Launcher->HighScore();

	for (size_t i = 0; i < 3; i++)
	{
		m_ScoreInt[i] = TempInt[i];
	}

	UpdateData(FALSE);
}
