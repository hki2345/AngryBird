#pragma once
class Split_Data
{
public:
	wchar_t path[256];
	wchar_t name[256];

	size_t X;
	size_t Y;

public:
	Split_Data() : X(1), Y(1)
	{

	}
};

#include <unordered_map>
class User_Data
{
private:
	static std::unordered_map<int, int> m_ScoreList;

public:
	struct ScoreData
	{
		int Stage;
		int HighScore;
	};

public:
	static bool Is_HighScore(const ScoreData& _Data);

	static int FindScore(const int& _Stage);
	static void InsertScore(const ScoreData& _Data);
	static void SaveScore();
	static  std::unordered_map<int, int>* LoadScore();
};


#include <State.h>
#include "Panza.h"
#include "Pig.h"


class Bird_Launcher;
class Map_Data 
{
private:
	static std::unordered_map<int, std::list<KPtr<TheOne>>> m_MapList;

	enum MAP_TYPE
	{
		NONE = -1,
		PANZA,
		BOTTOM,
		LAUNCHER, 
		BOMB,
		GRASS,
		PIG
	};
	
	struct TypeData
	{
		MAP_TYPE m_Type;
	};

	struct PanzaData
	{
		KVector m_Trans;
		Panza::PAN_MAT_TYPE m_PMATT;
		Panza::PAN_SHP_TYPE m_PSHPT;
		Panza::PAN_SIZ_TYPE m_PSIZT;
	};

	struct BottomData
	{
		KVector Size;
	};

	struct LauncherData
	{
		int HighScore[3];
		KVector m_Trans;
		int	Size;
	};

	struct PigData
	{
		KVector Trans;
		Pig::PIG_SIZ_TYPE Size;
	};
	struct GrassData
	{
		KVector Trans;
		int ImageNumber;
	}; 
	struct BombData
	{
		KVector Trans;
	};

public:
	static size_t CountingStar();
	
	static void Map_Save(KPtr<State> _State, const wchar_t* _Path);
	static void Map_Load(KPtr<State> _State, const wchar_t* _Path);
	static void Map_Erase(KPtr<State> _State);
	static size_t Map_Count(KPtr<State> _State);
	static size_t Save_Count(KPtr<State> _State);
};