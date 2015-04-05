#pragma once

template <typename T>

/*抽象工具。用于创建映射函数*/
class MapFunction{
public:
	MapFunction<T>()
	{
	}

	/*获取从from映射的结果*/
	T map(T from)
	{
	}
};