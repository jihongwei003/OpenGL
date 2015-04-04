#include <glut.h>

#include "stdio.h"

const GLint pickSize = 32;
int winWidth = 400, winHeight = 400;

void Initial(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void DrawRect(GLenum mode)
{
	if (mode == GL_SELECT) 
		glPushName(1); //压入堆栈
	glColor3f(1.0f, 0.0f, 0.0f);
	//glRectf(60.0f, 50.0f, 150.0f, 150.0f);
	glPushMatrix();
	glTranslatef(1, 0, 0);
	glutSolidSphere(1.0f, 20.0f, 20.0f);
	glPopMatrix();

	if (mode == GL_SELECT) 
		glPushName(2); //压入堆栈
	glColor3f(0.0f, 1.0f, 0.0f);
	//glRectf(230.0f, 50.0f, 330.0f, 150.0f);
	glPushMatrix();
	glTranslatef(1, 0, 2);
	glutSolidSphere(2.0f, 20.0f, 20.0f);
	glPopMatrix();

	if (mode == GL_SELECT) 
		glPushName(3); //压入堆栈
	glColor3f(0.0f, 0.0f, 1.0f);
	//glRectf(140.0f, 140.0f, 240.0f, 240.0f);
	glPushMatrix();
	glTranslatef(1, 0, 6);
	glutSolidSphere(2.0f, 20.0f, 20.0f);
	glPopMatrix();
}

void ProcessPicks(GLint nPicks, GLuint pickBuffer[])
{
	GLint i;
	GLuint name, *ptr;
	printf("选中的数目为%d个\n", nPicks);

	ptr = pickBuffer;
	for (i = 0; i<nPicks; i++){
		name = *ptr;	  //选中图元在堆栈中的位置
		ptr += 3;		  //跳过名字和深度信息
		ptr += name - 1;  //根据位置信息获得选中的图元名字

		if (*ptr == 1)
		{
			printf("你选择了红色图元\n");
		}
		if (*ptr == 2)
		{
			printf("你选择了绿色图元\n");
		}
		if (*ptr == 3)
		{
			printf("你选择了蓝色图元\n");
		}
		ptr++;
	}
	printf("\n\n");
}

void ChangeSize(int w, int h)
{
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		-10, 5, 0,
		1, 0, 3,  
		0, 1, 0);

	{
		GLfloat sun_light_position[] = { 0.0f, 20.0f, 0.0f, 1.0f }; //位置（第4个参数为0代表无限远）
		GLfloat sun_light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };  //多次反射后强度
		GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };  //漫反射后强度
		GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //镜面反射后强度

		glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position); //（几号光源，什么属性，设置成什么）
		glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);

		glEnable(GL_LIGHT0);   //启用光源
		glEnable(GL_LIGHTING); //开启光照
		//glEnable(GL_DEPTH_TEST);

		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	}

	DrawRect(GL_RENDER);

	glFlush();
}

void MousePlot(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
	GLuint pickBuffer[pickSize];
	GLint nPicks, vp[4];

	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN){
		glSelectBuffer(pickSize, pickBuffer); //设置选择缓冲区
		glRenderMode(GL_SELECT); //激活选择模式
		glInitNames();   //初始化名字堆栈

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();

		glGetIntegerv(GL_VIEWPORT, vp);
		//定义一个10×10的选择区域
		gluPickMatrix(
			GLdouble(xMouse),		   //设定我们选择框的大小，建立拾取矩阵，就是上面的公式 
			GLdouble(vp[3] - yMouse),  //viewport[3]保存的是窗口的高度，窗口坐标转换为OpenGL坐标 
			10.0, 10.0,				   //选择框的大小为10，10
			vp);					   //视口信息，包括视口的起始位置和大小 

		//gluOrtho2D(0.0, winWidth, 0.0, winHeight); //拾取矩阵乘以投影矩阵，这样就可以让选择框放大为和视体一样大 

		gluPerspective(45.0f, (GLfloat) (vp[2]-vp[0])/(GLfloat) (vp[3]-vp[1]), 0.1f, 100.0f);
		glMatrixMode(GL_MODELVIEW);

		DrawRect(GL_SELECT);

		//恢复投影变换
		glMatrixMode(GL_PROJECTION);
		glPopMatrix(); 
		glMatrixMode(GL_MODELVIEW);


		glFlush();

		//获得选择集并输出
		nPicks = glRenderMode(GL_RENDER); //得到选中物体的数目
		if( 0 != nPicks )
			ProcessPicks(nPicks, pickBuffer);

		glutPostRedisplay();
	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("拾取操作");
	glutDisplayFunc(Display);
	glutReshapeFunc(ChangeSize);
	glutMouseFunc(MousePlot);
	Initial();
	glutMainLoop();
	return 0;
}