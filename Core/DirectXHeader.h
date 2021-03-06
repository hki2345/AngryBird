#pragma once
#include <d3d11.h>  // 五昔伯希
#include <d3dcompiler.h> // 拾戚希遂 巨獄焔伯希
#include <DirectXPackedVector.h> // 陥戚刑闘拭辞 床澗 困斗魚是税 舘是 更 益訓 敗呪級
#include <Box2D\Box2D.h>


#if X64
#if _DEBUG
#pragma comment(lib, "Box2D64_DEBUG")
#else if NDEBUG
#pragma comment(lib, "Box2D64_RELEASE")
#endif
#else if WIN32
#if _DEBUG
#pragma comment(lib, "Box2D86_DEBUG")
#else if NDEBUG
#pragma comment(lib, "Box2D86_RELEASE")
#endif
#endif // DEBUG

// 虞戚崎君軒 戚嬢爽澗 暗
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")


#define KPI 3.14159265358979323846264338327950288f

class int_compare
{
public:
	union
	{
		struct
		{
			int X;
			int Y;
		};

		struct
		{
			int Left;
			int Right;
		};

		__int64 m_i64;
	};

public:
	operator __int64()
	{
		return *((__int64*)&X);
	}

public:
	int_compare(int _X, int _Y) : X(_X), Y(_Y) {}
	int_compare(__int64 _Value) : m_i64(_Value) {}
	int_compare() {}
};

class KVector2
{

public:
	// 戚採歳精 紫叔 獣蝿遂 困斗研 姥薄馬檎辞 蟹尽揮 鎧遂績しし
	// 戚硯 蒸澗 因遂端 -> 識情蒸戚 郊稽 蓄亜--- 姥繕端人 旭精 呼喰
	union
	{
		// 陥戚刑闘X 拭識 Vector3莫縦聖 走据馬澗 依戚 赤生蟹
		// 拙遂馬澗 困斗澗 戚 困斗(x, y, z, w)稽 鋼発廃陥.
		// 魚虞辞 戚 困斗研 呉獄稽 亜走壱 赤澗 依績
		DirectX::XMFLOAT2 m_Vector;

		b2Vec2 m_b2Vec2;

		float s[2];

		// 戚硯蒸澗 姥繕端 -> 識情蒸戚 郊稽 蓄亜背辞 昔切葵拭 羨悦亜管
		// 戚格適掘什 魚是税 姥繕端亜 焼還
		struct
		{
			float x;
			float y;
		};

		struct
		{
			float m1;
			float m2;
		};

		struct
		{
			int ix;
			int iy;
		};

		__int64 m_i64;
	};

public:
	KVector2() : m_Vector(.0f, .0f) {}
	KVector2(__int64 _Value) : m_i64(_Value) {}
	KVector2(float _Value) : m_Vector(_Value, _Value) {}
	KVector2(float _x, float _y) : m_Vector(_x, _y) {}
	KVector2(int _x, int _y) : ix(_x), iy(_y) {}
	KVector2(const KVector2& _Other) : m_Vector(_Other.x, _Other.y) {}

	// 困斗拭辞 益凶壕錘 巴茎 4鯵研 軒堂拭巨照 背 亜舌 匙牽惟 尻至 拝 呪 赤惟 煽舌 焼森 煽舌舘域拭辞 採斗 しし
	KVector2(const DirectX::XMVECTOR& _Other) { DirectX::XMStoreFloat2(&m_Vector, _Other); }
	KVector2(const b2Vec2& _Other) { m_b2Vec2 = b2Vec2(_Other); }


public:
	static const KVector2 Zero;
	static const KVector2 Left;
	static const KVector2 Right;
	static const KVector2 Up;
	static const KVector2 Down;


	void set_vector2(const float& _X, const float& _Y) { x = _X; y = _Y; }
	float x_part() const { return x * .5f; }
	float y_part() const { return y * .5f; }

	KVector2 IntToFloat() const
	{
		return KVector2((float)ix, (float)iy);
	}

	KVector2 FloatToInt() const
	{
		return KVector2(ix, iy);
	}

	KVector2 operator + (const KVector2& _Other)
	{
		return{ x + _Other.x, y + _Other.y };
	}

	KVector2& operator = (const KVector2& _Value)
	{
		m_Vector = _Value.m_Vector;
		return *this;
	}


