#include "GLFramework.h"  
#include <glut.h>

/** 构造函数 */
GLFramework::GLFramework()
{
}

GLFramework::GLFramework(int argc, char* argv[], std::string title, unsigned width, unsigned height)
{
	m_WindowP = new GLWindow(argc, argv, title, width, height);
}

/* 委托GLWindow类创建窗口，以及实现窗口变化时的回调函数 */
void GLFramework::CreateGLWindow()
{
	m_WindowP->CreateGLWindow();
}

void GLFramework::Reshape(unsigned newWidth, unsigned newHeight)
{
	m_WindowP->Reshape(newWidth, newHeight);
}
