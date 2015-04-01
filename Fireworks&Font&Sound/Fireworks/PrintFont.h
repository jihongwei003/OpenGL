#pragma once

#include <glut.h>

#include <stdio.h>
#include <Windows.h> //创建字体

class PrintFont
{
public:
	PrintFont();

	GLvoid GenFont(GLvoid); //修改这个函数的参数，可以在外部设定字体属性！
	GLvoid ApplyFont(GLvoid);
	GLvoid DestroyFont(GLvoid);

	virtual GLvoid BuildFont(GLvoid) = 0;
	virtual GLvoid KillFont(GLvoid) = 0; //killWindow()时调用？
	virtual GLvoid glPrint(GLint x, GLint y, char *string) = 0;

	//~PrintFont();
protected:
	//PrintFont(const PrintFont& other){}
	//PrintFont& operator=(const PrintFont& other){}

	HDC m_hDC; //设备上下文
	GLuint m_base; //绘制字体的显示列表的开始位置.字符‘A’在显示列表中是65,应保存在显示列表中的base + 65这个位置

private:
	HFONT m_font;	 //字体句柄
	HFONT m_oldFont; //旧的字体句柄
};
