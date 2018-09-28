#pragma once
#include "Dlg_Component.h"
#include <Bird.h>

// Dlg_Bird 대화 상자입니다.

class Dlg_Bird : public Dlg_Component
{
	DECLARE_DYNAMIC(Dlg_Bird)

public:
	Dlg_Bird(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Dlg_Bird();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BIRD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CButton m_RadioBtn[9];

	CEdit	m_PanValue[7];
	float	m_PanFloat[7];
	Bird*   m_Bird;

	afx_msg void OnEnChangedPanValue(UINT _id);
	afx_msg void OnEnChangedBirdValue(UINT _id);
	afx_msg void OnBnClickedBirdload();
	afx_msg void OnBnClickedBirdsave();
	virtual void set_component(Component* _Com);
	void Update_Bird();
};
