#include "DXUT.h"
#include "cAnimation.h"


cAnimation::cAnimation(cObject* Owner)
	:cComponent(Owner)
{
}


cAnimation::~cAnimation()
{
}

void cAnimation::Init()
{
	m_CurFrame = 0;
	m_Timer = 0;
	m_Speed = 0;
}

void cAnimation::Update()
{
	m_Timer -= SYSTEM->GetTimeScale();
	if (m_Timer <= 0)
	{
		m_CurFrame++;
		if (m_CurFrame == m_CurAnimation->Size)
		{
			if (m_Loop)
			{
				m_CurFrame = 0;
			}
			else
			{
				m_Speed = 100000000;
				m_CurFrame--;
			}
		}
		m_Timer = m_Speed;
		GetComponent<cRenderer>()->SetImage(m_CurAnimation->Image->at(m_CurFrame));
	}
}

void cAnimation::Render()
{
}

void cAnimation::Release()
{
	for (auto& iter : m_Animations)
	{
		SAFE_DELETE(iter.second);
	}
}

void cAnimation::AddAnimation(string Key, string ResourceKey, float Speed, bool Loop)
{
	Animation* Temp = new Animation;
	Temp->Key = Key;
	Temp->Image = IMAGE->FindAnimation(ResourceKey);
	Temp->Loop = Loop;
	Temp->Speed = Speed;
	Temp->Size = Temp->Image->size();

	m_Animations.insert(make_pair(Key, Temp));
}

void cAnimation::SetAnimation(string Key)
{
	m_CurAnimation = m_Animations[Key];
	m_Speed = m_CurAnimation->Speed;
	m_Loop = m_CurAnimation->Loop;
	m_Timer = m_Speed;
	m_CurFrame = 0;
	GetComponent<cRenderer>()->SetImage(m_CurAnimation->Image->at(m_CurFrame));
}
