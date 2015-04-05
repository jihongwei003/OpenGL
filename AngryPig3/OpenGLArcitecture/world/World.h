#pragma once

#include <Windows.h>
#include <string>

#include "Camera.h"

class World{
public:
	/*不要使用无参构造*/
	World();

	/*构造并初始化
	*设定视口大小
	*设定帧长度
	*绑定并初始化摄像机*/
	World(int argc, char* argv[], std::string title, unsigned width, unsigned height, unsigned frameTimeMs, Camera *pCamera);

	/*绑定摄像机*/
	void bindCamera(Camera *pCamera);

	/*每次显示场景时执行的操作
	*被glutDisplayFunc()回调的那个函数的函数体应该包括world.onDisplay()
	*使用前需要绑定摄像机
	*重写时应该实现：
	*1.帧逻辑运算：执行相关物体的游戏逻辑
	*2.渲染场景：将相关物体绘制到场景中
	*3.视角变换：调用一个Camera实例的apply()方法，可以采用该实例的视角*/
	virtual void onDisplay();

	/*屏幕大小改变时执行的操作
	*被glutReshapeFunc()回调的那个函数的函数体应该包括world.onChangeSize()
	*使用前需要绑定摄像机
	*重写时应该实现：
	*1.更改渲染宽高比：调用一个Camera实例的setRatioWH(新宽高比)方法，更改视野的宽高比*/
	virtual void onChangeSize(unsigned newW, unsigned newH);

	/*获取视口宽度*/
	unsigned getWidth();

	/*获取视口高度*/
	unsigned getHeight();

	/*获取所在窗口的句柄*/
	HWND getRenderWindowHandle();

protected:
	/*渲染前清屏*/
	static void ClearScreen();

	/*声明渲染结束*/
	static void RenderFinish();

	/*指向当前采用的摄像机的指针*/
	Camera *m_pCurCam;

	/*视口宽高*/
	unsigned m_portWidth;
	unsigned m_portHeight;

	/*帧长度，以毫秒计*/
	unsigned m_frameTimeMs;

	/*渲染窗口的句柄*/
	HWND m_hRenderWindow;
};