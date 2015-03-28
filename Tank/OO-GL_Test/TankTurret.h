#pragma once

#include "Object.h"
#include "Movable.h"

class TankTurret : public Object , public Movable
{
public:
	TankTurret();

	void SetSpeed(float speed);

	void Move(); 
	void Render();

private:
	float m_speed;
};