#include "World.h"

#include <glut.h>
#include "Light.h"
#include "Mesh.h"

World::World()
{
}

/*构造并初始化
*设定视口大小
*设定帧长度
*绑定并初始化摄像机*/
World::World(int argc, char* argv[], std::string title, unsigned width, unsigned height, unsigned frameTimeMs, Camera *pCamera)
{
	m_portWidth = width;
	m_portHeight = height;

	m_frameTimeMs = frameTimeMs;

	bindCamera(pCamera);

	/*初始化窗口*/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(m_portWidth, m_portHeight);

	glutCreateWindow(title.c_str());

	m_hRenderWindow = WindowFromDC(wglGetCurrentDC());

	/*设定渲染参数*/
	//设定渲染模型时的参数
	Mesh::InitMesh(true, false, Mesh::COLOR);

	//打开光照
	Light::Enable();

	//打开2D纹理贴图
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

/*绑定摄像机
*同时用属性域更新摄像机的宽高比*/
void World::bindCamera(Camera *pCamera)
{
	m_pCurCam = pCamera;
	pCamera->setRatioWH((float)m_portWidth / (float)m_portHeight);
}

/*每次显示场景时执行的操作*/
void World::onDisplay()
{
	ClearScreen();

	//在这里计算游戏逻辑
	//以及绘制物体

	m_pCurCam->apply();

	RenderFinish();
}

/*屏幕大小改变时执行的操作*/
void World::onChangeSize(unsigned newW, unsigned newH)
{
	m_portWidth = newW;
	m_portHeight = newH;

	glViewport(0, 0, newW, newH);

	m_pCurCam->setRatioWH((float)m_portWidth / (float)m_portHeight);
}

/*获取视口宽度*/
unsigned World::getWidth()
{
	return m_portWidth;
}

/*获取视口高度*/
unsigned World::getHeight()
{
	return m_portHeight;
}

/*获取所在窗口的句柄*/
HWND World::getRenderWindowHandle()
{
	return m_hRenderWindow;
}

/*渲染前清屏*/
void World::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// 清理颜色&深度缓冲区
}

/*声明渲染结束*/
void World::RenderFinish()
{
	glutSwapBuffers();
}