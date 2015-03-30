/*如果要实现两个粒子系统，
* 好比烟花 上升 和 炸开 的两个过程，只能创建两个不同的粒子系统，让第一个结束的位置设定第二个开始的位置！*/
#pragma once

#include "ParticleSys.h"
#include "Tail.h"

class Fireworks : public ParticleSys
{
public:
	Fireworks();

	void Init() override;
	void Run() override;
	void Render() override;

	
//private:
	Tail m_arrTail[MAX_PARTICLES];

};