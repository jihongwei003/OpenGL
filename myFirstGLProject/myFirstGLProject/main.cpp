#include <glut.h>//其中已经包含<GL/gl.h>和<GL/glu.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static GLfloat angle = 0.0f;

void myDisplayLight(void);
void myDisplayList(void);
void myDisplayBlend(void);

#define WindowWidth  400
#define WindowHeight 400
#define BMP_Header_Length 54

/*Windows所使用的BMP文件，在开始处有一个文件头，大小为54字节
*54个字节以后，如果是16色或256色BMP，则还有一个颜色表，但24位色BMP没有这个
*单一像素的大小为3字节
*图象的宽度和高度都是一个32位整数，在文件中的地址分别为0x0012和0x0016
*BMP文件采用了一种“对齐”的机制，每一行像素数据的长度若不是4的倍数，则填充一些数据使它是4的倍数
*分配内存时，一定要小心，不能直接使用“图象的高度乘以宽度乘以每一像素的字节数”来计算分配空间的长度
*/

//截图
void grab(void)
{
	glReadBuffer(GL_FRONT);//以保证读取到的内容正好就是显示的内容

	// 计算像素数据的实际长度
	GLint i = WindowWidth * 3;// 得到每一行的像素数据长度
	while (i % 4 != 0)// 补充数据，直到i是的倍数
		++i;
	GLint PixelDataLength = i * WindowHeight;

	// 分配内存和打开文件
	GLubyte* pPixelData = (GLubyte*)malloc(PixelDataLength);//BMP文件尾的像素数据
	if (pPixelData == 0)
		exit(0);

	FILE* pDummyFile = fopen("dummy.bmp", "rb");
	if (pDummyFile == 0)
		exit(0);

	FILE* pWritingFile = fopen("grab.bmp", "wb");
	if (pWritingFile == 0)
		exit(0);

	// 读取像素
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glReadPixels(0, 0, WindowWidth, WindowHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, pPixelData);

	// 把dummy.bmp的文件头复制为新文件的文件头
	GLubyte  BMP_Header[BMP_Header_Length];//BMP头54字节的数据

	fread(BMP_Header, sizeof(BMP_Header), 1, pDummyFile);
	fwrite(BMP_Header, sizeof(BMP_Header), 1, pWritingFile);
	fseek(pWritingFile, 0x0012, SEEK_SET);

	i = WindowWidth;
	GLint j = WindowHeight;
	fwrite(&i, sizeof(i), 1, pWritingFile);
	fwrite(&j, sizeof(j), 1, pWritingFile);

	// 写入像素数据
	fseek(pWritingFile, 0, SEEK_END);
	fwrite(pPixelData, PixelDataLength, 1, pWritingFile);

	// 释放内存和关闭文件
	fclose(pDummyFile);
	fclose(pWritingFile);
	free(pPixelData);
}

/* 在空闲时调用，作用是把日期往后移动一天并重新绘制，达到动画效果 */
void myIdle(void)
{
	//++day;
	//if (day >= 360) day = 0;

	angle += 1.0f;
	if (angle >= 360.0f)
		angle = 0.0f;

	myDisplayBlend();
}

//计算帧速，一秒钟内播放的画面数目（FPS），在myDisplayLight()中使用
double CalFrequency()
{
	static int count;
	static double save;
	static clock_t last, current;
	double timegap;

	++count;
	if (count <= 50)
		return save;
	count = 0;
	last = current;
	current = clock();
	timegap = (current - last) / (double)CLK_TCK;
	save = 50.0 / timegap;
	return save;
}

