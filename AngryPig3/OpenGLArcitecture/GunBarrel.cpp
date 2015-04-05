#include "GunBarrel.h"
#include "model\GunBarrelData.h"

#include <math.h>
#include "MathConst.h"

GunBarrel::GunBarrel(void)
	: SolidObject()
{
	y = 2;
	loadMesh(GunBarrelData::vertexNum, 
		GunBarrelData::face_indicies, sizeof(GunBarrelData::face_indicies), 
		GunBarrelData::vertices, sizeof(GunBarrelData::vertices), 
		GunBarrelData::normals, sizeof(GunBarrelData::normals), 
		GunBarrelData::r, GunBarrelData::g, GunBarrelData::b);
}

/*计算左炮管前端的坐标*/
void GunBarrel::countLeftFrontCoord(float *pRetX, float *pRetY, float *pRetZ)
{
	float retX;
	float retY = GunBarrelData::LENGTH * sin(rotZ * MathConst::A_TO_R);
	float retZ;

	float pRX = - GunBarrelData::DISTANCE / 2 * sin(rotY * MathConst::A_TO_R);
	float pRZ = - GunBarrelData::DISTANCE / 2 * cos(rotY * MathConst::A_TO_R);

	float rXZ = GunBarrelData::LENGTH * cos(rotZ * MathConst::A_TO_R);//炮管长度在水平面的投影

	retX = pRX + rXZ * cos(rotY * MathConst::A_TO_R);
	retZ = pRZ - rXZ * sin(rotY * MathConst::A_TO_R);

	 *pRetX = retX;
	 *pRetY = retY + y - 0.1f;
	 *pRetZ = retZ;
}

/*计算右炮管前端的坐标*/
void GunBarrel::countRightFrontCoord(float *pRetX, float *pRetY, float *pRetZ)
{
	float retX;
	float retY = GunBarrelData::LENGTH * sin(rotZ * MathConst::A_TO_R);
	float retZ;

	float pRX = GunBarrelData::DISTANCE / 2 * sin(rotY * MathConst::A_TO_R);
	float pRZ = GunBarrelData::DISTANCE / 2 * cos(rotY * MathConst::A_TO_R);

	float rXZ = GunBarrelData::LENGTH * cos(rotZ * MathConst::A_TO_R);//炮管长度在水平面的投影

	retX = pRX + rXZ * cos(rotY * MathConst::A_TO_R);
	retZ = pRZ - rXZ * sin(rotY * MathConst::A_TO_R);

	 *pRetX = retX;
	 *pRetY = retY + y - 0.1f;
	 *pRetZ = retZ;
}

/*渲染到屏幕上
*返回值：这个实例渲染结束后是否被删除*/
bool GunBarrel::render()
{
	SolidObject::render();

	return false;
}