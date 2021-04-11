#pragma once
#include "cBulletBase.h"
class cBullet : public cBulletBase
{
public:
	cBullet(cObject* Owner);
	~cBullet();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

