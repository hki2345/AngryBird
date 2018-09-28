#pragma once
#include <Some_One.h>


class Collider2D_DE;
class KRigid_2D;
class Renderer_Sprite;
class Sprite_Changer;
class Pig : public Some_One
{
public:
	Pig();
	~Pig();


public:
	enum PIG_SIZ_TYPE
	{
		PIG_NONE = -1,
		PIG_SMALL,
		PIG_MIDDLE,
		PIG_BIG,
		PIG_GIANT,
		PIG_NUMBER
	};

	enum PIG_STATE
	{
		PSH_NONE = -1,
		PIG_STANBY,
		PIG_WEEKWOUND,
		PIG_HEAVYWOUND
	};

private:
	KPtr<Collider2D_DE> m_Collider;
	KPtr<KRigid_2D> m_Rigid;
	KPtr<Renderer_Sprite> m_Render;
	KPtr<Sprite_Changer> m_Changer;

	PIG_SIZ_TYPE m_SizeType;
	PIG_STATE m_PigState;


	int m_hp;

private:
	void Update_Damage();
	void Update_Image();
	
	void Init_Render();
	void Init_Collider();

public:
	void Damage();


	void Reset_Rigid();
	void Set_Transform(const KVector& _Pos, const KVector& _Rotate, const KVector& _Scale);
	void Set_Pos(const KVector& _Pos);
	void Set_Rotate(const KVector& _Rotate);
	void Set_Scale(const KVector& _Scale);

	// Type
	PIG_SIZ_TYPE& Size_Type() { return m_SizeType; }
	PIG_STATE&	Pig_State() { return m_PigState; }

	void		 Size_Type(const PIG_SIZ_TYPE& _Value) { m_SizeType = _Value; }
	void		 Pig_State(const PIG_STATE& _Value) { m_PigState = _Value; }

	// Mass, Inertia, Center
	void MassData(const KVector& _Value);
	KVector MassData() const;

	// Density, Friction, Restitude
	void FigureData(const KVector3& _Value);
	KVector3 FigureData() const;



	bool Init(const PIG_SIZ_TYPE& _Mat);
	void Update() override;

	void save();
	void load();
		
};