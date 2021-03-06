#include "Vertex_Shader.h"
#include "Core_Class.h"
#include "KMacro.h"


Vertex_Shader::Vertex_Shader()
{
	m_Type = SHADER_TYPE::ST_VS;
}


Vertex_Shader::~Vertex_Shader()
{
	if (nullptr != m_Shader) { m_Shader->Release(); }
	if (nullptr != m_InputLayout) { m_InputLayout->Release(); }
}



bool Vertex_Shader::Load(const char* _Func, UINT _VH, UINT _VL)
{
	UINT iFlag = 0;

	// 11戚窮 10戚窮 促杷 旭精 室戚希 巨獄益稽 吉陥. -> 蕉段拭 11精 赤走亀 省製
#ifdef  _DEBUG
	iFlag = D3D10_SHADER_DEBUG;
#endif //  _DEBUG

	char tBuffer[256] = {};
	sprintf_s(tBuffer, "vs_%d_%d", _VH, _VL);

	std::wstring ss = path();

	// 陳督析 幻 背左澗 依戚陥 しししししし
	if (S_OK != D3DCompileFromFile(path(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		_Func, tBuffer, iFlag, 0, &m_Blob, &m_Blob_Error))
	{
		return false;
	}


	// 背雁 巨郊戚什拭 獄努什室戚希研 室特
	if (S_OK != Core_Class::device()->CreateVertexShader(
		m_Blob->GetBufferPointer(),
		m_Blob->GetBufferSize(),
		nullptr, &m_Shader))
	{
		return false;
	}

	return true;
}

void Vertex_Shader::Update()
{
	// 食奄辞澗 傾戚焼数聖 宜鍵陥.
	Core_Class::device_context()->VSSetShader(m_Shader, 0, 0);
}


bool Vertex_Shader::Add_Layout(LPCSTR _SName, UINT _SI, DXGI_FORMAT _Fm, UINT _IS, 
	D3D11_INPUT_CLASSIFICATION _ISC, UINT _IDSR)
{
	D3D11_INPUT_ELEMENT_DESC NewLayout = D3D11_INPUT_ELEMENT_DESC();

	if (_IS >= D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT)
	{
		return false;
	}

	NewLayout.SemanticName = _SName;
	NewLayout.SemanticIndex = _SI;
	NewLayout.Format = _Fm;
	NewLayout.InputSlot = _IS;
	NewLayout.InputSlotClass = _ISC;
	NewLayout.InstanceDataStepRate = _IDSR;
	NewLayout.AlignedByteOffset = m_Offset;

	m_Offset += VertShaderFormat::size_Formet(_Fm);
	m_vec_InputLayoutData.push_back(NewLayout);

	return true;
}

bool Vertex_Shader::Create_LayOut()
{
	KASSERT(nullptr == m_Shader);
	if (nullptr == m_Shader)
	{
		return false;
	}

	// 
	if (S_OK != Core_Class::device()->CreateInputLayout(
		&m_vec_InputLayoutData[0], (UINT)m_vec_InputLayoutData.size(),
		m_Blob->GetBufferPointer(), m_Blob->GetBufferSize(), &m_InputLayout))
	{
		return false;
	}

	return true;
}

void Vertex_Shader::Set_LayOut()
{
	Core_Class::device_context()->IASetInputLayout(m_InputLayout);
}