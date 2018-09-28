#include "Shader.h"



Shader::Shader() : m_Type(SHADER_TYPE::ST_NONE)
{
}


Shader::~Shader()
{
	// �� �������� �Լ��� ���� �̰͵��� ����Ʈ �����ͷ� �����ִٴ� ���� �� �� �ִ�.
	// ���� ���⼭ ����Ʈ ���� ������ ���� ��
	if (nullptr != m_Blob) { m_Blob->Release(); }
	if (nullptr != m_Blob_Error) { m_Blob_Error->Release(); }
}
