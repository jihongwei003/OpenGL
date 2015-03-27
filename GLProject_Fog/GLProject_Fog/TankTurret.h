#pragma once

#include "Object.h"

class TankTurret : public Object
{
public:
	TankTurret();

	void SetSpeed(float speed);

	void Render();

private:
	float m_speed;
};