	KVector2 operator + (const KVector2& _Value) const
	{
		return KVector2(x + _Value.x, y + _Value.y);
	}
	KVector2 operator * (const KVector2& _Value) const
	{
		return KVector2(x * _Value.x, y * _Value.y);
	}
	KVector2 operator - (const KVector2& _Value) const
	{
		return KVector2(x - _Value.x, y - _Value.y);
	}
	KVector2 operator / (const KVector2& _Value) const
	{
		return KVector2(x / _Value.x, y / _Value.y);
	}

	KVector2 operator + (const float& _Value) const
	{
		return KVector2(x + _Value, y + _Value);
	}
	KVector2 operator * (const float& _Value)const
	{
		return KVector2(x * _Value, y * _Value);
	}
	KVector2 operator - (const float& _Value)const
	{
		return KVector2(x - _Value, y - _Value);
	}
	KVector2 operator / (const float& _Value)const
	{
		return KVector2(x / _Value, y / _Value);
	}



	KVector2& operator += (const KVector2& _Value)
	{
		x += _Value.x;
		y += _Value.y;

		return *this;
	}
	KVector2& operator -= (const KVector2& _Value)
	{
		x -= _Value.x;
		y -= _Value.y;

		return *this;
	}
	KVector2& operator *= (const KVector2& _Value)
	{
		x *= _Value.x;
		y *= _Value.y;

		return *this;
	}
	KVector2& operator /= (const KVector2& _Value)
	{
		x /= _Value.x;
		y /= _Value.y;

		return *this;
	}

	bool operator == (const KVector2& _Value)
	{
		return (x == _Value.x && y == _Value.y);
	}
	bool operator != (const KVector2& _Value)
	{
		return (x != _Value.x && y != _Value.y);
	}


	bool operator == (const KVector2& _Value) const
	{
		return (x == _Value.x && y == _Value.y);
	}
	bool operator != (const KVector2& _Value) const
	{
		return (x != _Value.x || y != _Value.y);
	}
	bool operator >= (const KVector2& _Value) const
	{
		return (x >= _Value.x && y >= _Value.y);
	}
	bool operator <= (const KVector2& _Value) const
	{
		return (x <= _Value.x && y <= _Value.y);
	}



	operator DirectX::XMVECTOR() const
	{
		return DirectX::XMLoadFloat2(&m_Vector);
	}

	operator b2Vec2() const
	{
		return b2Vec2(m_b2Vec2);
	}
	operator __int64() const
	{
		return m_i64;
	}


	float length() const
	{
		return sqrtf(x*x + y*y);
	}

	float distance() const
	{
		return sqrtf((x) * (x) + (y) * (y));
	}

	float distance(const KVector2& _Value) const
	{
		return sqrtf((x - _Value.x) * (x - _Value.x) + (y - _Value.y) * (y - _Value.y));
	}

	void normalize()
	{
		*this = DirectX::XMVector2Normalize(*this);
	}

	const float dot(const KVector2& _Left, const KVector2& _Right)
	{
		KVector2 Value = DirectX::XMVector2Dot(_Left, _Right);
		return Value.x;
	}

	float dot(const KVector2& _Other) const
	{
		return x * _Other.x + y * _Other.y;
	}

	KVector2& y_reverse()
	{
		y *= -1.0f;
		return *this;
	}

	float x_ratio() const
	{
		if (0 > y)
		{
			return .0f;
		}

		return x / y;
	}
	float y_ratio() const
	{
		if (0 > x)
		{
			return .0f;
		}

		return y / x;
	}


};
typedef KVector2 KPoint;


class KVector3
{
public:
	// 戚採歳精 紫叔 獣蝿遂 困斗研 姥薄馬檎辞 蟹尽揮 鎧遂績しし
	// 戚硯 蒸澗 因遂端 -> 識情蒸戚 郊稽 蓄亜--- 姥繕端人 旭精 呼喰
	union
	{
		// 陥戚刑闘X 拭識 Vector3莫縦聖 走据馬澗 依戚 赤生蟹
		// 拙遂馬澗 困斗澗 戚 困斗(x, y, z, w)稽 鋼発廃陥.
		// 魚虞辞 戚 困斗研 呉獄稽 亜走壱 赤澗 依績
		DirectX::XMFLOAT3 m_Vector;

