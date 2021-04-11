#include "DXUT.h"
#include "cMath.h"

int Math::Random(int Min, int Max)
{
	return (rand() % (Max - Min + 1)) + Min;
}

float Math::Random(float Min, float Max)
{
	Min *= 10000.f;
	Max *= 10000.f;
	return ((((rand() << 15) | rand()) % (int)(Max - Min + 1)) + Min) * 0.0001;
}

float Math::RadAngle(Vec2 v1, Vec2 v2)
{
	return atan2(v2.y - v1.y, v2.x - v1.x);
}

float Math::DegAngle(Vec2 v1, Vec2 v2)
{
	return D3DXToDegree(atan2(v2.y - v1.y, v2.x - v1.x));
}

Vec2 Math::RotateVec(Vec2 v, float r)
{
	r = D3DXToRadian(r);
	return Vec2(v.x * cos(r) + v.y * -sin(r), v.x * sin(r) + v.y * cos(r));
}

float Math::Sign(float Val)
{
	if (Val > 0) return 1;
	if (Val < 0) return -1;
	return 0;
}
