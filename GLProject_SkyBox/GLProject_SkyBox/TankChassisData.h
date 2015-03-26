#pragma once

#include <glut.h>
#include <string>

namespace TankChassisData{
	extern unsigned vertexNum;
	extern GLint face_indicies[522][9];
	extern GLfloat vertices[1050][3];
	extern GLfloat normals[1566][3];
	extern std::string texureFileName;
	extern GLfloat textures[1566][2];

	extern const float LENGTH;
}