#include "TheOne.h"
#include "State.h"
#include "Component.h"
#include "Stl_Assistor.h"
#include "KMacro.h"
#include "Core_Class.h"
#include "RenderManager.h"

#include "Collider2DManager.h"
#include "Collider2D.h"

TheOne::TheOne()
{
}


TheOne::~TheOne()
{
}

void TheOne::all_abs()
{
	m_AbsType = OBJ_ABSTYPE::ALL_ABS;

	// �ش� ������Ʈ���� ���� �ʿ䰡 ����. - �̹� ������ ����
	if (true == window()->this_StateManager.find_absOne(this))
	{
		return;
	}

	window()->this_StateManager.m_AbsOneList.push_back(this);


	std::unordered_map<std::wstring, KPtr<State>>::iterator StartlistIter = window()->this_StateManager.m_StateMap.begin();
	std::unordered_map<std::wstring, KPtr<State>>::iterator EndlistIter = window()->this_StateManager.m_StateMap.end();

	for (; StartlistIter != EndlistIter; ++StartlistIter)
	{
		if (StartlistIter->second == state())
		{
			continue;
		}

		StartlistIter->second->insert_AbsOne(this);
	}
}

void TheOne::PrevUpdate()
{
	MAP_HELPER(m_Componentlist, m_Com_StartIter, m_Com_EndIter, PrevUpdate());
	MAP_HELPER(m_ChildList, m_Child_StartIter, m_Child_EndIter, PrevUpdate());
}
void TheOne::Update()
{
	MAP_HELPER(m_Componentlist, m_Com_StartIter, m_Com_EndIter, Update());
	MAP_HELPER(m_ChildList, m_Child_StartIter, m_Child_EndIter, Update());
}
void TheOne::NextUpdate()
{
	MAP_HELPER(m_Componentlist, m_Com_StartIter, m_Com_EndIter, NextUpdate());
	MAP_HELPER(m_ChildList, m_Child_StartIter, m_Child_EndIter, NextUpdate());
}
void TheOne::FinalUpdate()
{
	MAP_HELPER(m_Componentlist, m_Com_StartIter, m_Com_EndIter, FinalUpdate());
	MAP_HELPER(m_ChildList, m_Child_StartIter, m_Child_EndIter, FinalUpdate());
}

void TheOne::UIRender()
{
	MAP_HELPER(m_Componentlist, m_Com_StartIter, m_Com_EndIter, UIRender());
	MAP_HELPER(m_ChildList, m_Child_StartIter, m_Child_EndIter, UIRender());
}

void TheOne::DebugUpdate()
{
	MAP_HELPER(m_Componentlist, m_Com_StartIter, m_Com_EndIter, DebugUpdate());
	MAP_HELPER(m_ChildList, m_Child_StartIter, m_Child_EndIter, DebugUpdate());
}

void TheOne::DebugRender()
{
	MAP_HELPER(m_Componentlist, m_Com_StartIter, m_Com_EndIter, DebugRender());
	MAP_HELPER(m_ChildList, m_Child_StartIter, m_Child_EndIter, DebugRender());
}


void TheOne::End_Update()
{
	MAP_HELPER(m_Componentlist, m_Com_StartIter, m_Com_EndIter, End_Update());
	MAP_HELPER(m_ChildList, m_Child_StartIter, m_Child_EndIter, End_Update());
}

void TheOne::Release()
{
	m_Com_StartIter = m_Componentlist.begin();
	m_Com_EndIter = m_Componentlist.end();

	for (; m_Com_StartIter != m_Com_EndIter;)
	{
		if (true == (*m_Com_StartIter)->is_Death())
		{
			m_Com_StartIter = m_Componentlist.erase(m_Com_StartIter);
		}
		else
		{
			++m_Com_StartIter;
		}
	}


	m_Child_StartIter = m_ChildList.begin();
	m_Child_EndIter = m_ChildList.end();

	for (; m_Child_StartIter != m_Child_EndIter; m_Child_StartIter++)
	{
		(*m_Child_StartIter)->Release();
	}
}

#include "KRigid_2DManager.h"
#include "KRigid_2D.h"

void TheOne::set_Death()
{
	Begin_Updater::set_Death();


	// �ٸ� ������ �� ���͸� ������ ������ �ϱ� ������ ���� ����� �����Ѵ�.
	std::list<KPtr<Component>>::iterator Com_StartIter = m_Componentlist.begin();
	std::list<KPtr<Component>>::iterator Com_EndIter = m_Componentlist.end();

	for (; Com_StartIter != Com_EndIter; ++Com_StartIter)
	{
		// ���迡�� ���ܽ����־���Ѵ�.
		if (&typeid(KRigid_2D) == (*Com_StartIter)->typeinfo())
		{
			state()->this_KRigid2DManager.Delete_KRigid2D((*Com_StartIter));
		}

		(*Com_StartIter)->set_Death();
	}
}


