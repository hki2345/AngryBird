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

	// ������ �ٵ� ������Ʈ�� ������� ������ �Ͽ�����
	// ���ο��� �����Ͱ� ���������� ��� ������ ���� ������ -> ���� 
	// ¥�� ������ ���ϵ� ���� ����. -> ���带 �� �� ������ ���
private:
	unsigned int ThreadUpdate(void*);

public:
	KRigid_2DManager();
	~KRigid_2DManager();
};

