#pragma once
class cTimeLine : public cComponent
{
public:
	cTimeLine(cObject* Owner);
	virtual ~cTimeLine();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

protected:
	float m_Cur = 0;
	int m_Last = 0;
	bool m_Loop = false;
	bool m_Pause = false;

public:
	void SetLoop(bool Loop) { m_Loop = Loop; }
	void SetPause(bool Pause) { m_Pause = Pause; }
};

