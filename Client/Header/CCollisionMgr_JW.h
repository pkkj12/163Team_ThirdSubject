#pragma once
#include "Define_JW.h"

class CObj_JW;

// THX HW!
struct CCollisionMgr_JW
{
	static void CheckCollision_SAT	(ObjType_JW eType1, ObjType_JW eType2);
	static bool IsCollide_SAT		(const CObj_JW* Obj1, const CObj_JW* Obj2);
	static void Project				(const CObj_JW* obj, const _vec3 vAxis, float& fOutMin, float& fOutMax);
//
	static void CheckCollision		();
};
