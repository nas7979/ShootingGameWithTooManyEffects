#pragma once
#include "cBulletBase.h"

class cBullet_Homing : public cBulletBase
{
public:
	cBullet_Homing(cObject* Owner);
	~cBullet_Homing();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

private:
	cObject* m_Target;
	float m_RotateSpeed;
	float m_RotateSpeedVel;

public:
	void SetTarget(cObject* Target) { m_Target = Target; }
	void SetRotateSpeed(float Speed) { m_RotateSpeed = Speed; }
	void SetRotateSpeedVel(float Vel) { m_RotateSpeedVel = Vel; }
};

