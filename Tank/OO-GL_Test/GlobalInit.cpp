#include "GlobalInit.h"

GLenum GlobalInit::m_mode = GL_CCW;

/*
* 初始化渲染参数(在使用MeshModel之前调用)
* 指定正面
* 打开背面剔除
* 打开深度测试
* 打开平滑渐变
* 设定清除颜色为黑色
* 打开混合；设定alpha混合方程
* 打开vertex顶点数组
*/
GlobalInit::GlobalInit(GLenum mode)
{
	glEnable(GL_CULL_FACE);
	//glPolygonMode(GL_FRONT, GL_FILL);
	SetFrontFace(mode);

	glEnable(GL_DEPTH_TEST);

	glShadeModel(GL_SMOOTH); //带有抗锯齿

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//打开顶点数组
	glEnableClientState(GL_VERTEX_ARRAY);
}

void GlobalInit::SetFrontFace(GLenum mode)
{
	glFrontFace(mode);
}
