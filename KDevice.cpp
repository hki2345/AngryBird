#include "KDevice.h"
#include "KWindow.h"
#include "Core_Class.h"
#include "Pixel_Shader.h"
#include "Stl_Assistor.h"

#include "DirectXHeader_DE.h"
#include "ResourceManager.h"
#include "Mesh.h"
#include "Material.h"
#include "Blend.h"

#include "KMath.h"
#include "KFont.h"



KDevice::KDevice(KWindow* _Window) : Mother_KWindow(_Window),
m_pDevice(nullptr),
m_pContext(nullptr),
m_pTargetView(nullptr),
m_pTexture2D(nullptr),
m_pDepthStencilView(nullptr),
m_pSwapChain(nullptr),
m_bInit(false),
m_Color(.5f, .5f, .5f, 1.0f)
{
}

KDevice::~KDevice()
{
	Release();
}
bool KDevice::Init()
{
	m_bInit = false;
	int iFlag = 0;

#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif

	// � �������� ����̽��� ������ ���̳�-- �ٵ� �ڵ��������ִϱ� �� �װ� ����.
	// �뵵�� ���� ������ ������� ã�� ���̴�.
	D3D_FEATURE_LEVEL eLv = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;

	// D3D_DRIVER_TYPE_HARDWARE ��� �ߴٸ� 3D �ܺ� 3D��ġ�� ã�´�. 
	// -> ��ī�� ã�´ٴ� ��
	// ����Ʈ�� ���� CPU�� ���� ó�� - ������ �ص� �̳����� �� ���� �ʳ� ��������

	//  
	if (S_OK != D3D11CreateDevice(
		/*Ư����Ȳ*/nullptr, /*�ܺ���ġ*/D3D_DRIVER_TYPE_HARDWARE
		, /*�ܺθ��*/nullptr, /*Flag*/ iFlag, 
		/*??*/nullptr,/*??*/ 0,/*SDK ����*/ D3D11_SDK_VERSION, 
		/*�޾ƿ� ��ġ*/&m_pDevice, /*�޾ƿ� ���� ����*/&eLv, 
		/*�޾ƿ� Context - ������ ���߿��Ѵ�µ� ���������� ��� ����*/&m_pContext))
	{
		Release();
		return false;
	}

	// ��Ƽ ���ø� ������ üũ�Ѵ�.
	// ��ܰ�� �ε巴�� �� ���̳� -> �� �ܰ�� Ȯ���Ų �̹����� �ռ��� ���̳�
	// ���⼭�� 4�ܰ�� �Ͽ���.
	m_pDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m_iMSLv);

	// ��ȯ���� 0�̸� ���� �߻��� ���� - �翬 �ȵǾ�¡
	if (0 == m_iMSLv) { Release(); return false; }

	if (false == Create_SwapChain()) { Release(); return false; }
	if (false == Create_View()) { Release(); return false; }
	if (false == Create_ViewPort()) { Release(); return false; }
	if (false == Create_RasterizeState()) { Release(); return false; }

	m_bInit = true;
	return true;
}


bool KDevice::Create_SwapChain()
{
	// �� �� ���� ����ü��. -> �̰͵��� ��� �ʱ�ȭ���־�� �Ѵꤾ������
	// ���� �׳� �Ǵ� �� �ƴϰ�... ��� Ÿ�� Ÿ�� Ÿ�� ���� �ʱ�ȭ �ϴ� ��
	/*DXGI_MODE_DESC BufferDesc;
	DXGI_SAMPLE_DESC SampleDesc;
	DXGI_USAGE BufferUsage;
	UINT BufferCount;
	HWND OutputWindow;
	BOOL Windowed;
	DXGI_SWAP_EFFECT SwapEffect;
	UINT Flags;*/
	DXGI_SWAP_CHAIN_DESC m_Decs = {};

	// ����� ũ��
	m_Decs.BufferDesc.Width = (UINT)window()->width();
	m_Decs.BufferDesc.Height = (UINT)window()->heigth();

	// ����� �ֻ��� + ����� ����
	m_Decs.BufferDesc.RefreshRate.Numerator = 60;
	m_Decs.BufferDesc.RefreshRate.Denominator = 1;

	// ������ �Ȼ� - ��� �� �������� ������ �Ȼ��� ä��ڴ�.
	m_Decs.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// ��ĵ ���� ������ ���� - �ָ� ����
	m_Decs.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	m_Decs.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// ������ �뵵 - ȭ�� ����
	m_Decs.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;


	// ���ø� ���� - �̰� ���� �ܰ迡�� �� �ܰ�� �����ϴ��� �޾ƿ� ���̴�.
	m_Decs.SampleDesc.Count = m_iMSLv;
	m_Decs.SampleDesc.Quality = m_iMSLv - 1;


	// ������ ����
	m_Decs.OutputWindow = window()->KWnd();

	// �����Ҷ� ����Ʈ- �츰 �����.
	m_Decs.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// ���� ����
	m_Decs.BufferCount = 1;

	// ��üȭ�� ���� - �ش� �������� �켱���� __ ��üȭ���� �ֿ켱
	m_Decs.Windowed = !window()->Is_Full();


	/*********** ���� ���� *************/ // �İ�ü�� ������������
	IDXGIDevice* p_Device = nullptr;
	IDXGIAdapter* p_Adapter = nullptr;
	IDXGIFactory* p_Factory = nullptr;

	m_pDevice->QueryInterface(__uuidof(p_Device), (void**)&p_Device);
	if (nullptr == p_Device) { return false; }

	p_Device->GetParent(__uuidof(IDXGIAdapter), (void**)&p_Adapter);
	if (nullptr == p_Adapter) { return false; }

	p_Adapter->GetParent(__uuidof(IDXGIFactory), (void**)&p_Factory);
	if (nullptr == p_Factory) { return false; }

	// ���⼭ ����ü���� �޾ƿ��� �����̴�.
	if (nullptr != p_Factory && S_OK != p_Factory->CreateSwapChain(m_pDevice, &m_Decs, &m_pSwapChain))
	{
		return false;
	}

	// �� �Ķ�� �ʿ䰡 ���� ������ ����
	p_Factory->Release();
	p_Adapter->Release();
	p_Device->Release();

	return true;
}

