#pragma once
#include "Independent_Trans.h"

#include "Mesh.h"
#include "Material.h"

class Renderer : public Independent_Trans
{
protected:
	int			m_Order;

	KPtr<Mesh>		m_Mesh;
	KPtr<Material>	m_Material;

public:
	int& order() { return m_Order; }
	bool Set_Mesh(const wchar_t* _Name);
	bool Set_Mesh();
	bool Set_Material(const wchar_t* _Name);

public:
	virtual bool Init(int _Order = 0);
	virtual void Render(const KMatrix& _VP) = 0;

public:
	Renderer();
	~Renderer();
};

