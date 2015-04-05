#include "Bullet.h"

#include "model\BulletData.h"
#include "Vector3f.h"

#include <iostream>

Bullet::Bullet(void)
	: DynamicObject()
{
	m_time = 0;
	m_removable = false;

	m_pMesh = new Mesh(2, GL_LINES);
	m_pMesh->loadVertex(BulletData::vertex, sizeof(BulletData::vertex), GL_FLOAT, 3);
	m_pMesh->loadColor(BulletData::color, sizeof(BulletData::color), GL_FLOAT, 4);
}

/*根据初始位置和角度{水平转角、仰角}设置属性域*
*设置位置
*设置角度
*设置初速度*/
void Bullet::setInitStatus(float x, float y, float z, float rotY, float rotZ, float velocity)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->rotY = rotY;
	this->rotZ = rotZ;

	/*计算属性域中的速度*/
	Vector3f vecVelocity;//注意：Vector3f使用标准数学坐标系，openGL使用GL坐标系。二者间需要互化
	vecVelocity.countProjectLenOnAxis(velocity, rotY + 90, rotZ);
	this->vx = vecVelocity.getY();
	this->vy = vecVelocity.getZ();
	this->vz = vecVelocity.getX();
}

void Bullet::getFrontCoord(float *pRetX, float *pRetY, float *pRetZ)
{
	Vector3f vecBullet;//子弹的半方向向量

	vecBullet.countProjectLenOnAxis(BulletData::LENGTH/2.0f, 90+rotY, rotZ);

	//offset[XYZ]使用GL坐标系。
	float offsetX = vecBullet.getY();
	float offsetY = vecBullet.getZ();
	float offsetZ = vecBullet.getX();

	*pRetX = x + offsetX;
	*pRetY = y + offsetY;
	*pRetZ = z + offsetZ;
}

void Bullet::getBackCoord(float *pRetX, float *pRetY, float *pRetZ)
{
	Vector3f vecBullet;//子弹的半方向向量
	vecBullet.countProjectLenOnAxis(BulletData::LENGTH/2.0f, 90+rotY, rotZ);

	//offset[XYZ]使用GL坐标系。
	float offsetX = vecBullet.getY();
	float offsetY = vecBullet.getZ();
	float offsetZ = vecBullet.getX();

	*pRetX = x - offsetX;
	*pRetY = y - offsetY;
	*pRetZ = z - offsetZ;
}

/*当击中目标时调用*/
void Bullet::hitTarget()
{
	m_removable = true;
}

/*渲染到屏幕上
*返回值：这个实例渲染结束后是否被删除*/
bool Bullet::render()
{
	m_time++;

	if(m_time > BulletData::MAX_TIME)
		m_removable = true;

	DynamicObject::render();

	return m_removable;
}