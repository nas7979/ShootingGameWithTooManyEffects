#pragma once
#include "cBulletBase.h"
class cBullet_Friction : public cBulletBase
{
public:
	cBullet_Friction(cObject* Owner);
	~cBullet_Friction();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

private:
	float m_Friction;
	float m_EndSpeed;

public:
	void SetFriction(float Friction, float EndSpeed) { m_Friction = Friction; m_EndSpeed = EndSpeed; }
};

