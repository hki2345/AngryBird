#pragma once
#include <State.h>

class AngryStart : public State::State_Builder
{
public:
	AngryStart();
	~AngryStart();


	// State_Builder��(��) ���� ��ӵ�
	virtual void Build_State() override;
};

