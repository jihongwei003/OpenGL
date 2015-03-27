#pragma once

#include <glut.h>
#include <string>

namespace TankTurretData{
	extern unsigned vertexNum;
	extern GLint face_indicies[122][9];
	extern GLfloat vertices[189][3];
	extern GLfloat normals[366][3];
	extern std::string texureFileName;
	extern GLfloat textures[366][2];

	extern const float LENGTH;
}