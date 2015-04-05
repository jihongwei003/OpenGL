#include "Axis.h"


Axis::Axis(void)
	: SolidObject()
{
	float vertexArray[] = {
		//x轴
		0, 0, 0,
		10, 0, 0, 
		//y轴
		0, 0, 0,
		0, 10, 0, 
		//z轴
		0, 0, 0,
		0, 0, 10};
	float colorArray[] = {
		//红色x轴
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 0.5f,
		//绿色y轴
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 0.5f,
		//蓝色z轴
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.5f
	};

	GLuint indexArray[] = {0, 1, 2, 3, 4, 5};

	m_pMesh = new Mesh(6, GL_LINES);

	m_pMesh->loadVertex((void*)vertexArray, sizeof(vertexArray), GL_FLOAT, 3);
	m_pMesh->loadColor((void*)colorArray, sizeof(colorArray), GL_FLOAT, 4);  
	m_pMesh->loadIndex((void*)indexArray, sizeof(indexArray), GL_UNSIGNED_INT);
}


/*渲染到屏幕上
*返回值：这个实例渲染结束后是否被删除*/
bool Axis::render()
{
	m_pMesh->paint();
	return false;
}

Axis::~Axis(void)
{
}
