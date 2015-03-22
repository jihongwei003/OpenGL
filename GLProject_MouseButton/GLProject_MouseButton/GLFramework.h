/**
*	你必须在继承类中完成以下函数的实现
*
*	void Init(); //委托GlobalInit类实现
*
*	Display(); //glutDisplayFunc()的回调函数；调用glClear()
*
*	MouseMotion();
*	MousePassiveMotion();
*	MouseButtion();
*
*	KeyboardSet()
*	KeyboardUpSet()
*	KeyboardRespond()
*	SpecialKey()
*
*	使用时需要在main()函数中编写如下函数，因为glutDisplayFunc()只接受普通函数指针，不接受类成员函数指针
*		void DisplayCal()
*		{
*			object->Display();
*		}
*/

#pragma once

#include "GLWindow.h"
#include "GlobalInit.h"

/** 基本的程序框架类，继承它用来创建OpenGL程序 */
class GLFramework
{
public:
	//virtual ~GLFramework() {}; //虚析构函数 

	/* 构造函数 */
	GLFramework();
	GLFramework(int argc, char* argv[], std::string title, unsigned width, unsigned height);

	/* 委托GLWindow类创建窗口，以及实现窗口变化时的回调函数 */
	void CreateGLWindow();
	void Reshape(unsigned newWidth, unsigned newHeight);

protected:
	/* 下面的函数必须被继承类实现，完成基本的OpenGL渲染过程*/
	virtual void Init() = 0;
	virtual void Display() = 0; 

	virtual void MouseMotion(int x, int y) = 0;
	virtual void MousePassiveMotion(int x, int y) = 0;
	virtual void MouseButton(int button, int state, int x, int y) = 0;

	//virtual void KeyboardSet(unsigned char key, int x, int y) = 0; //设定按键按下与释放
	//virtual void KeyboardUpSet(unsigned char key, int x, int y) = 0;

	//virtual void KeyboardRespond() = 0; //在Timer中调用
	//virtual void SpecialKey(int key, int x, int y) = 0;

	GLWindow *m_WindowP; 
};