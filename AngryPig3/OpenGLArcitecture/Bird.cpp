#include "Bird.h"
#include "model\BirdData.h"
#include "Vector3f.h"
#include "PhysicsConst.h"

Bird::Bird(void)
	: DynamicObject()
{
	m_removable = false;

	loadMesh(BirdData::vertexNum, 
		BirdData::face_indicies, sizeof(BirdData::face_indicies), 
		BirdData::vertices, sizeof(BirdData::vertices), 
		BirdData::normals, sizeof(BirdData::normals), 
		BirdData::r, BirdData::g, BirdData::b);
}

/*弹弓发射小鸟时调用
*参数：
*1-3：位置
*4,5：水平转角、仰角
*6：初速度*/
void Bird::setInitStatus(float x, float y, float z, float rotY, float rotZ, float velocity)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->rotY = rotY;
	this->rotZ = -30;

	/*计算属性域中的速度*/
	Vector3f vecVelocity;//注意：Vector3f使用标准数学坐标系，openGL使用GL坐标系。二者间需要互化
	vecVelocity.countProjectLenOnAxis(velocity, rotY + 90, rotZ);
	this->vx = vecVelocity.getY();
	this->vy = vecVelocity.getZ();
	this->vz = vecVelocity.getX();
}

/*返回中心点坐标*/
void Bird::getCenCoordinate(float *pResultX, float *pResultY, float *pResultZ)
{
	*pResultX = x;
	*pResultY = y;
	*pResultZ = z;
}

/*返回碰撞半径*/
float Bird::getRadius()
{
	return 1.5f;
}

/*被击杀时调用*/
void Bird::killed()
{
	m_removable = true;
}

/*渲染到屏幕上
*返回值：这个实例渲染结束后是否被删除*/
bool Bird::render()
{
	this->vy -= PhysicsConst::G;

	DynamicObject::render();

	return m_removable;
}