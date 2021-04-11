#pragma once
enum Weapon
{
	Wep_Default,
	Wep_Plasma,
	Wep_BFG,
	Wep_Chain,
	Wep_Sniper,
	Wep_Rocket
};
class cPlayerMenu : public cComponent
{
	friend class cSystemManager;
public:
	cPlayerMenu(cObject* Owner);
	~cPlayerMenu();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

private:
	float m_Hp;
	float m_Speed;
	Weapon m_Weapon = Wep_Default;
	bool m_AttackAble;
	bool m_InDash;
	bool m_DashAble;
	bool m_Hit;
	bool m_Dead;
	bool m_MeleeAble;
	bool m_Invincible;
	float m_BFGCharging;
	Vec2 m_DashDirection;
	int m_PlasmaAmmo;
	int m_ChainAmmo;
	int m_RocketAmmo;
	int m_SniperAmmo;
	float m_Direction;
	LPDIRECTSOUNDBUFFER m_BFGChargingSound;

public:
	float GetHp() { return m_Hp; }
	void SetHp(float Hp) { m_Hp = Hp; }
	void AddHp(float Hp) { m_Hp += Hp; }
	void Attack(float Dir);
	void FireBFG(float Dir, float Charge);
	void Melee(float Dir);
	void Dash(Vec2 Dir);
	void SetWeapon(Weapon Wep) { m_Weapon = Wep; }
};

