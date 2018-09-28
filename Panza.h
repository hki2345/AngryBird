#pragma once
#include <Some_One.h>


class Collider2D_DE;
class KRigid_2D;
class Renderer_Sprite;
class Sprite_Changer;
class KRaycast_2D;
class KFont;
class Panza : public Some_One
{
public:
	Panza();
	~Panza();


public:
	enum PAN_MAT_TYPE
	{
		PMT_NONE = -1,
		PMT_ICE,
		PMT_WOOD,
		PMT_STONE,
		PMT_NUMBER
	};

	enum PAN_SHP_TYPE
	{
		PSH_NONE = -1,
		PSH_ABS_TRIANGLE,
		PSH_RIA_TRIANGLE,
		PSH_ABS_RECT,
		PSH_ANG_RECT,
		PSH_CIRCLE,
		PSH_NUMBER
	};

	enum PAN_SIZ_TYPE
	{
		PSI_NONE = -1,
		PSI_SMALL,
		PSI_MIDDLE,
		PSI_BIG,
		PSI_GIANT,
		PSI_NUMBER
	};

private:
	KPtr<KFont> m_Font;
	KPtr<Collider2D_DE> m_Collider;
	KPtr<KRigid_2D> m_Rigid;
	KPtr<Renderer_Sprite> m_Render;
	KPtr<Sprite_Changer> m_Changer;
	std::wstring m_FileName;


	PAN_SHP_TYPE m_ShapeType;
	PAN_MAT_TYPE m_MatType;
	PAN_SIZ_TYPE m_SizeType;

	void Update_Damage();
	void Update_Image();

	int m_hp;

public:
	void Damage();


	void Reset_Rigid();
	void Set_Transform(const KVector& _Pos, const KVector& _Rotate, const KVector& _Scale);
	void Set_Pos(const KVector& _Pos);
	void Set_Rotate(const KVector& _Rotate);
	void Set_Scale(const KVector& _Scale);

	// Name
	const wchar_t* PanName() const { return m_FileName.c_str(); }

	// Type
	PAN_SHP_TYPE& Shape_Type()		{ return m_ShapeType; }
	PAN_MAT_TYPE& Material_Type()	{ return m_MatType; }
	PAN_SIZ_TYPE& Size_Type()		{ return m_SizeType; }

	void		 Shape_Type(const PAN_SHP_TYPE& _Value)		{ m_ShapeType = _Value; }
	void		 Material_Type(const PAN_MAT_TYPE& _Value)	{ m_MatType = _Value; }
	void		 Size_Type(const PAN_SIZ_TYPE& _Value)		{ m_SizeType = _Value; }

	// Mass, Inertia, Center
	void MassData(const KVector& _Value);
	KVector MassData() const;

	// Density, Friction, Restitude
	void FigureData(const KVector3& _Value);
	KVector3 FigureData() const;


	
	bool Init(const PAN_MAT_TYPE& _Mat, const PAN_SHP_TYPE& _Shape, const PAN_SIZ_TYPE& _Size, const bool& _Init = true);
	void Update() override;
	void DebugRender() override;

	void save();
	void load();


private:
	void Set_Panza(const bool& _Init);
};

