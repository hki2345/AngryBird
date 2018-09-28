#pragma once
#include "Dlg_Component.h"
#include <Pig.h>

// Dlg_Pig 대화 상자입니다.

class Dlg_Pig : public Dlg_Component
{
	DECLARE_DYNAMIC(Dlg_Pig)

public:
	Dlg_Pig(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Dlg_Pig();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PIG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CButton m_PigBtn[4];
	Pig*  m_Pig;
	virtual void set_component(Component* _Com);

	afx_msg void Update_Pig(UINT _Id);
};
