#pragma once

//#include "MathConst.h"
#include "GLPointf.h"

//平面方程为: ax + by + cz + d = 0
typedef struct
{
	float a;
	float b;
	float c;
	float d;
}
PlaneEq;

//三角形面
class TriangleFace
{
public:
	TriangleFace();

	void CalculatePlane(GLPointf v1, GLPointf v2, GLPointf v3); //setPlaneEq()

	//~TriangleFace();

//private:
	//TriangleFace(const TriangleFace& other){}
	//TriangleFace& operator=(const TriangleFace& other){}

	unsigned int faceIndices[3];	//三角形面的3个索引值
	PlaneEq planeEq;				//平面表达式的4个参数
	unsigned int neighbourFace[3];  //3个相邻面的索引
	bool lighted;					//是否为光照面
};