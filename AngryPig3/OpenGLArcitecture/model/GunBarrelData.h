#pragma once

#include <glut.h>

namespace GunBarrelData{
	extern unsigned vertexNum;
	extern const float LENGTH;//炮管长度
	extern const float DISTANCE;//炮管间距
	extern float r, g, b;
	extern GLint face_indicies[396][6];
	extern GLfloat vertices [739][3];
	extern GLfloat normals [1188][3]; 
}