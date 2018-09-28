#include "AngryBuilder.h"


#include <Panza.h>
#include <Bottom.h>


#include <ResourceManager.h>
#include <GameData.h>

AngryBuilder::AngryBuilder()
{
}


AngryBuilder::~AngryBuilder()
{
}

void AngryBuilder::Build_State()
{
	// 강체에서 체인을 못 걸어준다. ㅠㅜㅜ-> 다른 오더간 체인을 말한다. -> 오더로 몇번째 월드를 만드느냐
	state()->this_Collider2DManager.chain(0, 0);
	state()->this_KRigid2DManager.gravity(KVector2(0.0f, -200.0f));

	KPtr<TheOne> NewCamera = state()->Create_TheOne();
	KPtr<Camera> CameraCom = NewCamera->Add_Component<Camera>();
	CameraCom->Insert_LayerData(0, 2, 3, 4);
	NewCamera->Local_Pos({ .0f, .0f, -10.0f });

	//	NewPanza2->insert_Child(NewPanza3);
}
