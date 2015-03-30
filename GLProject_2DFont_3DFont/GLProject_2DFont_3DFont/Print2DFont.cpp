#include "Print2DFont.h"

#include <stdarg.h>	//用来定义可变参数的头文件(va_list)

Print2DFont::Print2DFont() 
: PrintFont()
{

}

GLvoid Print2DFont::BuildFont(GLvoid)
{
	GenFont();

	m_base = glGenLists(96); //96个连续显示列表的索引，返回这块连续索引的起始位置

	ApplyFont();

	//可以使用wglUseFontBitmaps函数(windows)来批量的产生显示字符用的显示列表。(将ASCII字符装入显示列表)
	wglUseFontBitmaps(m_hDC, 32, 96, m_base); //创建96个显示列表，绘制从ASCII码为32-128的字符

	DestroyFont();
}

GLvoid Print2DFont::KillFont(GLvoid)
{
	glDeleteLists(m_base, 96); //(begin,range)
}

//（左，下） = （0,0）
GLvoid Print2DFont::glPrint(GLint x, GLint y, char *string)
{
	char text[256]; //保存文字串
	va_list ap;     //指向一个变量列表的指针

	if (string == NULL)
		return;

	//接下来三行代码将文字中的所有符号转换为它们的字符编号。最后，文字和转换的符号被存储在一个叫做text的字符串中。
	va_start(ap, string); //分析可变参数
	//int vsprintf(char *string, char *format, va_list param); //将param 按格式format写入字符串string中
	vsprintf(text, string, ap); //把参数值写入字符串 
	va_end(ap); //结束分析

	//glMatrixMode(GL_PROJECTION);
	//glPushMatrix();
	//glLoadIdentity();
	//gluOrtho2D(0.0, 640, 0.0, 480);

	//glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();
	//glLoadIdentity();

	glColor3f(0, 1, 0);//红色字体
	glRasterPos2f(x, y); //使用的世界坐标系！

	glPushAttrib(GL_LIST_BIT);	//把显示列表属性压入属性堆栈

	//指定一个偏移量，这个偏移量将与显示列表索引相加，以获得最终的显示列表索引
	glListBase(m_base - 32); //设置显示列表的基础值（base-32就到了0，然后显示列表是从0偏移32个开始的）

	//（执行列表序列的个数、列表值的类型、所要显示的文本）
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	//调用显示列表绘制字符串

	glPopAttrib();
	glColor3f(1, 1, 1); //恢复场景颜色！

	//glMatrixMode(GL_PROJECTION);
	//glPopMatrix();
	
	//glMatrixMode(GL_MODELVIEW);	
	//glPopMatrix();
}