#pragma once
#include <Some_One.h>

class Renderer_Sprite;
class Collider2D_DE;
class Grass : public Some_One
{
public:
	Grass();
	~Grass();


private:
	KPtr<TheOne>	m_ColPos;
	KPtr<Renderer_Sprite> m_Render;
	KPtr<Collider2D_DE> m_Collider;
	int m_hp;

public:
	KPtr<TheOne> Col_One() { return m_ColPos; }

	bool Init(const size_t& _Inx);
	void Update() override;
};

