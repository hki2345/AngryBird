#pragma once
#include <Some_One.h>
#include <list>
#include "Bird.h"


class Renderer_Sprite;
class Collider2D_DE;
class KFont;
class Bird_Launcher : public Some_One
{
public:
	Bird_Launcher();
	~Bird_Launcher();


private:
	int m_HighScore[3];


	int m_GameScore;
	int m_MovingScore;
	int m_RecordScore;

	KVector2 m_Launch_Point;

	KPtr<Renderer_Sprite> m_Render[2];
	KPtr<Collider2D_DE> m_Collider;
	KPtr<KFont> m_Font;

	std::list<KPtr<Bird>> m_BirdList;

	std::list<KPtr<Bird>>::iterator m_SBList;
	std::list<KPtr<Bird>>::iterator m_EBList;
	
	KPtr<Bird> m_LRBird;

	std::wstring m_FileName;

public:
	KPtr<Bird> ReadyBird()
	{
		return m_LRBird;
	}
	void ReadyBird(KPtr<Bird> _Bird)
	{
		m_LRBird = _Bird;
	}
	

	std::list<KPtr<Bird>> BirdList()
	{
		return m_BirdList;
	}
	KVector2 Launch_Point()
	{
		return m_Launch_Point;
	}

	KPtr<Bird> FindBird(KPtr<Bird> _Bird);
	KPtr<Bird> CreateBird(const Bird::BIRD_TYPE& _Type);
	void DeleteBird(KPtr<Bird> _Bird);
	void MinusIdxBird();

	void Plus_Score(const int& _Score)
	{
		m_MovingScore += _Score;
	}

	void HighScore(const int* _ScoreValue)
	{
		for (size_t i = 0; i < 3; i++)
		{
			m_HighScore[i] = _ScoreValue[i];
		}
	}

	int* HighScore()
	{
		return m_HighScore;
	}


	int GameScore() const
	{
		return m_GameScore;
	}

public:
	void Set_Transform(const KVector& _Pos);



	bool Init() override;
	void Update() override;
	void UIRender();

private:
	void Update_LP();
	void Update_List();
};

