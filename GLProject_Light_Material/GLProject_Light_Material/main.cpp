#include <glut.h>//其中已经包含<GL/gl.h>和<GL/glu.h>

static GLfloat angle = 0.0f;

void myDisplayLight(void);

//材质、光照、视图变换
void myDisplayLight(void)
{
	glEnable(GL_DEPTH_TEST);//深度测试
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清空深度缓冲

	glMatrixMode(GL_PROJECTION);//设置当前操作的矩阵为“投影矩阵”
	glLoadIdentity();//把当前矩阵设置为单位矩阵
	gluPerspective(75, 1, 1, 400);//将当前的可视空间设置为透视投影空间（角度，宽高比，近，远）

	glMatrixMode(GL_MODELVIEW);//设置当前操作的矩阵为“模型视图矩阵”
	glLoadIdentity();
	gluLookAt(0, -200, 200, 0, 0, 0, 0, 0, 1);//（相机位置，相机朝向，相机向上方向）

	// 定义太阳光源，它是一种白色的光源
	{
		GLfloat sun_light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f }; //位置（第4个参数为0代表无限远）
		GLfloat sun_light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };  //多次反射后强度
		GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };  //漫反射后强度
		GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //镜面反射后强度

		glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position); //（几号光源，什么属性，设置成什么）
		glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);

		glEnable(GL_LIGHT0);   //启用光源
		glEnable(GL_LIGHTING); //开启光照
	}

	// 定义太阳的材质并绘制太阳
	{
		GLfloat sun_mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };  //多次反射后强度
		GLfloat sun_mat_diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };  //漫反射后强度
		GLfloat sun_mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f }; //镜面反射后强度
		GLfloat sun_mat_emission[] = { 0.5f, 0.0f, 0.0f, 1.0f }; //材质颜色
		GLfloat sun_mat_shininess = 0.0f;                        //“镜面指数”，即粗糙程度

		glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient); //（面，哪个属性，设置成什么）
		glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
		glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);

		glutSolidSphere(69, 20, 20);
	}

	// 定义地球的材质并绘制地球
	{
		GLfloat earth_mat_ambient[] = { 0.0f, 0.0f, 0.5f, 1.0f };
		GLfloat earth_mat_diffuse[] = { 0.0f, 0.0f, 0.5f, 1.0f };
		GLfloat earth_mat_specular[] = { 0.0f, 0.0f, 1.0f, 1.0f };
		GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat earth_mat_shininess = 30.0f;

		glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
		glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);

		glRotatef(angle, 0.0f, -1.0f, 0.0f);
		glTranslatef(150, 0.0f, 0.0f);

		glutSolidSphere(30, 20, 20);
	}

	glFlush();//保证前面的OpenGL命令立即执行（而不是让它们在缓冲区中等待）
	glutSwapBuffers();//交换缓冲区
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);//在其它的GLUT使用之前调用一次
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);//设置显示方式，使用RGB颜色，缓冲区模式
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("OpenGL程序中的光照、材质、视图变化");//根据前面设置的信息创建窗口

	//当需要画图时，请调用myDisplay函数(myDisplay为回调函数)
	glutDisplayFunc(&myDisplayLight);

	glutMainLoop();
	return 0;
}
