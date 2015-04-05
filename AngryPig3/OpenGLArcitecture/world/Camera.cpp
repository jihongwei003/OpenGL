#include "Camera.h"

#include <glut.h>
#include <math.h>
#include "../MathConst.h"

Camera::Camera()
{
	setEyePos(0.0f, 0.0f, 0.0f);
	setCenterPos(1.0f, 0.0f, 0.0f);

	m_aspect = 90.0f;
	m_ratioWH = 1.3333333f;//大约对应于宽640，高480
	m_near = 0.1f;
	m_far = 200.0f;

	setRatioWH(m_ratioWH);
}

/*设定眼睛（观察点）位置*/
void Camera::setEyePos(float eyeX, float eyeY, float eyeZ)
{
	m_eyeX = eyeX;
	m_eyeY = eyeY;
	m_eyeZ = eyeZ;
}

/*设定观察中心（被观察点）位置*/
void Camera::setCenterPos(float centerX, float centerY, float centerZ)
{
	m_centerX = centerX;
	m_centerY = centerY;
	m_centerZ = centerZ;
}

/*固定中心位置，根据观察角度（角度制）设定眼睛位置
*参数：
*1.水平旋转角度（绕y轴旋转的角度）
*2.抬升角度（绕z轴旋转的角度）*/
void Camera::setViewAngleWithCenterFixed(float distance, float rotY, float rotZ)
{
	float rXZ = distance * cos(rotZ * MathConst::A_TO_R);//视线向量投影到xz平面后的长度

	m_eyeX = m_centerX - rXZ * cos(rotY * MathConst::A_TO_R);
	m_eyeZ = m_centerZ + rXZ * sin(rotY * MathConst::A_TO_R);
	m_eyeY = m_centerY - distance * sin(rotZ * MathConst::A_TO_R);
}

/*固定眼睛位置，根据观察角度（角度制）设定观察点位置（相当于第一视角）*/
void Camera::setViewAngleWithEyeFixed(float rotY, float rotZ)
{
	//设向量长度为1

	float rXZ = cos(rotZ * MathConst::A_TO_R);//在xz平面上的投影的长度

	m_centerX = m_eyeX + rXZ * cos(rotY * MathConst::A_TO_R);
	m_centerZ = m_eyeZ - rXZ * sin(rotY * MathConst::A_TO_R);
	m_centerY = m_eyeY + sin(rotZ * MathConst::A_TO_R);
}

/*重设宽高比*/
void Camera::setRatioWH(float ratioWH)
{
	m_ratioWH = ratioWH;
	updatePerspective();
}

/*应用这个摄像机来更新视角*/
void Camera::apply()
{
	glLoadIdentity();

	gluLookAt(
		m_eyeX, m_eyeY, m_eyeZ,
		m_centerX, m_centerY, m_centerZ,
		0, 1, 0);
}

/*使用属性域更新视野参数*/
/*更新视角后恢复矩阵状态为modelView*/
void Camera::updatePerspective()
{
	//修改状态为投影矩阵
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//角度，宽高比，近，远
	gluPerspective(m_aspect, m_ratioWH, m_near, m_far);

	//恢复状态为模型视图矩阵
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}