#pragma once

#include "PrintFont.h"

class Print2DFont : public PrintFont
{
public:
	Print2DFont();

	GLvoid BuildFont(GLvoid) override;
	GLvoid KillFont(GLvoid) override;

	GLvoid glPrint(GLint x, GLint y, char *string) override;

	//~Print2DFont();

private:
	//Print2DFont(const Print2DFont& other){}
	//Print2DFont& operator=(const Print2DFont& other){}


};
