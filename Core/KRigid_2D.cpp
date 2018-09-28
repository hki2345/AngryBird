#include "KRigid_2D.h"
#include "KMacro.h"
#include "KMath.h"

#include "Collider2D_DE.h"
#include "KRigid_2DManager.h"
#include "State.h"
#include "KThread.h"


#include "WriteStream.h"
#include "ReadStream.h"
#include "ResourceManager.h"


#include "Mesh.h"
#include "DirectXHeader_DE.h"

#include <time.h>


KRigid_2D::KRigid_2D() :
	m_Body(nullptr),
	m_Circle(nullptr),
	m_Poly(nullptr),
	m_Col2D(nullptr),
	m_FD(nullptr),
	m_Fixture(nullptr),
	m_MD(nullptr)
{
}

KRigid_2D::~KRigid_2D()
{
	NEW_DELETE(m_Poly);
	NEW_DELETE(m_Circle);
	NEW_DELETE(m_FD);
	NEW_DELETE(m_MD);

	for (size_t i = 0; i < m_VertexVec.size(); i++)
	{
		m_VertexVec[i]->set_Death();
	}

	m_VertexVec.clear();
}

void KRigid_2D::Init_Component()
{
	m_Trans = one()->Get_Component<TransPosition>();
	m_Col2D = one()->Get_Component<Collider2D_DE>();
	m_Body = state()->this_KRigid2DManager.Create_KRigid2D(this);


	KASSERT(nullptr == m_Body);
	m_Body->SetType(b2BodyType::b2_dynamicBody);
}

void KRigid_2D::Update()
{
	if (true == is_Death())
	{
		return;
	}

	switch (m_Col2D->type())
	{
	case COL_CIRCLE2D:
	case COL_RECT2D:// 트랜스에서 수정이 될 여지가 있으면 통과 함
	{
		if (true == m_Trans->BWorld())
		{
			Set_Transform();
			return;
		}


		float ss = m_Body->GetAngle();
		b2Vec2 qa = m_Body->GetPosition();

		m_Trans->Local_Pos({ qa, m_Trans->Local_Pos().z });
		m_Trans->Local_Rotate_Radian(.0f, .0f, ss);
	}
		break;

	case COL_POLY2D:
	{
		if (b2BodyType::b2_dynamicBody == m_Body->GetType())
		{
			if (true == m_Trans->BWorld())
			{
				Set_Transform();
				return;
			}

			float ss = m_Body->GetAngle();
			b2Vec2 qa = m_Body->GetPosition();

			m_Trans->Local_Pos({ qa, m_Trans->Local_Pos().z });
			m_Trans->Local_Rotate_Radian(.0f, .0f, ss);

			for (size_t i = 0; i < m_VertexVec.size(); ++i)
			{
				m_VertexVec[i]->Get_Component<Collider2D_DE>()->active_Off();
			}
		}
		else if (b2BodyType::b2_staticBody == m_Body->GetType())
		{
			for (size_t i = 0; i < m_VertexVec.size(); ++i)
			{
				if (true == one()->BWorld())
				{
					int a = 0;
				}

				if (true == m_VertexVec[i]->BWorld())
				{
					m_Trans->Local_Pos(KMath::CenterOfGravity(m_Trans), 10.0f);
					Set_Poly();
				}
			}
		}
	}
		break;
	default:
		break;
	}
}



void KRigid_2D::Rid_Pos(const KVector& _Value)
{
	m_Body->SetTransform(_Value.m_Pos, m_Body->GetAngle());
}

void KRigid_2D::Rid_Rotate(const KVector& _Value)
{
	m_Body->SetTransform(m_Body->GetPosition(), _Value.z);
}

void KRigid_2D::Rid_Scale(const KVector& _Value)
{
	KASSERT(nullptr == m_FD);
	if (m_Fixture != nullptr)
	{
		m_Body->DestroyFixture(m_Fixture);
	}

	NEW_DELETE(m_Poly);
	m_Poly = new b2PolygonShape;
	m_Poly->SetAsBox(_Value.x * .5f, _Value.y * .5f);
	m_FD->shape = m_Poly;

	m_Fixture = m_Body->CreateFixture(m_FD);
}

