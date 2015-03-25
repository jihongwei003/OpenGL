#pragma once

#include "GLFramework.h"//#include "GlobalInit.h" //父类中已经包含过

#include "Light.h"
#include "Camera.h"
#include "Axis.h"

#include "Keys.h"

/* 自定义模型 */
#include "TankChassis.h"
#include "TankTurret.h"
#include "TankBarrel.h"


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
	void MouseButton(int button, int state, int x, int y);

	void KeyboardSet(unsigned char key, int x, int y);
	void KeyboardUpSet(unsigned char key, int x, int y);

	void KeyboardRespond(); //在Timer中调用
	void SpecialKey(int key, int x, int y);

private:
	GlobalInit *m_init;
	Light *m_light0;
	Camera *m_camera0;
	Axis *m_axis;

	Keys *keys;

	/* 自定义模型 */

	TankChassis *pTankChassis;
	TankTurret *pTankTurret;
	TankBarrel *pTankBarrel;


	/* 类内部全局变量，用来协调视角、鼠标控制视线、键盘按下与响应 */
	
	//鼠标在某一点的映射角度
	float viewAngleZ; //Mouse设定，Display使用
	float viewAngleY;

	//切换两种视角，1 true：主角视角；0 false:上帝视角
	bool viewMode; //Keyboard设定，Display使用

};