#include "KRaycast_2D.h"

#include "KRigid_2D.h"
#include "State.h"


KRaycast_2D::KRaycast_2D()
{
}


KRaycast_2D::~KRaycast_2D()
{
}

KRaycast_2D::RayData* KRaycast_2D::check(const KVector2& _Origin, const KVector2& _Target)
{
	m_RD.KRigid = nullptr;
	m_RD.normal = KVector2::Zero;
	m_RD.point = KVector2::Zero;
	m_RD.fraction = .0f;

	b2World* ThisWorld = state()->this_KRigid2DManager.find_world(0);

	KVector2 TempPos = one()->Local_Pos().m_Pos;
	ThisWorld->RayCast(this, _Origin, _Target);

	return &m_RD;
}

float32 KRaycast_2D::ReportFixture(b2Fixture* _fixture, const b2Vec2& _point,
	const b2Vec2& _normal, float32 _fraction)
{
	m_RD.KRigid = state()->this_KRigid2DManager.b2BodyToKRigid_2D(_fixture->GetBody());
	m_RD.fraction = _fraction;
	m_RD.normal = _normal;
	m_RD.point = _point;

	return 0;
}


KPtr<KRigid_2D> KRaycast_2D::b2FixtureToKRigid_2D(b2Fixture* _Value)
{
	//std::list<KPtr<KRigid_2D>>* Temp = state()->this_KRigid2DManager.This_KRigid_2D();

	//std::list<KPtr<KRigid_2D>>::iterator S_List = Temp->begin();
	//std::list<KPtr<KRigid_2D>>::iterator E_List = Temp->end();

	//for (; S_List != E_List; ++S_List)
	//{
	//	if (_Value == (*S_List)->)
	//	{
	//		return (*S_List);
	//	}
	//}

	return nullptr;
}