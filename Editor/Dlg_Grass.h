#pragma once
#include "Dlg_Component.h"
#include <Grass.h>
#include "afxwin.h"

// Dlg_Grass ��ȭ �����Դϴ�.

class Dlg_Grass : public Dlg_Component
{
	DECLARE_DYNAMIC(Dlg_Grass)

public:
	Dlg_Grass(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Dlg_Grass();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRASS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CButton m_GrassBtn[6];
	Grass*  m_Grass;
	virtual void set_component(Component* _Com);

	afx_msg void OnCbnSelchangeImagecom(UINT _Id);
};
