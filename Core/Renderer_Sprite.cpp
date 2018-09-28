#include "Renderer_Sprite.h"
#include "DirectXHeader_DE.h"
#include "KMacro.h"
#include "KWindow.h"
#include "ResourceManager.h"
#include "Shader.h"
#include "Blend.h"

#include "Texture.h"
#include "Sampler.h"


Renderer_Sprite::Renderer_Sprite() :
	m_Color(1.0f, 1.0f, 1.0f,1.0f),
	m_SplitIndex(0)
{
}


Renderer_Sprite::~Renderer_Sprite()
{
}

bool Renderer_Sprite::Init(int _Order)
{
	Renderer::Init(_Order);
	if (false == Set_Material(L"IMGMAT") || false == Set_Mesh(L"TEXMESH"))
	{
		return false;
	}

	return true;
}

bool Renderer_Sprite::Init(const wchar_t* _Name, int _Order)
{
	image(_Name);
	if (nullptr == m_Image)
	{
		return false;
	}

	if (false == Init(_Order))
	{
		return false;
	}

	return true;
}

void Renderer_Sprite::Render(const KMatrix& _VP)
{
	if (nullptr == m_Image)
	{
		return;
	}

	KASSERT(nullptr == m_Trans);
	if (nullptr == m_Trans)
	{
		return;
	}

	if (false == one()->is_Active())
	{
		return;
	}
	
	// �θ����� ������� ���Ǿ�� �Ѵ�.
	Indepen_Update();

	m_Border = 0.0f;
	m_Color = KColor::Green;

	// �ѱ���� �������� - ���ؾ���� �Ѵ�.
	KBorder NewBorder;
	NewBorder.m_Color = this->m_Color;
	NewBorder.m_UvPerPixel = KVector2(1.0f / m_Image->size().x, 1.0f / m_Image->size().y );
	NewBorder.m_Border = this->m_Border;



	// ����̽��� ���� �Ѿ�� ����
	window()->device().Set_ConstBuffer<KMatrix>(L"TRANS", 
		(independent_Matrix() * _VP).TransPose_Referance(), Shader::SHADER_TYPE::ST_VS);
	window()->device().Set_ConstBuffer<KBorder>(L"BORDER", NewBorder, Shader::SHADER_TYPE::ST_PS);
	window()->device().Set_ConstBuffer<KVector4>(L"MULTI", m_Image->uv(m_SplitIndex), Shader::SHADER_TYPE::ST_PS);
	

	m_Material->Update();
	m_Mesh->Update();

	m_Image->sampler()->Update();
	m_Image->texture()->Update();
	m_Mesh->Render();
}

void Renderer_Sprite::image(const wchar_t* _Name) 
{
	// �������� ���� ���ϰ� �Ϸ��� �Ϻη� null �� �־� m_Image�� �����
	if (nullptr == _Name)
	{
		m_Image = nullptr;
		return;
	}

	m_Image = ResourceManager<KImage>::Find(_Name);
	KASSERT(nullptr == m_Image);
}


KVector2 Renderer_Sprite::set_image_size()
{
	if (nullptr == m_Image )
	{
		return KVector2::Zero;
	}

	KVector2 NewScale = m_Image->texture()->size();
	inde_scale(NewScale);

	return NewScale;
}

KVector2 Renderer_Sprite::image_size()
{
	return m_Image->texture()->size();
}