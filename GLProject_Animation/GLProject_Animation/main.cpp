#include <glut.h>//其中已经包含<GL/gl.h>和<GL/glu.h>

static GLfloat angle = 0.0f;

void myDisplayBlend(void);

/* 在空闲时调用，作用是把日期往后移动一天并重新绘制，达到动画效果 */
void myIdle(void)
{
	angle += 0.1f;
	if (angle >= 360.0f)
		angle = 0.0f;

	myDisplayBlend();
}

//在myDisplayBlend()中使用
void setLight(void)
{
	static const GLfloat light_position[] = { 1.0f, 1.0f, -1.0f, 1.0f };
	static const GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	static const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	static const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

//在myDisplayBlend()中使用
void setMatirial(const GLfloat mat_diffuse[4], GLfloat mat_shininess)
{
	static const GLfloat mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	static const GLfloat mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
}

//混合
void myDisplayBlend(void)
{
	// 定义一些材质颜色
	const static GLfloat red_color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	const static GLfloat green_color[] = { 0.0f, 1.0f, 0.0f, 0.3333f };
	const static GLfloat blue_color[] = { 0.0f, 0.0f, 1.0f, 0.5f };

	// 使用默认的RGBA和深度值清除屏幕
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 启动混合并设置混合因子
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//(源因子，目标因子)

	// 设置光源
	setLight();

	// 以(0, 0, 0.5)为中心，绘制一个半径为0.3的不透明红色球体（离观察者最远）
	setMatirial(red_color, 30.0);
	glPushMatrix();

	glRotatef(angle, 0.0f, -1.0f, 0.0f);

	glTranslatef(0.0f, 0.0f, 0.5f);
	glutSolidSphere(0.3, 30, 30);
	glPopMatrix();

	// 下面将绘制半透明物体了，因此将深度缓冲设置为只读
	glDepthMask(GL_FALSE);

	// 以(0.2, 0, -0.5)为中心，绘制一个半径为0.2的半透明蓝色球体（离观察者最近）
	setMatirial(blue_color, 30.0);
	glPushMatrix();

	glRotatef(angle, 1.0f, 0.0f, 0.0f);

	glTranslatef(0.2f, 0.0f, -0.5f);
	glutSolidSphere(0.2, 30, 30);
	glPopMatrix();

	// 以(0.1, 0, 0)为中心，绘制一个半径为0.15的半透明绿色球体（在前两个球体之间）
	setMatirial(green_color, 30.0);
	glPushMatrix();

	glRotatef(angle, 0.0f, 0.0f, 1.0f);

	glTranslatef(0.1, 0, 0);
	glutSolidSphere(0.15, 30, 30);
	glPopMatrix();

	// 完成半透明物体的绘制，将深度缓冲区恢复为可读可写的形式
	glDepthMask(GL_TRUE);

	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);//在其它的GLUT使用之前调用一次
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);//设置显示方式，使用RGB颜色，缓冲区模式
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("OpenGL程序中的动画");//根据前面设置的信息创建窗口

	//当需要画图时，请调用myDisplay函数(myDisplay为回调函数)
	glutDisplayFunc(&myDisplayBlend);

	glutIdleFunc(&myIdle);//空闲时调用

	glutMainLoop();
	return 0;
}
