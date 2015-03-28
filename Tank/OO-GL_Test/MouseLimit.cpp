#include "MouseLimit.h"

/* 构造MouseLimit，它的相应操作相对于当前窗口 */
MouseLimit::MouseLimit()
{
	m_hWnd = GetForegroundWindow();

	GetCursorPos(&pt);           //填写鼠标相对于屏幕左上角的坐标
	ScreenToClient(m_hWnd, &pt); //转换为窗口坐标
}

MouseLimit::MouseLimit(HWND m_hWnd)
{
	this->m_hWnd = m_hWnd;

	GetCursorPos(&pt);           //填写鼠标相对于屏幕左上角的坐标
	ScreenToClient(m_hWnd, &pt); //转换为窗口坐标
}

int MouseLimit::GetCursorX()
{
	return pt.x;
}

int MouseLimit::GetCursorY()
{
	return pt.y;
}

/*glut可以检测鼠标是否跳出窗口，
* 再根据鼠标跳出时的位置也可以实现回绕 */

/* 限制鼠标左右移动的范围，相对于构造时指定的那个窗口 */
void MouseLimit::MouseMovLimitRL(int left, int right, MouseLimitMode mode)
{
	RECT windowRect;
	GetWindowRect(m_hWnd, &windowRect); //获取指定窗口相当于屏幕的范围（上下左右）
	int screenW = windowRect.right - windowRect.left;
	int screenH = windowRect.top - windowRect.bottom;

	const int limitLeft = left;   //鼠标移动范围的左界
	const int limitRight = right; //鼠标移动范围的右界

	//GetCursorPos(&pt);           //填写鼠标相对于屏幕左上角的坐标
	//ScreenToClient(m_hWnd, &pt); //转换为窗口坐标
	
	if (pt.x <= limitLeft){
		pt.x = limitRight - 1;
		ClientToScreen(m_hWnd, &pt); //重设为相对于屏幕左端的坐标
		SetCursorPos(pt.x, pt.y);
	}
	else if (pt.x >= limitRight){
		pt.x = limitLeft + 9;
		ClientToScreen(m_hWnd, &pt); //重设为相对于屏幕右端的坐标
		SetCursorPos(pt.x, pt.y);
	}
}

//从窗口中鼠标的位置映射到离窗口中心的角度rotY(左右)、rotZ(上下)
void MouseLimit::PosIntoAngleY(float left, float righat, float swingAngleL, float swingAngleR)
{
	mapAngleY.SetRange(left, righat, swingAngleL, swingAngleR);
}
void MouseLimit::PosIntoAngleZ(float top, float bottom, float elevationT, float elevationB)
{
	mapAngleZ.SetRange(top, bottom, elevationT, elevationB);
}

//得到映射结果
float MouseLimit::GetMapAngleY(int x)
{
	return mapAngleY.Map(x);
}
float MouseLimit::GetMapAngleZ(int y)
{
	return mapAngleZ.Map(y);
}

/* 显示鼠标指针 */
void MouseLimit::Show()
{
	ShowCursor(true);
}

/* 隐藏鼠标指针 */
void MouseLimit::Hide()
{
	ShowCursor(false);
}