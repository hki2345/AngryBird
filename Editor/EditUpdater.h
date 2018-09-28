#pragma once
#include <State.h>

class EditUpdater :public State::State_Updater
{
public:
	float CamSpeed;

private:
	// KPtr<State> FindState;
	KVector2		m_OriginScreen;

	int Number;
	int CheckNumber;

	bool m_bTestThread;


private:
	void Update_OneTree();
	void Update_Mouse();

	void CamMove();
	void ObjToMouseCheck();
	bool Mouse_InScreen();
	void Update_Trans();

	void TestThread();

	unsigned int Func(void* _Test);

	void Edit_Vertex();
	void Edit_One();


public:
	virtual void Update_State() override;
	virtual void Start_State() override;
	virtual void Debug_Render() override;

public:
	EditUpdater();
	~EditUpdater();
};

