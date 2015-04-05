#pragma once

#include <Windows.h>

/*封装了对鼠标的操作*/
class MouseController{
protected:
	typedef enum{
		WRAP,//回绕至另一侧（例：如果鼠标位置超过右界，将鼠标回绕到左界处）
		KNOCK_BACK//移回边界内（例：如果鼠标位置超过右界，禁止鼠标继续右移，将其移回右界内部）
	}MouseLimitMode;//如何限制鼠标移动

public:
	HWND windowHdl;

	/*构造MouseController，它的相应操作相对于当前窗口*/
	MouseController();

	/*构造MouseController，它的相应操作相对于指定窗口*/
	MouseController(HWND windowHdl);

	/*限制鼠标左右移动的范围，相对于构造时指定的那个窗口*/
	void limitMouseMovingDomainRL(int left, int right, MouseLimitMode mode = MouseController::WRAP);

	/*限制鼠标上下移动的范围，相对于构造时指定的那个窗口*/
	//void limitMouseMovingDomainTB(int top, int bottom,  Controller::MouseLimitMode mode);

	/*显示鼠标指针*/
	static void MouseController::Show();

	/*隐藏鼠标指针*/
	static void MouseController::Hide();
};