// ����ü�ο� ���� �ؽ�ó�� ���⼭ �����.
// ��ȭ���� ����ٴ� �����̴�.
bool KDevice::Create_View()
{
	ID3D11Texture2D* p_BackBuffer = nullptr;
	if(S_OK != m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&p_BackBuffer))
	{
		return false;
	}

	// Ÿ�ٺ並 �δܰ踦 ���ļ� �����´�.�̷���...
	if (S_OK != m_pDevice->CreateRenderTargetView(p_BackBuffer, 0, &m_pTargetView))
	{
		return false;
	}

	p_BackBuffer->Release();



	// �ؽ��� ���� ����
	D3D11_TEXTURE2D_DESC m_Decs = {};

	m_Decs.ArraySize = 1;

	// ���⼭ ������ ����� ȭ�鿡 �ݹۿ� �ȳ��´ٰ�..��������
	m_Decs.Width = (UINT)window()->width();
	m_Decs.Height = (UINT)window()->heigth();
	m_Decs.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	m_Decs.SampleDesc.Count = m_iMSLv;
	m_Decs.SampleDesc.Quality = m_iMSLv - 1;

	// �Ӹ� ����
	m_Decs.MipLevels = 1;

	m_Decs.Usage = D3D11_USAGE_DEFAULT;
	m_Decs.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	

	m_pDevice->CreateTexture2D(&m_Decs, 0, &m_pTexture2D);

	if (S_OK != m_pDevice->CreateDepthStencilView(m_pTexture2D, 0, &m_pDepthStencilView))
	{
		return false;
	}


	// ������ ������ ���ΰ� �����ִٴ� ... ���� �϶��
	m_pContext->OMSetRenderTargets(1, &m_pTargetView, m_pDepthStencilView);

	return true;
}

bool KDevice::Create_ViewPort()
{
	D3D11_VIEWPORT m_Decs = {};

	m_Decs.TopLeftX = 0;
	m_Decs.TopLeftY = 0;

	m_Decs.Width = (float)window()->width();
	m_Decs.Height = (float)window()->heigth();

	m_Decs.MinDepth = 0;
	m_Decs.MaxDepth = 1;

	m_pContext->RSSetViewports(1, &m_Decs);

	return true;
}

bool KDevice::Create_RasterizeState()
{
	D3D11_RASTERIZER_DESC m_Desc = {};

	m_Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	m_Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;

	if (S_OK != m_pDevice->CreateRasterizerState(&m_Desc, &m_ArrRs[(UINT)RASTER_TPYE::RT_FRONT]))
	{
		return false;
	}



	m_Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	m_Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;

	if (S_OK != m_pDevice->CreateRasterizerState(&m_Desc, &m_ArrRs[(UINT)RASTER_TPYE::RT_BACK]))
	{
		return false;
	}


	m_Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	m_Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;

	if (S_OK != m_pDevice->CreateRasterizerState(&m_Desc, &m_ArrRs[(UINT)RASTER_TPYE::RT_ALL]))
	{
		return false;
	}



	m_Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
	m_Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;

	if (S_OK != m_pDevice->CreateRasterizerState(&m_Desc, &m_ArrRs[(UINT)RASTER_TPYE::RT_WIRE]))
	{
		return false;
	}

	m_pContext->RSSetState(m_ArrRs[(UINT)RASTER_TPYE::RT_ALL]); 

	return true;
}


// ������ ���ִ� �Լ�
void KDevice::Clear_Target()
{
	m_pContext->ClearRenderTargetView(m_pTargetView, m_Color.s);
	m_pContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
}

// ����ִ� �Լ�
void KDevice::Present()
{
	m_pSwapChain->Present(0, 0);
}

void KDevice::Release()
{
	for (size_t i = 0; i < RASTER_TPYE::RT_END; i++)
	{
		if (nullptr != m_ArrRs[i])
		{
			m_ArrRs[i]->Release();
		}
	}

	if (nullptr != m_pDepthStencilView) { m_pDepthStencilView->Release(); }
	if (nullptr != m_pTargetView) { m_pTargetView->Release(); }
	if (nullptr != m_pSwapChain) { m_pSwapChain->Release(); }
	if (nullptr != m_pTexture2D) { m_pTexture2D->Release(); }
	if (nullptr != m_pDevice) { m_pDevice->Release(); }
	if (nullptr != m_pContext) { m_pContext->Release(); }
}

KPtr<KDevice::Const_Buffer> KDevice::Find_ConstBuffer(const wchar_t* _Name)
{
	return Map_Find<KPtr<KDevice::Const_Buffer>>(m_Map_ConstBuffer, _Name);
}


void KDevice::reset_context()
{
	m_pContext->VSSetShader(nullptr, nullptr, 0);
	m_pContext->HSSetShader(nullptr, nullptr, 0);
	m_pContext->GSSetShader(nullptr, nullptr, 0);
	m_pContext->CSSetShader(nullptr, nullptr, 0);
	m_pContext->PSSetShader(nullptr, nullptr, 0);
}