void KRigid_2D::Rid_Radius(const float& _Value)
{
	KASSERT(nullptr == m_FD);
	if (m_Fixture != nullptr)
	{
		m_Body->DestroyFixture(m_Fixture);
	}

	NEW_DELETE(m_Circle);
	m_Circle = new b2CircleShape;
	m_Circle->m_radius = _Value * .5f;
	m_FD->shape = m_Circle;

	m_Fixture = m_Body->CreateFixture(m_FD);
}

void KRigid_2D::Rid_Transform(const KVector& _Pos, const KVector& _Rotate, const KVector& _Scale)
{
	KASSERT(nullptr == m_FD);
	
	Rid_Pos(_Pos);
	Rid_Rotate(_Rotate);

	switch (m_Col2D->type())
	{
	case COLL_TYPE::COL_RECT2D:
		Rid_Scale(_Scale);
		break;
	case COLL_TYPE::COL_CIRCLE2D:
		Rid_Radius(_Scale.x);
		break;
	default:
		break;
	}
}

// Mass, Inertia, Center
void KRigid_2D::MassData(const KVector& _Value)
{
	NEW_DELETE(m_MD);

	m_MD = new b2MassData;

	m_MD->mass = _Value.x;
	m_MD->I = _Value.y;
	m_MD->center = _Value.m_Back;

	m_Body->SetMassData(m_MD);
}

// Density, Friction, Restitude
void KRigid_2D::FigureData(const KVector3& _Value)
{
	KASSERT(nullptr == m_MD);
	NEW_DELETE(m_FD);

	m_FD = new b2FixtureDef;

	m_FD->density = _Value.x;
	m_FD->friction = _Value.y;
	m_FD->restitution = _Value.z;

	switch (m_Col2D->type())
	{
	case COLL_TYPE::COL_RECT2D:
	case COLL_TYPE::COL_CIRCLE2D:
		Set_Transform();
		break;
	default:
		break;
	}
}


void KRigid_2D::Impulse(const KVector2& _Impulse)
{
	m_Body->SetLinearVelocity(_Impulse);
}

void KRigid_2D::AngularImpulse(const float& _Impulse)
{
	m_Body->SetAngularVelocity(_Impulse);
}

float KRigid_2D:: CollisionForce()
{
	b2ContactEdge* TempEdge = m_Body->GetContactList();
	KVector2 TempScale = one()->Local_Scale().m_Pos;

	if (nullptr != TempEdge && nullptr != TempEdge->next)
	{
		return m_Body->GetMass() * m_Body->GetLinearVelocity().Length() / (TempScale.x * TempScale.y);
	}

	return .0f;
}

bool KRigid_2D::load(const wchar_t* _Name)
{
	std::wstring LoadFolder = PathManager::Find_Path(L"KRigid2D_Data");
	LoadFolder += _Name;
	LoadFolder += L".K2D";

	std::wstring BackFolder = PathManager::Find_Path(L"KRigid2D_Back");
	wchar_t BackNumber[256];
	_itow_s((int)time(nullptr), BackNumber, 10);
	BackFolder += BackNumber;
	BackFolder += _Name;
	BackFolder += L".K2D";

	ReadStream LoadStream = ReadStream(LoadFolder.c_str());
	ReadStream LoadBackStream = ReadStream(BackFolder.c_str());

	KRigid2D_Data NewData;

	LoadStream.read(&NewData, sizeof(KRigid2D_Data), sizeof(KRigid2D_Data));
	LoadBackStream.read(&NewData, sizeof(KRigid2D_Data), sizeof(KRigid2D_Data));

	MassData(NewData.m_MassData);
	FigureData(NewData.m_FigureData);

	Set_Poly();

	return 0;
}

