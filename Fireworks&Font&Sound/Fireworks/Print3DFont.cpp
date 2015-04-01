#include "Print3DFont.h"

Print3DFont::Print3DFont()
:PrintFont()
{
	m_usingTex = false;
}

GLvoid Print3DFont::BuildFont(GLvoid)
{
	m_tex.LoadTexture("mingzhuta.bmp");

	m_base = glGenLists(256);

	GenFont(); //3D字体只能显示TrueType字体！
	ApplyFont();

	wglUseFontOutlines(
		m_hDC,				//设置当前窗口设备描述表的句柄
		0,					//用于创建显示列表字体的第一个字符的ASCII值
		255,				//字符数
		m_base,				//一个显示列表的名称
		0.0f,				//字体的光滑度，越小越光滑，0.0为最光滑的状态
		0.2f,				//在z方向突出的距离
		WGL_FONT_POLYGONS,	//使用多边形来生成字符，每个顶点具有独立的法线
		m_gmf);				//一个接收字形度量数据的数组的地址，每个数组元素用它对应的显示列表字符的数据填充 

	DestroyFont();
}

GLvoid Print3DFont::KillFont(GLvoid)
{
	glDeleteLists(m_base, 256); //(begin,range)
}

GLvoid Print3DFont::glPrint(GLint x, GLint y, char *string)
{
	//float length = 0; //查询字符串的长度///////////////以后不一定会用到！

	char text[256]; //保存文字串
	va_list ap;     //指向一个变量列表的指针

	if (string == NULL)
		return;

	va_start(ap, string);       //分析可变参数
	vsprintf(text, string, ap); //把参数值写入字符串 
	va_end(ap);					//结束分析

	//for (unsigned int loop = 0; loop<(strlen(text)); loop++)	//查找整个字符串的长度
	//{
	//	length += gmf[text[loop]].gmfCellIncX;
	//}

	glPushMatrix();

	glColor3f(0, 1, 0);
	//glTranslatef(-length / 2, 0.0f, 0.0f);	//把字符串置于最左边
	glTranslatef(x, y, 0);

	glPushAttrib(GL_LIST_BIT);			

	if (true == m_usingTex)
	{
		//设置纹理映射模式
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glEnable(GL_TEXTURE_GEN_S);	//使用自动生成纹理
		glEnable(GL_TEXTURE_GEN_T);

		glEnable(GL_TEXTURE_2D);
		m_tex.Apply();
	}

	glListBase(m_base);	//设置显示列表的基础值为0
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text); //调用显示列表绘制字符串

	if (true == m_usingTex)
	{
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
	}

	glPopAttrib();
	glPopMatrix();

	glColor3f(1, 1, 1); //恢复场景颜色！
}