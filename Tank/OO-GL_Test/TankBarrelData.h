#pragma once

#include <glut.h>
#include <string>

namespace TankBarrelData{
	extern unsigned vertexNum;
	extern GLint face_indicies[40][9];
	extern GLfloat vertices[96][3];
	extern GLfloat normals[120][3];
	extern std::string texureFileName;
	extern GLfloat textures[120][2];

	extern const float LENGTH; //ÅÚÍ²³¤¶È
}