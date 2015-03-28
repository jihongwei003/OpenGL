/*目前的雾只是深度雾，没有使用雾坐标
* 如果需要使用体积雾，则用glFogi(GL_FOG_COORD_SRC,GL_FOG_COORD)显式启用雾坐标作为雾深度
* 并用glFogCoordf(x)填写雾坐标！！！
* 体积雾好像是绑定在模型上的，不是整个窗口的？*/
#pragma once

#include <glut.h>

class Fog
{
public:
	Fog();

	void SetFogMode(unsigned int fogFilter);
	void SetFogColor(float r, float g, float b);
	void SetFogDensity(float density);
	void SetFogDepth(float near, float far);

	void Apply();

private:
	unsigned int m_fogMode[3]; //雾气的模式
	float m_fogColor[4];
};