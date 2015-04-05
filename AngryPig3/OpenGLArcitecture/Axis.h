#pragma once
#include "world\SolidObject.h"
//一个预置的类，可以绘制出轴长度均为10的坐标系。
//其中x轴为红色，y轴为绿色，z轴为蓝色
//绘图模式：不需要索引，不需要光照，使用颜色
class Axis :
	public SolidObject
{
public:
	Axis(void);

	/*渲染到屏幕上
	*返回值：这个实例渲染结束后是否被删除*/
	virtual bool render();

	~Axis(void);
};

