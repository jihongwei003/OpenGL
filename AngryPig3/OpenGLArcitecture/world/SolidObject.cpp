#include "SolidObject.h"

#include <glut.h>
#include <vector>

SolidObject::SolidObject()
{
	x = 0;
	y = 0;
	z = 0;
	rotY = 0;
	rotZ = 0;
}

bool SolidObject::render()
{
	glPushMatrix();

	glTranslatef(x, y, z);
	glRotatef(rotY, 0.0f, 1.0f, 0.0f);
	glRotatef(rotZ, 0.0f, 0.0f, 1.0f);

	m_pMesh->paint();

	glPopMatrix();

	return false;
}

/*实用函数，用于加载来自3DExploration的openGL顶点数组，并以此设置属性域
*该方法只加载不含纹理坐标的顶点数组
*参数：
*1.顶点数目。查询3DExploration的顶点数组的三角形数目（位于转换得到的.cpp顶端），然后将这个数目乘3
*2-4.相应顶点数组的名称
*这个方法不能放在Mesh类中，因为该方法涉及到构造一个新的Mesh，Mesh没有自构造的能力*/
void SolidObject::loadMesh(unsigned vertexNum, 
	int face_indicies[][6], unsigned faceIndiciesLength, 
	float vertices[][3],  unsigned verticesLength,
	float normals[][3],	 unsigned normalsLength,
	float colorR, float colorG, float colorB)
{
	std::vector<float> vecVertex;
	std::vector<float> vecNormal;
	std::vector<float> vecColor;

	for(unsigned i=0;i<faceIndiciesLength/sizeof(face_indicies[0]);i++)
	{
		for(unsigned j=0;j<3;j++)
		{
			int vi=face_indicies[i][j];
			int ni=face_indicies[i][j+3];//Normal index
			vecVertex.push_back(vertices[vi][0]);
			vecVertex.push_back(vertices[vi][1]);
			vecVertex.push_back(vertices[vi][2]);
			vecNormal.push_back(normals[ni][0]);
			vecNormal.push_back(normals[ni][1]);
			vecNormal.push_back(normals[ni][2]);
			vecColor.push_back(colorR);
			vecColor.push_back(colorG);
			vecColor.push_back(colorB);
		}
	}

	m_pMesh = new Mesh(vertexNum, GL_TRIANGLES);
	m_pMesh->loadColor(vecColor.data(), vecColor.size()*sizeof(float), GL_FLOAT, 3);
	m_pMesh->loadVertex(vecVertex.data(), vecVertex.size()*sizeof(float), GL_FLOAT, 3);
	m_pMesh->loadNormal(vecNormal.data(), vecNormal.size()*sizeof(float), GL_FLOAT);
}

SolidObject::~SolidObject()
{
	delete m_pMesh;
}