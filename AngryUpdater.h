#pragma once
#include <State.h>


class KFont;
class SoundPlayer;
class AngryUpdater : public State::State_Updater
{
private:
	float	m_CamSpeed;
	int		m_Stage;

	bool	WinBoard;
	float	WinDTime;


	KVector2		m_OriginScreen;
	KPtr<KFont>		m_Font;

	// BG
	KPtr<TheOne>		m_Logo;
	KPtr<TheOne>		m_GroundOne[2];
	KPtr<TheOne>		m_WoodOne[2];
	KPtr<TheOne>		m_MountainOne[2];
	KPtr<TheOne>		m_SkyOne[2];
	KPtr<TheOne>		PlayBtn;

	KPtr<TheOne>		m_WBoard;
	KPtr<TheOne>		m_MBoard;
	KPtr<SoundPlayer>	m_SP;

	bool m_EndSound;

public:
	AngryUpdater();
	~AngryUpdater();

	// State_Updater을(를) 통해 상속됨
	void Start_State() override;
	void Update_State() override;
	void UI_Render()	override;
	void Debug_Render() override;

private:
	void End_Angry();

	void Start_BG();
	void Win_Stage();

	void Update_Cam();
	void Update_Mouse();
	void Update_WinCheck();
	void Update_WinBoard();
};

