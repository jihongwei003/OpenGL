#pragma once

#include "Object.h"
#include "Controllable.h"
#include "Movable.h"

class TestPlane : public Object , public Controllable , public Movable
{
public:
	TestPlane();

	void Render();

	void RenderShadow(float lightPos[4]);

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


inline void TestPlane::SetSpeed(float speed)
{
	m_speed = speed;
}

//前进后退
inline void TestPlane::Forward()
{
	if (m_speed < m_speedMax)
		m_speed += m_speedAcceleration; //这里提升的值其实为Acceleration - Recovery！
}
inline void TestPlane::Backward()
{
	if (m_speed > m_speedMin)
		m_speed -= m_speedAcceleration;
}

//左右转角
inline void TestPlane::TurnLeft()
{
	if (m_rotW < m_rotWMax)
		m_rotW += m_rotWAcceleration;
}
inline void TestPlane::TurnRight()
{
	if (m_rotW > m_rotWMin)
		m_rotW -= m_rotWAcceleration;
}