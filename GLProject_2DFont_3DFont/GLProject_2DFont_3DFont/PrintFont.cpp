#include "PrintFont.h"

PrintFont::PrintFont()
{
	//hDC = wglGetCurrentDC(); //获取不到？
	m_hDC = GetDC(GetForegroundWindow());
	m_base = 0;
}

GLvoid PrintFont::GenFont(GLvoid)
{
	m_font = CreateFont(
		-24,	 //字体高度
		0,		 //字体宽度，0为默认比例
		0,		 //字体的旋转角度 Angle Of Escapement
		0,		 //字体底线的旋转角度Orientation Angle
		FW_BOLD, //字体的重量（粗细）
		FALSE,	 //是否使用斜体
		FALSE,	 //是否使用下划线
		FALSE,	 //是否使用删除线
		ANSI_CHARSET,	     //设置字符集
		OUT_TT_PRECIS,		 //输出精度
		CLIP_DEFAULT_PRECIS, //裁剪精度
		ANTIALIASED_QUALITY, //输出质量（反锯齿）
		FF_DONTCARE | DEFAULT_PITCH, //Family And Pitch
		"Courier New");			     //字体名称
}

GLvoid PrintFont::ApplyFont(GLvoid)
{
	m_oldFont = (HFONT)SelectObject(m_hDC, m_font); //选择我们需要的字体
}

GLvoid PrintFont::DestroyFont(GLvoid)
{
	SelectObject(m_hDC, m_oldFont); //选择原来的字体

	DeleteObject(m_font);	//删除字体
}