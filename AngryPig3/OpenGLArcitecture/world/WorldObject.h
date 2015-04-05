#pragma once

class WorldObject{
public:
	WorldObject();

	/*渲染到屏幕上
	*返回值：这个实例渲染结束后是否被删除*/
	virtual bool render() = 0;
};