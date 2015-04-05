#pragma once

#include <iostream>
#include <math.h>
using namespace std;

/*3维向量，数据用float型表示。使用标准右手系：x向外，y向右，z向上；水平转角以朝向x轴方向为0°
*【注：openGL使用GL右手系：x向右，y向上，z向外；水平转角以朝向x轴方向为0°】
*根据速度大小（用长度表示），horiAng(水平面上的投影与x轴正方向的夹角)，elevAng（速度方向与水平面的夹角，即仰角）
*计算它在x\y\z轴上的投影长度*/
class Vector3f
{
public :
	Vector3f()
	{
		x=0;
		y=0;
		z=0;
	}

	void countProjectLenOnAxis(float length,float horiAng,float elevAng)
	{
		x = length*cos(elevAng*3.14/180)*cos(horiAng*3.14/180);
		y = length*cos(elevAng*3.14/180)*sin(horiAng*3.14/180);
		z = length*sin(elevAng*3.14/180);
	}
	
	double getX()
	{
		return x;
	}
	double getY()
	{
		return y;
	}
	double getZ()
	{
		return z;
	}

private :
	double x;
	double y;
	double z;
};