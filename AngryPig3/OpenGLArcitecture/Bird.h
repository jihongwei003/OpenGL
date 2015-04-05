#pragma once
#include "world\DynamicObject.h"
/*绘图模式：不需要索引，需要光照，使用颜色*/
class Bird : public DynamicObject
{
public:
	Bird(void);

	/*弹弓发射小鸟时调用
	*参数：
	*1-3：位置
	*4,5：水平转角、仰角
	*6：初速度*/
	void setInitStatus(float x, float y, float z, float rotY, float rotZ, float velocity);

	/*返回中心点坐标*/
	void getCenCoordinate(float *pResultX, float *pResultY, float *pResultZ);

	/*返回碰撞半径*/
	float getRadius();

	/*被击杀时调用*/
	void killed();

	/*渲染到屏幕上
	*返回值：这个实例渲染结束后是否被删除*/
	bool render() override;

protected:
	bool m_removable;
};
