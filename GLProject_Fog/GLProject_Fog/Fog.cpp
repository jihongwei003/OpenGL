#include "Fog.h"

Fog::Fog()
{
	m_fogMode[0] = GL_EXP;
	m_fogMode[1] = GL_EXP2;
	m_fogMode[2] = GL_LINEAR;

	glFogi(GL_FOG_MODE, m_fogMode[2]); // 设置雾气的模式

	m_fogColor[0] = 0.5f;
	m_fogColor[1] = 0.5f;
	m_fogColor[2] = 0.5f;
	m_fogColor[3] = 1.0f;

	glFogfv(GL_FOG_COLOR, m_fogColor); //雾颜色
	glFogf(GL_FOG_DENSITY, 0.01f);     //设置雾浓度

	glFogf(GL_FOG_START, 240.0f); //雾气的开始位置
	glFogf(GL_FOG_END, 300.0f);  //雾气的结束位置
}

void Fog::SetFogMode(unsigned int fogFilter)
{
	glFogi(GL_FOG_MODE, m_fogMode[fogFilter]);
}

void Fog::SetFogColor(float r, float g, float b)
{
	m_fogColor[0] = r;
	m_fogColor[1] = g;
	m_fogColor[2] = b;
	m_fogColor[3] = 1.0f;

	glFogfv(GL_FOG_COLOR, m_fogColor);
}

void Fog::SetFogDensity(float density)
{
	glFogf(GL_FOG_DENSITY, density);
}

void Fog::SetFogDepth(float near, float far)
{
	glFogf(GL_FOG_START, near);	//雾气的开始位置
	glFogf(GL_FOG_END, far);    //雾气的结束位置
}

void Fog::Apply()
{
	glHint(GL_FOG_HINT, GL_DONT_CARE); //设置系统如何计算雾气
	glEnable(GL_FOG);
}