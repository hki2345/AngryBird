#pragma once
#include "Shader.h"
#include <vector>

class Vertex_Shader : public Shader
{
private:
	ID3D11VertexShader* m_Shader;

	// ��ǲ��ų ���ؽ� �����͸� ������ �ִ� ����
	// 
	std::vector<D3D11_INPUT_ELEMENT_DESC>	m_vec_InputLayoutData;
	UINT m_Offset;
	ID3D11InputLayout*						m_InputLayout;

public:
	bool Load(const char* _Func, UINT _VH = 5, UINT _VL = 0);
	void Update() override;

	//D3D11_INPUT_ELEMENT_DESC �� �߰��Ǿ���� ����-> ���ؽ� ���̴��� �̷��� �����ؾ��Ѵ�.
	// �ֳ�? �ƴ� �̷��� �����ϱ� ����
	//LPCSTR SemanticName;
	//UINT SemanticIndex;
	//DXGI_FORMAT Format;
	//UINT InputSlot;
	//UINT AlignedByteOffset;
	//D3D11_INPUT_CLASSIFICATION InputSlotClass;
	//UINT InstanceDataStepRate;
	bool Add_Layout(LPCSTR _SName, UINT _SI, DXGI_FORMAT _Fm, UINT _IS, 
		D3D11_INPUT_CLASSIFICATION _ISC = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, UINT _IDSR = 0);
	bool Create_LayOut();
	void Set_LayOut();


public:
	Vertex_Shader();
	~Vertex_Shader();
};

