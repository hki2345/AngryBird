#pragma once
#include "Dlg_Component.h"
#include <Panza.h>
#include "afxwin.h"


// Dlg_Panza ��ȭ �����Դϴ�.
class Dlg_Panza : public Dlg_Component
{
	DECLARE_DYNAMIC(Dlg_Panza)

public:
	Dlg_Panza(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Dlg_Panza();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PANZA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
