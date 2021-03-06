#pragma once

#include "GLFramework.h"//#include "GlobalInit.h" //父类中已经包含过

#include "Camera.h"
#include "Axis.h"
#include "Fireworks.h"
#include "Keys.h"
#include "Print2DFont.h"
#include "Print3DFont.h"


/* 自定义模型 */


#include <list> //放烟花

class FireworksFrame : public GLFramework
{
public:
	FireworksFrame();
	FireworksFrame(int argc, char* argv[], std::string title, unsigned width, unsigned height);

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
	Camera *m_camera0;
	Axis *m_axis;

	Keys *keys;

	Print2DFont font;
	Print3DFont font3D;


	/* 自定义模型 */



	/* 类内部全局变量，用来协调视角、鼠标控制视线、键盘按下与响应 */
	
	//鼠标在某一点的映射角度
	float viewAngleZ; //Mouse设定，Display使用
	float viewAngleY;

	//切换两种视角，1 true：主角视角；0 false:上帝视角
	bool viewMode; //Keyboard设定，Display使用

	bool isShoot; //Keyboard设定，Display使用
	int shootTimer;


	Fireworks *pParticle;

	std::list<Fireworks*> m_fireworksList;
	std::list<Fireworks*>::iterator m_fireworksListIter;

	Texture t;
	

	/* 内部使用的函数 */

	void Shoot();

};