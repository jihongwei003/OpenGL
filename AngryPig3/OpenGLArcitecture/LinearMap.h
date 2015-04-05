#pragma once

#include "MapFunction.h"

template <typename T>

/*工具类。用于表示一次函数，建立从一个范围到另一个范围的线性映射。例：从[0, 200]线性映射到[200, 500]
*可选模板：整型、浮点型*/
class LinearMap : public MapFunction<T>{
public:
	LinearMap<T>()
	{
	}

	/*按范围构造一次映射函数*/
	LinearMap<T>(T fromRange[2], T toRange[2])
	{
		this->fromRange[0] = fromRange[0];
		this->fromRange[1] = fromRange[1];
		this->toRange[0] = toRange[0];
		this->toRange[1] = toRange[1];
	}

	/*按范围构造一次映射函数*/
	LinearMap<T>(T fromRange0, T fromRange1, T toRange0, T toRange1)
	{
		this->fromRange[0] = fromRange0;
		this->fromRange[1] = fromRange1;
		this->toRange[0] = toRange0;
		this->toRange[1] = toRange1;
	}

	/*计算一次映射的结果*/
	T map(T from)
	{
		return (toRange[1] - toRange[0])/(fromRange[1] - fromRange[0])*(from - fromRange[0]) + toRange[0];
	}

protected:
	T fromRange[2];
	T toRange[2];
};