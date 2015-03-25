#include "Axis.h"

Axis::Axis()
{
	float vertexArray[] = {
		//xÖá
		0, 0, 0,
		10, 0, 0,
		//yÖá
		0, 0, 0,
		0, 10, 0,
		//zÖá
		0, 0, 0,
		0, 0, 10 };
	float colorArray[] = {
		//ºìÉ«xÖá
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 0.5f,
		//ÂÌÉ«yÖá
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 0.5f,
		//À¶É«zÖá
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.5f
	};

	GLuint indexArray[] = { 0, 1, 2, 3, 4, 5 };

	m_meshModel.LoadVertex((void*)vertexArray, sizeof(vertexArray), GL_FLOAT, 3);
	m_meshModel.LoadColor((void*)colorArray, sizeof(colorArray), GL_FLOAT, 4);
	//LoadIndex((void*)indexArray, sizeof(indexArray), GL_UNSIGNED_INT);
}

void Axis::InitList()
{

}

void Axis::Render()
{
	//m_paintMode = GL_LINES; //SetRenderMode(...);
	Paint(6);
}