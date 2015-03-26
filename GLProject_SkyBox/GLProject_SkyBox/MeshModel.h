/**
*  你必须在继承类中完成以下函数的实现
*
*  void InitList();
*
*/
#pragma once

#include "VertexArray.h"
#include "Texture.h"
#include "GlobalInit.h"

/* 3D网格模型MeshModel */
class MeshModel{
public:
	MeshModel(); 

	/* 在继承类中重写，可选添加显示列表 */
	//virtual void InitList() = 0;

	//定义材质
	void SetMatirial(
		const float ambient[4],  //多次反射后强度
		const float diffuse[4],  //漫反射后强度
		const float specular[4], //镜面反射后强度
		const float emission[4], //材质颜色
		const float shininess);  //“镜面指数”，即粗糙程度

	/*实用函数，用于加载来自3DExploration的openGL顶点数组，并以此设置属性域
	*该方法只加载不含纹理坐标的顶点数组
	*参数：
	*1.顶点数目。查询3DExploration的顶点数组的三角形数目（位于转换得到的.cpp顶端），然后将这个数目乘3
	*2-7.相应顶点数组的名称
	*/
	void LoadMeshDataFrom3DE(
		unsigned vertexNum,
		int face_indicies[][6], unsigned faceIndiciesLength,
		float vertices[][3], unsigned verticesLength,
		float normals[][3], unsigned normalsLength,
		float colorR, float colorG, float colorB);

	void LoadMeshDataWithTexFrom3DE(
		unsigned vertexNum,
		int face_indicies[][9], unsigned faceIndiciesLength,
		float vertices[][3], unsigned verticesLength,
		float normals[][3], unsigned normalsLength,
		std::string fileName,
		float textures[][2], unsigned texturesLength);

	/*析构*/
	~MeshModel();

	/*绘制像坐标轴这样的线型物体，不可避免要使用这两个方法，就不放在private里了*/
	void LoadVertex(void *pSrc, int length, GLenum type, int size); //装载顶点坐标 
	void LoadColor(void *pSrc, int length, GLenum type, int size);  //装载颜色 

	//坐标数组，必须使用
	VertexArray m_vertexArray;

	//法向量数组，计算光照时使用
	VertexArray m_normalArray;

	//颜色数组，二选一：1.直接指定颜色 或 2.来自纹理
	VertexArray m_colorArray;
	VertexArray m_textureArray;
	Texture m_texture;

	//索引数组，可选
	VertexArray m_indexArray;

private:
	/*复制并装载数据，以下函数均委托给VertexArray类完成
	* 参数：
	* 1.指向源数据的指针（任意类型指针可以强转成void*类型再传参），源数据将被复制
	* 2.源数据长度（字节数）
	* 3.数据类型，从以下列表选取{GL_INT, GL_UNSIGNED_INT, GL_FLOAT, GL_DOUBLE……}
	* 4.多少个数据表示一个点（如对于RGB表示的颜色，该参数为3）
	*/
	void LoadNormal(void *pSrc, int length, GLenum type); //装载法向量 
	void LoadIndex(void *pSrc, int length, GLenum type);  //装载索引 
	void LoadTexture(std::string fileName, void *pSrc, int length, GLenum type, int size);//装载纹理坐标

	/* 清空各个顶点数组数据 */
	void Clear();

	/* 材质 */
	float m_ambient[4];  //多次反射后强度
	float m_diffuse[4];  //漫反射后强度
	float m_specular[4]; //镜面反射后强度
	float m_emission[4]; //材质颜色
	float m_shininess;   //“镜面指数”，即粗糙程度
};