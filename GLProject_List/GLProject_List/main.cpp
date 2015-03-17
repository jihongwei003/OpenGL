#include <glut.h>//其中已经包含<GL/gl.h>和<GL/glu.h>
#include <iostream>

static GLfloat angle = 0.0f;

void myDisplayList(void);

//点、线、多边形、顶点、显示列表
void myDisplayList(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glRectf(-0.5f, -0.5f, 0.5f, 0.5f);

	//glShadeModel(GL_SMOOTH);   // 平滑方式，这也是默认方式。两顶点使用不同颜色时有渐变效果
	//glShadeModel(GL_FLAT);     // 单色方式

	//glColor3f(0.0f, 1.0f, 1.0f);

	// glPointSize(5.0f);//设置点大小

	//glEnable(GL_LINE_STIPPLE);//启用虚线
	//glLineStipple(2, 0x0F0F);//虚线样式
	//glLineWidth(10.0f);

	//glPolygonMode(GL_FRONT, GL_FILL); // 设置正面为填充模式
	//glPolygonMode(GL_BACK, GL_LINE);  // 设置反面为线形模式
	//glFrontFace(GL_CCW);              // 设置逆时针方向为正面	

	#define ColoredVertex(c, v) do{ glColor3fv(c); glVertex3fv(v); }while(0)//

	static int list = 0;
	if (list == 0)
	{
		// 如果显示列表不存在，则创建
		GLfloat
			PointA[] = { 0.5f, -sqrt(6.0f) / 12, -sqrt(3.0f) / 6 },
			PointB[] = { -0.5f, -sqrt(6.0f) / 12, -sqrt(3.0f) / 6 },
			PointC[] = { 0.0f, -sqrt(6.0f) / 12, sqrt(3.0f) / 3 },
			PointD[] = { 0.0f, sqrt(6.0f) / 4, 0 };
		GLfloat
			ColorR[] = { 1, 0, 0 },
			ColorG[] = { 0, 1, 0 },
			ColorB[] = { 0, 0, 1 },
			ColorY[] = { 1, 1, 0 };

		list = glGenLists(1);

		glNewList(list, GL_COMPILE); //以下的内容只是装入到显示列表，但现在不执行它们

		//glBegin( /* 在这里填上你所希望的模式 */);
		/* 在这里使用glVertex*系列函数 */
		/* 指定你所希望的顶点位置 */
		//glEnd();
		glBegin(GL_TRIANGLES);       //把每个顶点作为一个独立的三角形
		// 平面ABC
		ColoredVertex(ColorR, PointA);
		ColoredVertex(ColorG, PointB);
		ColoredVertex(ColorB, PointC);
		// 平面ACD
		ColoredVertex(ColorR, PointA);
		ColoredVertex(ColorB, PointC);
		ColoredVertex(ColorY, PointD);
		// 平面CBD
		ColoredVertex(ColorB, PointC);
		ColoredVertex(ColorG, PointB);
		ColoredVertex(ColorY, PointD);
		// 平面BAD
		ColoredVertex(ColorG, PointB);
		ColoredVertex(ColorR, PointA);
		ColoredVertex(ColorY, PointD);

		glEnd();

		glEndList();

		glEnable(GL_DEPTH_TEST);
	}

	// 已经创建了显示列表，在每次绘制正四面体时将调用它
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glRotatef(angle, 1, 0.5, 0);//相当于旋转了世界坐标轴
	glCallList(list);
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);//在其它的GLUT使用之前调用一次
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);//设置显示方式，使用RGB颜色，缓冲区模式
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("OpenGL程序中的显示列表");//根据前面设置的信息创建窗口

	//当需要画图时，请调用myDisplay函数(myDisplay为回调函数)
	glutDisplayFunc(&myDisplayList);

	glutMainLoop();
	return 0;
}
