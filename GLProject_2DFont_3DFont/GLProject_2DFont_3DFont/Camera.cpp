#include "Camera.h"

#include <glut.h>
#include <math.h>
#include "MathConst.h"

#include <iostream>

/*OpenGL坐标轴方向：
*	x轴：屏幕左下角->右下角
*	y轴：屏幕左下角->左上角
*	z轴：向外
* 物体摆放方向：面向x轴正方向，头顶朝向y轴正方向
*/
Camera::Camera()
{
	SetEyePos(0.0f, 0.0f, 0.0f);
	SetTargetPos(1.0f, 0.0f, 0.0f);

	m_aspect = 90.0f;
	m_ratioWH = 1.3333333f; //大约对应于宽640，高480
	m_near = 0.1f;
	m_far = 3000.0f;
}

void Camera::SetEyePos(float eyeX, float eyeY, float eyeZ)
{
	m_eyeX = eyeX;
	m_eyeY = eyeY;
	m_eyeZ = eyeZ;
}

void Camera::SetTargetPos(float targetX, float targetY, float targetZ)
{
	m_targetX = targetX;
	m_targetY = targetY;
	m_targetZ = targetZ;
}

/*第三人称环视物体
* 参数：
*	1.距离
*	2.左右摆角
*	3.上下仰角*/
void Camera::SetViewAngleWithTargetFixed(float distance, float rotY, float rotZ)
{
	float rXZ = distance * cos(rotZ * MathConst::PI / 180); //视线向量投影到xz平面后的长度

	m_eyeX = m_targetX - rXZ * cos(rotY * MathConst::PI / 180);
	m_eyeZ = m_targetZ + rXZ * sin(rotY * MathConst::PI / 180);
	m_eyeY = m_targetY - distance * sin(rotZ * MathConst::PI / 180);
}

/*第一人称环视周围
* 参数：
*	1.左右摆角
*	2.上下仰角*/
void Camera::SetViewAngleWithEyeFixed(float rotY, float rotZ)//摄像机不需要设定rotZ
{
	//设向量长度为1
	float rXZ = cos(rotZ * MathConst::PI / 180);//在xz平面上的投影的长度

	m_targetX = m_eyeX + rXZ * cos(rotY * MathConst::PI / 180);
	m_targetZ = m_eyeZ - rXZ * sin(rotY * MathConst::PI / 180);
	m_targetY = m_eyeY + sin(rotZ * MathConst::PI / 180);
}

/* 使用属性域更新视野参数 */
void Camera::UpdatePerspective(float aspect, float ratioWH)
{
	m_aspect = aspect;
	m_ratioWH = ratioWH;

	//修改状态为投影矩阵
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//角度，宽高比，近，远
	gluPerspective(m_aspect, m_ratioWH, m_near, m_far);

	//恢复状态为模型视图矩阵
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/*应用这个摄像机来更新视角*/
void Camera::Apply()
{
	glLoadIdentity();

	gluLookAt(
		m_eyeX, m_eyeY, m_eyeZ,
		m_targetX, m_targetY, m_targetZ,
		0, 1, 0); 
}