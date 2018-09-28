#pragma once
#include "Dlg_Component.h"
#include <Grass.h>
#include "afxwin.h"

// Dlg_Grass 대화 상자입니다.

class Dlg_Grass : public Dlg_Component
{
	DECLARE_DYNAMIC(Dlg_Grass)

public:
	Dlg_Grass(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Dlg_Grass();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRASS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CButton m_GrassBtn[6];
	Grass*  m_Grass;
	virtual void set_component(Component* _Com);

	afx_msg void OnCbnSelchangeImagecom(UINT _Id);
};
