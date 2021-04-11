#pragma once
class cParticle_Anim : public cParticle_Base
{
	friend class cParticleManager;
public:
	cParticle_Anim();
	~cParticle_Anim();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

private:
	vector<Texture*>* m_CurAnimation;
	int m_CurFrame;
	float m_AnimSpeed;
	float m_Timer;

public:
	void SetAnimation(vector<Texture*>* Anim, float Speed) { m_CurAnimation = Anim; m_AnimSpeed = m_Timer = Speed; m_Image = Anim->at(0); }
	void SetFrame(int Frame) { m_CurFrame = Frame; }
};

