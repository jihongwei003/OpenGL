#include "Ground.h"

Ground::Ground()
{
}

Ground::Ground(float x0, float z0, float x1, float z1, float height, float r, float g, float b)
{
   	setPosition(x0, z0, x1, z1, height);
	setColor(r, g, b);

	float vertex[12] = {
		x0, height, z0,
		x1, height, z0,
		x1, height, z1,
		x0, height, z1
	};

	float normal[12] = {
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	float color[12] = {
		r, g, b,
		r, g, b,
		r, g, b,
		r, g, b
	};

	m_pMesh = new Mesh(4, GL_QUADS);

	m_pMesh->loadVertex(vertex, sizeof(vertex), GL_FLOAT, 3);
	m_pMesh->loadNormal(normal, sizeof(normal), GL_FLOAT); 
	m_pMesh->loadColor(color, sizeof(color), GL_FLOAT, 3);

}

void Ground::setPosition(float x0, float z0, float x1, float z1, float height)
{
	m_x0 = x0;
	m_z0 = z0;
	m_x1 = x1;
	m_z1 = z1;
	m_height = height;
}

void Ground::setColor(float r, float g, float b)
{
	m_r = r;
	m_g = g;
	m_b = b;
}

bool Ground::render()
{
	m_pMesh->paint();
	return false;
}