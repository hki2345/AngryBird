#pragma once
#include <set>
#include "DirectXHeader.h"
#include "Component_DE.h"


// 3D 구현에 핵심
class TransPosition;
class RenderManager;
class Camera final: public Component_DE
{
public:
	friend RenderManager;

public:
	enum PROJ_MODE
	{
		PM_PERSPECTIVE,
		PM_ORTHGRAPHICS
	};

	// 윈도우와 내가 원한 윈도우를 결정
	enum SIZE_MODE
	{
		SM_WINDOW,
		SM_CUSTOM
	};

private:
	
	KMatrix m_View;
	KMatrix m_Proj;
	KMatrix m_VP;

	PROJ_MODE m_ePMode;
	SIZE_MODE m_eSMode;

	KVector2 m_ScreenSize;
	KVector2 m_OriginPos;
	float m_ScreenRatioX;
	float m_ScreenRatioY;

	float m_fFov;
	float m_fNear;
	float m_fFar;

	float m_DTime;
	float m_ITime;
	float m_STime;
	float m_SSize;

public:
	const KMatrix& View_Proj() const
	{
		return m_VP;
	}

	void screen_size(const KVector2& _Value)
	{
		m_ScreenSize = _Value;
		m_eSMode = SM_CUSTOM;
	}
	KVector2& screen_size ()
	{
		return m_ScreenSize;
	}

	void Shaking(const float& _Time, const float& _Size)
	{
		m_DTime = .0f;
		m_STime = _Time;
		m_SSize = _Size;
	}


	// 카메라가 비추어줄 레이어
private:
	std::set<int> m_Layer;
	
public:
	bool Init() override;
	KVector2 screen_to_world(const KVector2& _StatePos);

	template<typename ...Rest>
	void Insert_LayerData(Rest ...Args)
	{
		Insert_Layer(Args...);
	}

private:
	template<typename ...Rest>
	void Insert_Layer(int _Data, Rest ...Args)
	{ 
		m_Layer.insert(_Data);
		Insert_Layer(Args...);
	}
	void Insert_Layer()  {}

private:
	virtual void Update() override;
	virtual void FinalUpdate() override;
	virtual void End_Update() override;
	void Shake_Update();

public:
	Camera();
	~Camera();
};

