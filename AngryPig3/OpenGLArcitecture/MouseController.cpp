#include "MouseController.h"

/*构造MouseController，它的相应操作相对于当前窗口*/
MouseController::MouseController(){
	windowHdl = GetForegroundWindow();
}

/*构造MouseController，它的相应操作相对于指定窗口*/
MouseController::MouseController(HWND windowHdl){
	this->windowHdl = windowHdl;
}

/*限制鼠标左右移动的范围，相对于构造时指定的那个窗口*/
void MouseController::limitMouseMovingDomainRL(int left, int right, MouseLimitMode mode){
	RECT windowRect;
	GetWindowRect(windowHdl, &windowRect);//获取指定窗口相当于屏幕的范围（上下左右）

	int screenW = windowRect.right - windowRect.left;
	int screenH = windowRect.top - windowRect.bottom;

	const int limitLeft = left;//鼠标移动范围的左界
	const int limitRight = right;//鼠标移动范围的右界
	/*	  limitLeft	    		limitRight
	↓					   ↓
	|					                    |
	|					                    |
	<-edge->|<-------可行范围------>|<-edge->
	|					                    |
	|					                    |
	|					                    |
	<----------------整个窗口--------------->
	*/
	POINT pt;

	GetCursorPos(&pt);//填写鼠标相对于屏幕左上角的坐标
	ScreenToClient(windowHdl, &pt);//转换为窗口坐标

	if(pt.x <= limitLeft){
		pt.x = limitRight-1;
		ClientToScreen(windowHdl, &pt);//将pt的坐标从窗口坐标转换为相对于屏幕的坐标
		SetCursorPos(pt.x, pt.y);
	}else if(pt.x >= limitRight){
		pt.x = limitLeft+9;
		ClientToScreen(windowHdl, &pt);//将pt的坐标从窗口坐标转换为相对于屏幕的坐标
		SetCursorPos(pt.x, pt.y);
	}
}

/*显示鼠标指针*/
void MouseController::Show(){
	ShowCursor(true);
}

/*隐藏鼠标指针*/
void MouseController::Hide(){
	ShowCursor(false);
}