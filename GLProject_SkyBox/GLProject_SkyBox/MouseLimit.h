#pragma once

#include <Windows.h>
#include "LinearMap.h"

/* 鼠标移动类 */
class MouseLimit{
protected:
	typedef enum{
		WRAP,      //回绕至另一侧（例：如果鼠标位置超过右界，将鼠标回绕到左界处）
		KNOCK_BACK //移回边界内（例：如果鼠标位置超过右界，禁止鼠标继续右移，将其移回右界内部）
	}MouseLimitMode;

public:
	HWND m_hWnd;

	/* 构造Mouse，它的相应操作相对于当前窗口 */
	MouseLimit();
	MouseLimit(HWND m_hWnd);

	int GetCursorX();
	int GetCursorY();

	/* 限制鼠标左右移动的范围，相对于构造时指定的那个窗口 */
	void MouseMovLimitRL(int left, int right, MouseLimitMode mode = MouseLimit::WRAP);
	/*限制鼠标上下移动的范围，相对于构造时指定的那个窗口*/
	//void limitMouseMovingDomainTB(int top, int bottom,  Controller::MouseLimitMode mode);

	//从窗口中鼠标的位置映射到离窗口中心的角度rotY(左右)、rotZ(上下)
	void PosIntoAngleY(float left, float righat, float swingAngleL, float swingAngleR);
	void PosIntoAngleZ(float top, float bottom, float elevationT, float elevationB);

	float GetMapAngleY(int x);
	float GetMapAngleZ(int y);

	/*显示鼠标指针*/
	static void MouseLimit::Show();
	/*隐藏鼠标指针*/
	static void MouseLimit::Hide();

private:
	POINT pt;
	LinearMap<int> a;
	LinearMap<float> mapAngleY;
	LinearMap<float> mapAngleZ;
};