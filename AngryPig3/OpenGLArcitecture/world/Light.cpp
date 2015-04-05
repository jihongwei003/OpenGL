#include "Light.h"

#include <glut.h>
#include <string.h>

Light::Light(void)
{
	m_id = 0;
	memset(m_ambient, 0, sizeof(m_ambient));
	memset(m_diffuse, 0, sizeof(m_diffuse));
	glLightfv(GL_LIGHT0 + m_id, GL_AMBIENT, m_ambient);
    glLightfv(GL_LIGHT0 + m_id, GL_DIFFUSE, m_diffuse);
}

/*光照序号，必须介于（含）0-7之间*/
Light::Light(unsigned short id)
{
	m_id = id;
	memset(m_ambient, 0, sizeof(m_ambient));
	memset(m_diffuse, 0, sizeof(m_diffuse));
	glLightfv(GL_LIGHT0 + m_id, GL_AMBIENT, m_ambient);
    glLightfv(GL_LIGHT0 + m_id, GL_DIFFUSE, m_diffuse);
}

/*打开这个光源*/
void Light::turnOn()
{
	glEnable(GL_LIGHT0 + m_id);
}

/*关闭这个光源*/
void Light::turnOff()
{
	glDisable(GL_LIGHT0 + m_id);
}

/*设定环境光*/
void Light::setAmbient(float *src)
{
	memcpy(m_ambient, src, sizeof(m_ambient));
	glLightfv(GL_LIGHT0 + m_id, GL_AMBIENT, m_ambient);
}

/*设定散射光*/
void Light::setDiffuse(float *src)
{
	memcpy(m_diffuse, src, sizeof(m_diffuse));
	glLightfv(GL_LIGHT0 + m_id, GL_DIFFUSE, m_diffuse);
}

void Light::Enable()
{
	//打开光照
	glEnable(GL_LIGHTING);
	//打开颜色追踪
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

Light::~Light(void)
{
}
