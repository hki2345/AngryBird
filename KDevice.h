#pragma once
#include "DirectXHeader.h"
#include "Mother_KWindow.h"
#include "SmartPtr.h"
#include "Shader.h"
#include "KMacro.h"

#include <unordered_map>


// ���������� �׷���ī���� ���� �Ϻθ� �������� ���̴�.
// ���⼭ �� ������ ��� ���� Window, fmod���� ������ �������� �Ͱ� �ϸƻ� ���Ѵ�.
// ������ ������ ������ ���� -> ������ -> �ٸ� ����� ������ ������ -> ����
// ����̽��� �ش� ������ �ҷ������� �����츦 �˾ƾ��Ѵ�.
class KDevice : public Mother_KWindow
{
public:
	friend KWindow;

public:
	// ������� �������� �� ���̳�///
	// �ո鸸 �޸鸸
	// ���� ���̾� -> 3D MAX �����ϸ� ��
	enum RASTER_TPYE
	{
		RT_FRONT,
		RT_BACK,
		RT_ALL,
		RT_WIRE,
		RT_END,
	};

private:
	ID3D11Device*				m_pDevice;
	ID3D11DeviceContext*		m_pContext;
	ID3D11RenderTargetView*		m_pTargetView;
	ID3D11Texture2D*			m_pTexture2D;
	ID3D11DepthStencilView*		m_pDepthStencilView;
	IDXGISwapChain*				m_pSwapChain;
	UINT						m_iMSLv;
	KColor						m_Color;
	bool						m_bInit;

	// NUMCOLORS �÷��� ���߿� �ϴ� �ɷ� ����
	ID3D11RasterizerState*		m_ArrRs[(UINT)RASTER_TPYE::RT_END];

public:
	// ���̷�Ʈ �ʱ�ȭ�� ������ �ؾ� �ϴ� ��찡 �����. -> �ʱ�ȭ�� �ƴµ�
	// ��üȭ�� ���� ƨ��ų� alt +tab�� ���� ����ȭ������ �������� ��쿡��
	// ����̽��� �Ҿ���� ���� �ֱ� ������ �̷��� ������ �Ѵ�.
	bool& Is_Init()  { return m_bInit; }
	bool Init();

	ID3D11Device*				device() { return m_pDevice; }
	ID3D11DeviceContext*		context() { return m_pContext; }

	void reset_context();

	/******************************** ��� ���� ************************************/
public:
	class Const_Buffer : public SmartPtr
	{
	public:
		D3D11_BUFFER_DESC	tDesc;
		ID3D11Buffer*		p_ConstBuffer; // ����� ��� ���� -> D11���� ���̴����� ���� ���۵�����
											// ��� ��� �ڷ������� ����ȴ�
		UINT				iReg;

		~Const_Buffer()
		{
			if (nullptr != p_ConstBuffer) { p_ConstBuffer->Release(); }
		}
	};

private:
	std::unordered_map<std::wstring, KPtr<Const_Buffer>> m_Map_ConstBuffer;

public:
	template<typename BUFTYPE>
	bool Create_ConstBuf(const wchar_t* _Name, D3D11_USAGE _eUsage, UINT _iReg)
	{
		Const_Buffer* NewBuf = new Const_Buffer();

		NewBuf->tDesc.ByteWidth = sizeof(BUFTYPE);
		NewBuf->tDesc.Usage = _eUsage;
		NewBuf->tDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		if (NewBuf->tDesc.Usage == D3D11_USAGE_DYNAMIC)
		{
			NewBuf->tDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
		}

		if (S_OK != m_pDevice->CreateBuffer(&NewBuf->tDesc, nullptr, &(NewBuf->p_ConstBuffer)))
		{
			delete NewBuf;
			return false;
		}

		NewBuf->iReg = _iReg;

		m_Map_ConstBuffer.insert(std::unordered_map<std::wstring, KPtr<Const_Buffer>>::value_type(_Name, NewBuf));

		return true;
	}

	template<typename BUFTYPE>
	void Set_ConstBuffer(const wchar_t* _Name, const BUFTYPE& _Data, Shader::SHADER_TYPE _eType)
	{
		KPtr<Const_Buffer> Buf = Find_ConstBuffer(_Name);

		if (nullptr == Buf && Buf->tDesc.ByteWidth != sizeof(BUFTYPE))
		{
			return;
		}

		// ū �����͸� �ѹ��� �ѱ���� �ϸ� ������.
		D3D11_MAPPED_SUBRESOURCE tSub = {};
		m_pContext->Map(Buf->p_ConstBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &tSub);
		memcpy(tSub.pData, &_Data, sizeof(BUFTYPE));
		m_pContext->Unmap(Buf->p_ConstBuffer, 0);

		switch (_eType)
		{
		case Shader::ST_NONE:
			KASSERT(true);
			break;
		case Shader::ST_VS:
			m_pContext->VSSetConstantBuffers(Buf->iReg, 1, &Buf->p_ConstBuffer);
			break;
		case Shader::ST_PS:
			m_pContext->PSSetConstantBuffers(Buf->iReg, 1, &Buf->p_ConstBuffer);
			break;
		default:
			break;
		}
	}

	KPtr<Const_Buffer> Find_ConstBuffer(const wchar_t* _Name);

private:
	bool Create_SwapChain();
	bool Create_View();
	bool Create_ViewPort();
	bool Create_RasterizeState();
	bool Init_DefaultData();

	void Clear_Target();
	void Present();

	void Release();

public:
	KDevice(KWindow* _Window);
	~KDevice();
};

