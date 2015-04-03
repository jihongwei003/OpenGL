#include "Camera.h"

#include <glut.h>
#include <math.h>
#include "MathConst.h"

#include <iostream>//////////////////////////////////////

Camera::Camera()
{
	SetEyePos(0.0f, 0.0f, 0.0f);
	SetTargetPos(1.0f, 0.0f, 0.0f);

	m_directionVector = GLPointf::CalculateVector(m_eyePos, m_targetPos);
	m_directionVector.Normalize();

	m_aspect = 75.0f;
	m_ratioWH = 1.3333333f; //大约对应于宽640，高480
	m_near = 0.1f;
	m_far = 700.0f;
}

/*第三人称环视物体
* 参数：
*	1.距离
*	2.左右摆角
*	3.上下仰角*/
void Camera::SetViewAngleWithTargetFixed(float distance, float rotY, float rotZ)
{
	float rXZ = distance * cos(rotZ * MathConst::PI / 180); //视线向量投影到xz平面后的长度

	m_eyePos.x = m_targetPos.x - rXZ * cos(rotY * MathConst::PI / 180);
	m_eyePos.y = m_targetPos.y - distance * sin(rotZ * MathConst::PI / 180);
	m_eyePos.z = m_targetPos.z + rXZ * sin(rotY * MathConst::PI / 180);

	m_directionVector = GLPointf::CalculateVector(m_eyePos, m_targetPos);
	m_directionVector.Normalize();
}

/*第一人称环视周围
* 参数：
*	1.左右摆角
*	2.上下仰角*/
void Camera::SetViewAngleWithEyeFixed(float rotY, float rotZ)//摄像机不需要设定rotZ
{
	//设向量长度为1
	float rXZ = cos(rotZ * MathConst::PI / 180);//在xz平面上的投影的长度
	
	m_targetPos.x = m_eyePos.x + rXZ * cos(rotY * MathConst::PI / 180);
	m_targetPos.y = m_eyePos.y + sin(rotZ * MathConst::PI / 180);
	m_targetPos.z = m_eyePos.z - rXZ * sin(rotY * MathConst::PI / 180);

	m_directionVector = GLPointf::CalculateVector(m_eyePos, m_targetPos);
	m_directionVector.Normalize();
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
		m_eyePos.x, m_eyePos.y, m_eyePos.z,
		m_targetPos.x, m_targetPos.y, m_targetPos.z,
		0, 1, 0); 
}



