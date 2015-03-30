#include "Fireworks.h"
#include <random>
#include <glut.h>

Fireworks::Fireworks() : ParticleSys()
{
	
}

void Fireworks::Init()
{
	SetAmount(50); //烟花弹片数

	static GLfloat colors[12][3] =	// 彩虹颜色
	{
		{ 1.0f, 0.5f, 0.5f }, { 1.0f, 0.75f, 0.5f }, { 1.0f, 1.0f, 0.5f }, { 0.75f, 1.0f, 0.5f },
		{ 0.5f, 1.0f, 0.5f }, { 0.5f, 1.0f, 0.75f }, { 0.5f, 1.0f, 1.0f }, { 0.5f, 0.75f, 1.0f },
		{ 0.5f, 0.5f, 1.0f }, { 0.75f, 0.5f, 1.0f }, { 1.0f, 0.5f, 1.0f }, { 1.0f, 0.5f, 0.75f }
	};
	int colorNum  = rand() % 11;

	float r = colors[colorNum][0];
	float g = colors[colorNum][1];
	float b = colors[colorNum][2];

	float x = 0.0f;
	float y = 0.0f;
	float z = float(rand() % 400) - 200.0f;

	float speedX = 0.0f;
	float speedY = float(rand() % 3) + 4.0f;
	float speedZ = 0.0f;

	float accelX = 0.0f;
	float accelY = -0.01f;
	float accelZ = 0.0f;

	for (int i = 0; i < GetAmount(); i++)
	{
		m_arrParticles[i].SetActive(true);
		m_arrParticles[i].SetSize(1);  //半径

		m_arrParticles[i].SetLife(1.0f);
		m_arrParticles[i].SetFade(0.01f); //衰减速度

		m_arrParticles[i].SetColor(r, g, b);
		m_arrParticles[i].SetPos(x, y, z);
		m_arrParticles[i].SetSpeed(speedX, speedY, speedZ); //速度比生命大，生命衰减到0后还有一定的速度
		m_arrParticles[i].SetAccel(accelX, accelY, accelZ); //假设只受重力

		//初始化拖尾

		m_arrParticles[i].GetColor(r, g, b);
		m_arrParticles[i].GetPos(x, y, z);
		m_arrParticles[i].GetSpeed(speedX, speedY, speedZ);
		m_arrParticles[i].GetAccel(accelX, accelY, accelZ);

		m_arrTail[i].m_queTail.push_front(Particles(
			m_arrParticles[i].GetSize(),
			m_arrParticles[i].GetLife(),
			r, g, b,
			x, y, z,
			speedX, speedY, speedZ,
			accelX, accelY, accelZ));
	}
}

void Fireworks::Run()
{
	float r = 0.0f, g = 0.0f, b = 0.0f;
	float x = 0.0f, y = 0.0f, z = 0.0f;
	float speedX = 0.0f, speedY = 0.0f, speedZ = 0.0f;
	float accelX = 0.0f, accelY = 0.0f, accelZ = 0.0f;

	for (int i = 0; i < GetAmount(); i++)
	{
		if (true == m_arrParticles[i].GetActive())
		{
			m_arrParticles[i].GetColor(r, g, b);
			m_arrParticles[i].GetPos(x, y, z);
			m_arrParticles[i].GetSpeed(speedX, speedY, speedZ);
			m_arrParticles[i].GetAccel(accelX, accelY, accelZ);

			//位置变化
			m_arrParticles[i].SetPos(x + speedX, y + speedY, z + speedZ);

			//速度变化
			m_arrParticles[i].SetSpeed(speedX + accelX, speedY + accelY, speedZ + accelZ);

			//生命衰减
			m_arrParticles[i].SetLife(m_arrParticles[i].GetLife() - m_arrParticles[i].GetFade());

			//拖尾
			m_arrTail[i].m_queTail.push_front(Particles(
				m_arrParticles[i].GetSize(),
				m_arrParticles[i].GetLife(),
				r, g, b,
				x, y, z,
				speedX, speedY, speedZ,
				accelX, accelY, accelZ));


			//炸开效果
			if (m_arrParticles[i].GetLife() < 0.0f)
			{
				if (speedY > 0.0f)
				{
					m_arrParticles[i].SetSize(2.0f);

					m_arrParticles[i].SetLife(1.0f);
					m_arrParticles[i].SetFade(0.005f);

					//设定炸开速度
					float x = float(rand() % 21 - 10) * 0.1;
					float y = float(rand() % 21 - 10) * 0.1;
					float z = float(rand() % 21 - 10) * 0.1;
					m_arrParticles[i].SetSpeed(x, y, z);

					//设定炸开加速度
					m_arrParticles[i].SetAccel(0.0f, -0.01, 0.0f);
				}
				else
					m_arrParticles[i].SetActive(false);
			}
		}
	}


}

void Fireworks::Render()
{
	float r = 0.0f, g = 0.0f, b = 0.0f;
	float x = 0.0f, y = 0.0f, z = 0.0f;

	for (int i = 0; i < GetAmount(); i++)
	{
		if (true == m_arrParticles[i].GetActive())
		{
			m_arrParticles[i].GetColor(r, g, b);
			m_arrParticles[i].GetPos(x, y, z);

			glPushAttrib(GL_COLOR_BUFFER_BIT);
			glColor4f(r, g, b, m_arrParticles[i].GetLife());
			glPopAttrib();

			glPushMatrix();
			glTranslatef(x, y, z);

			glutSolidSphere(m_arrParticles[i].GetSize(), 5, 5);

			glPopMatrix();

			//拖尾的绘制
			m_arrTail[i].Render();
		}
	}
}