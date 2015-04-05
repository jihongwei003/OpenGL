#include "Mountain.h"
#include "model\MountainData.h"

Mountain::Mountain(void)
	: SolidObject()
{
	x = 32;
	y = 0.5;
	rotY = -90;
	loadMesh(MountainData::vertexNum, 
		MountainData::face_indicies, sizeof(MountainData::face_indicies), 
		MountainData::vertices, sizeof(MountainData::vertices), 
		MountainData::normals, sizeof(MountainData::normals), 
		MountainData::color[0], MountainData::color[1], MountainData::color[2]);
}

/*渲染到屏幕上
*返回值：这个实例渲染结束后是否被删除*/
bool Mountain::render()
{
	glPushMatrix();

	glScalef(1, 3.5, 1);

	SolidObject::render();

	glPopMatrix();

	return false;
}

Mountain::~Mountain(void)
{
}
