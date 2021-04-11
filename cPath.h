#pragma once
class cPath : public cComponent
{
public:
	cPath(cObject* Owner);
	~cPath();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

private:
	vector<Vec2> m_Points;
	float m_Speed;
	float m_Direction;
	float m_Friction;
	int m_NextPoint;

public:
	void AddPath(Vec2 Goal, Vec2 Cont = Vec2(-1, -1));
	void ClearPath() { m_Points.clear(); m_NextPoint = 0; }
	void SetSpeed(float Speed) { m_Speed = Speed; }
	float GetSpeed() { return m_Speed; }
	float GetDirection() { return D3DXToDegree(m_Direction); }
	void SetFriction(float Friction) { m_Friction = Friction; }
};

