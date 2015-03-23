#pragma once

static const unsigned int MAX_KEYS = 256;

/** 键盘类 */
class Keys												 
{
public:
	Keys();

	bool IsPressed(unsigned int key);   //判断某个键是否按下 
	void SetPressed(unsigned int key);  //设置某个键被按下 
	void SetReleased(unsigned int key); //设置某个键被释放 

private:
	void Clear(); //清空所有的按键信息 
	bool m_KeyDown[MAX_KEYS]; //保存256个按键的状态[ascii码]
};