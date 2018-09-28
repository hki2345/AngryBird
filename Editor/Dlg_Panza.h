#pragma once
#include "Dlg_Component.h"
#include <Panza.h>
#include "afxwin.h"


// Dlg_Panza 대화 상자입니다.
class Dlg_Panza : public Dlg_Component
{
	DECLARE_DYNAMIC(Dlg_Panza)

public:
	Dlg_Panza(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Dlg_Panza();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PANZA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CButton m_RadioBtn[12];

	CEdit	m_PanValue[7];
	float	m_PanFloat[7];
	Panza*  m_Panza;

	afx_msg void OnEnChangedPanValue(UINT _id);

	virtual void set_component(Component* _Com);
	void Update_Panza();
	afx_msg void OnBnClickedPanzasave();
	afx_msg void OnBnClickedPanzaload();
};
