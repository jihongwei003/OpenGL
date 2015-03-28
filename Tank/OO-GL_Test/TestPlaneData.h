#pragma once

#include <glut.h>
#include <string>

namespace TestPlaneData{
	extern unsigned vertexNum;
	extern GLint face_indicies[472][9];
	extern GLfloat vertices[388][3];
	extern GLfloat normals[1416][3];
	extern std::string texureFileName;
	extern GLfloat textures[1416][2];
}