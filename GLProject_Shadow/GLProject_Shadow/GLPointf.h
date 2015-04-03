#pragma once

#include "GLVector3Df.h"

class GLPointf
{
public:
	GLPointf();
	GLPointf(float x, float y, float z);

	//点 = 点 + 向量
	GLPointf operator+(const GLVector3Df& vector);
	GLPointf operator-(const GLVector3Df& vector);

	GLPointf& operator+=(const GLVector3Df& vector);
	GLPointf& operator-=(const GLVector3Df& vector);

	//向量 = 点2 - 点1
	static GLVector3Df CalculateVector(const GLPointf& point1, const GLPointf& point2);

	//赋值和拷贝构造
	GLPointf(const GLPointf& other);
	GLPointf& operator=(const GLPointf& other);
	//~GLPointf();

	//为了使用方便，设成公有的，且没写“m_”
	float x;
	float y;
	float z;
};
