#pragma once
#include <Some_One.h>

class Collider2D_DE;
class KRigid_2D;
class KRaycast_2D;
class Renderer_Sprite;
class Bomb : public Some_One
{
public:
	Bomb();
	~Bomb();

public:
	enum BOMB_STATE
	{
		NONE = 0,
		STAND_BY,
		EXPOLOSION,
	};

private:
	KPtr<Collider2D_DE> m_Collider;
	KPtr<KRigid_2D> m_Rigid;
	KPtr<KRaycast_2D> m_Ray;
	KPtr<Renderer_Sprite> m_Render;
	BOMB_STATE m_State;

	void Init_Render();
	void Init_Collider();

	void Update_Damage();
	void Update_Image();

public:
	void Reset_Rigid();
	void Set_Transform(const KVector& _Pos, const KVector& _Rotate, const KVector& _Scale);
	void Set_Pos(const KVector& _Pos);
	void Set_Rotate(const KVector& _Rotate);
	void Set_Scale(const KVector& _Scale);
	void Activate_Bomb();

	// Mass, Inertia, Center
	void MassData(const KVector& _Value);
	KVector MassData() const;

	// Density, Friction, Restitude
	void FigureData(const KVector3& _Value);
	KVector3 FigureData() const;


	bool Init();
	void Update() override;

	void save();
	void load();

};

