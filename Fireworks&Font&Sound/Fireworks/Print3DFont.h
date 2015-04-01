#pragma once

#include "PrintFont.h"
#include "Texture.h"

class Print3DFont : public PrintFont
{
public:
	Print3DFont();

	GLvoid BuildFont(GLvoid) override;
	GLvoid KillFont(GLvoid) override;

	GLvoid glPrint(GLint x, GLint y, char *string) override;

	void UseTex(bool usingTex);

	//~Print3DFont();

private:
	//Print3DFont(const Print3DFont& other){}
	//Print3DFont& operator=(const Print3DFont& other){}

	GLYPHMETRICSFLOAT m_gmf[256];	//记录256个字符的信息
	bool m_usingTex;
	Texture m_tex;
};

inline
void Print3DFont::UseTex(bool usingTex)
{
	m_usingTex = usingTex;
}