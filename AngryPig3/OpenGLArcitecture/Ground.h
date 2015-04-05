#pragma once
#include "world\SolidObject.h"
/*地面（水平的矩形）
*绘图方式：不需要索引，需要光照，使用颜色*/
class Ground : public SolidObject
{
public:
	/*空的无参构造，不推荐调用*/
	Ground(void);

	Ground(float x0, float z0, float x1, float z1, float height, float r, float g, float b);

	/*渲染到屏幕上
	*返回值：这个实例渲染结束后是否被删除*/
	bool render() override;

protected:
	void setPosition(float x0, float z0, float x1, float z1, float height);
	void setColor(float r, float g, float b);

	float m_x0, m_z0;
	float m_x1, m_z1;
	float m_height;
	float m_r, m_g, m_b;
};
													  ;