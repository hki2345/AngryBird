#pragma once
#include "Dlg_Component.h"
#include <Pig.h>

// Dlg_Pig ��ȭ �����Դϴ�.

class Dlg_Pig : public Dlg_Component
{
	DECLARE_DYNAMIC(Dlg_Pig)

public:
	Dlg_Pig(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Dlg_Pig();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PIG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CButton m_PigBtn[4];
	Pig*  m_Pig;
	virtual void set_component(Component* _Com);

	afx_msg void Update_Pig(UINT _Id);
};