// 获得当前视景体的6个平面方程的参数
void Camera::UpdateFrustum()
{
	GLfloat   clip[16];
	GLfloat   proj[16];
	GLfloat   modl[16];
	GLfloat   t;
	//返回投影矩阵
	glGetFloatv(GL_PROJECTION_MATRIX, proj);

	//返回模型变换矩阵
	glGetFloatv(GL_MODELVIEW_MATRIX, modl);

	//计算剪切矩阵，即上面两个矩阵的乘积
	clip[0] = modl[0] * proj[0] + modl[1] * proj[4] + modl[2] * proj[8] + modl[3] * proj[12];
	clip[1] = modl[0] * proj[1] + modl[1] * proj[5] + modl[2] * proj[9] + modl[3] * proj[13];
	clip[2] = modl[0] * proj[2] + modl[1] * proj[6] + modl[2] * proj[10] + modl[3] * proj[14];
	clip[3] = modl[0] * proj[3] + modl[1] * proj[7] + modl[2] * proj[11] + modl[3] * proj[15];

	clip[4] = modl[4] * proj[0] + modl[5] * proj[4] + modl[6] * proj[8] + modl[7] * proj[12];
	clip[5] = modl[4] * proj[1] + modl[5] * proj[5] + modl[6] * proj[9] + modl[7] * proj[13];
	clip[6] = modl[4] * proj[2] + modl[5] * proj[6] + modl[6] * proj[10] + modl[7] * proj[14];
	clip[7] = modl[4] * proj[3] + modl[5] * proj[7] + modl[6] * proj[11] + modl[7] * proj[15];

	clip[8] = modl[8] * proj[0] + modl[9] * proj[4] + modl[10] * proj[8] + modl[11] * proj[12];
	clip[9] = modl[8] * proj[1] + modl[9] * proj[5] + modl[10] * proj[9] + modl[11] * proj[13];
	clip[10] = modl[8] * proj[2] + modl[9] * proj[6] + modl[10] * proj[10] + modl[11] * proj[14];
	clip[11] = modl[8] * proj[3] + modl[9] * proj[7] + modl[10] * proj[11] + modl[11] * proj[15];

	clip[12] = modl[12] * proj[0] + modl[13] * proj[4] + modl[14] * proj[8] + modl[15] * proj[12];
	clip[13] = modl[12] * proj[1] + modl[13] * proj[5] + modl[14] * proj[9] + modl[15] * proj[13];
	clip[14] = modl[12] * proj[2] + modl[13] * proj[6] + modl[14] * proj[10] + modl[15] * proj[14];
	clip[15] = modl[12] * proj[3] + modl[13] * proj[7] + modl[14] * proj[11] + modl[15] * proj[15];

	//提取右面的平面方程系数
	m_Frustum[0][0] = clip[3] - clip[0];
	m_Frustum[0][1] = clip[7] - clip[4];
	m_Frustum[0][2] = clip[11] - clip[8];
	m_Frustum[0][3] = clip[15] - clip[12];
	t = GLfloat(sqrt(m_Frustum[0][0] * m_Frustum[0][0] + m_Frustum[0][1] * m_Frustum[0][1] + m_Frustum[0][2] * m_Frustum[0][2]));
	m_Frustum[0][0] /= t;
	m_Frustum[0][1] /= t;
	m_Frustum[0][2] /= t;
	m_Frustum[0][3] /= t;

	//提取左面的平面方程系数
	m_Frustum[1][0] = clip[3] + clip[0];
	m_Frustum[1][1] = clip[7] + clip[4];
	m_Frustum[1][2] = clip[11] + clip[8];
	m_Frustum[1][3] = clip[15] + clip[12];
	t = GLfloat(sqrt(m_Frustum[1][0] * m_Frustum[1][0] + m_Frustum[1][1] * m_Frustum[1][1] + m_Frustum[1][2] * m_Frustum[1][2]));
	m_Frustum[1][0] /= t;
	m_Frustum[1][1] /= t;
	m_Frustum[1][2] /= t;
	m_Frustum[1][3] /= t;

	//提取下面的平面方程系数
	m_Frustum[2][0] = clip[3] + clip[1];
	m_Frustum[2][1] = clip[7] + clip[5];
	m_Frustum[2][2] = clip[11] + clip[9];
	m_Frustum[2][3] = clip[15] + clip[13];
	t = GLfloat(sqrt(m_Frustum[2][0] * m_Frustum[2][0] + m_Frustum[2][1] * m_Frustum[2][1] + m_Frustum[2][2] * m_Frustum[2][2]));
	m_Frustum[2][0] /= t;
	m_Frustum[2][1] /= t;
	m_Frustum[2][2] /= t;
	m_Frustum[2][3] /= t;

	//提取上面的平面方程系数
	m_Frustum[3][0] = clip[3] - clip[1];
	m_Frustum[3][1] = clip[7] - clip[5];
	m_Frustum[3][2] = clip[11] - clip[9];
	m_Frustum[3][3] = clip[15] - clip[13];
	t = GLfloat(sqrt(m_Frustum[3][0] * m_Frustum[3][0] + m_Frustum[3][1] * m_Frustum[3][1] + m_Frustum[3][2] * m_Frustum[3][2]));
	m_Frustum[3][0] /= t;
	m_Frustum[3][1] /= t;
	m_Frustum[3][2] /= t;
	m_Frustum[3][3] /= t;

	//提取远面的平面方程系数
	m_Frustum[4][0] = clip[3] - clip[2];
	m_Frustum[4][1] = clip[7] - clip[6];
	m_Frustum[4][2] = clip[11] - clip[10];
	m_Frustum[4][3] = clip[15] - clip[14];
	t = GLfloat(sqrt(m_Frustum[4][0] * m_Frustum[4][0] + m_Frustum[4][1] * m_Frustum[4][1] + m_Frustum[4][2] * m_Frustum[4][2]));
	m_Frustum[4][0] /= t;
	m_Frustum[4][1] /= t;
	m_Frustum[4][2] /= t;
	m_Frustum[4][3] /= t;

	//提取近面的平面方程系数
	m_Frustum[5][0] = clip[3] + clip[2];
	m_Frustum[5][1] = clip[7] + clip[6];
	m_Frustum[5][2] = clip[11] + clip[10];
	m_Frustum[5][3] = clip[15] + clip[14];
	t = GLfloat(sqrt(m_Frustum[5][0] * m_Frustum[5][0] + m_Frustum[5][1] * m_Frustum[5][1] + m_Frustum[5][2] * m_Frustum[5][2]));
	m_Frustum[5][0] /= t;
	m_Frustum[5][1] /= t;
	m_Frustum[5][2] /= t;
	m_Frustum[5][3] /= t;
}

