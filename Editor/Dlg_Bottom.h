#pragma once

#include "Dlg_Component.h"
#include <Bottom.h>


// Dlg_Bottom ��ȭ �����Դϴ�.

class Dlg_Bottom : public Dlg_Component
{
	DECLARE_DYNAMIC(Dlg_Bottom)

public:
	Dlg_Bottom(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Dlg_Bottom();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BOTTOM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

private:
	size_t  m_VerIdx;
	CEdit	m_PanValue[7];
	float	m_PanFloat[7];
	Bottom*  m_Bottom;

	CButton m_Edit;
	CButton m_BCheck;
public:

	afx_msg void OnEnChangedPanValue(UINT _id);

	virtual void set_component(Component* _Com);


	void Update_Panza();
	void Create_Vertex();
	
	BOOL EditOn();
	void EditOn(const BOOL& _Value);

	afx_msg void OnBnClickedBottomedit();
};
