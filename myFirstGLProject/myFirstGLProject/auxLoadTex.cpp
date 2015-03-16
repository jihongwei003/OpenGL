#include <stdio.h>
#include <GLAUX.H>//Nehe

GLuint texture[1];// 存储一个纹理

// 载入位图图象
AUX_RGBImageRec *LoadBMP(char *Filename)
{
	FILE *File = NULL;
	if (!Filename)
	{
		return NULL;
	}
	File = fopen(Filename, "r");
	if (File)
	{
		fclose(File);
		return auxDIBImageLoad(Filename);// 载入位图并返回指针
	}
	return NULL;
}

// 载入位图(调用上面的代码)并转换成纹理
int LoadGLTextures()
{
	int Status = FALSE;
	AUX_RGBImageRec *TextureImage[1];// 创建纹理的存储空间
	memset(TextureImage, 0, sizeof(void *)* 1);

	// 载入位图，检查有无错误，如果位图没找到则退出
	if (TextureImage[0] = LoadBMP("Data/NeHe.bmp"))
	{
		Status = TRUE;
		glGenTextures(1, &texture[0]);// 创建纹理

		// 使用来自位图数据生成的典型纹理
		glBindTexture(GL_TEXTURE_2D, texture[0]);

		// 生成纹理
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);// 线形滤波
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);// 线形滤波
	}

	if (TextureImage[0])// 纹理是否存在
	{
		if (TextureImage[0]->data)// 纹理图像是否存在
		{
			free(TextureImage[0]->data);
		}
		free(TextureImage[0]);
	}
	return Status;
}