//测试一个点或圆是否在视景体内
bool Camera::IsPointInFrustum(GLPointf p)
{
	for (unsigned int i = 0; i < 6; i++)
	{
		if (m_Frustum[i][0] * p.x + m_Frustum[i][1] * p.y + m_Frustum[i][2] * p.z + m_Frustum[i][3] < 0)
		{
			return(false);
		}
	}
	return(true);
}

//测试某个点是否位于当前场景中物体的前面
bool Camera::IsOccluded(GLPointf p)
{
	GLint viewport[4];
	GLdouble mvmatrix[16], projmatrix[16];
	GLdouble winx, winy, winz;
	GLdouble flareZ;
	GLfloat bufferZ;

	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);

	// 返回顶点p在单位立方体中的位置
	gluProject(p.x, p.y, p.z, mvmatrix, projmatrix, viewport, &winx, &winy, &winz);
	flareZ = winz;

	// 读取点(winx,winy)的深度坐标
	glReadPixels(winx, winy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &bufferZ);

	// 如果深度坐标小于点的坐标，则返回true
	if (bufferZ < flareZ)
		return true;
	else
		return false;
}

//绘制透镜耀斑
void Camera::RenderLensFlare(GLPointf lightPos) 
{
	// 如果我们的光源在我们的视线范围内，则绘制它
	if (IsPointInFrustum(lightPos) == true)
	{
		//计算光源到我们视线的距离
		GLfloat lengthFromEyeToLight = sqrt(
			(lightPos.x - m_eyePos.x)*(lightPos.x - m_eyePos.x) +
			(lightPos.y - m_eyePos.y)*(lightPos.y - m_eyePos.y) +
			(lightPos.z - m_eyePos.z)*(lightPos.z - m_eyePos.z));
		//std::cout << m_directionVector.i << " " << m_directionVector.j << " " << m_directionVector.k << std::endl;

		//计算延长的视线向量
		GLVector3Df vFromEyeToLight = m_directionVector * lengthFromEyeToLight;
		//std::cout << vFromEyeToLight.i << " " << vFromEyeToLight.j << " " << vFromEyeToLight.k << std::endl;

		//计算插入点位置
		GLPointf ptIntersect = m_eyePos;
		//std::cout << ptIntersect.x << " " << ptIntersect.y << " " << ptIntersect.z << std::endl;

		ptIntersect += vFromEyeToLight;
		//std::cout << ptIntersect.x << " " << ptIntersect.y << " " << ptIntersect.z << std::endl;

		//计算插入点到光源的向量
		GLVector3Df vFromLightToIntersect = GLPointf::CalculateVector(lightPos, ptIntersect);

		//计算插入点到光源的距离
		GLfloat lengthFromLightToIntersect = vFromLightToIntersect.length;

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glDepthMask(GL_FALSE);//混合用
		glEnable(GL_TEXTURE_2D);
		if (false == IsOccluded(lightPos))	//如果光晕可见
		{
			//std::cout << lightPos.x <<" "<<lightPos.y<<" "<<lightPos.z << std::endl;

			//渲染中间的光晕
			RenderBigGlow(0.60f, 0.60f, 0.8f, 1.0f, lightPos, 16.0f); //叠在一起

			GLPointf pt;
			pt = lightPos;

			pt += vFromLightToIntersect * 0.05f;
			RenderStreaks(0.60f, 0.60f, 0.8f, 1.0f, pt, 16.0f);

			pt += vFromLightToIntersect * 0.08f;
			RenderGlow(0.8f, 0.8f, 1.0f, 0.5f, lightPos, 3.5f);
			//std::cout << pt.x << " " << pt.y << " " << pt.z << std::endl; //这里正确

			//绘制到光晕结束位置的0.1处的光晕
			pt += vFromLightToIntersect * 0.1f;
			RenderGlow(0.9f, 0.6f, 0.4f, 0.5f, pt, 0.6f);
			//std::cout << vFromLightToIntersect.i << " " << vFromLightToIntersect.j << " " << vFromLightToIntersect.k<<std::endl;

			//绘制到光晕结束位置的0.15处的光晕
			pt += vFromLightToIntersect * 0.15f;
			RenderHalo(0.8f, 0.5f, 0.6f, 0.5f, pt, 1.7f);

			//绘制到光晕结束位置的0.175处的光晕
			pt += vFromLightToIntersect * 0.175f;
			RenderHalo(0.9f, 0.2f, 0.1f, 0.5f, pt, 0.83f);

			//绘制到光晕结束位置的0.285处的光晕
			pt += vFromLightToIntersect * 0.285f;
			RenderHalo(0.7f, 0.7f, 0.4f, 0.5f, pt, 1.6f);

			//绘制到光晕结束位置的0.2755处的光晕
			pt += vFromLightToIntersect * 0.2755f;
			RenderGlow(0.9f, 0.9f, 0.2f, 0.5f, pt, 0.8f);

			//绘制到光晕结束位置的0.4755处的光晕
			pt += vFromLightToIntersect * 0.4755f;
			RenderGlow(0.93f, 0.82f, 0.73f, 0.5f, pt, 1.0f);

			//绘制到光晕结束位置的0.49处的光晕
			pt += vFromLightToIntersect * 0.49f;
			RenderHalo(0.7f, 0.6f, 0.5f, 0.5f, pt, 1.4f);

			//绘制到光晕结束位置的0.65处的光晕
			pt += vFromLightToIntersect * 0.65f;
			RenderGlow(0.7f, 0.8f, 0.3f, 0.5f, pt, 1.8f);

			//绘制到光晕结束位置的0.63处的光晕
			pt += vFromLightToIntersect * 0.63f;
			RenderGlow(0.4f, 0.3f, 0.2f, 0.5f, pt, 1.4f);

			//绘制到光晕结束位置的0.8处的光晕
			pt += vFromLightToIntersect * 0.8f;
			RenderHalo(0.7f, 0.5f, 0.5f, 0.5f, pt, 1.4f);

			//绘制到光晕结束位置的0.7825处的光晕
			pt += vFromLightToIntersect * 0.7825f;
			RenderGlow(0.8f, 0.5f, 0.1f, 0.5f, pt, 0.6f);

			//绘制到光晕结束位置的1.0处的光晕
			pt += vFromLightToIntersect;
			RenderHalo(0.5f, 0.5f, 0.7f, 0.5f, pt, 1.7f);

			//绘制到光晕结束位置的0.975处的光晕
			pt += vFromLightToIntersect * 0.975f;
			RenderGlow(0.4f, 0.1f, 0.9f, 0.5f, pt, 2.0f);

		}
		glDisable(GL_BLEND);
		glDepthMask(GL_TRUE);
		glDisable(GL_TEXTURE_2D);
		glColor3f(1.0, 1.0, 1.0);
	}
}

