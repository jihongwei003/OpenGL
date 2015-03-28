#include "TestPlane.h"
#include "TestPlaneData.h"

#include "MathConst.h"
#include <math.h>
#include "ProjectToAxis.h"

TestPlane::TestPlane() : Object()
{
	m_meshModel.LoadMeshDataWithTexFrom3DE(TestPlaneData::vertexNum,
		TestPlaneData::face_indicies, sizeof(TestPlaneData::face_indicies),
		TestPlaneData::vertices, sizeof(TestPlaneData::vertices),
		TestPlaneData::normals, sizeof(TestPlaneData::normals),
		std::string(TestPlaneData::texureFileName),
		TestPlaneData::textures, sizeof(TestPlaneData::textures));

	m_speed = 0;			   
	m_speedMax = 0.3;
	m_speedMin = -0.3; 
	m_speedAcceleration = 0.02; 
	m_speedRecovery = 0.01;     

	m_rotY = 0; //当前转角

	m_rotW = 0; //键盘控制的是rotW！
	m_rotWMax = 1;
	m_rotWMin = -1;
	m_rotWAcceleration = 0.04; //实际的变化速度为0.04-0.02！
	m_rotWRecovery = 0.02;

	m_rotZ = 0; //当前仰角
}

void TestPlane::SetSpeed(float speed)
{
	m_speed = speed;
}

/*根据 速度、转角、仰角 计算 位置
* 计算状态的恢复 */
void TestPlane::Move()
{
	/* 计算状态恢复 */
	if (m_rotW > 0) 
		m_rotW -= m_rotWRecovery; //从1每回减少0.02到0也能转一会儿
	if (m_rotW < 0)
		m_rotW += m_rotWRecovery;

	m_rotY += m_rotW;

	/* 计算侧翻 角速度以弧度为单位 */
	//					  角速度×线速度
	//物理公式：tanθ =  ----------------，θ代表侧翻的角度
	//					     重力加速度 
	//angel = atan(slope)
	//x 的反正切函数值tan - 1x，传回的值在[-pi / 2, pi / 2] 之间
	//m_rotX = -atan(m_rotW * MathConst::A_TO_R * m_speed / MathConst::PHYSICS_G)*10000*5; //没效果啊？//特别小的数

	//只有转角和仰角影响速度方向，侧翻角不影响速度方向
	float lenX = 0;
	float lenY = 0;
	float lenZ = 0;
	ProjectToAxis::CountProjectLenOnAxis(&lenX, &lenY, &lenZ, m_speed, m_rotY, m_rotZ);

	m_x += lenX;
	m_y += lenY;
	m_z -= lenZ; //“-”是因为x轴左侧为z的负方向，而rotY是向左转的！
}


//前进后退
void TestPlane::Forward()
{
	if (m_speed < m_speedMax)
		m_speed += m_speedAcceleration; //这里提升的值其实为Acceleration - Recovery！
}
void TestPlane::Backward()
{
	if (m_speed > m_speedMin)
		m_speed -= m_speedAcceleration;
}

//左右转角
void TestPlane::TurnLeft()
{
	if (m_rotW < m_rotWMax)
		m_rotW += m_rotWAcceleration;
}
void TestPlane::TurnRight()
{
	if (m_rotW > m_rotWMin)
		m_rotW -= m_rotWAcceleration;
}


void TestPlane::Render()
{
	Paint(TestPlaneData::vertexNum); //默认移动方式下的绘制
}