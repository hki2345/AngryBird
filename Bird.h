#pragma once
#include <Some_One.h>


class Collider2D_DE;
class KRigid_2D;
class KRaycast_2D;
class Bird_Launcher;
class Renderer_Sprite;
class Bird : public Some_One
{
public:
	Bird();
	~Bird();


public:
	enum BIRD_TYPE
	{
		BT_NONE = -1,
		BT_BOMB,
		BT_BLUE,
		BT_BUBBLE,
		BT_CHUCK,
		BT_HAL,
		BT_MATILDA,
		BT_MIGHTY_EAGLE,
		BT_RED,
		BT_TERENCE,
		BT_MATILDAEGG,
		BT_NUM,
	};

	enum BIRD_STATE
	{
		BS_NONE = -1,
		BS_STAND,
		BS_MOVE,
		BS_LOAD,
		BS_STANDBY,
		BS_TRIGGER,
		BS_FIRE,
		BS_CRUISE,
		BS_ACTIVATE,
		BS_ACTCRUISE,
		BS_UNPOWER,
		BS_IGNITION,
		BS_NUM,
	};


private:
	bool m_Sound;
	size_t PrevStandByInx;
	size_t mStandByInx;

	Bird_Launcher* m_Launcher;
	KPtr<Collider2D_DE> m_Collider;
	KPtr<Collider2D_DE> m_LaunchCol;
	KPtr<KRigid_2D> m_Rigid;
	KPtr<Renderer_Sprite> m_Render;

	BIRD_TYPE m_BT;
	BIRD_STATE m_BS;


	KPtr<KRaycast_2D> m_Ray;
	float	m_BirdTime;


private:
	void Init_Bird();
	void Init_Render();
	void Init_Collider();

	void Update_Damage();
	void Update_Image();

	void Update_State();


	void Update_Stand();
	void Update_Load();
	void Update_Move();
	void Update_StandBy();
	void Update_Trigger();
	void Update_Fire();
	void Update_Cruise();
	void Update_Activate();
	void Update_Ingnition();
	void Update_ActCruise();
	void Update_UnPowered();


	void Activate_Bomb();
	void Activate_Blue();
	void Activate_Bubble();
	void Activate_Chuck();
	void Activate_Hal();
	void Activate_Matilda();
	void Activate_MightyEagle();
	void Activate_Red();
	void Activate_Terence();
	void Activate_Egg();

public:
	void Damage();


	void StandBy_IDX(const size_t& _Value)
	{
		mStandByInx = _Value;
	}

	size_t StandBy_IDX() const
	{
		return mStandByInx;
	}


	size_t MinusStandBy_IDX()
	{
		return --mStandByInx;
	}



	// Type
	BIRD_TYPE& Bird_Type() { return m_BT; }
	void Bird_Type(const BIRD_TYPE& _Value) { m_BT = _Value ; }


	BIRD_STATE& Bird_State() { return m_BS; }
	void Bird_State(const BIRD_STATE& _Value) { m_BS = _Value; }

	void		 Shape_Type(const BIRD_TYPE& _Value) { m_BT = _Value; }



	// 애딧에서 정보만 바꾸기 위함
	bool Init(const BIRD_TYPE& _Type);
	bool Init(const BIRD_TYPE& _Type, KPtr<Bird_Launcher> _Launcher, const size_t& _Index);
	void Update() override;

	void save();
	void load();
};