void Camera::RenderHalo(GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLPointf p, GLfloat scale)
{
	GLPointf q[4];

	q[0].x = (p.x - scale);
	q[0].y = (p.z - scale);

	q[1].x = (p.x - scale);
	q[1].y = (p.z + scale);

	q[2].x = (p.x + scale);
	q[2].y = (p.z - scale);

	q[3].x = (p.x + scale);
	q[3].y = (p.z + scale);
	//std::cout << p.x << " " << p.y << " " << p.z << std::endl; //为什么在动 - 因为加了视线向量

	glPushMatrix();
	glTranslatef(p.x, p.y, p.z);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);//转到向下
	//glRotatef(-m_HeadingDegrees, 0.0f, 1.0f, 0.0f);
	//glRotatef(-m_PitchDegrees, 1.0f, 0.0f, 0.0f);

	m_HaloTexture.LoadTexture("halo.bmp");
	m_HaloTexture.Apply();

	glColor4f(r, g, b, a);

	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(q[0].x, q[0].y);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(q[1].x, q[1].y);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(q[2].x, q[2].y);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(q[3].x, q[3].y);
	glEnd();
	glPopMatrix();
}

void Camera::RenderGlow(GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLPointf p, GLfloat scale)
{
	GLPointf q[4];

	q[0].x = (p.x - scale);
	q[0].y = (p.z - scale);

	q[1].x = (p.x - scale);
	q[1].y = (p.z + scale);

	q[2].x = (p.x + scale);
	q[2].y = (p.z - scale);

	q[3].x = (p.x + scale);
	q[3].y = (p.z + scale);

	glPushMatrix();
	glTranslatef(p.x, p.y, p.z);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);//转到向下
	//glRotatef(-m_HeadingDegrees, 0.0f, 1.0f, 0.0f);
	//glRotatef(-m_PitchDegrees, 1.0f, 0.0f, 0.0f);

	m_GlowTexture.LoadTexture("glow.bmp");
	m_GlowTexture.Apply();
	
	glColor4f(r, g, b, a);

	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(q[0].x, q[0].y);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(q[1].x, q[1].y);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(q[2].x, q[2].y);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(q[3].x, q[3].y);
	glEnd();
	glPopMatrix();
}

