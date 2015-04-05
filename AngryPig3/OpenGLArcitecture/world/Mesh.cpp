#include "Mesh.h"

#include <stdlib.h>

bool Mesh::m_usingIndex = true;
bool Mesh::m_usingLighting = true;
Mesh::ColorMode Mesh::m_colorMode = TEXTURE;

Mesh::Mesh()
{
}

Mesh::Mesh(unsigned vertexAmount, GLenum paintMode)
{
	m_vertexAmount = vertexAmount;
	m_paintMode = paintMode;
}

/*清空数据*/
void Mesh::clear()
{
	m_vertexArray.clear(); 
	m_normalArray.clear();
	m_colorArray.clear();
	m_textureArray.clear();
	m_indexArray.clear();
}

void Mesh::paint()
{
	/*装入数据*/
	//顶点坐标
	glVertexPointer(m_vertexArray.getSize(), m_vertexArray.getType(), 0, m_vertexArray.getInfoPointer());
	//如果需要则装入法向量
	if(m_usingLighting)
	{
		glNormalPointer(m_normalArray.getType(), 0, m_normalArray.getInfoPointer());
	}
	//根据渲染模式装入颜色或者纹理
	if(TEXTURE == m_colorMode)
	{
		glTexCoordPointer(m_textureArray.getSize(), m_textureArray.getType(), 0, m_textureArray.getInfoPointer());
	}
	else
	{
		glColorPointer(m_colorArray.getSize(), m_colorArray.getType(), 0, m_colorArray.getInfoPointer());
	}

	/*使用数据渲染*/
	if(m_usingIndex)
	{  
		glDrawElements(m_paintMode, m_vertexAmount, m_indexArray.getType(), m_indexArray.getInfoPointer());
	}
	else
	{
		glDrawArrays(m_paintMode, 0, m_vertexAmount);
	}

}

/*装载顶点坐标*/
void Mesh::loadVertex(void *pSrc, int length, GLenum type, int size)
{
	m_vertexArray.loadArray(pSrc, length, type, size);
}
/*装载颜色*/
void Mesh::loadColor(void *pSrc, int length, GLenum type, int size)
{
	m_colorArray.loadArray(pSrc, length, type, size);
}
/*装载法向量*/
void Mesh::loadNormal(void *pSrc, int length, GLenum type)
{
	m_normalArray.loadArray(pSrc, length, type, 3);
}
/*装载索引*/
void Mesh::loadIndex(void *pSrc, int length, GLenum type)
{
	m_indexArray.loadArray(pSrc, length, type, 1);
}

/*析构*/
Mesh::~Mesh()
{
}

/*初始化渲染参数*/
void Mesh::InitMesh(bool usingIndex, bool usingLighting, ColorMode colorMode, GLenum mode)
{
	glEnable(GL_CULL_FACE);
	//glPolygonMode(GL_FRONT, GL_FILL);
	SetFrontFace(mode);

	glEnable(GL_DEPTH_TEST);

	glShadeModel(GL_SMOOTH);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//打开顶点数组
	glEnableClientState(GL_VERTEX_ARRAY);
	SetRenderMode(usingIndex, usingLighting, colorMode);
}

/*定义“正面”的环绕方向，参数为GL_CCW（逆时针）或GL_CW（顺时针）*/
void Mesh::SetFrontFace(GLenum mode)
{
	glFrontFace(mode);
}

/*设定绘画模式*/
void Mesh::SetRenderMode(bool usingIndex, bool usingLighting, ColorMode colorMode)
{
	Mesh::m_usingIndex = usingIndex;
	Mesh::m_usingLighting = usingLighting;
	Mesh::m_colorMode = colorMode;

	if(usingLighting)
		glEnableClientState(GL_NORMAL_ARRAY);
	else
		glDisableClientState(GL_NORMAL_ARRAY);

	if(TEXTURE == colorMode)
	{
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);	
	}
	else
	{
		glEnableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}
