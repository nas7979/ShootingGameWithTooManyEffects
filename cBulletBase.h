#pragma once
class cBulletBase : public cComponent
{
public:
	cBulletBase(cObject* Owner);
	~cBulletBase();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

protected:
	float m_Speed;
	float m_Direction;
	float m_Damage;
	bool m_RotateAssigntoDirection = true;

	bool IsOutMap();

public:
	void SetSpeed(float Speed) { m_Speed = Speed; }
	void SetDirection(float Direction) { m_Direction = D3DXToRadian(Direction); }
	float GetDirection() { return D3DXToDegree(m_Direction); }
	void SetDamage(float Damage) { m_Damage = Damage; }
	float GetDamage() { return m_Damage; }
	void SetRotateAssignToDirection(bool Value) { m_RotateAssigntoDirection = Value; }
};

