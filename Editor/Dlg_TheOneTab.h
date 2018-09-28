#pragma once
#include "TabState.h"
#include "Mouse_Droper.h"

#include "afxcmn.h"
#include "afxwin.h"

// Dlg_TheOneTab 대화 상자입니다.

class Dlg_TheOneTab : public TabState
{
	DECLARE_DYNAMIC(Dlg_TheOneTab)

public:
	Dlg_TheOneTab(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Dlg_TheOneTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_THEONE };
#endif

protected:
	Mouse_Droper m_Droper;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTvnSelchangedOnetree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnBegindragOnetree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnKeydownOnetree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnEndlabeleditOnetree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickOnetree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickOnetree(NMHDR *pNMHDR, LRESULT *pResult);


	
public:
	UINT TheOne_TreeCount()
	{
		if (nullptr != m_TheOneTree)
		{
			return m_TheOneTree.GetCount();
		}

		return 0;
	}

	CTreeCtrl m_TheOneTree;
	HTREEITEM m_SelectObject;
	HTREEITEM m_Launcher;
	virtual BOOL OnInitDialog();
	void Reset_OneTree();

	afx_msg void OnBnClickedSmallpan();

	afx_msg void OnEnChangedGravity(UINT _id);


	float m_GravityX;
	float m_GravityY;
	afx_msg void OnBnClickedBottomcreator();
	afx_msg void OnBnClickedLaunchercreator();
	afx_msg void OnBnClickedMiddlepan();
	afx_msg void OnBnClickedBigpan();
	afx_msg void OnBnClickedGiantpan();
	afx_msg void OnBnClickedDeleteall();
	afx_msg void OnBnClickedBombcreator();
	afx_msg void OnBnClickedPigcreator();
	afx_msg void OnBnClickedGrasscreator();
};
