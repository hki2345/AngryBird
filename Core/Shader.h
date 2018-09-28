#pragma once
#include "Resource.h"
#include "DirectXHeader.h"

class Shader : public Resource
{
public:
	enum SHADER_TYPE
	{
		ST_NONE,
		ST_VS,
		ST_PS,
	};
	SHADER_TYPE& type() { return m_Type; }

protected:
	SHADER_TYPE m_Type;

	// ���̴� �ڵ带 ������ ������ ������ "�ڵ�"�� ����Ʈ ���
	// ���̴� �ڵ带 ������ ������ ������ "����"�� ����Ʈ ���
	ID3DBlob* m_Blob;
	ID3DBlob* m_Blob_Error;

private:
	virtual void Update() = 0;

public:
	Shader();
	~Shader();
};