bool KRigid_2D::save(const wchar_t* _Name)
{
	std::wstring SaveFolder = PathManager::Find_Path(L"KRigid2D_Data");
	SaveFolder += L"Init";
	SaveFolder += L".K2D";

	std::wstring BackFolder = PathManager::Find_Path(L"KRigid2D_Back");
	wchar_t BackNumber[256];
	_itow_s((int)time(nullptr), BackNumber, 10);
	BackFolder += _Name;
	BackFolder += L"_";
	BackFolder += BackNumber;
	BackFolder += L".K2D";

	WriteStream SaveStream = WriteStream(SaveFolder.c_str());
	WriteStream SaveBackStream = WriteStream(BackFolder.c_str());

	KRigid2D_Data NewData;

	NewData.m_MassData.m1 = m_MD->mass;
	NewData.m_MassData.m2 = m_MD->I;
	NewData.m_MassData.m_Back = m_MD->center;

	NewData.m_FigureData.m1 = m_FD->density;
	NewData.m_FigureData.m2 = m_FD->friction;
	NewData.m_FigureData.m3 = m_FD->restitution;

	SaveStream.write(&NewData, sizeof(KRigid2D_Data));
	SaveBackStream.write(&NewData, sizeof(KRigid2D_Data));

	return 0;
}

void KRigid_2D::Insert_VertexList(std::vector<KVector2> _Value)
{
	for (size_t i = 0; i < _Value.size(); i++)
	{
		m_VertexVec.push_back(Create_Vertex(_Value[i]));
	}
	Set_Poly();
}

void KRigid_2D::Set_VertexList(std::vector<KVector2>* _Value)
{
	for (size_t i = 0; i < m_VertexVec.size(); i++)
	{
		m_VertexVec[i]->set_Death();
	}

	m_VertexVec.clear();
	std::vector<KVector2> Temp = *_Value;

	for (size_t i = 0; i < Temp.size(); i++)
	{
		m_VertexVec.push_back(Create_Vertex(Temp[i]));
	}
	load(L"Init");
	Set_Poly();
}

void KRigid_2D::Insert_Vertex(const KVector2& _Value)
{
	if (COL_POLY2D != m_Col2D->type())
	{
		return;
	}

	KPtr<TheOne> NewOne = Create_Vertex(_Value);

	if (nullptr != NewOne)
	{
		m_VertexVec.push_back(NewOne);

		int XPos = 100;
		while (3 > m_VertexVec.capacity())
		{
			m_VertexVec.push_back(Create_Vertex({ XPos - 10.0f, 0.0f }));
			XPos *= 2;
		}

		Set_Poly();
	}
}

void KRigid_2D::Delete_Vertex(KPtr<TheOne> _Value)
{
	for (size_t i = 0; i < m_VertexVec.size(); ++i)
	{
		if (m_VertexVec[i] == _Value)
		{
			std::vector<KPtr<TheOne>>::iterator FindIter = m_VertexVec.begin();

			// 어차피 erase 함수가 실행된다면 배열의 뒷요소들이 자동으로 한칸씩 당겨지기 때문에
			// erase 함수가 실행되지 않은 경우에만 인덱스를 증가시키는 식으로 설계해야한다.
			m_VertexVec[i]->set_Death();
			m_VertexVec.erase(m_VertexVec.begin() + i);
		}
	}

	Set_Poly();
}

void KRigid_2D::Active_Vertex(const bool& _Value)
{
	for (size_t i = 0; i < m_VertexVec.size(); ++i)
	{
		if (true == _Value)
		{
			m_VertexVec[i]->active_On();
		}
		else
		{
			m_VertexVec[i]->active_Off();
		}
	}
}

KPtr<TheOne> KRigid_2D::Create_Vertex(const KVector2& _Value)
{
	// 설마 같은 곳에 하는지 체크 - 그나마 체크 ㅋㅋ
	for (size_t i = 0; i < m_VertexVec.size(); ++i)
	{
		if (m_VertexVec[i]->Local_Pos().m_Pos.FloatToInt() == _Value.FloatToInt())
		{
			return nullptr;
		}
	}

	KPtr<TheOne> NewVertex = state()->Create_TheOne();
	NewVertex->Local_Scale(KVector(10.0f, 10.0f));
	NewVertex->name(L"Vertex");

	KPtr<Collider2D_DE> NewVertexCol = NewVertex->Add_Component<Collider2D_DE>(0);
	NewVertexCol->type(COLL_TYPE::COL_CIRCLE2D);
	NewVertexCol->color(KColor::White);


	NewVertex->Local_Pos(_Value, 2.0f);

	return NewVertex;
}

