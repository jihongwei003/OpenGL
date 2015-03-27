#pragma once

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

#include <glut.h>

class GlobalInit
{
public:
	/*定义“正面”的环绕方向，参数为GL_CCW（逆时针）或GL_CW（顺时针）*/
	GlobalInit(GLenum mode = GL_CCW);

	void SetFrontFace(GLenum mode);

protected:
	static GLenum m_mode;
};