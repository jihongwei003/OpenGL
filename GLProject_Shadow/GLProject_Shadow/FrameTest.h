#pragma once

#include "GLFramework.h"//#include "GLInit.h" //父类中已经包含过

#include "Light.h"
#include "Camera.h"
#include "Keys.h"

#include <list>

/* 自定义模型 */
#include "TestPlane.h" 
#include "SkyBox.h"

class FrameTest : public GLFramework
{
public:
	FrameTest();
	FrameTest(int argc, char* argv[], std::string title, unsigned width, unsigned height);

	//处理选择的回调函数
	void DrawScene(GLenum mode);
	void ProcessPicks(GLuint *name); 

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

	/* 自定义模型 */
	SkyBox *pSkyBox; //带纹理的东西得用指针，要么ID分配会失败！

	TestPlane *pPlane;
	

	/* 类内部全局变量，用来协调视角、鼠标控制视线、键盘按下与响应 */
	
	//鼠标在某一点的映射角度
	float viewAngleZ; //Mouse设定，Display使用
	float viewAngleY;

	//切换两种视角，1 true：主角视角；0 false:上帝视角
	bool viewMode; //Keyboard设定，Display使用

};