void KRigid_2D::Set_Poly()
{
	if (0 == m_VertexVec.size())
	{
		return;
	}

	KASSERT(nullptr == m_FD);
	if (m_Fixture != nullptr)
	{
		m_Body->DestroyFixture(m_Fixture);
	}
	NEW_DELETE(m_Poly);
	
	m_Poly = new b2PolygonShape;
	b2Vec2 KVecVec[8] = { {.0f, .0f}, };

	for (size_t i = 0; i < m_VertexVec.size(); ++i)
	{
		KVecVec[i] = m_VertexVec[i]->Local_Pos().m_Pos;
	}

	m_Poly->Set(KVecVec, m_VertexVec.size());


	m_FD->shape = m_Poly;
	m_Fixture = m_Body->CreateFixture(m_FD);

	Sort_Vertex();
}

void KRigid_2D::Create_Mesh(const wchar_t* _Name)
{
	std::wstring Name = _Name;
	if (nullptr != ResourceManager<Mesh>::Find(Name.c_str()))
	{
		ResourceManager<Mesh>::Delete(Name.c_str());
	}

	// 최대 버텍스8개 인덱스6개
	Vertex_Texture TextureVert[8] = {};
	std::vector<KVector2> EvenVert;
	Index_16 TextureIdx[6] = {};
	size_t PolyVert = m_MeshVec.size() - 2;
	size_t PolyCnt = 0;

	for (size_t i = 0; i < m_MeshVec.size(); i++)
	{
		KVector2 TempVec2;
		if (b2BodyType::b2_dynamicBody == m_Body->GetType())
		{
			TempVec2 = m_MeshVec[i];
		}
		else if (b2BodyType::b2_staticBody == m_Body->GetType())
		{
			TempVec2 = m_MeshVec[i] - m_Trans->Local_Pos();
		}
		KVector4 Temp = TempVec2 / one()->Local_Scale().m_Pos;
		
		Temp.w = 1.0f;
		TextureVert[i].Pos = Temp;
		TextureVert[i].Uv = (Temp + .5f) * KVector2(1.0f, -1.0f);
	}

	// 짝수 버텍스 정렬
	for (size_t i = 0; i < (size_t)(m_MeshVec.size() / 2); i++)
	{
		EvenVert.push_back(TextureVert[i * 2].Pos);
	}

	WORD ind = 0;
	for (size_t i = 0; i < PolyVert; i++)
	{
		if (ind + 1 == PolyVert + 2)
		{
			// 짝수 다각형은 해당 안됌
			if (0 != (PolyVert + 2) % 2)
			{
				break;
			}

			TextureIdx[i] = Index_16(ind, 0, 1);
			++PolyCnt;
			break;
		}

		else if (ind + 2 == PolyVert + 2)
		{
			TextureIdx[i] = Index_16(ind, ind + 1, 0);
			++PolyCnt;
			break;
		}
		TextureIdx[i] = Index_16(ind, ind + 1, ind + 2);
		ind += 2;
		++PolyCnt;
	}

	if (PolyVert >= 3)
	{
		// 짝수 그리기 - 쏙통 채우기 - 남은 삼각형 개수
		ind = 0;
		for (size_t i = PolyCnt; i < PolyVert; i++)
		{
			if ((ind + 2) * 2 >= (WORD)PolyVert + 2)
			{
				TextureIdx[i] = Index_16(ind * 2, (ind + 1) * 2, 0);
				break;
			}
			TextureIdx[i] = Index_16(ind * 2, (ind + 1) * 2, (ind + 2) * 2);
			ind += 2;
		}
	}

	ResourceManager<Mesh>::Create(Name.c_str(),
		m_MeshVec.size(), (UINT)sizeof(Vertex_Texture), D3D11_USAGE_DYNAMIC, TextureVert,
		PolyVert * 3, (UINT)Index_16::MemberSize(), D3D11_USAGE_DEFAULT, TextureIdx,
		Index_16::FM());
}

