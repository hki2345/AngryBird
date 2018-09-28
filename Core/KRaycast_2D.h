#pragma once
#include "Component_DE.h"
#include <Box2D/Box2D.h>
#include <vector>


class KRigid_2D;
class KRaycast_2D : public Component_DE, b2RayCastCallback
{
public:
	struct RayData
	{
		KPtr<KRigid_2D> KRigid;
		KVector2 point;
		KVector2 normal;
		float fraction;
	};


private:
	RayData m_RD;
	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point,
		const b2Vec2& normal, float32 fraction);

public:
	RayData* raydata() { return &m_RD; }
	RayData* check(const KVector2& _Origin, const KVector2& _Target);


	KPtr<KRigid_2D> b2FixtureToKRigid_2D(b2Fixture* _Value);

public:
	KRaycast_2D();
	~KRaycast_2D();
};

