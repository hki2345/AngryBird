#pragma once
#include "Resource.h"
#include "Vertex_Shader.h"
#include "Pixel_Shader.h"
#include "Blend.h"


class Material : public Resource
{
public:
	KPtr<Vertex_Shader> m_Vertex_Shader;
	KPtr<Pixel_Shader> m_Pixel_Shader;
	KPtr<Blend>			m_Blend;

public:
	bool Set_VertexShader(const wchar_t* _Name);
	bool Set_PixelShader(const wchar_t* _Name);
	bool Set_Blend(const wchar_t* _Name);


	bool Create();
	void Update();

public:
	Material();
	~Material();
};

