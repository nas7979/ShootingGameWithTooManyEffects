#include "DXUT.h"
#include "cBulletBase.h"


cBulletBase::cBulletBase(cObject* Owner)
	:cComponent(Owner)
{
}


cBulletBase::~cBulletBase()
{
}

bool cBulletBase::IsOutMap()
{
	Vec2 Pos = m_pObject->GetPosition();
	float Size = 16;
	return (Pos.x - Size > 1000 || Pos.x + Size < 0 || Pos.y - Size > WINSIZEY || Pos.y + Size < 0);
}
