#pragma once
#include "DirectXHeader.h"
#include "Collision.h"
#include "FW1FontWrapper.h"

#define DRAW_FONT DebugManager::draw_font


class TransPosition;
class TheOne;
// 어떠한 것을 관리하는게 아니라 어떤 객체에서 디버깅 랜더를 실행하게 한다.
class DebugManager
{
private:
	static bool m_Debug;

public:
	static void Debug_On()
	{
		m_Debug = true;
	}
	static void Debug_Off()
	{
		m_Debug = false;
	}

	static void draw_rect(const KRect& _Rect, const KColor& _Color, const float& _Border = 1);
	static void draw_rect(const KVector2& _Pos, const KVector2& _Size, const KColor& _Color = { .0f, 1.0f, .0f, 1.0f }, const float& _Border = 1);
	static void draw_rect( TransPosition* _One, const COLL_TYPE& _type, const float& _Border, const KColor& _Color = {.0f, 255.0f, .0f, 255.0f});
	static void draw_font(const wchar_t* _pStr, const KVector2& _Pos, const float& _fSize, const KColor& _COLOR = KColor::Black, FW1_TEXT_FLAG _Flag = FW1_TEXT_FLAG::FW1_TOP);

public:
	DebugManager();
	~DebugManager();
};

