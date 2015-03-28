#include "TankShell.h"
#include "TankShellData.h"

#include <math.h>
#include "MathConst.h"
#include "ProjectToAxis.h"

TankShell::TankShell(void)
: Object()
{
	m_meshModel.LoadMeshDataFrom3DE(TankShellData::vertexNum,
		TankShellData::face_indicies, sizeof(TankShellData::face_indicies),
		TankShellData::vertices, sizeof(TankShellData::vertices),
		TankShellData::normals, sizeof(TankShellData::normals),
		TankShellData::r, TankShellData::g, TankShellData::b);

	m_speed = 0;
}

void TankShell::SetSpeed(float speed)
{
	m_speed = speed;
}

void  TankShell::Move()
{
	float lenX = 0;
	float lenY = 0;
	float lenZ = 0;
	ProjectToAxis::CountProjectLenOnAxis(&lenX, &lenY, &lenZ, m_speed, m_rotY, m_rotZ);

	m_x += lenX;
	m_y += lenY;
	m_z -= lenZ;
}

/*渲染到屏幕上
*返回值：这个实例渲染结束后是否被删除*/
void TankShell::Render()
{
	Paint(TankShellData::vertexNum);
}