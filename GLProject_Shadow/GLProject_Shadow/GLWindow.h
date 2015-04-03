#pragma once

#include <Windows.h>
#include <string>

/** windows窗口类 */
class GLWindow
{
public:
	/* 初始化并创建windows窗口 */
	GLWindow();
	GLWindow(int argc, char* argv[], std::string title, unsigned width, unsigned height);

	/* 创建窗口 */
	void CreateGLWindow();

	/* 返回窗口的大小 */
	int GetWidth();
	int GetHeight();

	/* 获取所在窗口的句柄 */
	HWND GetWindowHandle();

	/*窗口大小改变回调函数 */
	void Reshape(unsigned newWidth, unsigned newHeight);

private:
	HWND m_hWnd; //窗口句柄 
	unsigned m_windowWidth;   
	unsigned m_windowHeight;  
	std::string m_title;
};