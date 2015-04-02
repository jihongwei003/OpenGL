#pragma once

/*interface：可控制的*/
class Controllable
{
public:
	Controllable(){};

	/*注意，最好定义此虚析构函数，够避免子类不能正常调用析构函数！
	* 如果定义为纯虚析构函数，则必须带定义体，因为子类隐含调用该析构函数 */
	virtual ~Controllable() = 0{}; 

	/* 子类必须重写下面函数，但是实现可以为空！ */

	//前进后退（如果子类需要恢复，在子类的Run方法中添加）
	virtual void Forward() = 0;
	virtual void Backward() = 0;

	//左右转角
	virtual void TurnLeft() = 0;
	virtual void TurnRight() = 0;

	//上下仰角
	virtual void Raise() = 0;
	virtual void Bow() = 0;

	//左右侧翻 //加特林枪管的转动可以用到！
	virtual void RollLeft() = 0;
	virtual void RollRight() = 0;
};