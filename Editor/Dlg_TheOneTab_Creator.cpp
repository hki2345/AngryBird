#include "stdafx.h"
#include "Editor.h"
#include "Dlg_TheOneTab.h"
#include "afxdialogex.h"

#include "Edit_Class.h" 
#include "View_Component.h"


//#include <>
#include <TransPosition.h>
#include <Renderer_Sprite.h>
#include <Collider2D_DE.h>


#include <Panza.h>
#include <Bottom.h>
#include <Bird_Launcher.h>
#include <Bird.h>
#include <Pig.h>
#include <Grass.h>
#include <Bomb.h>

#include <Container_Class.h>

void Dlg_TheOneTab::OnBnClickedSmallpan()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (nullptr == Core_Class::main_state())
	{
		return;
	}

	KPtr<TheOne> newOne = Core_Class::main_state()->Create_TheOne(L"Panza");
	newOne->Add_Component<Panza>(Panza::PAN_MAT_TYPE::PMT_WOOD, Panza::PAN_SHP_TYPE::PSH_ANG_RECT, Panza::PAN_SIZ_TYPE::PSI_SMALL);
	Edit_Class::FocusOne = newOne;
	newOne->Local_Pos(Core_Class::main_state()->camera()->one()->Local_Pos().m_Pos, newOne->Local_Pos().z);

	HTREEITEM NewItem = m_TheOneTree.InsertItem(L"Panza");
	m_TheOneTree.SetItemData(NewItem, (DWORD_PTR)((TheOne*)newOne));
}

void Dlg_TheOneTab::OnBnClickedMiddlepan()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (nullptr == Core_Class::main_state())
	{
		return;
	}

	KPtr<TheOne> newOne = Core_Class::main_state()->Create_TheOne(L"Panza");
	newOne->Add_Component<Panza>(Panza::PAN_MAT_TYPE::PMT_WOOD, Panza::PAN_SHP_TYPE::PSH_ANG_RECT, Panza::PAN_SIZ_TYPE::PSI_MIDDLE);
	Edit_Class::FocusOne = newOne;
	newOne->Local_Pos(Core_Class::main_state()->camera()->one()->Local_Pos().m_Pos, newOne->Local_Pos().z);

	HTREEITEM NewItem = m_TheOneTree.InsertItem(L"Panza");
	m_TheOneTree.SetItemData(NewItem, (DWORD_PTR)((TheOne*)newOne));
}


void Dlg_TheOneTab::OnBnClickedBigpan()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (nullptr == Core_Class::main_state())
	{
		return;
	}

	KPtr<TheOne> newOne = Core_Class::main_state()->Create_TheOne(L"Panza");
	newOne->Add_Component<Panza>(Panza::PAN_MAT_TYPE::PMT_WOOD, Panza::PAN_SHP_TYPE::PSH_ANG_RECT, Panza::PAN_SIZ_TYPE::PSI_BIG);
	Edit_Class::FocusOne = newOne;
	newOne->Local_Pos(Core_Class::main_state()->camera()->one()->Local_Pos().m_Pos, newOne->Local_Pos().z);

	HTREEITEM NewItem = m_TheOneTree.InsertItem(L"Panza");
	m_TheOneTree.SetItemData(NewItem, (DWORD_PTR)((TheOne*)newOne));
}


void Dlg_TheOneTab::OnBnClickedGiantpan()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (nullptr == Core_Class::main_state())
	{
		return;
	}

	KPtr<TheOne> newOne = Core_Class::main_state()->Create_TheOne(L"Panza");
	newOne->Add_Component<Panza>(Panza::PAN_MAT_TYPE::PMT_WOOD, Panza::PAN_SHP_TYPE::PSH_ANG_RECT, Panza::PAN_SIZ_TYPE::PSI_GIANT);
	Edit_Class::FocusOne = newOne;
	newOne->Local_Pos(Core_Class::main_state()->camera()->one()->Local_Pos().m_Pos, newOne->Local_Pos().z);

	HTREEITEM NewItem = m_TheOneTree.InsertItem(L"Panza");
	m_TheOneTree.SetItemData(NewItem, (DWORD_PTR)((TheOne*)newOne));
}


void Dlg_TheOneTab::OnBnClickedBottomcreator()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (nullptr == Core_Class::main_state())
	{
		return;
	}

	KPtr<TheOne> newOne = Core_Class::main_state()->Create_TheOne();
	newOne->Add_Component<Bottom>();
	newOne->Local_Pos(Core_Class::main_state()->camera()->one()->Local_Pos().m_Pos, newOne->Local_Pos().z);

	HTREEITEM NewItem = m_TheOneTree.InsertItem(L"Bottom");
	m_TheOneTree.SetItemData(NewItem, (DWORD_PTR)((TheOne*)newOne));
}


void Dlg_TheOneTab::OnBnClickedLaunchercreator()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (nullptr == Core_Class::main_state())
	{
		return;
	}

	KPtr<TheOne> newOne = Core_Class::main_state()->Create_TheOne(L"Launcher");
	Container_Class::Insert_BirdLauncher(Core_Class::main_state(), newOne->Add_Component<Bird_Launcher>());
	Edit_Class::FocusOne = newOne;
	newOne->Local_Pos(Core_Class::main_state()->camera()->one()->Local_Pos().m_Pos, newOne->Local_Pos().z);

	HTREEITEM NewItem = m_TheOneTree.InsertItem(L"Launcher");
	m_TheOneTree.SetItemData(NewItem, (DWORD_PTR)((TheOne*)newOne));
}


void Dlg_TheOneTab::OnBnClickedBombcreator()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (nullptr == Core_Class::main_state())
	{
		return;
	}

	KPtr<TheOne> newOne = Core_Class::main_state()->Create_TheOne(L"Bomb");
	Edit_Class::FocusOne = newOne;
	newOne->Add_Component<Bomb>();
	newOne->Local_Pos(Core_Class::main_state()->camera()->one()->Local_Pos().m_Pos, newOne->Local_Pos().z);

	HTREEITEM NewItem = m_TheOneTree.InsertItem(L"Bomb");
	m_TheOneTree.SetItemData(NewItem, (DWORD_PTR)((TheOne*)newOne));
}

void Dlg_TheOneTab::OnBnClickedPigcreator()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (nullptr == Core_Class::main_state())
	{
		return;
	}

	KPtr<TheOne> newOne = Core_Class::main_state()->Create_TheOne(L"Pig");
	newOne->Add_Component<Pig>(Pig::PIG_SIZ_TYPE::PIG_SMALL);
	Edit_Class::FocusOne = newOne;
	newOne->Local_Pos(Core_Class::main_state()->camera()->one()->Local_Pos().m_Pos, newOne->Local_Pos().z);

	HTREEITEM NewItem = m_TheOneTree.InsertItem(L"Pig");
	m_TheOneTree.SetItemData(NewItem, (DWORD_PTR)((TheOne*)newOne));
}

void Dlg_TheOneTab::OnBnClickedGrasscreator()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (nullptr == Core_Class::main_state())
	{
		return;
	}

	KPtr<TheOne> newOne = Core_Class::main_state()->Create_TheOne(L"Grass");
	KPtr<Grass> NewGrass = newOne->Add_Component<Grass>(0);
	Edit_Class::FocusOne = newOne;
	NewGrass->Col_One()->Local_Pos(Core_Class::main_state()->camera()->one()->Local_Pos().m_Pos, newOne->Local_Pos().z);

	HTREEITEM NewItem = m_TheOneTree.InsertItem(L"Grass");
	m_TheOneTree.SetItemData(NewItem, (DWORD_PTR)((TheOne*)newOne));
}
