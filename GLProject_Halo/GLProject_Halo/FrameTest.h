#pragma once

#include "GLFramework.h"//#include "GLInit.h" //父类中已经包含过

#include "Light.h"
#include "Camera.h"
#include "Keys.h"

class FrameTest : public GLFramework
{
public:
	FrameTest();
	FrameTest(int argc, char* argv[], std::string title, unsigned width, unsigned height);

	void DrawScene(GLenum mode);

	/* 重写父类纯虚函数 */
	void Init();
	void Display();	

	void MouseMotion(int x, int y);
	void MousePassiveMotion(int x, int y);
	void MouseButton(int button, int state, int x, int y);

	void KeyboardSet(unsigned char key, int x, int y);
	void KeyboardUpSet(unsigned char key, int x, int y);

	void KeyboardRespond(); //在Timer中调用
	void SpecialKey(int key, int x, int y);

private:
	Light m_light0;
	Camera m_camera0;

	//创建和设置或和启用不在同一个函数中的用作成员对象
	Keys m_keys;

	//鼠标在某一点的映射角度
	float viewAngleZ; //Mouse设定，Display使用
	float viewAngleY;

	//切换两种视角，1 true：主角视角；0 false:上帝视角
	bool viewMode; //Keyboard设定，Display使用

};