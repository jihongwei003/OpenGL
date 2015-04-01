/**
*  你必须在继承类中完成以下函数的实现
*
*  void InitList();
*
*/
#include "MeshModel.h"

#include <stdlib.h>
#include <vector>

MeshModel::MeshModel()
{

}

/*装载顶点坐标*/
void MeshModel::LoadVertex(void *pSrc, int length, GLenum type, int size)
{
	m_vertexArray.LoadArray(pSrc, length, type, size);
}
/*装载颜色*/
void MeshModel::LoadColor(void *pSrc, int length, GLenum type, int size)
{
	m_colorArray.LoadArray(pSrc, length, type, size);
}
/*装载法向量*/
void MeshModel::LoadNormal(void *pSrc, int length, GLenum type)
{
	m_normalArray.LoadArray(pSrc, length, type, 3);
}
/*装载索引*/
void MeshModel::LoadIndex(void *pSrc, int length, GLenum type)
{
	m_indexArray.LoadArray(pSrc, length, type, 1);
}
/*装载纹理*/
void MeshModel::LoadTexture(std::string fileName, void *pSrc, int length, GLenum type, int size)
{
	m_texture.LoadTexture(fileName);
	//m_texture.Apply(); //SetRenderMode里绑定
	m_textureArray.LoadArray(pSrc, length, type, size);
}

void MeshModel::SetMatirial(
	const float ambient[4],  //多次反射后强度
	const float diffuse[4],  //漫反射后强度
	const float specular[4], //镜面反射后强度
	const float emission[4], //材质颜色
	const float shininess)   //“镜面指数”，即粗糙程度
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient); //（面，哪个属性，设置成什么）
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}

/* 首先，已知顶点位置坐标v0 v1 v2 v3…和法向量n0 n1 n2 n3…。
* (上述vi 和 ni都是数组，长度为3，表示一个三维向量)
* 因此，指定3个序号，比如0,1,2代表v0v1v2即可指定一个三角形3个顶点的位置；
* 又指定3个序号，比如0,2,4代表n0n2n4即可指定一个三角形3个顶点的法向量。
* 把刚才指定的序号结合在一起，即0，1,2,0,2,4，即可描述一个三角形面的位置和方向 
*/
void MeshModel::LoadMeshDataFrom3DE(
	unsigned vertexNum,
	int face_indicies[][6], unsigned faceIndiciesLength,
	float vertices[][3], unsigned verticesLength,
	float normals[][3], unsigned normalsLength,
	float colorR, float colorG, float colorB)
{
	std::vector<float> vecVertex;
	std::vector<float> vecNormal;
	std::vector<float> vecColor;

	for (unsigned i = 0; i<faceIndiciesLength / sizeof(face_indicies[0]); i++)
	{
		for (unsigned j = 0; j<3; j++)
		{
			int vi = face_indicies[i][j];
			int ni = face_indicies[i][j + 3];//Normal index
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

	LoadColor(vecColor.data(), vecColor.size()*sizeof(float), GL_FLOAT, 3);
	LoadVertex(vecVertex.data(), vecVertex.size()*sizeof(float), GL_FLOAT, 3);
	LoadNormal(vecNormal.data(), vecNormal.size()*sizeof(float), GL_FLOAT);
}

void MeshModel::LoadMeshDataWithTexFrom3DE(
	unsigned vertexNum,
	int face_indicies[][9], unsigned faceIndiciesLength,
	float vertices[][3], unsigned verticesLength,
	float normals[][3], unsigned normalsLength,
	std::string fileName,
	float textures[][2], unsigned texturesLength)
{
	std::vector<float> vecVertex;
	std::vector<float> vecNormal;
	std::vector<float> vecTexture;

	for (unsigned i = 0; i<faceIndiciesLength / sizeof(face_indicies[0]); i++)
	{
		for (unsigned j = 0; j<3; j++)
		{
			int vi = face_indicies[i][j];     //顶点坐标的序号
			int ni = face_indicies[i][j + 3]; //法向量的序号
			int ti = face_indicies[i][j + 6]; //纹理坐标的序号
			vecVertex.push_back(vertices[vi][0]);
			vecVertex.push_back(vertices[vi][1]);
			vecVertex.push_back(vertices[vi][2]);
			vecNormal.push_back(normals[ni][0]);
			vecNormal.push_back(normals[ni][1]);
			vecNormal.push_back(normals[ni][2]);
			vecTexture.push_back(textures[ti][0]);
			vecTexture.push_back(textures[ti][1]);
		}
	}

	LoadVertex(vecVertex.data(), vecVertex.size()*sizeof(float), GL_FLOAT, 3);
	LoadNormal(vecNormal.data(), vecNormal.size()*sizeof(float), GL_FLOAT);
	LoadTexture(fileName, vecTexture.data(), vecTexture.size()*sizeof(float), GL_FLOAT, 2);
}


/*清空数据*/
void MeshModel::Clear()
{
	m_vertexArray.Clear();
	m_normalArray.Clear();
	m_indexArray.Clear();
	m_colorArray.Clear();
	m_textureArray.Clear(); //纹理
}

/*析构*/
MeshModel::~MeshModel()
{
	Clear();
}
