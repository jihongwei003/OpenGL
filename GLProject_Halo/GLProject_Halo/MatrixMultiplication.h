#pragma once

#include <glut.h>

class MatrixMultiplication
{
public:
	static void MatrixMultiply(float M[16], float v[4])
	{
		GLfloat res[4];	// 保存中间计算结果

		res[0] = M[0] * v[0] + M[4] * v[1] + M[8] * v[2] + M[12] * v[3];
		res[1] = M[1] * v[0] + M[5] * v[1] + M[9] * v[2] + M[13] * v[3];
		res[2] = M[2] * v[0] + M[6] * v[1] + M[10] * v[2] + M[14] * v[3];
		res[3] = M[3] * v[0] + M[7] * v[1] + M[11] * v[2] + M[15] * v[3];

		v[0] = res[0]; // 把结果保存在V中
		v[1] = res[1];
		v[2] = res[2];
		v[3] = res[3];
	}
};