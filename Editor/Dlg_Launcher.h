#pragma once

#include "Dlg_Component.h"


// Dlg_Launcher ��ȭ �����Դϴ�.
class Bird_Launcher;
class Dlg_Launcher : public Dlg_Component
{
	DECLARE_DYNAMIC(Dlg_Launcher)

public:
	Dlg_Launcher(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Dlg_Launcher();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LAUNCHER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:

	CEdit	m_ScoreValue[3];
	int		m_ScoreInt[3];

	CButton				m_RadioBtn[9];
	Bird_Launcher*		m_Launcher;

	afx_msg void OnBnClickedDeleteall();
	afx_msg void OnBnClickedCreate();
	afx_msg void OnEnChangedBirdValue(UINT _id);
	afx_msg void OnEnChangedScoreValue(UINT _id);

	virtual void set_component(Component* _Com);
};
