#pragma once

class GLVector3Df
{
public:
	GLVector3Df();
	GLVector3Df(float i, float j, float k);

	//加、减、数乘
	GLVector3Df operator+(const GLVector3Df& other);
	GLVector3Df operator-(const GLVector3Df& other);
	GLVector3Df operator*(const float& length);

	//+= -= *=
	GLVector3Df& operator+=(const GLVector3Df& other);
	GLVector3Df& operator-=(const GLVector3Df& other);
	GLVector3Df& operator*=(const float& length);

	//单位化
	void Normalize();

	//赋值和拷贝构造
	GLVector3Df(const GLVector3Df& other);
	GLVector3Df& operator=(const GLVector3Df& other);
	//~GLPointf();

	//为了使用方便，设成公有的，且没写“m_”
	float i;
	float j;
	float k;
	float length;
};