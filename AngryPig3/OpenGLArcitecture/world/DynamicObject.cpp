#include "DynamicObject.h"

DynamicObject::DynamicObject()
	:SolidObject()
{
	 vx = 0;
	 vy = 0;
	 vz = 0;
}

bool DynamicObject::render()
{
	x += vx;
	y += vy;
	z += vz;

	SolidObject::render();
	return false;
}