		float s[3];

		// 戚硯蒸澗 姥繕端 -> 識情蒸戚 郊稽 蓄亜背辞 昔切葵拭 羨悦亜管
		// 戚格適掘什 魚是税 姥繕端亜 焼還
		struct
		{
			KVector2 m_Pos;
			float Radius;
		};

		struct
		{
			float x;
			float y;
			float z;
		};
		
		struct
		{
			float m1;
			float m2;
			float m3;
		};

		struct
		{
			KVector2 m_Vector2;
			float Value;
		};
	};

public:
	KVector3() : m_Vector(.0f, .0f, .0f) {}
	KVector3(float _Value) : m_Vector(_Value, _Value, _Value) {}
	KVector3(float _x, float _y, float _z) : m_Vector(_x, _y, _z) {}
	KVector3(const KVector2& _Other, float _z) : m_Vector(_Other.x, _Other.y, _z) {}
	KVector3(const KVector3& _Other) : m_Vector(_Other.x, _Other.y, _Other.z) {}

	// 困斗拭辞 益凶壕錘 巴茎 4鯵研 軒堂拭巨照 背 亜舌 匙牽惟 尻至 拝 呪 赤惟 煽舌 焼森 煽舌舘域拭辞 採斗 しし
	KVector3(const DirectX::XMVECTOR& _Other) { DirectX::XMStoreFloat3(&m_Vector, _Other); }


public:
	static const KVector3 Zero;
	static const KVector3 Left;
	static const KVector3 Right;
	static const KVector3 Up;
	static const KVector3 Down;
	static const KVector3 Forword;
	static const KVector3 Back;
	static const KVector3 One; // 事薗走舛ししし


	void set_vector3(const float& _X, const float& _Y, const float& _Z) { x = _X; y = _Y; z = _Z; }
	float x_part() { return x * .5f; }
	float y_part() { return y * .5f; }
	float z_part() { return z * .5f; }

	KVector3 operator + (const KVector3& _Other)
	{
		return{ x + _Other.x, y + _Other.y , z + _Other.z};
	}

	KVector3& operator = (const KVector3& _Value)
	{
		m_Vector = _Value.m_Vector;
		return *this;
	}

	KVector3& operator = (const DirectX::XMVECTOR& _Value)
	{
		DirectX::XMStoreFloat3(&m_Vector, _Value);
		return *this;
	}
	KVector3 operator + (const KVector3& _Value) const
	{
		return KVector3(x + _Value.x, y + _Value.y, z + _Value.z);
	}
	KVector3 operator * (const KVector3& _Value) const
	{
		return KVector3(x * _Value.x, y * _Value.y, z * _Value.z);
	}
	KVector3 operator - (const KVector3& _Value) const
	{
		return KVector3(x - _Value.x, y - _Value.y, z - _Value.z);
	}
	KVector3 operator / (const KVector3& _Value) const
	{
		return KVector3(x / _Value.x, y / _Value.y, z / _Value.z);
	}

	KVector3 operator + (const float& _Value) const
	{
		return KVector3(x + _Value, y + _Value, z + _Value);
	}
	KVector3 operator * (const float& _Value)const
	{
		return KVector3(x * _Value, y * _Value, z * _Value);
	}
	KVector3 operator - (const float& _Value)const
	{
		return KVector3(x - _Value, y - _Value, z - _Value);
	}
	KVector3 operator / (const float& _Value)const
	{
		return KVector3(x / _Value, y / _Value, z / _Value);
	}



	KVector3& operator += (const KVector3& _Value)
	{
		x += _Value.x;
		y += _Value.y;
		z += _Value.z;

		return *this;
	}
	KVector3& operator -= (const KVector3& _Value)
	{
		x -= _Value.x;
		y -= _Value.y;
		z -= _Value.z;

		return *this;
	}
	KVector3& operator *= (const KVector3& _Value)
	{
		x *= _Value.x;
		y *= _Value.y;
		z *= _Value.z;

		return *this;
	}
	KVector3& operator /= (const KVector3& _Value)
	{
		x /= _Value.x;
		y /= _Value.y;
		z /= _Value.z;

		return *this;
	}