std::vector<KPtr<TheOne>>* KRigid_2D::Vertex_Data()
{
	return &m_VertexVec;
}

std::vector<KVector2>* KRigid_2D::Mesh_Data()
{
	return &m_MeshVec;
}

bool KRigid_2D::IsChangeVertex()
{
	for (size_t i = 0; i < m_VertexVec.size(); ++i)
	{
		if (true == m_VertexVec[i]->BWorld())
		{
			return true;
		}
	}

	return false;
}

void KRigid_2D::Sort_Vertex()
{
	m_MeshVec.clear();

	for (size_t i = 0; i < (size_t)m_Poly->GetVertexCount(); i++)
	{
		m_MeshVec.push_back(m_Poly->GetVertex(i));
	}

	m_Trans->Col_Vertex(&m_MeshVec);

	// 왼쪽
	// 오른쪽
	// 위
	// 아래
	float LX = m_VertexVec[0]->Local_Pos().x;
	float RX = m_VertexVec[0]->Local_Pos().x;
	float UY = m_VertexVec[0]->Local_Pos().y;
	float DY = m_VertexVec[0]->Local_Pos().y;
	for (size_t i = 0; i < m_VertexVec.size(); i++)
	{
		for (size_t j = 0; j < m_VertexVec.size(); j++)
		{
			if (LX > m_VertexVec[j]->Local_Pos().x)
			{
				LX = m_VertexVec[j]->Local_Pos().x;
			}

			if (RX < m_VertexVec[j]->Local_Pos().x)
			{
				RX = m_VertexVec[j]->Local_Pos().x;
			}

			if (UY < m_VertexVec[j]->Local_Pos().y)
			{
				UY = m_VertexVec[j]->Local_Pos().y;
			}

			if (DY > m_VertexVec[j]->Local_Pos().y)
			{
				DY = m_VertexVec[j]->Local_Pos().y;
			}
		}
	}
	
	
	m_Trans->Col_Vertex(&m_MeshVec);
	one()->Local_Scale(KVector(RX - LX, UY - DY, 10.0f));
}


void KRigid_2D::ColDown()
{
	for (size_t i = 0; i < m_VertexVec.size(); i++)
	{
		m_VertexVec[i]->Get_Component<Collider2D_DE>()->active_Off();
	}
}

void KRigid_2D::ColUp()
{
	for (size_t i = 0; i < m_VertexVec.size(); i++)
	{
		m_VertexVec[i]->Get_Component<Collider2D_DE>()->active_On();
	}
}

std::list<KPtr<KRigid_2D>> KRigid_2D::Contact_List()
{
	m_Con_KRigid2D.clear();
	Push_Contact(m_Body);
	return m_Con_KRigid2D;
}

void KRigid_2D::Push_Contact(b2Body* _Value)
{
	b2ContactEdge* List = _Value->GetContactList();
	if (nullptr == List)
	{
		return;
	}

	KPtr<KRigid_2D> Temp = state()->this_KRigid2DManager.b2BodyToKRigid_2D(_Value);
	if (nullptr != Temp)
	{
		std::list<KPtr<KRigid_2D>>::iterator S_List = m_Con_KRigid2D.begin();
		std::list<KPtr<KRigid_2D>>::iterator E_List = m_Con_KRigid2D.end();

		// 있으면 차단
		for (; S_List != E_List; ++S_List)
		{
			if ((*S_List) == Temp)
			{
				return;
			}
		}

		m_Con_KRigid2D.push_back(Temp);

		if (nullptr != List->next)
		{
			Push_Contact(List->next->other);
		}

		else
		{
			return;
		}
	}

}
