#include "Container_Class.h"
#include <Stl_Assistor.h>
#include <Core_Class.h>

std::map<std::wstring, KPtr<Bird_Launcher>> Container_Class::m_MapBirdLauncher;

Container_Class::Container_Class()
{
}


Container_Class::~Container_Class()
{
}

void Container_Class::Insert_BirdLauncher(KPtr<State> _State, KPtr<Bird_Launcher> _Value)
{
	if (nullptr != _Value)
	{
		m_MapBirdLauncher.insert(std::map<std::wstring, KPtr<Bird_Launcher>>::value_type(_State->name(), _Value));
	}
}


KPtr<Bird_Launcher> Container_Class::This_BirdLauncher()
{
	KPtr<Bird_Launcher> Launcher = Map_Find<KPtr<Bird_Launcher>, std::map<std::wstring, KPtr<Bird_Launcher>>, std::wstring>
		(m_MapBirdLauncher, Core_Class::main_state()->name());

	if (nullptr == Launcher)
	{
		return nullptr;
	}

	return Launcher;
}

KPtr<Bird_Launcher> Container_Class::Set_BirdLauncher(KPtr<State> _State)
{
	std::map<std::wstring, KPtr<Bird_Launcher>>::iterator FindIter = m_MapBirdLauncher.find(_State->name());
	if (FindIter == m_MapBirdLauncher.end())
	{
		return nullptr;
	}
	return FindIter->second;
}


void Container_Class::Erase_BirdLauncher(KPtr<State> _State)
{
	std::map<std::wstring, KPtr<Bird_Launcher>>::iterator FindIter = m_MapBirdLauncher.find(_State->name());
	if (FindIter == m_MapBirdLauncher.end())
	{
		return;
	}
	m_MapBirdLauncher.erase(FindIter);
}