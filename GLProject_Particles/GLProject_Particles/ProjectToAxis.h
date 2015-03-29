#pragma once

#include <math.h>

/*
* 【注：openGL使用GL右手系：x向右，y向上，z向外；】
*
* 根据速度大小（用长度表示），horiAng(水平面上的投影与x轴正方向的夹角)，elevAng（速度方向与水平面的夹角，即仰角）
* 计算它在x\y\z轴上的投影长度
* 这里的【速度】是全局速度，相当于运动的列车；相对的局部速度就是人在车厢里走动
*/
class ProjectToAxis
{
public :
	//局部坐标系 转化到 世界坐标系
	static void CountProjectLenOnAxis(
		float *lenX, float *lenY, float *lenZ,
		float length,float horiAng,float elevAng)
	{
		*lenX = length*cos(elevAng*3.14 / 180)*cos(horiAng*3.14 / 180);
		*lenY = length*sin(elevAng*3.14 / 180);
		*lenZ = length*cos(elevAng*3.14 / 180)*sin(horiAng*3.14 / 180);
	}
};