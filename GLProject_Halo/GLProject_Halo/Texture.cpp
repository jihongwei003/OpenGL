#include "Texture.h"
#include <iostream>/////////////////////////////////////

#include <windows.h>

Texture::Texture()
{
	m_texId = 0;
	m_texWidth = 0;
	m_texHeight = 0;
}

/*应用为当前纹理*/
void Texture::Apply()
{
	glBindTexture(GL_TEXTURE_2D, m_texId);
}

/*检查一个整数是否为2的整数次方，如果是，返回1，否则返回0
* 实际上只要查看其二进制位中有多少个，如果正好有1个，返回1，否则返回0
* 在“查看其二进制位中有多少个”时使用了一个小技巧
* 使用n &= (n-1)可以使得n中的减少一个（具体原理大家可以自己思考）
*/
bool Texture::IsIntegerSquareOfTwo(int n)
{
	if (n <= 0)
		return 0;
	return (n & (n - 1)) == 0;
}

/*在旧版本的OpenGL中
* 如果图象的宽度和高度不是的整数次方，则需要进行缩放
* 这里并没有检查OpenGL版本，出于对版本兼容性的考虑，按旧版本处理
* 另外，无论是旧版本还是新版本，
* 当图象的宽度和高度超过当前OpenGL实现所支持的最大值时，也要进行缩放*/
bool Texture::ResizeBMP(GLint *width, GLint *height, GLubyte *pixels)
{
	GLint max;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
	if (!IsIntegerSquareOfTwo(*width)
		|| !IsIntegerSquareOfTwo(*height)
		|| *width > max
		|| *height > max)
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

		// 进行像素缩放
		gluScaleImage(GL_RGB,
			*width, *height, GL_UNSIGNED_BYTE, pixels,
			new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

		// 释放原来的像素数据，把pixels指向新的像素数据，并重新设置width和height
		free(pixels);
		pixels = new_pixels;
		*width = new_width;
		*height = new_height;
		return 1;
	}
	return 0;
}

unsigned char* Texture::LoadBMP(std::string fileName)
{
	FILE* pFile = fopen(fileName.c_str(), "rb"); //缺少检测是否打开成功！

	//读取文件中图象的宽度和高度，为了计算像素分配内存大小
	GLint width, height;
	fseek(pFile, 0x0012, SEEK_SET);
	fread(&width, 4, 1, pFile);
	fread(&height, 4, 1, pFile);
	fseek(pFile, 54, SEEK_SET);

	//计算每行像素所占字节数，并根据此数据计算总像素字节数
	GLint totalBytes;
	{
		GLint lineBytes = width * 3;
		while (lineBytes % 4 != 0)
			++lineBytes;
		totalBytes = lineBytes * height;
	}

	//根据总像素字节数分配内存
	GLubyte* pixels = 0; //像素数据
	pixels = (GLubyte*)malloc(totalBytes); //缺少检测分配后是否还为0！

	//读取像素数据
	fread(pixels, totalBytes, 1, pFile); //缺少检测是否读取成功！

	//当图象的宽度和高度超过当前OpenGL实现所支持的最大值时，需要进行缩放
	if (ResizeBMP(&width, &height, pixels))
		std::cout << "纹理已经过调整为2的整数次方以及合适大小" << std::endl;
	
	m_texWidth = width;
	m_texHeight = height;

	fclose(pFile);
	return pixels;
}

//装载纹理，如果失败，返回0；如果成功，返回纹理编号
GLuint Texture::LoadTexture(std::string fileName)
{
	GLubyte* pixels = LoadBMP(fileName);

	//分配一个新的纹理编号
	GLuint texID = 0;
	glGenTextures(1, &texID); //(个数，给谁)
	//std::cout << "纹理ID分配：" << texID << std::endl;

	if (texID == 0)
	{
		free(pixels);
		return 0;
	}
	//std::cout << "出现这句话就说明纹理ID分配成功了：" << texID << std::endl;

	// 在绑定前，先获得原来绑定的纹理编号，以便在最后进行恢复
	GLint last_texture_ID;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture_ID);

	//绑定新的纹理，载入纹理并设置纹理参数
	glBindTexture(GL_TEXTURE_2D, texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //纹理图象被使用到一个等于它的形状上时
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //纹理图象被使用到一个大于它的形状上时
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);     //纹理坐标的第一维坐标值大于1.0或小于0.0时
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);     //纹理坐标的第二维坐标值大于1.0或小于0.0时

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);       //像素级别,指定纹理贴图和材质混合的方式

	/*载入二维纹理
	* 若使用mipmap，则将这个函数换成gluBuild2DMipmaps() */
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_texWidth, m_texHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, m_texWidth, m_texHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);

	glBindTexture(GL_TEXTURE_2D, last_texture_ID);

	/*之前为pixels分配的内存可在使用glTexImage2D以后释放.
	* 因为此时像素数据已经被OpenGL另行保存了一份（可能被保存到专门的图形硬件中） */
	free(pixels);

	m_texId = texID; 
	return texID;
}

//生成一个空的纹理，大小为128*128
GLuint Texture::GenEmptyTexture()
{
	unsigned int* data;	//存储数据

	//为纹理数据（128*128*4）建立存储区
	data = (unsigned int*)new GLuint[((128 * 128) * 4 * sizeof(unsigned int))];

	ZeroMemory(data, ((128 * 128) * 4 * sizeof(unsigned int)));	//清除存储区windows.h

	GLuint texID;
	glGenTextures(1, &texID);	//创建一个纹理
	glBindTexture(GL_TEXTURE_2D, texID);	//构造纹理
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 128, 128, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);//用数据中的信息构造纹理

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	delete[] data;	//释放数据

	m_texId = texID;
	return texID;	//返回纹理ID
}

//渲染到纹理（没有使用FBO）
void Texture::RenderToTexture(void(*DrawScene)(GLenum mode))
{
	glPushAttrib(GL_VIEWPORT_BIT);

	glViewport(0, 0, 128, 128);	//设置视口大小为空纹理大小

	DrawScene(GL_RENDER);

	glBindTexture(GL_TEXTURE_2D, m_texId);	//绑定模糊纹理

	//拷贝视口到模糊纹理 (从 0,0 到 128,128... 无边界)
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, 0, 0, 128, 128, 0);

	//glClearColor(0.0f, 0.0f, 0.5f, 0.5);	//调整清晰的色彩到中等蓝色

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//清屏和深度缓冲

	glPopAttrib(); //恢复视口大小
	//glViewport(0, 0, 640, 480);	//调整视口 (0,0 to 640x480)
}
