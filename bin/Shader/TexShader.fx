// 상수버퍼는 b
// 텍스처는 t
// 샘플러는 s

cbuffer TransformBuffer : register(b1)
{
	matrix g_WVP;
}

cbuffer SHAKE_COLIR : register(b2)
{
	float4 CBColor;
}

Texture2D g_Tex_0 : register(t0);
SamplerState g_Sam_0 : register(s0);

// 버텍스 버퍼에 대한 정보를 정의하는 
// POSITION을 시맨틱이라고 하는데.
// 버텍스 쉐이더에서 이용할 것.
struct VTXTEX_INPUT
{
	float4 vPos : POSITION;
	float2 vUv : TEXCOORD;
};

// 버텍스 쉐이더에서 리턴할 구조체를 만든다.
// SV_가 붙게되면 cosnt를 붙여서 그래픽 적으로 이데이터에 대해서 더이상의
// 변형을 불가능하게 한다.
struct VTXTEX_OUTPUT
{
	float4 vPos : SV_POSITION;
	float2 vUv : TEXCOORD;
};

struct PS_OUTPUT
{
	float4 vCol : SV_Target;
};

VTXTEX_OUTPUT VS_Tex(VTXTEX_INPUT _iN)
{
	VTXTEX_OUTPUT outData = (VTXTEX_OUTPUT)0.f;

	outData.vPos = mul(_iN.vPos, g_WVP);
	outData.vUv = _iN.vUv;

	return outData;
}

PS_OUTPUT PS_Tex(VTXTEX_OUTPUT _in)
{
	float4 vCol = g_Tex_0.Sample(g_Sam_0, _in.vUv);
	
	// 흑백
	// vCol.rgb = (vCol.r + vCol.g + vCol.b) / 3.0f;

	//  색을 빼는 과정
	if (0 >= vCol.a)
	{
		//return과 비슷 -> 굳이 데이터를 연산한 필요가 없기에
		clip(-1);
	}

	PS_OUTPUT outData = (PS_OUTPUT)0.0f;
	outData.vCol = vCol * CBColor;

	// 색을 빼는 과정을 먼저한다.
	//if (0 >= outData.vCol.a)
	//{
	//	clip(-1);
	//}

	return outData;
}