	bool operator == (const KVector3& _Value) const
	{
		return (x == _Value.x && y == _Value.y && z == _Value.z);
	}
	bool operator != (const KVector3& _Value) const
	{
		return (x != _Value.x && y != _Value.y && z != _Value.z);
	}


	operator DirectX::XMVECTOR() const
	{
		return DirectX::XMLoadFloat3(&m_Vector);
	}

	const KVector3 dot(const KVector3& _Left, const KVector3& _Right)
	{
		KVector3 Value = DirectX::XMVector3Dot(_Left, _Right);
		return Value.x;
	}

	float dot(const KVector3& _Other) const
	{
		KVector3 Value = DirectX::XMVector3Dot(*this, _Other);
		return Value.x;
	}

	// 雁尻備 託据戚 株焼遭陥.しししししししし
	KVector3 cross(const KVector2& _Left, const KVector2& _Right) const
	{
		return DirectX::XMVector3Cross(_Left, _Right);
	}

	// 雁尻備 託据戚 株焼遭陥.しししししししし
	KVector3 cross(const KVector2& _Right) const
	{
		return DirectX::XMVector3Cross(*this, _Right);
	}


	// 雁尻備 託据戚 株焼遭陥.しししししししし
	KVector3 cross(const KVector3& _Right) const
	{
		KVector3 Temp = *this * KPI / 180;
		return DirectX::XMVector3Cross(Temp, _Right);
	}

	// 3託据 困斗 暗軒 因縦 -- 据繊拭辞 困斗 -> 3託据 砧 疎妊拭辞税 暗軒
	float length() const
	{
		return sqrtf(x*x + y*y + z*z);
	}

	float diameter() const
	{
		return Radius * 2.0f;
	}

	KVector3& normalize()
	{
		return *this = DirectX::XMVector3Normalize(*this);
	}


	void Absolute()
	{
		x = fabsf(x); y = fabsf(y); z = fabsf(z);
	}
};
typedef KVector3 KCircle;

#define KRGBA(r, g, b, a) ( (COLORREF)(((BYTE)(r) | ((COLORREF)((BYTE)(g))<<8)) | ((COLORREF)(BYTE)(b))<<16 | ((COLORREF)(BYTE)(a))<<24 )

class KVector4
{
public:
	// 戚採歳精 紫叔 獣蝿遂 困斗研 姥薄馬檎辞 蟹尽揮 鎧遂績しし
	// 戚硯 蒸澗 因遂端 -> 識情蒸戚 郊稽 蓄亜--- 姥繕端人 旭精 呼喰
	union
	{
		// 陥戚刑闘X 拭識 Vector3莫縦聖 走据馬澗 依戚 赤生蟹
		// 拙遂馬澗 困斗澗 戚 困斗(x, y, z, w)稽 鋼発廃陥.
		// 魚虞辞 戚 困斗研 呉獄稽 亜走壱 赤澗 依績
		DirectX::XMFLOAT4 m_Vector;
		b2Vec2		m_b2Vec2;
		KVector2	m_Vector2;
		KVector3	m_Vector3;

		float s[4];
		
		
		// 戚硯蒸澗 姥繕端 -> 識情蒸戚 郊稽 蓄亜背辞 昔切葵拭 羨悦亜管
		// 戚格適掘什 魚是税 姥繕端亜 焼還
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};

		struct
		{
			float m1;
			float m2;
			float m3;
			float m4;
		};

		struct
		{
			KVector2 m_Pos;
			KVector2 m_Size;
		};

		struct
		{
			KVector2 m_Front;
			KVector2 m_Back;
		};

		struct
		{
			float r;
			float g;
			float b;
			float a;
		};
	};

public:
	static const KVector4 Left;
	static const KVector4 Right;
	static const KVector4 Up;
	static const KVector4 Down;
	static const KVector4 Forword;
	static const KVector4 Back;
	static const KVector4 Zero;
	static const KVector4 One; // 事薗走舛ししし


	static const KVector4 Color_None;
	static const KVector4 White;
	static const KVector4 Black;
	static const KVector4 Red;
	static const KVector4 Green;
	static const KVector4 Blue;
	static const KVector4 Yellow;
	static const KVector4 Majenta;
	static const KVector4 Cyan;
	static const KVector4 Gray;


