#pragma once

#include "Object.h"

class TankChassis : public Object
{
public:
	TankChassis();

	void Render();

	void SetSpeed(float speed);

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