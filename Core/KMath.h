#pragma once
#include "DirectXHeader.h"
#include <vector>

class TransPosition;
class KMath
{
public:
	static const float DegToRad;
	static const float RadToDeg;

public:
	static bool Rect2Rect(TransPosition* _LTrans, TransPosition* _RTrans);
	static bool Circle2Circle(const KCircle& _Left, const KCircle& _Right);
	static bool Circle2Point(const KCircle& _Left, const KPoint& _Right);

	// Vec 1 -> Up, Vec 2 -> Right, Vec 3 -> Pos, Vec 4 -> Scale
	// const  亜 照細澗 戚政澗 食奄辞 厳 葵戚 痕馬悟 伊窒馬奄 凶庚
	static bool Rect2Point(KMatrix& _LTrans, KMatrix& _RTrans);
	static bool Rect2Circle(TransPosition* _LTrans, TransPosition* _RTrans);

	static bool Poly2Point(TransPosition* _LTrans, TransPosition* _RTrans);
	static bool Poly2Circle(TransPosition* _LTrans, TransPosition* _RTrans);
	static bool Poly2Rect(TransPosition* _LTrans, TransPosition* _RTrans);
	static bool Poly2Poly(TransPosition* _LTrans, TransPosition* _RTrans);

	static KVector4 CenterOfGravity(TransPosition* _LTrans);
	static float Area(std::vector<KVector2>* _LVector);

private:
	static bool CheckOBB(KVector _T, const KMatrix& _LTRans, const KMatrix& _RTRans);
	static bool CheckOBB(KVector _T, TransPosition* _LTrans, TransPosition* _RTrans);

	// 虹軒闇 端滴 - 叡駅税 中宜 せせせせせせ
	static bool Poly2PolyOBB(TransPosition* _LTrans, TransPosition* _RTrans);
	static float TofVector2(const KVector2& _T, std::vector<KVector2> _Value);

public:
	KMath();
	~KMath();
};

