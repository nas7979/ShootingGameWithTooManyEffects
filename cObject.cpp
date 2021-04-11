#include "DXUT.h"
#include "cObject.h"


cObject::cObject()
{
}


cObject::~cObject()
{
}

void cObject::Release()
{
	for (auto& iter : m_Components)
	{
		iter->Release();
		SAFE_DELETE(iter);
	}
	m_Components.clear();
	if (m_Alarm != nullptr)
	{
		delete[] m_Alarm;
	}
}

void cObject::SetAlarmSize(int Size)
{
	m_Alarm = new float[Size];
	m_AlarmSize = Size;
	for (int i = 0; i < Size; i++)
	{
		m_Alarm[i] = -100;
	}
}
