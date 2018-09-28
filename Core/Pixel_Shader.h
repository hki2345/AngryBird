#pragma once
#include "Shader.h"

// �ȼ��� ���ؽ��� ���� �и��Ǿ� �ִµ�
// ���߿� ���� �ҋ� ������ �϶��
class Pixel_Shader :	public Shader
{
private:
	ID3D11PixelShader* m_Shader;

public:
	// �Լ� �̸� -> char�� �޴´�. GPU���� \
	// �ڿ� �ΰ��� UINT�� ���� ����
	bool Load(const char* _Func, UINT _VH = 5, UINT _VL = 0);
	void Update() override;


public:
	Pixel_Shader();
	~Pixel_Shader();
};

