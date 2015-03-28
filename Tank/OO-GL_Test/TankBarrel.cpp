#include "TankBarrel.h"
#include "TankBarrelData.h"

#include "ProjectToAxis.h"

#include <math.h>

#include <iostream>////////////////////////////////

TankBarrel::TankBarrel() : Object()
{
	m_meshModel.LoadMeshDataWithTexFrom3DE(TankBarrelData::vertexNum,
		TankBarrelData::face_indicies, sizeof(TankBarrelData::face_indicies),
		TankBarrelData::vertices, sizeof(TankBarrelData::vertices),
		TankBarrelData::normals, sizeof(TankBarrelData::normals),
		std::string(TankBarrelData::texureFileName),
		TankBarrelData::textures, sizeof(TankBarrelData::textures));

	m_speed = 0;
}

void TankBarrel::Move()
{
	
}

void TankBarrel::Render()
{
	
	glPushMatrix(); //保存世界坐标系
	
	glTranslatef(m_x, m_y, m_z); //速度变化后的位置

	/*对于旋转中心在物体中心的物体，rotY rotZ不会影响物体的中心位置
	* 对于旋转中心不在物体中心的物体，rotY rotZ会影响物体的中心位置！*/

	glTranslatef(-3, 0, 0); //rotY旋转中心相对于炮筒中心向x轴负方向移动3个单位！
	glRotatef(m_rotY, 0.0f, 1.0f, 0.0f); 
	
	glTranslatef(1, 0, 0); //rotZ旋转中心相对于炮筒中心向x轴负方向移动2个单位！
	glRotatef(m_rotZ, 0.0f, 0.0f, 1.0f);
	glTranslatef(2, 0, 0);

	float x = 0, y = 0, z = 0;

	/*物体的中心相当于在（m_x-3, m_y, m_z）*/
	m_x -= 3;
	m_x += 3 * cos(m_rotY*3.14 / 180)*cos(m_rotZ*3.14 / 180);
	m_z -= 3 * sin(m_rotY*3.14 / 180)*cos(m_rotZ*3.14 / 180);

	/*乘0.75是因为左右旋转轴长为3，上下旋转轴长为2，而计算的时候统一都后移了3，
	* 所以计算出y坐标之后向下移动1/4就会与原来的炮筒指向重合，只是x坐标小一些 */
	m_y += 2 * cos(m_rotY*3.14 / 180)*sin(m_rotZ*3.14 / 180) * 0.75;
	

	PaintModel(TankBarrelData::vertexNum);

	glPopMatrix();
}



//计算炮口位置
void TankBarrel::GetMuzzlePos(float *retX, float *retY, float *retZ)
{
	float x = 0, y = 0, z = 0;
	ProjectToAxis::CountProjectLenOnAxis(&x, &y, &z, TankBarrelData::LENGTH / 2, m_rotY, m_rotZ);

	*retX = m_x + x;
	*retY = m_y + y;
	*retZ = m_z - z;


}