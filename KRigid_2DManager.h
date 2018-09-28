#pragma once

#include <Box2D\Box2D.h>
#include <unordered_map>

#include "DirectXHeader.h"
#include "TimeManager.h"

class KRigid_2D;
class KRigid_2DManager
{
private:
	KPtr<TimeManager::Timer> m_Timer;

	std::unordered_map<int, b2World*> m_WorldMap;
	std::list<KPtr<KRigid_2D>> m_KRigidList;

	std::unordered_map<int, b2World*>::iterator m_S_WorldMap;
	std::unordered_map<int, b2World*>::iterator m_E_WorldMap;

	b2Body* m_Body;
	KVector2 m_Gravity;
	float DeltaTime;

public:
	KPtr<KRigid_2D> b2BodyToKRigid_2D(b2Body* _Value);


	b2World* find_world(const int& _Order);
	b2World* insert_world(const int& _Order);

	void Delete_KRigid2D(KPtr<KRigid_2D> _Rigid);
	b2Body* Create_KRigid2D(KRigid_2D* _Rigid);

	void gravity(const KVector2& _Value)
	{
		m_Gravity = _Value;
		m_S_WorldMap = m_WorldMap.begin();
		m_E_WorldMap = m_WorldMap.end();

		for (; m_S_WorldMap != m_E_WorldMap; ++m_S_WorldMap)
		{
			m_S_WorldMap->second->SetGravity(_Value);
		}
	}

	KVector2& gravity() { return m_Gravity; }


	void Progress();


	std::list<KPtr<KRigid_2D>>* This_KRigid_2D()
	{
		return &m_KRigidList;
	}

	// 리지드 바디 업데이트를 스레드로 돌리려 하였으나
	// 내부에서 포인터가 섞여버리는 사상 초유의 사탭 ㅏㄹ생 -> 포기 
	// 짜피 프레임 저하도 별로 없다. -> 월드를 두 개 돌리는 경우
private:
	unsigned int ThreadUpdate(void*);

public:
	KRigid_2DManager();
	~KRigid_2DManager();
};

