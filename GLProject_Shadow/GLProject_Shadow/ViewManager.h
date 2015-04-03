#pragma once 

#include <glut.h>

/*矩阵模式的切换与恢复，便于绘制2D图形
* ViewOrtho()和ViewPerspective()成对调用，且先调用ViewOrtho()
* 默认裁剪窗口为（-1,1,-1,1,-1,-1）*/
class ViewManager
{
public:
	ViewManager(){}

	//切换到投影矩阵，默认裁剪窗口为（-1,1,-1,1,-1,-1）
	static void ViewOrtho(GLdouble left = -1, GLdouble right = 1, GLdouble bottom = -1, GLdouble top = 1)
	{
		glMatrixMode(GL_PROJECTION);
		glPushMatrix(); //保存当前矩阵(投影矩阵)  
		glLoadIdentity();

		glOrtho(left, right, bottom, top, 1, -1);

		glMatrixMode(GL_MODELVIEW); //保存当前矩阵(视图矩阵)  
		glPushMatrix();
		glLoadIdentity();
	}

	//切换到透视矩阵
	static void ViewPerspective()
	{
		glMatrixMode(GL_PROJECTION);
		glPopMatrix(); //恢复投影矩阵  
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix(); //视图矩阵 
	}
};