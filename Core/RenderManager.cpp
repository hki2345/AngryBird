#include "RenderManager.h"
#include "Renderer.h"
#include "Camera.h"
#include "KMacro.h"

RenderManager::RenderManager()
{
}


RenderManager::~RenderManager()
{
}

bool RenderManager::Sort_Z(KPtr<Renderer> _Left, KPtr<Renderer> _Right)
{
	if (_Left->pivot_world().z > _Right->pivot_world().z)
	{
		return true;
	}

	return false;
}


void RenderManager::Insert_Camera(Camera* _Camera)
{
	KASSERT(nullptr == _Camera);
	m_CameraMap.insert(_Camera);
}
void RenderManager::Insert_Renderer(Renderer* _Renderer, int _Order)
{
	KASSERT(nullptr == _Renderer);

	m_Renderer_FindIter = m_RendererMap.find(_Order);

	// 해당 레이어(리스트)가 없으면 만들어 주고 거기에 삽입
	if (m_Renderer_FindIter == m_RendererMap.end())
	{
		m_RendererMap.insert(
			std::unordered_map<int, std::list<KPtr<Renderer>>>::value_type(_Order, std::list<KPtr<Renderer>>()));
		m_Renderer_FindIter = m_RendererMap.find(_Order);
	}

	m_Renderer_FindIter->second.push_back(_Renderer);
}

void RenderManager::insert_AbsRenderer(KPtr<Renderer> _Renderer)
{
	KASSERT(nullptr == _Renderer);

	m_Renderer_FindIter = m_RendererMap.find(_Renderer->order());

	if (m_Renderer_FindIter == m_RendererMap.end())
	{
		m_RendererMap.insert(std::unordered_map<int, std::list<KPtr<Renderer>>>::
			value_type(_Renderer->order(), std::list<KPtr<Renderer>>()));
	}

	m_Renderer_FindIter = m_RendererMap.find(_Renderer->order());
	m_Renderer_FindIter->second.push_back(_Renderer);
}


void RenderManager::Render()
{
	m_Camera_StartIter = m_CameraMap.begin();
	m_Camera_EndIter = m_CameraMap.end();

	// 카메라 별
	for (; m_Camera_StartIter != m_Camera_EndIter; ++m_Camera_StartIter)
	{
		m_Layer_StartIter = (*m_Camera_StartIter)->m_Layer.begin();
		m_Layer_EndIter = (*m_Camera_StartIter)->m_Layer.end();

		// 레이어 별
		for (; m_Layer_StartIter!= m_Layer_EndIter; ++m_Layer_StartIter)
		{
			m_Renderer_FindIter = m_RendererMap.find(*m_Layer_StartIter);

			// 해당 레이어가 카메라에 없으면 넘긴다.
			if (m_Renderer_FindIter == m_RendererMap.end())
			{
				continue;
			}

			if (2 <= m_Renderer_FindIter->second.size())
			{
				m_Renderer_FindIter->second.sort(&RenderManager::Sort_Z);
			}

			m_Renderer_StartIter = m_Renderer_FindIter->second.begin();
			m_Renderer_EndIter = m_Renderer_FindIter->second.end();

			for (; m_Renderer_StartIter != m_Renderer_EndIter; ++m_Renderer_StartIter)
			{
				(*m_Renderer_StartIter)->Render((*m_Camera_StartIter)->View_Proj());
			}
		}		
	}
}

void RenderManager::Release()
{
	m_AllRenderer_StartIter = m_RendererMap.begin();
	m_AllRenderer_EndIter = m_RendererMap.end();

	for (; m_AllRenderer_StartIter != m_AllRenderer_EndIter; ++m_AllRenderer_StartIter)
	{
		m_Renderer_StartIter = m_AllRenderer_StartIter->second.begin();
		m_Renderer_EndIter = m_AllRenderer_StartIter->second.end();

		for (; m_Renderer_StartIter != m_Renderer_EndIter;)
		{		
			if (true == (*m_Renderer_StartIter)->is_Death())
			{
				m_Renderer_StartIter = m_AllRenderer_StartIter->second.erase(m_Renderer_StartIter);
			}

			else
			{
				++m_Renderer_StartIter;
			}
		}
	}
}

bool RenderManager::Is_Name(const wchar_t* _Name)
{
	m_AllRenderer_StartIter = m_RendererMap.begin();
	m_AllRenderer_EndIter = m_RendererMap.end();

	for (; m_AllRenderer_StartIter != m_AllRenderer_EndIter; ++m_AllRenderer_StartIter)
	{
		m_Renderer_StartIter = m_AllRenderer_StartIter->second.begin();
		m_Renderer_EndIter = m_AllRenderer_StartIter->second.end();

		for (; m_Renderer_StartIter != m_Renderer_EndIter; ++m_Renderer_StartIter)
		{
			std::wstring OneName = (*m_Renderer_StartIter)->name();
			if (OneName == _Name && false == (*m_Renderer_StartIter)->is_Death())
			{
				return true;
			}
		}
	}

	return false;
}