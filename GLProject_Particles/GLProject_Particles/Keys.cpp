#include "Keys.h"

#include <windows.h>

Keys::Keys()
{
	Clear();
}

//清空所有的按键信息 
void Keys::Clear()
{
	//将指定的内存模块清零，第一个参数为内存的首地址，第二个参数为内存的大小
	ZeroMemory(&m_KeyDown, sizeof(m_KeyDown));
}

//判断某个键是否按下
bool Keys::IsPressed(unsigned int key)
{
	return (key < MAX_KEYS) ? (m_KeyDown[key] == true) : false;
}

//设置某个键被按下 
void Keys::SetPressed(unsigned int key)
{
	if (key < MAX_KEYS) m_KeyDown[key] = true;
}

//设置某个键被释放 
void Keys::SetReleased(unsigned int key)
{
	if (key < MAX_KEYS) m_KeyDown[key] = false;
}