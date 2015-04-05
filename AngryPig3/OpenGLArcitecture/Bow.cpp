#include "Bow.h"
#include "model\BowData.h"

Bow::Bow(void)
	: SolidObject()
{
	y = 1;
	rotY = 90;
	loadMesh(BowData::vertexNum, 
		BowData::face_indicies, sizeof(BowData::face_indicies), 
		BowData::vertices, sizeof(BowData::vertices), 
		BowData::normals, sizeof(BowData::normals), 
		BowData::r, BowData::g, BowData::b);
}

/*渲染到屏幕上
*返回值：这个实例渲染结束后是否被删除*/
bool Bow::render()
{
	SolidObject::render();

	return false;
}