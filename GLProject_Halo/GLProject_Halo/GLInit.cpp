#include "GLInit.h"

GLenum GLInit::m_mode = GL_CCW;

/*
* 初始化渲染参数(在使用MeshModel之前调用)
* 指定正面
* 打开背面剔除
* 打开深度测试
* 打开平滑渐变
* 设定清除颜色为黑色
*
* 打开vertex顶点数组
*/
GLInit::GLInit(GLenum mode)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 640, 0, 480);

	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_CULL_FACE);
	SetFrontFace(mode);

	glEnable(GL_DEPTH_TEST);

	glShadeModel(GL_SMOOTH); 

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 

	//打开顶点数组
	glEnableClientState(GL_VERTEX_ARRAY);
}

void GLInit::SetFrontFace(GLenum mode)
{
	glFrontFace(mode);
}
