#pragma once
#include "Bird_Launcher.h"
#include <map>

class State;
class Container_Class
{
private:
	static std::map<std::wstring, KPtr<Bird_Launcher>> m_MapBirdLauncher;

public:
	static void Insert_BirdLauncher(KPtr<State> _State, KPtr<Bird_Launcher> _Value);
	static KPtr<Bird_Launcher> This_BirdLauncher();
	static KPtr<Bird_Launcher> Set_BirdLauncher(KPtr<State> _State);
	static void Erase_BirdLauncher(KPtr<State> _State);

public:
	Container_Class();
	~Container_Class();
};