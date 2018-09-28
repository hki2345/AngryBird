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

	// 쉐이더 코드를 컴파일 했을때 나오는 "코드"의 바이트 행렬
	// 쉐이더 코드를 컴파일 했을때 나오는 "에러"의 바이트 행렬
	ID3DBlob* m_Blob;
	ID3DBlob* m_Blob_Error;

private:
	virtual void Update() = 0;

public:
	Shader();
	~Shader();
};