void TheOne::detach()
{
	std::list<KPtr<TheOne>>::iterator startIter = m_Parent->m_ChildList.begin();
	std::list<KPtr<TheOne>>::iterator endIter = m_Parent->m_ChildList.end();

	bool Check = false;
	for (; startIter != endIter; ++startIter)
	{
		if ((*startIter) == this)
		{
			m_Parent->m_ChildList.erase(startIter);
			Check = true;
			break;
		}
	}

	if (false == Check)
	{
		KASSERT(false == Check);
		return;
	}
}

void TheOne::insert_Child(KPtr<TheOne> _Child, const bool& _World/* = true*/)
{
	if (OBJ_ABSTYPE::NONE_ABS != _Child->abs_type())
	{
		return;
	}

	if (false == state()->detach(_Child))
	{
		return;
	}

	_Child->m_Parent = this;
	m_ChildList.push_back(_Child);

	if (true == _World && nullptr != transform() && nullptr != _Child->transform())
	{
		_Child->Local_Scale(_Child->Local_Scale() / Local_Scale());
		_Child->Local_Pos((_Child->Local_Pos() - Local_Pos()) / Local_Scale());
		_Child->Local_Rotate(_Child->Local_Rotate() - Local_Rotate());
	}
	else if (false == _World && nullptr != transform() && nullptr != _Child->transform())
	{
		_Child->transform()->reset();
	}
}




KVector4 TheOne::Local_Scale()
{
	return one_Trans->Local_Scale();
}
KVector4 TheOne::Local_Pos()
{
	return one_Trans->Local_Pos();
}
KVector4 TheOne::Local_Rotate()
{
	return one_Trans->Local_Rotate();
}

KVector4 TheOne::Local_Forward()
{
	return one_Trans->Local_Forward();
}
KVector4 TheOne::Local_Up()
{
	return one_Trans->Local_Up();
}
KVector4 TheOne::Local_Right()
{
	return one_Trans->Local_Right();
}
KVector4 TheOne::Local_Back()
{
	return one_Trans->Local_Back();
}
KVector4 TheOne::Local_Down()
{
	return one_Trans->Local_Down();
}
KVector4 TheOne::Local_Left()
{
	return one_Trans->Local_Left();
}


void TheOne::Local_Scale(const KVector4& _Value)
{
	one_Trans->Local_Scale(_Value);
}
void TheOne::Local_Pos(const KVector4& _Value)
{
	one_Trans->Local_Pos(_Value);
}
void TheOne::Local_Rotate(const KVector4& _Value)
{
	one_Trans->Local_Rotate(_Value);
}

void TheOne::Local_Scale(const float& _X, const float& _Y, const float& _Z)
{
	one_Trans->Local_Scale(_X, _Y, _Z);
}
void TheOne::Local_Pos(const float& _X, const float& _Y, const float& _Z)
{
	one_Trans->Local_Pos(_X, _Y, _Z);
}
void TheOne::Local_Rotate(const float& _X, const float& _Y, const float& _Z)
{
	one_Trans->Local_Rotate(_X, _Y, _Z);
}

void TheOne::Local_Scale(const KVector2& _Vec, const float& _Z)
{
	one_Trans->Local_Scale(_Vec, _Z);
}
void TheOne::Local_Pos(const KVector2& _Vec, const float& _Z)
{
	one_Trans->Local_Pos(_Vec, _Z);
}
void TheOne::Local_Rotate(const KVector2& _Vec, const float& _Z)
{
	one_Trans->Local_Rotate(_Vec, _Z);
}


bool TheOne::BWorld() const
{
	return one_Trans->BWorld();
}



#include "Collider2D_DE.h"
#include "Renderer_Sprite.h"

void TheOne::Set_ImageSize()
{
	m_Com_StartIter = m_Componentlist.begin();
	m_Com_EndIter = m_Componentlist.end();

	for (; m_Com_StartIter != m_Com_EndIter; ++m_Com_StartIter)
	{
		// �������� Ȯ���Ͽ� �־��ش�. -> �ȿ��� �������� ��ӹ޴� ���� ã��
		// �־��ִ� ����
		if (false == (*m_Com_StartIter)->is_parent<Renderer_Sprite>())
		{
			continue;
		}
		else
		{
			KPtr<Renderer_Sprite> ThisRender = (*m_Com_StartIter);
			Local_Scale(ThisRender->image_size());
		}
	}
}

