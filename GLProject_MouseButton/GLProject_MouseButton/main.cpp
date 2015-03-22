#include "FrameTest.h"

#include <glut.h>

FrameTest *ft;

/* 下面的函数均用来调用类成员函数中对应的回调函数 */
void TimerCal(int value){
	glutPostRedisplay();
	glutTimerFunc(20, TimerCal, 0);
}

void DisplayCal()
{
	ft->Display();
}
void ReshapeCal(int x, int y)
{
	ft->Reshape(x, y);
}

void MouseMotionCal(int x, int y)
{
	ft->MouseMotion(x,y);
}
void MousePassiveMotionCal(int x, int y)
{
	ft->MousePassiveMotion(x, y);
}

void MouseButtonCal(int button, int state, int x, int y)
{
	ft->MouseButton(button, state, x, y);
}


int main(int argc, char *argv[])
{
	std::string title = "鼠标按键的监听";
	unsigned width = 640;
	unsigned height = 480;

	ft = new FrameTest(argc, argv, title, width, height);

	ft->CreateGLWindow();
	ft->Init();

	glutDisplayFunc(DisplayCal);
	glutReshapeFunc(ReshapeCal);
	glutTimerFunc(20, TimerCal, 0); //注册按一定时间间隔触发的定时器回调函数

	glutMotionFunc(MouseMotionCal); //处理当鼠标键摁下时，鼠标拖动的事件
	glutPassiveMotionFunc(MousePassiveMotionCal); //当没有鼠标键摁下时，鼠标拖动的事件

	glutMouseFunc(MouseButtonCal);  //鼠标按下

	glutMainLoop();
	return 0;
}