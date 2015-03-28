#pragma once

#include "Object.h"
#include "Controllable.h"
#include "Movable.h"

class TankChassis : public Object , public Movable , public Controllable
{
public:
	TankChassis();

	void Render();

	void SetSpeed(float speed);

	/* interface：Movable的实现 */
	void Move(); 
	
	/* interface：Controllable的实现 */
	//前进后退
	void Forward();
	void Backward();

	//左右转角
	void TurnLeft();
	void TurnRight();

	void Raise(){}
	void Bow(){}
	void RollLeft(){}
	void RollRight(){}

private:
	float m_speed;
	float m_speedMax;  //正值
	float m_speedMin;  //负值         
	float m_speedAcceleration; //这里提升的值其实为Acceleration - Recovery！
	float m_speedRecovery;

	float m_rotW;
	float m_rotWMax; //正值
	float m_rotWMin; //负值
	float m_rotWAcceleration;
	float m_rotWRecovery;
};