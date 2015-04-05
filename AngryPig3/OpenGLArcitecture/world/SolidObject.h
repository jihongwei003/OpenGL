#pragma once

#include "WorldObject.h"
#include "Mesh.h"

class SolidObject : public WorldObject{
public:
	SolidObject();

	/*渲染到屏幕上
	*返回值：这个实例渲染结束后是否被删除*/
	virtual bool render() override;

	~SolidObject();

	float x;
	float y;
	float z;
	float rotY;//相对于y轴的旋转角度，即在水平面中的角度
	float rotZ;//相对于z轴的旋转角度，即仰角

	/*实用函数，用于加载来自3DExploration的openGL顶点数组，并以此设置属性域
	*该方法只加载不含纹理坐标的顶点数组
	*参数：
	*1.顶点数目。查询3DExploration的顶点数组的三角形数目（位于转换得到的.cpp顶端），然后将这个数目乘3
	*2-4.相应顶点数组的名称
	*5-7.设置模型颜色*/
	void loadMesh(unsigned vertexNum, 
		int face_indicies[][6], unsigned faceIndiciesLength, 
		float vertices[][3],  unsigned verticesLength,
		float normals[][3],	 unsigned normalsLength,
		float colorR, float colorG, float colorB);

protected:
	Mesh *m_pMesh;
};