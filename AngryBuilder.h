#pragma once
#include <State.h>


class AngryBuilder : public State::State_Builder
{
public:
	AngryBuilder();
	~AngryBuilder();

	// State_Builder을(를) 통해 상속됨
	virtual void Build_State() override;
};

