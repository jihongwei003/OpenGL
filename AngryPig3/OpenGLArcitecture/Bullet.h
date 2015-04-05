#pragma once
#include "world\DynamicObject.h"
/*炮台的子弹
*绘图模式：不需要索引，不需要光照，使用颜色*/
class Bullet : public DynamicObject
{
public:
	Bullet(void);

	/*根据初始位置和角度{水平转角、仰角}设置属性域*
	*设置位置
	*设置角度
	*设置初速度*/
	void setInitStatus(float x, float y, float z, float rotY, float rotZ, float velocity);

	/*计算前端的坐标*/
	void getFrontCoord(float *pRetX, float *pRetY, float *pRetZ);

	/*计算尾端的坐标*/
	void getBackCoord(float *pRetX, float *pRetY, float *pRetZ);

	/*当击中目标时调用*/
	void hitTarget();

	/*渲染到屏幕上
	*返回值：这个实例渲染结束后是否被删除*/
	bool render() override;

protected:
	unsigned m_time;//已经存在的时间
	bool m_removable;//是否可以删除
};
