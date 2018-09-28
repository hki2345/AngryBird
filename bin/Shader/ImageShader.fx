// 상수버퍼는 b
// 텍스처는 t
// 샘플러는 s

cbuffer TransformBuffer : register(b1)
{
	matrix g_WVP;
}

Texture2D g_Tex_0 : register(t0);
SamplerState g_Sam_0 : register(s0);

struct VTXTEX_INPUT
{
	float4 vPos : POSITION;
	float2 vUv : TEXCOORD;
};

struct VTXTEX_OUTPUT
{
	float4 vPos : SV_POSITION;
	float2 vUv : TEXCOORD;
};

struct PS_OUTPUT
{
	float4 vCol : SV_Target;
};


VTXTEX_OUTPUT VS_Img(VTXTEX_INPUT _iN)
{
	VTXTEX_OUTPUT outData = (VTXTEX_OUTPUT)0.f;

	outData.vPos = mul(_iN.vPos, g_WVP);
	outData.vUv = _iN.vUv;

	return outData;
}

cbuffer Border : register(b3)
{
	float4 CBColor;
	float2 m_PixelPer;
	float2 m_Border;
}

cbuffer ImageUv : register(b2)
{
	float2 vStart = float2(0.0f, 0.0f);
	float2 vSize = float2(1.0f, 1.0f);
};

PS_OUTPUT PS_Img(VTXTEX_OUTPUT _in)
{
	float4 vCol = g_Tex_0.Sample(g_Sam_0, 
		float2(vStart.x + (vSize.x * _in.vUv.x)
			, vStart.y + (vSize.y * _in.vUv.y)));

	float4 tempRCol = g_Tex_0.Sample(g_Sam_0,
		float2(
			vStart.x + (vSize.x  * _in.vUv.x) + (m_PixelPer.x * m_Border.x),
			vStart.y + (vSize.y  * _in.vUv.y)));

	float4 tempLCol = g_Tex_0.Sample(g_Sam_0,
		float2(
			vStart.x + (vSize.x  * _in.vUv.x) - (m_PixelPer.x * m_Border.x),
			vStart.y + (vSize.y  * _in.vUv.y)));

	float4 tempTCol = g_Tex_0.Sample(g_Sam_0,
		float2(
			vStart.x + (vSize.x  * _in.vUv.x),
			vStart.y + (vSize.y  * _in.vUv.y) + (m_PixelPer.y * m_Border.y)));

	float4 tempBCol = g_Tex_0.Sample(g_Sam_0,
		float2(
			vStart.x + (vSize.x  * _in.vUv.x) ,
			vStart.y + (vSize.y  * _in.vUv.y) - (m_PixelPer.y * m_Border.y)));

	float4 tempRTCol = g_Tex_0.Sample(g_Sam_0,
		float2(
			vStart.x + (vSize.x  * _in.vUv.x) + (m_PixelPer.x * m_Border.x),
			vStart.y + (vSize.y  * _in.vUv.y) + (m_PixelPer.y * m_Border.y)));

	float4 tempLBCol = g_Tex_0.Sample(g_Sam_0,
		float2(
			vStart.x + (vSize.x  * _in.vUv.x) - (m_PixelPer.x * m_Border.x),
			vStart.y + (vSize.y  * _in.vUv.y) - (m_PixelPer.y * m_Border.y)));

	// 1차 검열 보더를 더한 사이즈 만큼  바탕을 깔고 - 아웃 보더를 넣으려면
	// 메트릭스가 2개 필요하다 -> 보더의 사이즈 * 2만큼 키운 바탕 이미지에
	// 현재이미지를 씌우는 식
	/*float4 tempCol = g_Tex_0.Sample(g_Sam_0,
		float2(
			vStart.x + (vSize.x  * _in.vUv.x) + (m_PixelPer.x * m_Border.x),
			vStart.y + (vSize.y  * _in.vUv.y) + (m_PixelPer.y * m_Border.y)));

	if (0 < tempCol.a)
	{
		outData.vCol = CBColor;
	}*/

	// vCol = CBColor;
	
	// 샘플러를 while에 넣으면 안된다. 
	//	tempCol = g_Tex_0.Sample(g_Sam_0, tempX, vStart.y + (vSize.y * _in.vUv.y));
	/*while (tempX > vStart.x + (vSize.x * _in.vUv.x) + (m_PixelPer.x * m_Border.x))
	{
		if (0 < vCol.a)
		{
			break;
		}

		if ((0 >= vCol.a && 0 < tempCol.a))
		{
			outData.vCol = CBColor;	
			break;
		}

		tempX += m_PixelPer.x;
	}	
*/
	// 그 위에 그림을 그리는 식
	PS_OUTPUT outData = (PS_OUTPUT)0.0f;

	if (0 < vCol.a)
	{
		if (0 >= tempRCol.a || 0 >= tempLCol.a ||
			0 >= tempTCol.a || 0 >= tempBCol.a ||
			0 >= tempRTCol.a || 0 >= tempLBCol.a )
		{
			outData.vCol = CBColor;
			return outData;
		}
	}

	else if (0 >= vCol.a)
	{
		clip(-1);
	}

	outData.vCol = vCol/* * CBColor*/;

	return outData;
}