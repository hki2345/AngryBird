#include "AngryStart.h"

#include <KWindow.h>

#include <ResourceManager.h>

#include <Renderer_Sprite.h>
#include <Collider2D_DE.h>

AngryStart::AngryStart()
{
}


AngryStart::~AngryStart()
{
}

void AngryStart::Build_State()
{
	// 강체에서 체인을 못 걸어준다. ㅠㅜㅜ-> 다른 오더간 체인을 말한다. -> 오더로 몇번째 월드를 만드느냐
	state()->this_Collider2DManager.chain(0, 0);
	state()->this_KRigid2DManager.gravity(KVector2(0.0f, -200.0f));

	KPtr<TheOne> NewCamera = state()->Create_TheOne();
	KPtr<Camera> CameraCom = NewCamera->Add_Component<Camera>();
	CameraCom->Insert_LayerData(0, 2, 3, 4);
	NewCamera->Local_Pos({ .0f, .0f, -10.0f });

	KPtr<TheOne> NewTitle = state()->Create_TheOne();
	NewTitle->Local_Scale(window()->size());
	NewTitle->Add_Component<Renderer_Sprite>(L"Title.png");
	NewTitle->Add_Component<Collider2D_DE>(0);
	NewTitle->name(L"Title");
	//	NewPanza2->insert_Child(NewPanza3);
}
