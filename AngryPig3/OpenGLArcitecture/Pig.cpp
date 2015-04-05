#include "Pig.h"
#include "model\PigData.h"

Pig::Pig(void)
	: SolidObject()
{
	y = 1;
	loadMesh(PigData::vertexNum, 
		PigData::face_indicies, sizeof(PigData::face_indicies), 
		PigData::vertices, sizeof(PigData::vertices), 
		PigData::normals, sizeof(PigData::normals), 
		PigData::r, PigData::g, PigData::b);
}

/*渲染到屏幕上
*返回值：这个实例渲染结束后是否被删除*/
bool Pig::render()
{
	SolidObject::render();

	return false;
}