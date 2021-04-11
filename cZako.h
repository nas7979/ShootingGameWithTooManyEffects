#pragma once
#include "cEnemyBase.h"

class cZako : public cEnemyBase
{
public:
	cZako(cObject* Owner);
	~cZako();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

