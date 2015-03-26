#include "TankTurret.h"
#include "TankTurretData.h"

#include "MathConst.h"
#include <math.h>

TankTurret::TankTurret() : Object()
{
	m_meshModel.LoadMeshDataWithTexFrom3DE(TankTurretData::vertexNum,
		TankTurretData::face_indicies, sizeof(TankTurretData::face_indicies),
		TankTurretData::vertices, sizeof(TankTurretData::vertices),
		TankTurretData::normals, sizeof(TankTurretData::normals),
		std::string(TankTurretData::texureFileName),
		TankTurretData::textures, sizeof(TankTurretData::textures));

}

void TankTurret::SetSpeed(float speed)
{
	m_speed = speed;
}

void TankTurret::Render()
{
	Paint(TankTurretData::vertexNum);
}