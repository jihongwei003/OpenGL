#include "TankChassis.h"
#include "TankChassisData.h"

#include "MathConst.h"
#include <math.h>
#include "ProjectToAxis.h"

#include <iostream>///////////////////////////////

TankChassis::TankChassis() : Object()
{
	m_meshModel.LoadMeshDataWithTexFrom3DE(TankChassisData::vertexNum,
		TankChassisData::face_indicies, sizeof(TankChassisData::face_indicies),
		TankChassisData::vertices, sizeof(TankChassisData::vertices),
		TankChassisData::normals, sizeof(TankChassisData::normals),
		std::string(TankChassisData::texureFileName),
		TankChassisData::textures, sizeof(TankChassisData::textures));

	m_speed = 0;
	m_speedMax = 0.2;
	m_speedMin = -0.2;
	m_speedAcceleration = 0.02;
	m_speedRecovery = 0.01;

	m_rotY = 0; //当前转角

	m_rotW = 0; //键盘控制的是rotW！
	m_rotWMax = 1;
	m_rotWMin = -1;
	m_rotWAcceleration = 0.04; //实际的变化速度为0.04-0.02！
	m_rotWRecovery = 0.02;
}

void TankChassis::SetSpeed(float speed)
{
	m_speed = speed;
}

//继承父类的方法，并计算侧翻角、计算恢复
void TankChassis::Move()
{
	/* 计算状态恢复 */
	if (m_rotW > 0)
		m_rotW -= m_rotWRecovery; //从1每回减少0.02到0也能转一会儿
	if (m_rotW < 0)
		m_rotW += m_rotWRecovery;

	m_rotY += m_rotW;

	//只有转角和仰角影响速度方向，侧翻角不影响速度方向
	float lenX = 0;
	float lenY = 0;
	float lenZ = 0;
	ProjectToAxis::CountProjectLenOnAxis(&lenX, &lenY, &lenZ, m_speed, m_rotY, m_rotZ);

	m_x += lenX;
	m_y += lenY;
	m_z -= lenZ;

}

//前进后退
void TankChassis::Forward()
{
	if (m_speed < m_speedMax)
		m_speed += m_speedAcceleration; //这里提升的值其实为Acceleration - Recovery！
}
void TankChassis::Backward()
{
	if (m_speed > m_speedMin)
		m_speed -= m_speedAcceleration;
}

//左右转角
void TankChassis::TurnLeft()
{
	if (m_rotW < m_rotWMax)
		m_rotW += m_rotWAcceleration;
}
void TankChassis::TurnRight()
{
	if (m_rotW > m_rotWMin)
		m_rotW -= m_rotWAcceleration;
}

void TankChassis::Render()
{
	Paint(TankChassisData::vertexNum);
}