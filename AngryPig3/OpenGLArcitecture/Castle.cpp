#include "Castle.h"
#include "model\CastleData.h"

Castle::Castle(void)
	: SolidObject()
{
	x = -10;
	y = 10;

	rotY = 180;

	loadMesh(CastleData::vertexNum, 
		CastleData::face_indicies, sizeof(CastleData::face_indicies), 
		CastleData::vertices, sizeof(CastleData::vertices), 
		CastleData::normals, sizeof(CastleData::normals), 
		CastleData::r, CastleData::g, CastleData::b);
}

/*渲染到屏幕上
*返回值：这个实例渲染结束后是否被删除*/
bool Castle::render()
{
	SolidObject::render();

	return false;
}