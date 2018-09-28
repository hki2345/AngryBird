#pragma once
#include <Some_One.h>
#include <list>


class Collider2D_DE;
class KRigid_2D;
class Renderer_Sprite;
class Bottom : public Some_One
{
public:
	Bottom();
	~Bottom();


	
private:
	KPtr<Collider2D_DE> m_Collider;
	KPtr<KRigid_2D> m_Rigid;
	KPtr<Renderer_Sprite> m_Render;

public:
	void Set_Transform(const KVector& _Pos, const KVector& _Rotate, const KVector& _Scale);
	void Set_Pos(const KVector& _Pos);
	void Set_Rotate(const KVector& _Rotate);
	void Set_Scale(const KVector& _Scale);

	// Mass, Inertia, Center
	void MassData(const KVector& _Value);
	KVector MassData() const;

	// Density, Friction, Restitude
	void FigureData(const KVector3& _Value);
	KVector3 FigureData() const;
	
	bool Init();
	void Update() override;

	void save(const wchar_t* _Name);
	void load(const wchar_t* _Name);
};

