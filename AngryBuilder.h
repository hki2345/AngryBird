#pragma once
#include <State.h>


class AngryBuilder : public State::State_Builder
{
public:
	AngryBuilder();
	~AngryBuilder();

	// State_Builder��(��) ���� ��ӵ�
	virtual void Build_State() override;
};

