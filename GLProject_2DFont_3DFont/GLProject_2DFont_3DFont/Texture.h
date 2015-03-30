#pragma once

#include <glut.h>
#include <string>

/*二维贴图纹理
* 使用BMP类型的外部图片
* 功能：包括纹理的加载和应用*/
class Texture{
public:
	Texture();

	/*应用为当前纹理*/
	void Apply();

	//装载纹理，如果失败，返回0；如果成功，返回纹理编号
	GLuint LoadTexture(std::string fileName);

private:
	GLuint m_texId;   //Apply()的时候用
	GLint m_texWidth; //ResizeBMP()的时候用
	GLint m_texHeight;

	//读取一个24位BMP文件作为纹理
	unsigned char* LoadBMP(std::string fileName);

	//检查一个整数是否为2的整数次方，如果是，返回1，否则返回0
	bool IsIntegerSquareOfTwo(int n);

	/*在旧版本的OpenGL中
	* 如果图象的宽度和高度不是的整数次方，则需要进行缩放
	* 这里并没有检查OpenGL版本，出于对版本兼容性的考虑，按旧版本处理
	* 另外，无论是旧版本还是新版本，
	* 当图象的宽度和高度超过当前OpenGL实现所支持的最大值时，也要进行缩放*/
	bool ResizeBMP(GLint *width, GLint *height, GLubyte *pixels);
};