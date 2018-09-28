#include "DebugManager.h"
#include "Core_Class.h"
#include "KWindow.h"
#include "Mesh.h"
#include "Material.h"
#include "ResourceManager.h"
#include "DirectXHeader_DE.h"
#include "KFont.h"

#include "TransPosition.h"
#include "Renderer_Sprite.h"

bool DebugManager::m_Debug = true;

DebugManager::DebugManager()
{
}


DebugManager::~DebugManager()
{
}

void DebugManager::draw_rect(const KVector2& _Pos, const KVector2& _Size, const KColor& _Color, const float& _Border)
{
	draw_rect(KRect(_Pos, _Size), _Color, _Border);
}

void DebugManager:: draw_rect(const KRect& _Rect, const KColor& _Color, const float& _Border)
{
	if (false == m_Debug)
	{
		return;
	}

	if ( nullptr == Core_Class::Main_Window().this_StateManager.state()->camera())
	{
		return;
	}

	KVector2 m_Size = Core_Class::Main_Window().this_StateManager.state()->camera()->screen_size();

	KMatrix m_Scale;
	KMatrix m_Pos;
	KMatrix m_VP = Core_Class::Main_Window().this_StateManager.state()->camera()->View_Proj();

	m_Scale.Scale(KVector(_Rect.m_Size.x, _Rect.m_Size.y, 0.1f));
	m_Pos.Translation(KVector(
		_Rect.m_Pos.x - Core_Class::main_state()->camera()->one()->Local_Pos().x,
		_Rect.m_Pos.y - Core_Class::main_state()->camera()->one()->Local_Pos().y, 10.1f));

	
	KPtr<Material> m_Mat = ResourceManager<Material>::Find(L"LINEMAT");
	KPtr<Mesh> m_Mesh = ResourceManager<Mesh>::Find(L"LINEMESH");
	KBorder NewBorder;

	NewBorder.m_Color = _Color;
	NewBorder.m_UvPerPixel = KVector2(1 / _Rect.m_Size.x, 1 / _Rect.m_Size.y);
	NewBorder.m_Border = _Border;

	Core_Class::MainDevice().Set_ConstBuffer<KMatrix>(L"TRANS", (m_Scale * m_Pos * m_VP).TransPose_Referance(), Shader::ST_VS);
	Core_Class::MainDevice().Set_ConstBuffer<KBorder>(L"BORDER", NewBorder, Shader::SHADER_TYPE::ST_PS);

	m_Mat->Update();
	m_Mesh->Update();
	m_Mesh->Render();
}

void DebugManager::draw_rect(TransPosition* _One, const COLL_TYPE& _type,
	const float& _Border, const KColor& _Color /*= { .0f, 1.0f, .0f, 1.0f }*/)
{
	if (false == m_Debug)
	{
		return;
	}

	// 이거 다 멤버변수로 갈 것
	// 여태 다이렉트로 그래픽 뽑는 모든 과정이다 ㅋㅋ
	KMatrix m_Scale;
	KMatrix m_RotateX;
	KMatrix m_RotateY;
	KMatrix m_RotateZ;
	KMatrix m_Rotate;
	KMatrix m_Pos;

	KMatrix m_VP = Core_Class::Main_Window().this_StateManager.state()->camera()->View_Proj();
	
	// 카메라가 투영할 수 있는 가장 가까운 거리로 z를 잡았다. -> 일단 제일 위에 보이게 하려고
	// 허나 이 z좌표가 같아질 경우 안됌 -> 임시방편
	KVector Pos = _One->Local_Pos();
	Pos.z = .3f;
	m_Pos.Translation(Pos);
	m_RotateX.Rotate_X(_One->Local_Rotate().x);
	m_RotateY.Rotate_Y(_One->Local_Rotate().y);
	m_RotateZ.Rotate_Z(_One->Local_Rotate().z);
	m_Rotate = m_RotateX * m_RotateY * m_RotateZ;

	KPtr<Mesh> newMesh;
	KPtr<Material> newMat = ResourceManager<Material>::Find(L"LINEMAT");

	KBorder NewBorder;
	NewBorder.m_Border.y = _Border;

	switch (_type)
	{
	case COLL_TYPE::COL_RECT2D:
		m_Scale.Scale(KVector(_One->Local_Scale()));
		newMesh = ResourceManager<Mesh>::Find(L"LINEMESH");

		NewBorder.m_Border.x = 1;
		NewBorder.m_Color = _Color;
		NewBorder.m_UvPerPixel = KVector2( 1 / _One->Local_Scale().x, 1 / _One->Local_Scale().y) * .5f;
		break;

	case COLL_TYPE::COL_CIRCLE2D:
		m_Scale.Scale(KVector(_One->Local_Scale().x * .5f, _One->Local_Scale().y * .5f));
		newMesh = ResourceManager<Mesh>::Find(L"LINECIRCLEMESH");

		NewBorder.m_Border.x = 2;
		NewBorder.m_Color = _Color;
		NewBorder.m_UvPerPixel = KVector2(1 / _One->Local_Scale().x, 1 / _One->Local_Scale().x);
		break;

	case COLL_TYPE::COL_POINT2D:
		m_Scale.Scale(KVector(1.0f, 1.0f, 1.0f));
		newMesh = ResourceManager<Mesh>::Find(L"LINEMESH");
		NewBorder.m_Border.x = 2;
		NewBorder.m_Color = _Color;
		NewBorder.m_UvPerPixel = 1.0f;
		break;

	case COLL_TYPE::COL_POLY2D:
		m_Scale.Scale(KVector(_One->Local_Scale().x, _One->Local_Scale().y));
		newMesh = ResourceManager<Mesh>::Find(_One->one()->Get_Component<Renderer_Sprite>()->name());

		NewBorder.m_Border.x = 3;
		NewBorder.m_Color = _Color;
		NewBorder.m_UvPerPixel = KVector2(1 / _One->Local_Scale().x, 1 / _One->Local_Scale().y);
		break;
	default:
		break;
	}

	
	if (COLL_TYPE::COL_POLY2D == _type)
	{
		// KVector4 
		// Core_Class::MainDevice().Set_ConstBuffer<KVector4>(L"Poly", NewBorder, Shader::SHADER_TYPE::ST_PS);
	}

	// 색 섞어주기
	Core_Class::MainDevice().Set_ConstBuffer<KBorder>(L"BORDER", NewBorder, Shader::SHADER_TYPE::ST_PS);
	Core_Class::MainDevice().Set_ConstBuffer<KMatrix>(
		L"TRANS", (m_Scale * m_Rotate * m_Pos * m_VP).TransPose_Referance(), Shader::SHADER_TYPE::ST_VS);
	


	// 에디터와 업데이트간 차이 생김 -> 보정
	if (newMat == nullptr || newMesh == nullptr)
	{
		return;
	}

	newMesh->Update();
	newMat->Update();
	newMesh->Render();
}

void DebugManager::draw_font(const wchar_t* _pStr, const KVector2& _Pos, const float& _fSize, const KColor& _COLOR /*= KColor::Black*/, FW1_TEXT_FLAG _Flag /*= FW1_TEXT_FLAG::FW1_TOP*/)
{
	if (false == m_Debug)
	{
		return;
	}

	KPtr<KFont> m_Font = ResourceManager<KFont>().Find(L"AngryBirds");
	m_Font->draw_font(_pStr, _Pos, _fSize, _COLOR.color_to_reverse255(), _Flag);
}