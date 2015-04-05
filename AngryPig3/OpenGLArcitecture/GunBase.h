#pragma once
#include "world\SolidObject.h"
/*barrel：（枪）管
*绘图模式：不需要索引，需要光照，使用颜色*/
class GunBase : public SolidObject
{
public:
	GunBase(void);

	/*渲染到屏幕上
	*返回值：这个实例渲染结束后是否被删除*/
	bool render() override;
};