#include "Shader.h"



Shader::Shader() : m_Type(SHADER_TYPE::ST_NONE)
{
}


Shader::~Shader()
{
	// 이 포인터의 함수를 보면 이것들이 스마트 포인터로 엮여있다는 것을 알 수 있다.
	// 물론 여기서 스마트 폰은 지들이 만든 거
	if (nullptr != m_Blob) { m_Blob->Release(); }
	if (nullptr != m_Blob_Error) { m_Blob_Error->Release(); }
}
