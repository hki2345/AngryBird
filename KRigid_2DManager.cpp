#include "KRigid_2DManager.h"
#include "Stl_Assistor.h"
#include "KMacro.h"

#include "Collider2D_DE.h"
#include "KRigid_2D.h"
#include "KThread.h"
#include "MultiCritical.h"

KRigid_2DManager::KRigid_2DManager() : m_Gravity(KVector2::Zero)
{
}


KRigid_2DManager::~KRigid_2DManager()
{
	m_S_WorldMap = m_WorldMap.begin();
	m_E_WorldMap = m_WorldMap.end();

	// 8과 3이 가장 이상적이라고 합디다
	for (; m_S_WorldMap != m_E_WorldMap; ++m_S_WorldMap)
	{
		if (nullptr != m_S_WorldMap->second)
		{
			delete m_S_WorldMap->second;
		}
	}	

	m_WorldMap.clear();
}



b2World* KRigid_2DManager::find_world(const int& _Order)
{
	std::unordered_map<int, b2World*>::iterator Find_Iter = m_WorldMap.find(_Order);

	if (m_WorldMap.end() == Find_Iter)
	{
		return nullptr;
	}
	return Find_Iter->second;
}

b2World* KRigid_2DManager::insert_world(const int& _Order)
{
	b2World* NewWorld = new b2World(m_Gravity);

	m_WorldMap.insert(std::unordered_map<int, b2World*>::value_type(_Order, NewWorld));

	return NewWorld;
}

b2Body* KRigid_2DManager::Create_KRigid2D(KRigid_2D* _Rigid)
{
	KASSERT(nullptr == _Rigid->m_Col2D);
	int Order = _Rigid->m_Col2D->order();

	b2World* Find = find_world(Order);

	// 해당 오더의 세계가 없으면 만들어라
	if (nullptr == Find)
	{
		Find = insert_world(Order);
	}

	KASSERT(nullptr == Find);

	m_KRigidList.push_back(_Rigid);
	return m_Body = Find->CreateBody(&_Rigid->m_BD);
}


void KRigid_2DManager::Delete_KRigid2D(KPtr<KRigid_2D> _Rigid)
{
	std::list<KPtr<KRigid_2D>>::iterator S_LIst = m_KRigidList.begin();
	std::list<KPtr<KRigid_2D>>::iterator E_LIst = m_KRigidList.end();

	for (; S_LIst != E_LIst; ++S_LIst)
	{
		if ((*S_LIst) == _Rigid)
		{
			m_KRigidList.erase(S_LIst);
			break;
		}
	}

	std::unordered_map<int, b2World*>::iterator FI = m_WorldMap.find(_Rigid->m_Col2D->order());
	FI->second->DestroyBody(_Rigid->m_Body);
}


void KRigid_2DManager::Progress()
{
	m_S_WorldMap = m_WorldMap.begin();
	m_E_WorldMap = m_WorldMap.end();

	// 적분 횟수 8과 3이 가장 이상적이라고 합디다
	for (; m_S_WorldMap != m_E_WorldMap; ++m_S_WorldMap)
	{
		if (nullptr != m_S_WorldMap->second)
		{
			m_S_WorldMap->second->Step(DELTATIME, 8, 3);
		}
	}

	return;

	// 다른 라이브러리 내에서 불안정하고 - 무엇보다 프레임 개선이 전혀 없음
	// 의미 없음...
	// KThread::Start_Thread<KRigid_2DManager>(L"KRigid2D", &KRigid_2DManager::ThreadUpdate, this);
}



unsigned int KRigid_2DManager::ThreadUpdate(void*)
{
	DeltaTime = .0f;

	while (true)
	{
		MultiCritical(0);
		KPtr<TimeManager::Timer> ptr = TimeManager::Create_Timer(L"TestTimer");
		DeltaTime = ptr->Update();

		m_S_WorldMap = m_WorldMap.begin();
		m_E_WorldMap = m_WorldMap.end();

		// 적분 횟수 8과 3이 가장 이상적이라고 합디다
		for (; m_S_WorldMap != m_E_WorldMap; ++m_S_WorldMap)
		{
			if (nullptr != m_S_WorldMap->second)
			{
				m_S_WorldMap->second->Step(DeltaTime, 8, 3);
			}
		}
	}	
	
	return 0;
}


KPtr<KRigid_2D> KRigid_2DManager::b2BodyToKRigid_2D(b2Body* _Value)
{
	std::list<KPtr<KRigid_2D>>::iterator S_List = m_KRigidList.begin();
	std::list<KPtr<KRigid_2D>>::iterator E_List = m_KRigidList.end();

	for (; S_List != E_List; ++S_List)
	{
		if (_Value == (*S_List)->m_Body)
		{
			return (*S_List);
		}
	}

	return nullptr;
}