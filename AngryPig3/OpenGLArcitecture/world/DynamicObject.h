#pragma once

#include "SolidObject.h"

class DynamicObject	: public SolidObject
{
public:
	DynamicObject();

	/*渲染到屏幕上
	*返回值：这个实例渲染结束后是否被删除*/
	virtual bool render() override;

	float vx;
	float vy;
	float vz;
};