//光照、视图变换
void myDisplayLight(void)
{
	double FPS = CalFrequency();
	std::cout<<FPS<<"\n", FPS;

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
		//glEnable(GL_DEPTH_TEST);
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

	//static int day = 200; // day的变化：从0到359

	// 绘制红色的“太阳”
	//glColor3f(1.0f, 0.0f, 0.0f);
	//glutSolidSphere(69, 20, 20);//（半径，经线，纬线）
	// 绘制蓝色的“地球”
	//glColor3f(0.0f, 0.0f, 1.0f);
	//glRotatef(day / 360.0*360.0, 0.0f, 0.0f, -1.0f);//旋转
	//glTranslatef(150, 0.0f, 0.0f);//移动
	//glutSolidSphere(15, 20, 20);
	// 绘制黄色的“月亮”
	//glColor3f(1.0f, 1.0f, 0.0f);
	//glRotatef(day / 30.0*360.0 - day / 360.0*360.0, 0.0f, 0.0f, -1.0f);
	//glTranslatef(38, 0.0f, 0.0f);
	//glutSolidSphere(4, 20, 20);

	glFlush();//保证前面的OpenGL命令立即执行（而不是让它们在缓冲区中等待）
	glutSwapBuffers();//交换缓冲区
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
	glTranslatef(0.0f, 0.0f, 0.5f);
	glutSolidSphere(0.3, 30, 30);
	glPopMatrix();

	// 下面将绘制半透明物体了，因此将深度缓冲设置为只读
	glDepthMask(GL_FALSE);

	// 以(0.2, 0, -0.5)为中心，绘制一个半径为0.2的半透明蓝色球体（离观察者最近）
	setMatirial(blue_color, 30.0);
	glPushMatrix();
	glTranslatef(0.2f, 0.0f, -0.5f);
	glutSolidSphere(0.2, 30, 30);
	glPopMatrix();

	// 以(0.1, 0, 0)为中心，绘制一个半径为0.15的半透明绿色球体（在前两个球体之间）
	setMatirial(green_color, 30.0);
	glPushMatrix();
	glTranslatef(0.1, 0, 0);
	glutSolidSphere(0.15, 30, 30);
	glPopMatrix();

	// 完成半透明物体的绘制，将深度缓冲区恢复为可读可写的形式
	glDepthMask(GL_TRUE);

	glutSwapBuffers();
}

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


	//glBegin( /* 在这里填上你所希望的模式 */);
	/* 在这里使用glVertex*系列函数 */
	/* 指定你所希望的顶点位置 */
	//glEnd();

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

//两个纹理对象的编号
GLuint texGround;
GLuint texWall;

/* 函数power_of_two
* 检查一个整数是否为2的整数次方，如果是，返回1，否则返回0
* 实际上只要查看其二进制位中有多少个，如果正好有1个，返回1，否则返回0
* 在“查看其二进制位中有多少个”时使用了一个小技巧
* 使用n &= (n-1)可以使得n中的减少一个（具体原理大家可以自己思考）
*/
int power_of_two(int n)
{
	if (n <= 0)
		return 0;
	return (n & (n - 1)) == 0;
}

//读取一个BMP文件作为纹理.如果失败，返回0;如果成功，返回纹理编号
GLuint load_texture(const char* file_name)
{
	// 打开文件，如果失败，返回
	FILE* pFile = fopen(file_name, "rb");
	if (pFile == 0)
		return 0;

	// 读取文件中图象的宽度和高度
	GLint width, height;
	fseek(pFile, 0x0012, SEEK_SET);
	fread(&width, 4, 1, pFile);//读取出的值赋给传入的变量
	fread(&height, 4, 1, pFile);
	fseek(pFile, BMP_Header_Length, SEEK_SET);

	// 计算每行像素所占字节数，并根据此数据计算总像素字节数
	GLint total_bytes;
	{
		GLint line_bytes = width * 3;
		while (line_bytes % 4 != 0)
			++line_bytes;
		total_bytes = line_bytes * height;
	}

	// 根据总像素字节数分配内存
	GLubyte* pixels = 0;//像素数据
	pixels = (GLubyte*)malloc(total_bytes);
	if (pixels == 0)
	{
		fclose(pFile);
		return 0;
	}

	// 读取像素数据
	if (fread(pixels, total_bytes, 1, pFile) <= 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}


	// 在旧版本的OpenGL中
	// 如果图象的宽度和高度不是的整数次方，则需要进行缩放
	// 这里并没有检查OpenGL版本，出于对版本兼容性的考虑，按旧版本处理
	// 另外，无论是旧版本还是新版本，
	// 当图象的宽度和高度超过当前OpenGL实现所支持的最大值时，也要进行缩放
	{
		GLint max;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
		if (!power_of_two(width)
			|| !power_of_two(height)
			|| width > max
			|| height > max)
		{
			const GLint new_width = 256;
			const GLint new_height = 256; // 规定缩放后新的大小为边长的正方形
			GLint new_line_bytes, new_total_bytes;
			GLubyte* new_pixels = 0;

			// 计算每行需要的字节数和总字节数
			new_line_bytes = new_width * 3;
			while (new_line_bytes % 4 != 0)
				++new_line_bytes;
			new_total_bytes = new_line_bytes * new_height;

			// 分配内存
			new_pixels = (GLubyte*)malloc(new_total_bytes);
			if (new_pixels == 0)
			{
				free(pixels);
				fclose(pFile);
				return 0;
			}

			// 进行像素缩放
			gluScaleImage(GL_RGB,
				width, height, GL_UNSIGNED_BYTE, pixels,
				new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

			// 释放原来的像素数据，把pixels指向新的像素数据，并重新设置width和height
			free(pixels);
			pixels = new_pixels;
			width = new_width;
			height = new_height;
		}
	}



	// 分配一个新的纹理编号
	GLuint texture_ID = 0;
	glGenTextures(1, &texture_ID);//(个数，给谁)
	if (texture_ID == 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	// 在绑定前，先获得原来绑定的纹理编号，以便在最后进行恢复
	GLint last_texture_ID;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture_ID);

	// 绑定新的纹理，载入纹理并设置纹理参数
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//纹理图象被使用到一个等于它的形状上时
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//纹理图象被使用到一个大于它的形状上时
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//纹理坐标的第一维坐标值大于1.0或小于0.0时
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//纹理坐标的第二维坐标值大于1.0或小于0.0时

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);//像素级别,指定纹理贴图和材质混合的方式
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);//载入二维纹理

	glBindTexture(GL_TEXTURE_2D, last_texture_ID);

	// 之前为pixels分配的内存可在使用glTexImage2D以后释放.因为此时像素数据已经被OpenGL另行保存了一份（可能被保存到专门的图形硬件中）
	free(pixels);
	return texture_ID;
}

