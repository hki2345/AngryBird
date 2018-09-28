#include "GameData.h"
#include <ResourceManager.h>

std::unordered_map<int, int>  User_Data::m_ScoreList;


void User_Data::InsertScore(const ScoreData& _Data)
{
	std::unordered_map<int, int>::iterator FI = m_ScoreList.find(_Data.Stage);

	if (m_ScoreList.end() == FI)
	{
		m_ScoreList.insert(std::unordered_map<int, int>::value_type(_Data.Stage, _Data.HighScore));
	}

	else
	{
		if (FI->second < _Data.HighScore)
		{
			FI->second = _Data.HighScore;
		}
	}
}

void User_Data::SaveScore()
{
	std::wstring Temp = PathManager::Find_Path(L"User");

	Temp += L"Score.UD";
	WriteStream NewStream = WriteStream(Temp.c_str());
	
	// 12개의 스테이지 - 무조건 12개의 스테이지가 저장된다.
	for (int i = 1; i < 13; i++)
	{
		std::unordered_map<int, int>::iterator FI = m_ScoreList.find(i);

		if (m_ScoreList.end() == FI)
		{
			m_ScoreList.insert(std::unordered_map<int, int>::value_type(i, 0));
		}
	}

	std::unordered_map<int, int>::iterator SI = m_ScoreList.begin();
	std::unordered_map<int, int>::iterator EI = m_ScoreList.end();
	
	for (; SI != EI; ++SI)
	{
		ScoreData NewData;
		NewData.Stage = SI->first;
		NewData.HighScore = SI->second;
		NewStream.write(&NewData, sizeof(ScoreData));
	}
}


std::unordered_map<int, int>*  User_Data::LoadScore()
{
	std::wstring Temp = PathManager::Find_Path(L"User");

	Temp += L"Score.UD";
	ReadStream NewStream = ReadStream(Temp.c_str());
	m_ScoreList.clear();

	for (size_t i = 0; i < 12; i++)
	{
		ScoreData NewData;
		NewStream.read(&NewData, sizeof(ScoreData));
		InsertScore(NewData);
	}

	return &m_ScoreList;
}


bool  User_Data::Is_HighScore(const ScoreData& _Data)
{
	std::unordered_map<int, int>::iterator FI = m_ScoreList.find(_Data.Stage);

	if (m_ScoreList.end() == FI)
	{
		return true;
	}

	else
	{
		if (FI->second < _Data.HighScore)
		{
			return true;
		}
	}


	return false;
}


int User_Data::FindScore(const int& _Stage)
{
	std::unordered_map<int, int>::iterator FI = m_ScoreList.find(_Stage);

	if (m_ScoreList.end() == FI)
	{
		return -1;
	}

	else
	{
		return FI->second;
	}
	return -1;
}