void Camera::RenderBigGlow(GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLPointf p, GLfloat scale)
{
	GLPointf q[4];

	q[0].x = (p.x - scale);
	q[0].y = (p.z - scale);

	q[1].x = (p.x - scale);
	q[1].y = (p.z + scale);

	q[2].x = (p.x + scale);
	q[2].y = (p.z - scale);

	q[3].x = (p.x + scale);
	q[3].y = (p.z + scale);

	glPushMatrix();
	glTranslatef(p.x, p.y, p.z);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);//转到向下
	//glRotatef(-m_HeadingDegrees, 0.0f, 1.0f, 0.0f);
	//glRotatef(-m_PitchDegrees, 1.0f, 0.0f, 0.0f);

	m_BigGlowTexture.LoadTexture("bigGlow.bmp");
	m_BigGlowTexture.Apply();
	
	glColor4f(r, g, b, a);

	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(q[0].x, q[0].y);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(q[1].x, q[1].y);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(q[2].x, q[2].y);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(q[3].x, q[3].y);
	glEnd();
	glPopMatrix();
}

void Camera::RenderStreaks(GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLPointf p, GLfloat scale)
{
	GLPointf q[4];

	q[0].x = (p.x - scale);
	q[0].y = (p.z - scale);

	q[1].x = (p.x - scale);
	q[1].y = (p.z + scale);

	q[2].x = (p.x + scale);
	q[2].y = (p.z - scale);

	q[3].x = (p.x + scale);
	q[3].y = (p.z + scale);

	glPushMatrix();
	glTranslatef(p.x, p.y, p.z);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);//转到向下
	//glRotatef(-m_HeadingDegrees, 0.0f, 1.0f, 0.0f);
	//glRotatef(-m_PitchDegrees, 1.0f, 0.0f, 0.0f);

	m_StreakTexture.LoadTexture("streak.bmp");
	m_StreakTexture.Apply();
	
	glColor4f(r, g, b, a);

	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(q[0].x, q[0].y);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(q[1].x, q[1].y);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(q[2].x, q[2].y);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(q[3].x, q[3].y);
	glEnd();
	glPopMatrix();
}