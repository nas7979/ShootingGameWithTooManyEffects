#pragma once

namespace Math
{
	int Random(int Min, int Max);
	float Random(float Min, float Max);
	float RadAngle(Vec2 v1, Vec2 v2);
	float DegAngle(Vec2 v1, Vec2 v2);
	Vec2 RotateVec(Vec2 v, float r);
	float Sign(float Val);

	template <typename T>
	T Lerp(T Start, T End, float P)
	{
		return (End - Start) * P + Start;
	}
}
