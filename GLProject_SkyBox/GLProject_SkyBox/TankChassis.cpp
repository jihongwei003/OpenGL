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

void TankChassis::Render()
{
	Paint(TankChassisData::vertexNum);
}