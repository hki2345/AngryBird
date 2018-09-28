#pragma once
#include <State.h>


class KFont;
class SoundPlayer;
class Mouse_Col;
class AngryStartUpdater : public State::State_Updater
{
public:
	AngryStartUpdater();
	~AngryStartUpdater();


private:
	enum START_TYPE 
	{
		START_NONE = -1,
		START_TITLE = 0,
		START_INTRO,
		START_EPISODE,
		START_LEVEL,
		START_NUM,
	};

private:
	KPtr<KFont>			m_Font;
	KPtr<SoundPlayer>	m_SP;
	KPtr<Mouse_Col>		m_Mouse;

	KPtr<TheOne>		m_Back;

	// Intro
	KPtr<TheOne>		m_Logo;
	KPtr<TheOne>		m_GroundOne[2];
	KPtr<TheOne>		m_WoodOne[2];
	KPtr<TheOne>		m_MountainOne[2];
	KPtr<TheOne>		m_SkyOne[2];
	KPtr<TheOne>		PlayBtn;

	// Episode
	KPtr<TheOne>		m_EpisodeSelect;
	KPtr<TheOne>		m_Episode[3];
	KPtr<TheOne>		m_Lock[3];

	// Level Select
	KPtr<TheOne>		m_LevelSelect;
	KPtr<TheOne>		m_Level[4][3];
	/*KPtr<TheOne>		m_LevelStar[4][3][3];*/

	START_TYPE			m_StartFsm;
	bool				m_Title;

public:
	void State_Select()
	{
		m_StartFsm = START_TYPE::START_LEVEL;
	}

	// State_Updater을(를) 통해 상속됨
	void Start_State() override;
	void End_State() override;

	void Update_State() override;
	void UI_Render() override;
	void Debug_Render() override;

private:
	void Start_BG();
	void Start_Intro();
	void Start_Episode();
	void Start_Level();
	

	void Update_Title();
	void Update_Intro();
	void Update_Episode();
	void Update_Level();

	void Update_BG();

	void Active_Intro();
	void Active_Episode();
	void Active_Level();

	void UnActive_Intro();
	void UnActive_Episode();
	void UnActive_Level();
};
