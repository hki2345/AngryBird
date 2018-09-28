#pragma once
#include <unordered_map>
#include <set>
#include <list>

#include "SmartPtr.h"
#include "Camera.h"

class Renderer;
class TheOne;
class RenderManager
{
public:
	friend TheOne;
	friend Camera;
	friend Renderer;

private:
	// Camera
	std::set<KPtr<Camera>> m_CameraMap;
	std::set<KPtr<Camera>>::iterator m_Camera_StartIter;
	std::set<KPtr<Camera>>::iterator m_Camera_EndIter;

	// 이 레이어 이터는 카메라가 들고 있음 ㅇㅇ
	std::set<int>::iterator m_Layer_StartIter;
	std::set<int>::iterator m_Layer_EndIter;

	// Renderer
	std::unordered_map<int, std::list<KPtr<Renderer>>> m_RendererMap;
	std::unordered_map<int, std::list<KPtr<Renderer>>>::iterator m_Renderer_FindIter;
	std::unordered_map<int, std::list<KPtr<Renderer>>>::iterator m_AllRenderer_StartIter;
	std::unordered_map<int, std::list<KPtr<Renderer>>>::iterator m_AllRenderer_EndIter;
	std::list<KPtr<Renderer>>::iterator m_Renderer_StartIter;
	std::list<KPtr<Renderer>>::iterator m_Renderer_EndIter;



private:
	static bool Sort_Z(KPtr<Renderer> _Left, KPtr<Renderer> _Right);

	void Insert_Camera(Camera* _Camera);
	void Insert_Renderer(Renderer* _Renderer, int _Order);
	void insert_AbsRenderer(KPtr<Renderer> _Renderer);

public:
	void Render();
	void Release();

	bool Is_Name(const wchar_t* _Name);

public:
	RenderManager();
	~RenderManager();
};

