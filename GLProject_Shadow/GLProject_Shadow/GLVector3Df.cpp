#include "GLVector3Df.h"

#include <math.h>

GLVector3Df::GLVector3Df()
{
	i = 0.0f;
	j = 0.0f;
	k = 0.0f;

	length = sqrt(i*i + j*j + k*k);
}
GLVector3Df::GLVector3Df(float i, float j, float k)
{
	this->i = i;
	this->j = j;
	this->k = k;

	length = sqrt(i*i + j*j + k*k);
}

//加、减、数乘
GLVector3Df GLVector3Df::operator+(const GLVector3Df& other)
{
	return GLVector3Df(i + other.i, j + other.j, k + other.k);
}

GLVector3Df GLVector3Df::operator-(const GLVector3Df& other)
{
	return GLVector3Df(i - other.i, j - other.j, k - other.k);
}

GLVector3Df GLVector3Df::operator*(const float& length)
{
	return GLVector3Df(i * length, j * length, k * length);
}

//+= -= *=
GLVector3Df& GLVector3Df::operator+=(const GLVector3Df& other)
{
	i += other.i;
	j += other.j;
	k += other.k;

	return *this;
}

GLVector3Df& GLVector3Df::operator-=(const GLVector3Df& other)
{
	i -= other.i;
	j -= other.j;
	k -= other.k;

	return *this;
}

GLVector3Df& GLVector3Df::operator*=(const float& length)
{
	i *= length;
	j *= length;
	k *= length;

	return *this;
}

//单位化
void GLVector3Df::Normalize()
{
	length = sqrt(i*i + j*j + k*k);

	i = i / length;
	j = j / length;
	k = k / length;
}

//赋值和拷贝构造
GLVector3Df::GLVector3Df(const GLVector3Df& other)
{
	i = other.i;
	j = other.j;
	k = other.k;
}
GLVector3Df& GLVector3Df::operator = (const GLVector3Df& other)
{
	if (this == &other)//检查自己给自己赋值
	{
		return *this;//或不做任何处理
	}
	else
	{
		i = other.i;
		j = other.j;
		k = other.k;
	}
	return *this;
}