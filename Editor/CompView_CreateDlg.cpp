#include "stdafx.h"
#include "resource.h"
#include <Component.h>

#include "View_Component.h"
#include "Dlg_Trans.h"
#include "Dlg_Panza.h"
#include "Dlg_Bottom.h"
#include "Dlg_Launcher.h"
#include "Dlg_Bird.h"
#include "Dlg_Grass.h"
#include "Dlg_Pig.h"

Dlg_Component* View_Component::create_comDlg(const type_info* _Type)
{
	Dlg_Component* NewDlg = nullptr;

	if (_Type == &typeid(TransPosition))
	{
		NewDlg = new Dlg_Trans();
		NewDlg->Create(IDD_TRANS, this);
	}
	else if (_Type == &typeid(Panza))
	{
		NewDlg = new Dlg_Panza();
		NewDlg->Create(IDD_PANZA, this);
	}
	else if (_Type == &typeid(Bottom)) {
		NewDlg = new Dlg_Bottom();
		NewDlg->Create(IDD_BOTTOM, this);
	}
	else if (_Type == &typeid(Bird_Launcher)) {
		NewDlg = new Dlg_Launcher();
		NewDlg->Create(IDD_LAUNCHER, this);
	}
	else if (_Type == &typeid(Bird)) {
		NewDlg = new Dlg_Bird();
		NewDlg->Create(IDD_BIRD, this);
	}
	else if (_Type == &typeid(Grass)) {
		NewDlg = new Dlg_Grass();
		NewDlg->Create(IDD_GRASS, this);
	}
	else if (_Type == &typeid(Pig)) {
		NewDlg = new Dlg_Pig();
		NewDlg->Create(IDD_PIG, this);
	}

	return NewDlg;
}