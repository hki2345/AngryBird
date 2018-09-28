#pragma once
#include <State.h>

class AngryStart : public State::State_Builder
{
public:
	AngryStart();
	~AngryStart();


	// State_Builder을(를) 통해 상속됨
	virtual void Build_State() override;
};

