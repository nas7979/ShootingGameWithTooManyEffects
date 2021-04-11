#pragma once
class cParticle_Emitter : public cParticle_Base
{
public:
	cParticle_Emitter();
	~cParticle_Emitter();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

private:
	function<void(cParticle_Emitter* Part)> m_EmitterFunc;
	float m_EmitterSpeed;
	float m_Timer;

public:
	void SetEmitterFunc(float Speed, function<void(cParticle_Emitter* Part)> Func) { m_EmitterSpeed = m_Timer = Speed; m_EmitterFunc = Func; }
};

