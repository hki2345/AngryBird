#pragma once
#include "DirectXHeader.h"
#include "Mother_KWindow.h"
#include "SmartPtr.h"
#include "Shader.h"
#include "KMacro.h"

#include <unordered_map>


// 본격적으로 그래픽카드의 권한 일부를 가져오는 놈이다.
// 여기서 이 구조는 어떻게 보면 Window, fmod에서 권한을 가져오는 것과 일맥상 통한다.
// 권한을 가져올 포인터 마련 -> 가져옴 -> 다른 연결된 포인터 가져옴 -> 적용
// 디바이스는 해당 권한을 불러오려는 윈도우를 알아야한다.
class KDevice : public Mother_KWindow
{
public:
	friend KWindow;

public:
	// 어떤식으로 보여지게 할 것이냐///
	// 앞면만 뒷면만
	// 모든면 와이어 -> 3D MAX 생각하면 됌
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

	// NUMCOLORS 컬러는 나중에 하는 걸로 ㅇㅇ
	ID3D11RasterizerState*		m_ArrRs[(UINT)RASTER_TPYE::RT_END];

public:
	// 다이렉트 초기화를 여러번 해야 하는 경우가 생긴다. -> 초기화가 됐는데
	// 전체화면 도중 튕기거나 alt +tab을 눌러 바탕화면으로 빠져나올 경우에도
	// 디바이스를 잃어버릴 수도 있기 때문에 이러한 설정을 한다.
	bool& Is_Init()  { return m_bInit; }
	bool Init();

	ID3D11Device*				device() { return m_pDevice; }
	ID3D11DeviceContext*		context() { return m_pContext; }

	void reset_context();

	/******************************** 상수 버퍼 ************************************/
public:
	class Const_Buffer : public SmartPtr
	{
	public:
		D3D11_BUFFER_DESC	tDesc;
		ID3D11Buffer*		p_ConstBuffer; // 요놈이 상수 버퍼 -> D11에선 쉐이더에서 쓰일 버퍼따위도
											// 모두 요놈 자료형으로 저장된당
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

		// 큰 데이터를 한번에 넘기려고 하면 느리다.
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

