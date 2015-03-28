#include "SkyBox.h"
#include "SkyBoxData.h"

#include "MathConst.h"
#include <math.h>

#include <iostream>///////////////////////////////

SkyBox::SkyBox() : Object()
{
	m_meshModel.LoadMeshDataWithTexFrom3DE(SkyBoxData::vertexNum,
		SkyBoxData::face_indicies, sizeof(SkyBoxData::face_indicies),
		SkyBoxData::vertices, sizeof(SkyBoxData::vertices),
		SkyBoxData::normals, sizeof(SkyBoxData::normals),
		std::string(SkyBoxData::texureFileName),
		SkyBoxData::textures, sizeof(SkyBoxData::textures));
}


void SkyBox::Render()
{
	Paint(SkyBoxData::vertexNum);
}