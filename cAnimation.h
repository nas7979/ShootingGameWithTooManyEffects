#pragma once
struct Animation
{
	string Key;
	vector<Texture*>* Image;
	float Speed;
	bool Loop;
	int Size;
};
class cAnimation : public cComponent
{
public:
	cAnimation(cObject* Owner);
	~cAnimation();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

private:
	map<string, Animation*> m_Animations;
	Animation* m_CurAnimation;
	int m_CurFrame;
	float m_Speed;
	float m_Timer;
	bool m_Loop;

public:
	void AddAnimation(string Key, string ResourceKey, float Speed, bool Loop);
	void SetAnimation(string Key);
};

