#include "Renderer.h"
#include "KMacro.h"
#include "ResourceManager.h"
#include "State.h"


Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

bool Renderer::Init(int _Order /*= 0*/)
{
	m_Order = _Order;
	state()->this_RenderManager.Insert_Renderer(this, _Order);
	return true;
}

bool Renderer::Set_Mesh(const wchar_t* _Name)
{
	m_Mesh = ResourceManager<Mesh>::Find(_Name);
	KASSERT(nullptr == m_Mesh); 

	if (nullptr == m_Mesh)
	{
		return false;
	}

	return true;
}
bool Renderer::Set_Mesh()
{
	m_Mesh = ResourceManager<Mesh>::Find(name());
	KASSERT(nullptr == m_Mesh);

	if (nullptr == m_Mesh)
	{
		return false;
	}

	return true;
}


bool Renderer::Set_Material(const wchar_t* _Name)
{
	m_Material = ResourceManager<Material>::Find(_Name);
	KASSERT(nullptr == m_Material);

	if (nullptr == m_Material)
	{
		return false;
	}

	return true;
}