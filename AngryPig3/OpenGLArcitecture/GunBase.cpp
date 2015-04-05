#include "GunBase.h"
#include "model\GunBaseData.h"

GunBase::GunBase(void)
	: SolidObject()
{
	y = 0.8;
	loadMesh(GunBaseData::vertexNum, 
		GunBaseData::face_indicies, sizeof(GunBaseData::face_indicies), 
		GunBaseData::vertices, sizeof(GunBaseData::vertices), 
		GunBaseData::normals, sizeof(GunBaseData::normals), 
		GunBaseData::r, GunBaseData::g, GunBaseData::b);
}

/*渲染到屏幕上
*返回值：这个实例渲染结束后是否被删除*/
bool GunBase::render()
{
	SolidObject::render();

	return false;
}