void myDisplayTex(void)
{
	// 清除屏幕
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 设置视角
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, 1, 1, 21);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1, 5, 5, 0, 0, 0, 0, 0, 1);

	// 使用“地”纹理绘制土地
	glBindTexture(GL_TEXTURE_2D, texGround);
	glBegin(GL_QUADS);//绘制由四个顶点组成的一组单独的四边形
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-8.0f, -8.0f, 0.0f);//纹理坐标+顶点坐标
	glTexCoord2f(0.0f, 5.0f); glVertex3f(-8.0f, 8.0f, 0.0f);
	glTexCoord2f(5.0f, 5.0f); glVertex3f(8.0f, 8.0f, 0.0f);
	glTexCoord2f(5.0f, 0.0f); glVertex3f(8.0f, -8.0f, 0.0f);
	glEnd();

	// 使用“墙”纹理绘制栅栏
	glBindTexture(GL_TEXTURE_2D, texWall);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-6.0f, -3.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-6.0f, -3.0f, 1.5f);
	glTexCoord2f(5.0f, 1.0f); glVertex3f(6.0f, -3.0f, 1.5f);
	glTexCoord2f(5.0f, 0.0f); glVertex3f(6.0f, -3.0f, 0.0f);
	glEnd();

	// 旋转后再绘制一个
	glRotatef(-90, 0, 0, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-6.0f, -3.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-6.0f, -3.0f, 1.5f);
	glTexCoord2f(5.0f, 1.0f); glVertex3f(6.0f, -3.0f, 1.5f);
	glTexCoord2f(5.0f, 0.0f); glVertex3f(6.0f, -3.0f, 0.0f);
	glEnd();

	glutSwapBuffers();
	//grab();//截屏
}


int main(int argc, char *argv[])
{
	glutInit(&argc, argv);//在其它的GLUT使用之前调用一次
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);//设置显示方式，使用RGB颜色，缓冲区模式
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("第一个OpenGL程序");//根据前面设置的信息创建窗口

	glutDisplayFunc(&myDisplayTex);//当需要画图时，请调用myDisplay函数(myDisplay为回调函数)
	//glutDisplayFunc(&myDisplayList);
	//glutDisplayFunc(&myDisplayBlend);
	//glutDisplayFunc(&myDisplayLight);

	//glutIdleFunc(&myIdle);//空闲时调用

	// 在这里做一些初始化
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);//开启纹理
	texGround = load_texture("ground.bmp");
	texWall = load_texture("wall.bmp");

	glutMainLoop();
	return 0;
}
