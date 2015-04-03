#pragma once

#include <glut.h>
#include <string>

namespace SkyBoxData{
	extern unsigned vertexNum;
	extern GLint face_indicies[12][9];
	extern GLfloat vertices[32][3];
	extern GLfloat normals[36][3];
	extern std::string texureFileName;
	extern GLfloat textures[36][2];
}