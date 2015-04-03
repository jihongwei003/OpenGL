#include "TriangleFace.h"

#include <stdio.h>

TriangleFace::TriangleFace()
{
	faceIndices[0] = NULL;
	faceIndices[1] = NULL;
	faceIndices[2] = NULL;

	planeEq.a = NULL;
	planeEq.b = NULL;
	planeEq.c = NULL;
	planeEq.d = NULL;

	neighbourFace[0] = NULL;
	neighbourFace[1] = NULL;
	neighbourFace[2] = NULL;

	lighted = false;
}

void TriangleFace::CalculatePlane(GLPointf v1, GLPointf v2, GLPointf v3)
{
	planeEq.a = v1.y*(v2.z - v3.z) + v2.y*(v3.z - v1.z) + v3.y*(v1.z - v2.z);
	planeEq.b = v1.z*(v2.x - v3.x) + v2.z*(v3.x - v1.x) + v3.z*(v1.x - v2.x);
	planeEq.c = v1.x*(v2.y - v3.y) + v2.x*(v3.y - v1.y) + v3.x*(v1.y - v2.y);
	planeEq.d = -(v1.x*(v2.y*v3.z - v3.y*v2.z) + v2.x*(v3.y*v1.z - v1.y*v3.z) + v3.x*(v1.y*v2.z - v2.y*v1.z));
}