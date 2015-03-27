#pragma once

#include "Object.h"

class TankBarrel : public Object
{
public:
	TankBarrel();

	void Render();

	void GetMuzzlePos(float *retX, float *retY, float *retZ); //¼ÆËãÅÚ¿ÚÎ»ÖÃ

private:
	float m_speed;

};