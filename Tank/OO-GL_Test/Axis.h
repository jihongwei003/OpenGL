#pragma once

#include "Object.h"

/*一个预置的类，可以绘制出轴长度均为10的坐标系。
* 其中x轴为红色，y轴为绿色，z轴为蓝色
* 绘图模式：不需要索引，不需要光照，使用颜色 */
class Axis : public Object
{
public:
	Axis();

	void InitList();
	void Render();
};
