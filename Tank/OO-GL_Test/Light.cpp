#include "Light.h"

#include <glut.h>
#include <string.h> //memset

Light::Light(void)
{
	m_id = 0;

	memset(m_positionL, 0, sizeof(m_positionL));
	memset(m_ambientL, 0, sizeof(m_ambientL));
	memset(m_diffuseL, 0, sizeof(m_diffuseL));
	memset(m_specularL, 0, sizeof(m_specularL));

	glLightfv(GL_LIGHT0 + m_id, GL_POSITION, m_positionL);
	glLightfv(GL_LIGHT0 + m_id, GL_AMBIENT, m_ambientL);
    glLightfv(GL_LIGHT0 + m_id, GL_DIFFUSE, m_diffuseL);
	glLightfv(GL_LIGHT0 + m_id, GL_SPECULAR, m_specularL);
}

/* 光照序号，位置 */
void Light::SetLightPos(float positionL[])
{
	memcpy(m_positionL, positionL, sizeof(m_positionL));
	glLightfv(GL_LIGHT0 + m_id, GL_POSITION, m_positionL);
}

/* （几号光源，位置，多次反射后强度，漫反射强度，镜面反射强度） */
Light::Light(unsigned short id, float positionL[], float ambientL[], float diffuseL[], float specularL[])
{
	m_id = id;

	memcpy(m_positionL, positionL, sizeof(m_positionL));
	memcpy(m_ambientL, ambientL, sizeof(m_ambientL));
	memcpy(m_diffuseL, diffuseL, sizeof(m_diffuseL));
	memcpy(m_specularL, specularL, sizeof(m_specularL));

	glLightfv(GL_LIGHT0 + m_id, GL_POSITION, m_positionL);
	glLightfv(GL_LIGHT0 + m_id, GL_AMBIENT, m_ambientL);
	glLightfv(GL_LIGHT0 + m_id, GL_DIFFUSE, m_diffuseL);
	glLightfv(GL_LIGHT0 + m_id, GL_SPECULAR, m_specularL);
}

/*打开这个光源*/
void Light::TurnOn()
{
	glEnable(GL_LIGHT0 + m_id);
	glEnable(GL_LIGHTING);
}

/*关闭这个光源*/
void Light::TurnOff()
{
	glDisable(GL_LIGHT0 + m_id);
}

void Light::TurnOnColorTrack()
{
	//打开颜色追踪
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

Light::~Light(void)
{
}