public:
	KVector4() : m_Vector(.0f, .0f, .0f, .0f) {}
	KVector4(float _Value) : m_Vector(_Value, _Value, _Value, _Value) {}
	KVector4(float _x, float _y) : m_Vector(_x, _y, .0f, .0f) {}
	KVector4(float _x, float _y, float _z) : m_Vector(_x, _y, _z, .0f) {}
	KVector4(float _x, float _y, float _z, float _w) : m_Vector(_x, _y, _z, _w) {}
	KVector4(float _x, float _y, const KVector2& _Vec) : m_Front(_x, _y), m_Back(_Vec){}
	KVector4(const KVector4& _Other) : m_Vector(_Other.x, _Other.y, _Other.z, _Other.w) {}
	KVector4(const KVector2& _Other1, const KVector2& _Other2) : m_Front(_Other1), m_Back(_Other2) {}
	KVector4(const KVector3& _Other) : m_Vector(_Other.x, _Other.y, _Other.z, .0f) {}
	KVector4(const KVector2& _Other) : m_Vector(_Other.x, _Other.y, .0f, .0f) {}
	KVector4(const KVector2& _Other, const float& _V1) : m_Vector(_Other.x, _Other.y, _V1, .0f) {}
	KVector4(const KVector2& _Other, const float& _V1, const float& _V2) : m_Vector(_Other.x, _Other.y, _V1, _V2) {}

	// 困斗拭辞 益凶壕錘 巴茎 4鯵研 軒堂拭巨照 背 亜舌 匙牽惟 尻至 拝 呪 赤惟 煽舌 焼森 煽舌舘域拭辞 採斗 しし
	KVector4(const DirectX::XMVECTOR& _Other) { DirectX::XMStoreFloat4(&m_Vector, _Other); }

	
