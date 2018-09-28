#pragma once
#include <Some_One.h>
#include "IsoMap_Renderer.h"

class IsoMap_Editor : public Some_One
{
public:
	KPtr<IsoMap_Renderer> m_IsoRender;

public:
	bool Init() override;
	void Update() override;
	void DebugRender() override;
	
public:
	IsoMap_Editor();
	~IsoMap_Editor();
};

