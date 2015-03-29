#pragma once

#include "Particles.h"

#define MAX_PARTICLES 100

/*在使用run(),render()之前，关闭【深度测试】，之后再开启！*/
class ParticleSys
{
public:
	ParticleSys();
	ParticleSys(int num);

	void SetAmount(int num);

	float GetAmount();
	//Particles GetParticle(int i);/////////////////////////////

	//~ParticleSys();

	Particles m_arrParticles[MAX_PARTICLES]; //类对象成员在哪里调用构造来着？？？

private:
	int m_num;
	

protected:
	virtual void Init() = 0;
	virtual void Run() = 0;
	virtual void Render() = 0;
};

inline void ParticleSys::SetAmount(int num)
{
	if (num < MAX_PARTICLES)
		m_num = num;
}

inline float ParticleSys::GetAmount()
{
	return m_num;
}