public:
	float left() const { return m_Pos.x - m_Size.x_part(); }
	float right() const { return m_Pos.x + m_Size.x_part(); }
	float bottom() const { return m_Pos.y - m_Size.y_part(); }
	float top() const { return m_Pos.y + m_Size.y_part(); }

	KVector2 left_top() const { return{ left(), top() }; }
	KVector2 left_bottom() const { return{ left(), bottom() }; }
	KVector2 right_top() const { return{ right(), top() }; }
	KVector2 right_bottom() const { return{ right(), bottom() }; }

	float x_part() { return x * .5f; }
	float y_part() { return y * .5f; }
	float z_part() { return z * .5f; }
	float w_part() { return w * .5f; }

	UINT color_to_reverse255() const
	{
		return KRGBA((UINT)(r * 255), (UINT)(g * 255), (UINT)(b * 255), (UINT)(a * 255)));
	}

	KVector4& operator = (const KVector4& _Value)
	{
		m_Vector = _Value.m_Vector;
		return *this;
	}

	KVector4& operator = (const KVector3& _Value)
	{
		m_Vector3 = _Value;
		return *this;
	}

	KVector4& operator = (const DirectX::XMVECTOR& _Value)
	{
		DirectX::XMStoreFloat4(&m_Vector, _Value);
		return *this;
	}

	KVector4& operator = (const float& _Value)
	{
		m_Vector = { _Value, _Value, _Value, _Value };
		return *this;
	}

	KVector4 operator + (const KVector4& _Value) const
	{
		return KVector4(x + _Value.x, y + _Value.y, z + _Value.z, w + _Value.w);
	}
	KVector4 operator * (const KVector4& _Value) const
	{
		return KVector4(x * _Value.x, y * _Value.y, z * _Value.z, w * _Value.w);
	}
	KVector4 operator - (const KVector4& _Value) const
	{
		return KVector4(x - _Value.x, y - _Value.y, z - _Value.z, w - _Value.w);
	}
	KVector4 operator / (const KVector4& _Value) const
	{
		KVector4 temp;

		if (0 != _Value.x) { temp.x = x / _Value.x; } else { temp.x; }
		if (0 != _Value.y) { temp.y = y / _Value.y; } else { temp.y; }
		if (0 != _Value.z) { temp.z = z / _Value.z; } else { temp.z; }
		if (0 != _Value.w) { temp.w = w / _Value.w; } else { temp.w; }

		return temp;
	}

	KVector2 operator + (const KVector2& _Value) const
	{
		return KVector2(x + _Value.x, y + _Value.y);
	}
	KVector2 operator * (const KVector2& _Value) const
	{
		return KVector2(x * _Value.x, y * _Value.y);
	}
	KVector2 operator - (const KVector2& _Value) const
	{
		return KVector2(x - _Value.x, y - _Value.y);
	}
	KVector2 operator / (const KVector2& _Value) const
	{
		KVector2 temp;

		if (0 != _Value.x) { temp.x = x / _Value.x; }
		else { temp.x; }
		if (0 != _Value.y) { temp.y = y / _Value.y; }
		else { temp.y; }

		return temp;
	}

	KVector4 operator + (const float& _Value) const
	{
		return KVector4(x + _Value, y + _Value, z + _Value);
	}
	KVector4 operator * (const float& _Value)const
	{
		return KVector4(x * _Value, y * _Value, z * _Value);
	}
	KVector4 operator - (const float& _Value)const
	{
		return KVector4(x - _Value, y - _Value, z - _Value);
	}
	KVector4 operator / (const float& _Value)const
	{
		return KVector4(x / _Value, y / _Value, z / _Value);
	}



	KVector4& operator += (const float& _Value)
	{
		x += _Value;
		y += _Value;
		z += _Value;
		w += _Value;

		return *this;
	}
	KVector4& operator -= (const float& _Value)
	{
		x -= _Value;
		y -= _Value;
		z -= _Value;
		w -= _Value;

		return *this;
	}
	KVector4& operator *= (const float& _Value)
	{
		x *= _Value;
		y *= _Value;
		z *= _Value;
		w *= _Value;

		return *this;
	}
	KVector4& operator /= (const float& _Value)
	{
		{ x /= _Value; }
		{ y /= _Value; }
		{ z /= _Value; }
		{ w /= _Value; }

		return *this;
	}


	KVector4& operator += (const KVector4& _Value)
	{
		x += _Value.x;
		y += _Value.y;
		z += _Value.z;
		w += _Value.w;

		return *this;
	}
	KVector4& operator -= (const KVector4& _Value)
	{
		x -= _Value.x;
		y -= _Value.y;
		z -= _Value.z;
		w -= _Value.w;

		return *this;
	}
	KVector4& operator *= (const KVector4& _Value)
	{
		x *= _Value.x;
		y *= _Value.y;
		z *= _Value.z;
		w *= _Value.w;

		return *this;
	}
	KVector4& operator /= (const KVector4& _Value)
	{
		{ x /= _Value.x; }
		{ y /= _Value.y; }
		{ z /= _Value.z; }
		{ w /= _Value.w; }

		return *this;
	}

	bool operator == (const KVector4& _Value)
	{
		return (x == _Value.x && y == _Value.y && z == _Value.z && w == _Value.w );
	}
	bool operator != (const KVector4& _Value) const
	{
		return (x != _Value.x || y != _Value.y || z != _Value.z || w != _Value.w);
	}
	bool operator >= (const KVector4& _Value)
	{
		return (x == _Value.x && y == _Value.y && z == _Value.z && w == _Value.w);
	}
	bool operator <= (const KVector4& _Value) const
	{
		return (x != _Value.x || y != _Value.y || z != _Value.z || w != _Value.w);
	}

	operator KVector2() const
	{
		return{ m_Vector.x, m_Vector.y };
	}

	operator DirectX::XMVECTOR() const
	{
		return DirectX::XMLoadFloat4(&m_Vector);
	}

public:
	static KVector4 Dot(const KVector4& _Left, const KVector4& _Right)
	{
		KVector4 Value = DirectX::XMVector4Dot(_Left, _Right);
		return Value.x;
	}

	float Dot(const KVector4& _Other) const
	{
		KVector4 Value = DirectX::XMVector4Dot(*this, _Other);
		return Value.x;
	}

	void Normalize()
	{
		*this = DirectX::XMVector4Normalize(*this);
	}

	KVector3 Vec3lize()
	{
		return KVector3(x, y, z);
	}
};

typedef KVector4 KColor;
typedef KVector4 KRect;
typedef KVector4 KVector;



class KMatrix
{
public:
	union
	{
		DirectX::XMFLOAT4X4 m_Mat;

