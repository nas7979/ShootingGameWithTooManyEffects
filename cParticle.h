#pragma once
class cParticle : public cParticle_Base
{
	friend class cParticleManager;
public:
	cParticle();
	~cParticle();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