// X - �̹��� ������� ����
void TheOne::Set_Image_RatioW(const float& _Value)
{
	m_Com_StartIter = m_Componentlist.begin();
	m_Com_EndIter = m_Componentlist.end();

	for (; m_Com_StartIter != m_Com_EndIter; ++m_Com_StartIter)
	{
		// �������� Ȯ���Ͽ� �־��ش�. -> �ȿ��� �������� ��ӹ޴� ���� ã��
		// �־��ִ� ����
		if (false == (*m_Com_StartIter)->is_parent<Renderer_Sprite>())
		{
			continue;
		}
		else
		{
			KPtr<Renderer_Sprite> ThisRender = (*m_Com_StartIter);
			Local_Scale(_Value, _Value * ThisRender->image_size().y / ThisRender->image_size().x, 1.0f);
		}
	}
}

void TheOne::Set_Image_RatioH(const float& _Value)
{
	m_Com_StartIter = m_Componentlist.begin();
	m_Com_EndIter = m_Componentlist.end();

	for (; m_Com_StartIter != m_Com_EndIter; ++m_Com_StartIter)
	{
		// �������� Ȯ���Ͽ� �־��ش�. -> �ȿ��� �������� ��ӹ޴� ���� ã��
		// �־��ִ� ����
		if (false == (*m_Com_StartIter)->is_parent<Renderer_Sprite>())
		{
			continue;
		}
		else
		{
			KPtr<Renderer_Sprite> ThisRender = (*m_Com_StartIter);
			Local_Scale(_Value * ThisRender->image_size().y / ThisRender->image_size().x, _Value, 1.0f);
		}
	}
}



void TheOne::insert_AbsRender(RenderManager* _Render)
{
	m_Com_StartIter = m_Componentlist.begin();
	m_Com_EndIter = m_Componentlist.end();

	for (; m_Com_StartIter != m_Com_EndIter; ++m_Com_StartIter)
	{
		// �������� Ȯ���Ͽ� �־��ش�. -> �ȿ��� �������� ��ӹ޴� ���� ã��
		// �־��ִ� ����
		if (false == (*m_Com_StartIter)->is_parent<Renderer>())
		{
			continue;
		}
		_Render->insert_AbsRenderer((*m_Com_StartIter));
	}

	m_Child_StartIter = m_ChildList.begin();
	m_Child_EndIter = m_ChildList.end();

	for (; m_Child_StartIter != m_Child_EndIter; ++m_Child_StartIter)
	{
		(*m_Child_StartIter)->insert_AbsRender(_Render);
	}
}

void TheOne::insert_AbsCol2D(Collider2DManager* _Col2D)
{
	m_Com_StartIter = m_Componentlist.begin();
	m_Com_EndIter = m_Componentlist.end();

	for (; m_Com_StartIter != m_Com_EndIter; ++m_Com_StartIter)
	{
		// �浹ü�� Ȯ���Ͽ� �־��ش�. -> �ȿ��� �浹ü�� ��ӹ޴� ���� ã��
		// �־��ִ� ����
		if (false == (*m_Com_StartIter)->is_parent<Collider2D>())
		{
			continue;
		}
		_Col2D->insert_AbsCollider2D((*m_Com_StartIter));
	}

	m_Child_StartIter = m_ChildList.begin();
	m_Child_EndIter = m_ChildList.end();

	for (; m_Child_StartIter != m_Child_EndIter; ++m_Child_StartIter)
	{
		(*m_Child_StartIter)->insert_AbsCol2D(_Col2D);
	}
}

void TheOne::save(WriteStream& _Stream)
{
	UINT NewSize = order();
	_Stream.write(&NewSize, sizeof(UINT));

	NewSize = (UINT)name_size() + 1;
	_Stream.write(&NewSize, sizeof(UINT));
	_Stream.write_template(name(), sizeof(wchar_t) * NewSize);

	NewSize = (UINT)m_Componentlist.size();
	_Stream.write(&NewSize, sizeof(UINT));


	std::list<KPtr<Component>>::iterator Com_StartIter = m_Componentlist.begin();
	std::list<KPtr<Component>>::iterator Com_EndIter = m_Componentlist.end();

	for (; Com_StartIter != Com_EndIter; ++Com_StartIter)
	{
		(*Com_StartIter)->save(_Stream);
	}

	std::list<KPtr<TheOne>>::iterator Child_StartIter = m_ChildList.begin();
	std::list<KPtr<TheOne>>::iterator Child_EndIter = m_ChildList.end();
	
	// �ڽ��� ���͸� ������.
	for (; Child_StartIter != Child_EndIter; ++Child_StartIter)
	{
		(*Child_StartIter)->save(_Stream);
	}
}