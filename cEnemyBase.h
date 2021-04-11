#pragma once
enum Killedby
{
	Other,
	Plasma,
	Sniper,
	Rocket,
	BFG,
	Melee
};
class cEnemyBase : public cComponent
{
public:
	cEnemyBase(cObject* Owner);
	~cEnemyBase();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

protected:
	float m_Hp;
	int m_Score;
	Killedby m_Killedby = Other;

public:
	void SetHp(float Hp) { m_Hp = Hp; }
	float GetHp() { return m_Hp; }
	void AddHp(float Hp) { m_Hp += Hp; }
	void SetScore(int Score) { m_Score = Score; }
	int GetScore() { return m_Score; }
	void SetKilledby(Killedby By) { m_Killedby = By; }
};

