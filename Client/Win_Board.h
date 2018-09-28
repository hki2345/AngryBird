#pragma once
#include <Some_One.h>

class KFont;
class SoundPlayer;
class Win_Board : public Component
{
private:
	int m_Score;
	int m_Stage;
	size_t m_Star;

	float STime;

	KPtr<TheOne> SSelect;
	KPtr<TheOne> Replay;
	KPtr<TheOne> NSelect;
	KPtr<TheOne> Back;
	KPtr<TheOne> HighScore;

	KPtr<TheOne> Star[3];

	KPtr<KFont> m_Font;
	KPtr<SoundPlayer>	m_SP;

	bool SoundCheck;
	bool m_Start;
	bool m_HighScore;

private:
	void Set_Board();
	void Update_Star();

public:
	bool Init(const int& _Stage);
	void Update() override;
	void UIRender() override;

	void Set_Score(const int& _Score)
	{
		m_Score = _Score;
	}

public:
	Win_Board();
	~Win_Board();
};

