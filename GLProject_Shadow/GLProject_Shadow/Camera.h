#pragma once

#include "GLPointf.h"
#include "GLVector3Df.h"
#include "Texture.h"

/*OpenGL坐标轴方向：
*	x轴：屏幕左下角->右下角
*	y轴：屏幕左下角->左上角
*	z轴：向外
* 物体摆放方向：面向x轴正方向，头顶朝向y轴正方向
*/
class Camera{
public:
	Camera();

	void SetEyePos(float eyeX, float eyeY, float eyeZ);
	void SetTargetPos(float targetX, float targetY, float targetZ);

	/*第三人称环视物体
	* 参数：
	*	1.距离	
	*	2.左右摆角
	*	3.上下仰角*/
	void SetViewAngleWithTargetFixed(float distance, float rotY, float rotZ);

	/*第一人称环视周围
	* 参数：
	*	1.左右摆角
	*	2.上下仰角*/
	void SetViewAngleWithEyeFixed(float rotY, float rotZ);

	/* 应用摄像机 */
	void Apply();

	/* 更新视野参数 */
	void UpdatePerspective(float aspect, float ratioWH);

	/* 以下为绘制3D光晕 */

	//计算视景体的6个面的方程系数
	void UpdateFrustum(); 
	//绘制透镜耀斑
	void RenderLensFlare(GLPointf p); 

private:
	bool IsPointInFrustum(GLPointf p); //判断一个点是否在视景体内
	bool IsOccluded(GLPointf p); //测试某个点是否位于当前场景物体的前面

	void RenderHalo(GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLPointf p, GLfloat scale);
	void RenderGlow(GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLPointf p, GLfloat scale);
	void RenderBigGlow(GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLPointf p, GLfloat scale);
	void RenderStreaks(GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLPointf p, GLfloat scale);

	GLPointf m_eyePos;
	GLPointf m_targetPos;

	/*关于视野的属性*/
	float m_aspect;  //视野广度角度
	float m_ratioWH; //宽高比
	float m_near;
	float m_far;

	//视景体的6个面的方程系数
	float m_Frustum[6][4];

	//光晕纹理
	Texture m_HaloTexture;
	Texture m_GlowTexture;
	Texture m_BigGlowTexture;
	Texture m_StreakTexture;

	//视线方向单位向量
	GLVector3Df m_directionVector;

	//float m_HeadingDegrees;/////////////////////////////////////////////
	//float m_PitchDegrees;
};

inline void Camera::SetEyePos(float eyeX, float eyeY, float eyeZ)
{
	m_eyePos.x = eyeX;
	m_eyePos.y = eyeY;
	m_eyePos.z = eyeZ;
}

inline void Camera::SetTargetPos(float targetX, float targetY, float targetZ)
{
	m_targetPos.x = targetX;
	m_targetPos.y = targetY;
	m_targetPos.z = targetZ;
}