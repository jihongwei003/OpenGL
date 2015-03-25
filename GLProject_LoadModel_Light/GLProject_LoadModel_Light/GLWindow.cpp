#include "GLWindow.h" 

#include <glut.h>

/* 构造函数 */
GLWindow::GLWindow()
{
}

GLWindow::GLWindow(int argc, char* argv[], std::string title, unsigned width, unsigned height)
{
	m_hWnd = WindowFromDC(wglGetCurrentDC());

	m_windowWidth = width;
	m_windowHeight = height;
	m_title = title;

	/*初始化窗口*/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
}

/* 创建窗口 */
void GLWindow::CreateGLWindow()
{
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(m_windowWidth, m_windowHeight);
	glutCreateWindow(m_title.c_str());
}

/* 返回窗口的大小 */
int GLWindow::GetWidth()
{
	return m_windowWidth;
}

int GLWindow::GetHeight()
{
	return m_windowHeight;
}

/* 获取所在窗口的句柄 */
HWND GLWindow::GetWindowHandle()
{
	return m_hWnd;
}

/* 窗口大小改变时，通知OpenGL调整大小 */
void GLWindow::Reshape(unsigned newWidth, unsigned newHeight)
{
	m_windowWidth = newWidth;
	m_windowHeight = newHeight;
	glViewport(0, 0, newWidth, newHeight); //重新设置视口

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(45.0f, (float)width / (float)height, 1.0f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
