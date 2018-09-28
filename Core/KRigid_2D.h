#pragma once
#include "Component_DE.h"
#include <Box2D/Box2D.h>
#include <vector>



class KRigid_2DManager;
class Collider2D_DE;
class KRigid_2D : public Component_DE
{
private:
	struct KRigid2D_Data
	{
		KVector m_MassData;
		KVector3 m_FigureData;
	};

public:
	friend KRigid_2DManager;

private:
	KPtr<Collider2D_DE>	m_Col2D;
	b2BodyDef			m_BD;
	b2MassData*			m_MD;
	b2FixtureDef*		m_FD;

	b2Body*				m_Body;
	b2Shape*			m_Shape;

	b2PolygonShape*		m_Poly;
	b2CircleShape*		m_Circle;
	b2Fixture*			m_Fixture;
	KVector3			m_FV;

	std::vector<KPtr<TheOne>> m_VertexVec;
	std::vector<KVector2> m_MeshVec;
	std::list<KPtr<KRigid_2D>> m_Con_KRigid2D;

public:
	b2Body* Body() { return m_Body; }


	std::vector<KVector2>* Poly_Vertex()
	{
		return &m_MeshVec;
	}

	/************** RigidBase ****************/
	void Init_Component() override;
	void Update() override;


	/************** SetTrans ****************/
	
	void Rid_Pos(const KVector& _Value);
	void Rid_Rotate(const KVector& _Value);
	void Rid_Scale(const KVector& _Value);
	void Rid_Radius(const float& _Value);
	void Rid_Transform(const KVector& _Pos, const KVector& _Rotate, const KVector& _Scale);
	void Set_Transform()
	{
		Rid_Transform(m_Trans->Local_Pos(), m_Trans->Local_Rotate(), m_Trans->Local_Scale());
	}

	void Set_Type(const b2BodyType& _Value)
	{
		m_Body->SetType(_Value);

		if (_Value == b2BodyType::b2_staticBody)
		{
			MassData(KVector(100.0f, .2f, .0f));
			FigureData(KVector3(1.0f, .2f, .7f));
		}
	}
	b2BodyType Get_Type() const
	{
		return m_Body->GetType();
	}


	/************** MassData ****************/

	inline void Inertia(const float& _Value)
	{
		m_Body->GetMassData(m_MD);
		MassData(KVector(m_MD->mass, _Value, m_MD->center));
	}
	inline void Mass(const float& _Value)
	{
		m_Body->GetMassData(m_MD);
		MassData(KVector(_Value, m_MD->I, m_MD->center));
	}
	inline void Center(const KVector2& _Value)
	{
		m_Body->GetMassData(m_MD);
		MassData(KVector(m_MD->mass, m_MD->I, _Value));
	}

	// Mass, Inertia, Center
	void MassData(const KVector& _Value);
	KVector MassData() const { return KVector(m_MD->mass, m_MD->I, m_MD->center); }

	/************** FigureData ****************/
	// Density, Friction, Restitude
	void FigureData(const KVector3& _Value);
	KVector3 FigureData () const { return KVector3(m_FD->density, m_FD->friction, m_FD->restitution); }



	/***************** PhysicsData *******************/
	float CollisionForce();
	void Impulse(const KVector2& _Impulse);
	void AngularImpulse(const float& _Impulse);

	/***************** PolyData *******************/
	std::vector<KPtr<TheOne>>* Vertex_Data();
	std::vector<KVector2>* Mesh_Data();
	bool IsChangeVertex();

	/***************** Save & Load *******************/
	bool load(const wchar_t* _Name);
	bool save(const wchar_t* _Name);


	void Reset_Impulse()
	{
		Impulse(KVector2::Zero);
		AngularImpulse(.0f);
	}

private:
	// 현재 가지고 있는 버텍스 리스트로 폴리를 구성
	void Set_Poly();
	void Sort_Vertex();

	KPtr<TheOne> Create_Vertex(const KVector2& _Value);
	void Push_Contact(b2Body* _Value);


public:
	void ColDown();
	void ColUp();

	void Insert_VertexList(std::vector<KVector2> _Value);
	void Set_VertexList(std::vector<KVector2>* _Value);
	void Create_Mesh(const wchar_t* _Name);
	void Active_Vertex(const bool& _Value);
	void Insert_Vertex(const KVector2& _Value);
	void Delete_Vertex(KPtr<TheOne> _Value);

	std::list<KPtr<KRigid_2D>> Contact_List();


public:
	KRigid_2D();
	~KRigid_2D();
};

