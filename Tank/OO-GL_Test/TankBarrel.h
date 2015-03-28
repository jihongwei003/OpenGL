#pragma once

#include "Object.h"
#include "Movable.h"
//#include "Controllable.h"

class TankBarrel : public Object, public Movable
{
public:
	TankBarrel();

	void Move(); 
	void Render();

	void GetMuzzlePos(float *retX, float *retY, float *retZ); //计算炮口位置

	/* interface：Controllable的实现 */

private:
	float m_speed;

};