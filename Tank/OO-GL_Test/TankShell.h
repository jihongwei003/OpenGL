#pragma once
#include "Object.h"
#include "Movable.h"

/*绘图模式：不需要索引，需要光照，使用颜色*/
class TankShell : public Object , public Movable
{
public:
	TankShell(void);

	void SetSpeed(float speed);

	/* interface：Movable的实现 */
	void Move();

	void Render();

private:
	float m_speed;
};
