#pragma once

#include "GLFramework.h"//#include "GlobalInit.h" //父类中已经包含过
#include "Camera.h"

#include <list>

class FrameTest : public GLFramework
{
public:
	FrameTest();
	FrameTest(int argc, char* argv[], std::string title, unsigned width, unsigned height);

	/* 重写父类纯虚函数 */
	void Init();
	void Display();	

	void MouseMotion(int x, int y);
	void MousePassiveMotion(int x, int y);

private:
	GlobalInit *m_init;
	Camera *m_camera0;

	//鼠标在某一点的映射角度
	float viewAngleZ; //Mouse设定，Display使用
	float viewAngleY;

	//切换两种视角，1 true：主角视角；0 false:上帝视角
	bool viewMode; //Keyboard设定，Display使用

};