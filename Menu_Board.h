#pragma once
#include <Component.h>

class KFont;
class Menu_Board : public Component
{
private:
	int Stage;

	KPtr<TheOne> Play;
	KPtr<TheOne> Replay;
	KPtr<TheOne> SSelect;
	KPtr<TheOne> Back;

	KPtr<TheOne> Pause;

	KPtr<KFont> m_Font;

	bool m_Menu;

private:
	void Set_Board();
	void UNSet_Board();
	void Set_Pause();

	void Update_Col();

public:
	bool Init(const int& _Stage);
	void Update() override;
	void UIRender() override;

public:
	Menu_Board();
	~Menu_Board();
};