		// 伸舘是稽 亜走壱 赤奄 是敗
		struct
		{
			KVector4 vec1;
			KVector4 vec2;
			KVector4 vec3;
			KVector4 vec4;
		};

		float m[4][4];
	};

public:
	KMatrix() 	{}

	KMatrix(const KMatrix& _Other)
	{
		memcpy_s(this, sizeof(KMatrix), &_Other, sizeof(KMatrix));
	}

	KMatrix(const DirectX::XMMATRIX& _Other)
	{
		DirectX::XMStoreFloat4x4(&m_Mat, _Other);
	}


public:
	operator DirectX::XMMATRIX() const
	{
		return DirectX::XMLoadFloat4x4(&m_Mat);
	}


	KMatrix& operator= (const KMatrix& _Other)
	{
		memcpy_s(this, sizeof(KMatrix), &_Other, sizeof(KMatrix));
		return *this;
	}

	KMatrix& operator= (const DirectX::XMMATRIX& _Other)
	{
		DirectX::XMStoreFloat4x4(&m_Mat, _Other);
		return *this;
	}

	KMatrix operator*(const DirectX::XMMATRIX& _Value) const
	{
		return DirectX::XMMatrixMultiply(*this, _Value);
	}

public:
	KMatrix& Identity()
	{
		*this = DirectX::XMMatrixIdentity();
		return *this;
	}

	void Scale(const KVector4& _Scale)
	{
		*this = DirectX::XMMatrixScaling(_Scale.x, _Scale.y, _Scale.z);
		return;
	}

	void Rotate_X(float _Value)
	{
		*this = DirectX::XMMatrixRotationX(_Value);
		return;
	}

	void Rotate_Y(float _Value)
	{
		*this = DirectX::XMMatrixRotationY(_Value);
		return;
	}

	void Rotate_Z(float _Value)
	{
		*this = DirectX::XMMatrixRotationZ(_Value);
		return;
	}

	void Translation(const KVector4& _Value)
	{
		*this = DirectX::XMMatrixTranslation(_Value.x, _Value.y, _Value.z);
		return;
	}

	// 穿帖楳慶 - 企唖 奄層 企暢
	void TransPose()
	{
		*this = DirectX::XMMatrixTranspose(*this);
		return;
	}

	// 葵聖 鋼発背爽澗 楳慶
	const KMatrix& TransPose_Referance()
	{
		*this = DirectX::XMMatrixTranspose(*this);
		return *this;
	}

	// ViewAt -> 杉球拭 嬢汗疎妊稽 瑳依昔走 -> 照拭辞 号狽困斗研 姥敗
	// 是帖人 背雁 是帖研 皐辞 号狽困斗研 姥敗
	void ViewAt_LH(const KVector4& _CamPos, const KVector4& _LookWorldPos, const KVector4& _Up)
	{
		*this = DirectX::XMMatrixLookAtLH(_CamPos, _LookWorldPos, _Up);
		return;
	}

	// 号狽困斗研 郊稽 隔嬢 左惟敗
	void ViewTo_LH(const KVector4& _CamPos, const KVector4& _LookDirPos, const KVector4& _Up)
	{
		*this = DirectX::XMMatrixLookToLH(_CamPos, _LookDirPos, _Up);
		return;
	}


	// 燈慎 - 据悦
	void Proj_Perspective(float _Fov, float _Width, float _Height, float _Near, float _Far)
	{
		*this = DirectX::XMMatrixPerspectiveFovLH(_Fov, _Width / _Height, _Near, _Far);
		return;
	}

	// 燈慎 - 送嘘
	void Proj_Orthographic(float _Width, float _Height, float _Near, float _Far)
	{
		*this = DirectX::XMMatrixOrthographicLH(_Width, _Height, _Near, _Far);
		return;
	}

	KVector4 Multi_Vector_O(const KVector4& _Value)
	{
		return DirectX::XMVector3TransformCoord(_Value, *this);
	}

	KVector4 Multi_Vector_Z(const KVector4& _Value)
	{
		return DirectX::XMVector3TransformNormal(_Value, *this);
	}
};

class DATA
{
public:
	KMatrix m_W;
	KMatrix m_V;
	KMatrix m_P;
};

class VertShaderFormat
{
public:
	static UINT size_Formet(DXGI_FORMAT _Form);
};